#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    graphic1 = new Graphic(ui->qcp_year);
    graphic2 = new Graphic(ui->qcp_month);
    ui->qcp_year->xAxis->setLabel("Месяц");
    ui->qcp_year->yAxis->setLabel("Количество вылетов/прилетов");
    ui->qcp_year->xAxis->setRange(1, 12);
    ui->qcp_month->xAxis->setRange(1, 31);
    ui->qcp_month->xAxis->setLabel("День");
    ui->qcp_month->yAxis->setLabel("Количество вылетов/прилетов");

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

void Dialog::AddMonths()
{
    if(ui->cb_months->count() == 0){
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
    }
    else {
        ui->cb_months->setCurrentIndex(0);
    }
}

void Dialog::ResStatYear(QVector<double> counts, QVector<double> months)
{
    graphic1->ClearGraph(ui->qcp_year);
    graphic1->AddDataToBars(months, counts);
    graphic1->UpdateGraph(ui->qcp_year);
}

void Dialog::ResStatMonth(QVector<Database::statMonth> statistic)
{
    stat = statistic;
    graphic2->AddDataToGrahp(stat[MonthsNum::Jan].days,stat[MonthsNum::Jan].counts);
    graphic2->UpdateGraph(ui->qcp_month);
    AddMonths();

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
        graphic2->AddDataToGrahp(stat[MonthsNum::Jan].days,stat[MonthsNum::Jan].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 1:
        graphic2->AddDataToGrahp(stat[MonthsNum::Feb].days,stat[MonthsNum::Feb].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 2:
        graphic2->AddDataToGrahp(stat[MonthsNum::Mar].days,stat[MonthsNum::Mar].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 3:
        graphic2->AddDataToGrahp(stat[MonthsNum::Apr].days,stat[MonthsNum::Apr].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 4:
        graphic2->AddDataToGrahp(stat[MonthsNum::May].days,stat[MonthsNum::May].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 5:
        graphic2->AddDataToGrahp(stat[MonthsNum::Jun].days,stat[MonthsNum::Jun].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 6:
        graphic2->AddDataToGrahp(stat[MonthsNum::Jul].days,stat[MonthsNum::Jul].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 7:
        graphic2->AddDataToGrahp(stat[MonthsNum::Aug].days,stat[MonthsNum::Aug].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 8:
        graphic2->AddDataToGrahp(stat[MonthsNum::Sep].days,stat[MonthsNum::Sep].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 9:
        graphic2->AddDataToGrahp(stat[MonthsNum::Oct].days,stat[MonthsNum::Oct].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 10:
        graphic2->AddDataToGrahp(stat[MonthsNum::Nov].days,stat[MonthsNum::Nov].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    case 11:
        graphic2->AddDataToGrahp(stat[MonthsNum::Dec].days,stat[MonthsNum::Dec].counts);
        graphic2->UpdateGraph(ui->qcp_month);
        break;
    default:
        break;
    }
}

