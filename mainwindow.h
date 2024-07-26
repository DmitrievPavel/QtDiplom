#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include "dialog.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ConnectionStatus(bool status);
    void AutoReconnect();
    void ResAirportNames(QVector<QString> names, QVector<QString> codes);
    void ResQuery(QSqlQueryModel* model);

private slots:
    void on_pb_get_clicked();

    void on_pb_getstat_clicked();

private:
    Ui::MainWindow *ui;
    Dialog* dialog;
    Database* db;
    QMessageBox* msg;
};
#endif // MAINWINDOW_H
