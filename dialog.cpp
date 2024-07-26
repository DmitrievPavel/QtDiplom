#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    graphic1 = new Graphic(ui->qcp_year);
    graphic2 = new Graphic(ui->qcp_month);

}

Dialog::~Dialog()
{
    delete ui;
    delete graphic1;
    delete graphic2;
}

QLabel *Dialog::GetLBPtr()
{
    return ui->lb_airport_name;
}

void Dialog::ResStatYear(QVector<double> counts, QVector<double> months)
{
    graphic1->AddDataToBars(months, counts);
    ui->qcp_year->xAxis->setLabel("Месяц");
    ui->qcp_year->yAxis->setLabel("Количество вылетов/прилетов");
    ui->qcp_year->xAxis->setRange(0, 13);
    //ui->qcp_year->yAxis->setRange(0, 7000);
    graphic1->UpdateGraph(ui->qcp_year);
}

void Dialog::ResStatMonth(QVector<Database::statMonth> statistic)
{
    stat = statistic;
    ui->qcp_month->xAxis->setRange(0, 32);
    graphic2->AddDataToGrahp(stat[4].days,stat[4].counts);
    ui->qcp_month->xAxis->setLabel("День");
    ui->qcp_month->yAxis->setLabel("Количество вылетов/прилетов");
    graphic2->UpdateGraph(ui->qcp_month);
    ui->cb_months->addItem("Январь");
    ui->cb_months->addItem("Февраль");
    ui->cb_months->addItem("Март");
    ui->cb_months->addItem("Апрель");
    ui->cb_months->addItem("Май");
    ui->cb_months->addItem("Июнь");
    ui->cb_months->addItem("Июль");
    ui->cb_months->addItem("Август");
    ui->cb_months->addItem("Сентябрь");
    ui->cb_months->addItem("Октябрь");
    ui->cb_months->addItem("Ноябрь");
    ui->cb_months->addItem("Декабрь");
    ui->cb_months->setCurrentIndex(0);

}

void Dialog::on_pb_close_clicked()
{
    graphic1->ClearGraph(ui->qcp_year);
    graphic1->UpdateGraph(ui->qcp_year);
    graphic2->ClearGraph(ui->qcp_month);
    graphic2->UpdateGraph(ui->qcp_month);

}


void Dialog::on_cb_months_currentIndexChanged(int index)
{
    graphic2->ClearGraph(ui->qcp_month);
    graphic2->UpdateGraph(ui->qcp_month);
    switch (index) {
    case 0:
        graphic2->AddDataToGrahp(stat[4].days,stat[4].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 1:
        graphic2->AddDataToGrahp(stat[5].days,stat[5].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 2:
        graphic2->AddDataToGrahp(stat[6].days,stat[6].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 3:
        graphic2->AddDataToGrahp(stat[7].days,stat[7].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 4:
        graphic2->AddDataToGrahp(stat[8].days,stat[8].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 5:
        graphic2->AddDataToGrahp(stat[9].days,stat[9].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 6:
        graphic2->AddDataToGrahp(stat[10].days,stat[10].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 7:
        graphic2->AddDataToGrahp(stat[11].days,stat[11].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 8:
        graphic2->AddDataToGrahp(stat[0].days,stat[0].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 9:
        graphic2->AddDataToGrahp(stat[1].days,stat[1].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 10:
        graphic2->AddDataToGrahp(stat[2].days,stat[2].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 11:
        graphic2->AddDataToGrahp(stat[3].days,stat[3].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    default:
        break;
    }
}

