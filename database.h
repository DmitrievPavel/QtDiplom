#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDate>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    void Connect();
    void Disconnect();
    QSqlError GetError();
    void GetAirportNames();
    void GetArrive(int index, QString date);
    void GetDeparture(int index, QString date);
    void GetStatYear(int index);
    void GetStatMonth(int index);
    struct statMonth {
        QVector<double> counts;
        QVector<double> days;
    };

signals:
    void sig_send_con_status(bool);
    void sig_send_names_airports(QVector<QString> names, QVector<QString> codes);
    void sig_send_query(QSqlQueryModel* model);
    void sig_send_stat_year(QVector<double> counts, QVector<double> months);
    void sig_send_full_stat(QVector<statMonth> statistic);

private:
    QSqlDatabase* dataBase;
    QSqlQueryModel* queryModel;
    QString AirportNameQuery = {"SELECT airport_name->>'ru' as \"airportName\", airport_code FROM bookings.airports_data"};
    QVector<QString> airportNames;
    QVector<QString> airportCodes;
};

#endif // DATABASE_H
