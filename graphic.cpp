#include "graphic.h"

Graphic::Graphic(QCustomPlot* cPlot)
{
   graphs = new QCPGraph(cPlot->xAxis, cPlot->yAxis);
   bars = new QCPBars(cPlot->xAxis, cPlot->yAxis);
   cPlot->setInteraction(QCP::iRangeZoom, true);
   cPlot->setInteraction(QCP::iRangeDrag, true);
}


void Graphic::AddDataToGrahp(QVector<double> x, QVector<double> y)
{
    graphs->addData(x,y);
}

void Graphic::AddDataToBars(QVector<double> x, QVector<double> y)
{
    //bars->setPen(QPen(Qt::black));
    //bars->setBrush(QBrush(QColor(100, 200, 255)));
    bars->addData(x, y);
}


void Graphic::ClearGraph(QCustomPlot* cPlot)
{
    graphs->data()->clear();
    bars->data()->clear();

    for(int i = 0; i< cPlot->graphCount(); i++){
        cPlot->graph(i)->data()->clear();
    }

    cPlot->replot();

}

void Graphic::UpdateGraph(QCustomPlot *cPlot)
{
    cPlot->rescaleAxes();
    cPlot->replot();
}





