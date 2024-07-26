#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QObject>

#include "qcustomplot.h"

#define FIRST_GRAPH 0

class Graphic : public QObject
{
    Q_OBJECT   

public:
    Graphic(QCustomPlot* cPlot);
    void AddDataToGrahp(QVector<double> x, QVector<double> y);
    void AddDataToBars(QVector<double> x, QVector<double> y);
    void ClearGraph(QCustomPlot* cPlot);
    void UpdateGraph(QCustomPlot* cPlot);


private:

    QCPGraph* graphs;
    QCPBars* bars;

};

#endif // GRAPHIC_H
