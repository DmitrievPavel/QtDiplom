#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "graphic.h"
#include "database.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QLabel* GetLBPtr();
    enum MonthsNum{
        Sep,
        Oct,
        Nov,
        Dec,
        Jan,
        Feb,
        Mar,
        Apr,
        May,
        Jun,
        Jul,
        Aug
    };

    void AddMonths();
public slots:
    void ResStatYear(QVector<double> counts, QVector<double> months);
    void ResStatMonth(QVector<Database::statMonth> statistic);

private slots:
    void on_pb_close_clicked();

    void on_cb_months_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    Graphic* graphic1;
    Graphic* graphic2;
    QVector<Database::statMonth> stat;
};

#endif // DIALOG_H
