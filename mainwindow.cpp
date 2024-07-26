#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_status->setStyleSheet("color:red");
    ui->pb_get->setEnabled(false);
    ui->pb_getstat->setEnabled(false);
    db = new Database(this);
    msg = new QMessageBox(this);
    dialog = new Dialog(this);
    ui->rb_departure->setChecked(true);
    connect(db, &Database::sig_send_con_status, this, &MainWindow::ConnectionStatus);
    connect(msg, &QMessageBox::buttonClicked, this, &MainWindow::AutoReconnect);
    connect(db, &Database::sig_send_names_airports, this, &MainWindow::ResAirportNames);
    connect(db, &Database::sig_send_query, this, &MainWindow::ResQuery);
    connect(db, &Database::sig_send_stat_year, dialog, &Dialog::ResStatYear);
    connect(db, &Database::sig_send_full_stat, dialog, &Dialog::ResStatMonth);
    auto conn = [&]{db->Connect();};
    std::ignore = QtConcurrent::run(conn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectionStatus(bool status)
{
    if(status){
        ui->lb_status->setText("Подключено");
        ui->lb_status->setStyleSheet("color:green");
        ui->pb_get->setEnabled(true);
        ui->pb_getstat->setEnabled(true);
        db->GetAirportNames();
    }else {
        db->Disconnect();
        msg->setIcon(QMessageBox::Critical);
        msg->setText(db->GetError().text());
        msg->exec();
    }
}

void MainWindow::AutoReconnect()
{
    auto conn = [&]{QThread::sleep(5);
                    db->Connect();};
    std::ignore = QtConcurrent::run(conn);
}

void MainWindow::ResAirportNames(QVector<QString> names, QVector<QString> codes)
{
    for(int i = 0; i < names.size(); i++){
        ui->cb_airports->addItem(names[i] + " " + codes[i]);
    }
}

void MainWindow::ResQuery(QSqlQueryModel *model)
{
    ui->tv_result->setModel(model);
    ui->tv_result->resizeRowsToContents();
    ui->tv_result->resizeColumnsToContents();
    ui->tv_result->show();
}


void MainWindow::on_pb_get_clicked()
{
    if(ui->rb_arrival->isChecked()){
        int index = ui->cb_airports->currentIndex();
        QString date = ui->de_date->text();
        db->GetArrive(index, date);
    } else {
        int index = ui->cb_airports->currentIndex();
        QString date = ui->de_date->text();
        db->GetDeparture(index, date);
    }
}


void MainWindow::on_pb_getstat_clicked()
{
    QString name = ui->cb_airports->currentText();
    dialog->GetLBPtr()->setText(name);
    int index = ui->cb_airports->currentIndex();
    db->GetStatYear(index);
    db->GetStatMonth(index);
    ui->tv_result->setModel(nullptr);
    dialog->exec();
}

