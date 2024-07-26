#include "database.h"

Database::Database(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    queryModel = new QSqlQueryModel();
}

Database::~Database()
{
    delete dataBase;
    delete queryModel;
}

void Database::Connect()
{
    *dataBase = QSqlDatabase::addDatabase("QPSQL", "airportDB");
    dataBase->setHostName("981757-ca08998.tmweb.ru");
    dataBase->setDatabaseName("demo");
    dataBase->setUserName("netology_usr_cpp");
    dataBase->setPassword("CppNeto3");
    dataBase->setPort(5432);

    bool status = dataBase->open();
    emit sig_send_con_status(status);
}

void Database::Disconnect()
{
    dataBase->close();
}

QSqlError Database::GetError()
{
    return dataBase->lastError();
}


void Database::GetAirportNames()
{
    queryModel->setQuery(AirportNameQuery,*dataBase);
    for(int i = 0; i < 104; i++){
        QString name = queryModel->data(queryModel->index(i, 0)).toString();
        QString code = queryModel->data(queryModel->index(i, 1)).toString();
        airportNames.push_back(name);
        airportCodes.push_back(code);
    }
    emit sig_send_names_airports(airportNames,airportCodes);
}

void Database::GetArrive(int index, QString date)
{
    QString code = airportCodes[index];
    queryModel->setQuery("SELECT flight_no, scheduled_arrival::time, ad.airport_name->>'ru' as \"Name\" from bookings.flights f "
                         "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                         "where f.arrival_airport  = '" + code + "'and scheduled_arrival::date = '" + date + "'", *dataBase);

    queryModel->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
    queryModel->setHeaderData(2, Qt::Horizontal, tr("Аэропорт отправления"));
    emit sig_send_query(queryModel);
}

void Database::GetDeparture(int index, QString date)
{
    QString code = airportCodes[index];
    queryModel->setQuery("SELECT flight_no, scheduled_departure::time, ad.airport_name->>'ru' as \"Name\" from bookings.flights f "
                         "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                         "WHERE f.departure_airport  = '" + code + "' and scheduled_departure::date = '" + date + "'", *dataBase);

    queryModel->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
    queryModel->setHeaderData(2, Qt::Horizontal, tr("Аэропорт назначения"));
    emit sig_send_query(queryModel);
}

void Database::GetStatYear(int index)
{
    QString code = airportCodes[index];
    QVector<double> counts;
    QVector<double> months;
    queryModel->setQuery("SELECT count(flight_no), date_trunc('month', scheduled_departure) as \"Month\" from bookings.flights f "
                         "WHERE (scheduled_departure::date > date('2016-08-31') and scheduled_departure::date <= date('2017-08-31')) and ( departure_airport = '" + code + "' or arrival_airport = '" + code + "' ) "
                         "group by \"Month\"", *dataBase);


    for(int i = 0; i < 12; i++) {
        int count = queryModel->data(queryModel->index(i, 0)).toInt();
        QDate date = queryModel->data(queryModel->index(i, 1)).toDate();
        int month = date.month();
        counts.push_back(count);
        months.push_back(month);
    }
    emit sig_send_stat_year(counts, months);
}

void Database::GetStatMonth(int index)
{
    QString code = airportCodes[index];
    queryModel->setQuery("SELECT count(flight_no), date_trunc('day', scheduled_departure) as \"Day\" from bookings.flights f "
                         "WHERE(scheduled_departure::date > date('2016-08-31') and scheduled_departure::date <= date('2017-08-31')) and ( departure_airport = '" + code + "' or arrival_airport = '" + code + "') "
                         "GROUP BY \"Day\"", *dataBase);

    statMonth statisticMonth;
    QVector<statMonth> statFull;
    int startMonth = 9;
    for(int i = 0; i < 365; i++){
        int count = queryModel->data(queryModel->index(i, 0)).toInt();
        QDate date = queryModel->data(queryModel->index(i, 1)).toDate();
        int month = date.month();
        int day = date.day();
        if(month != startMonth){
            statFull.push_back(statisticMonth);
            statisticMonth.counts.clear();
            statisticMonth.days.clear();
            startMonth++;
            if(startMonth == 13){
                startMonth = 1;
            }
        }
        statisticMonth.counts.push_back(count);
        statisticMonth.days.push_back(day);
    }
    statFull.push_back(statisticMonth);
    emit sig_send_full_stat(statFull);
}
