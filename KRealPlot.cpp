#include "KRealPlot.h"

KRealPlot::KRealPlot(QObject *parent) : QObject(parent)
{
    this->isAttached = false;
    this->range = 8;
}

void KRealPlot::attach(QCustomPlot *plot)
{
     this->QPlot = plot;
     this->isAttached =true;
     QPen pen;

     pen.setColor(Qt::blue);
     pen.setWidth(1);

     this->QPlot->clearGraphs();

     this->QPlot->addGraph(); // blue line
     this->QPlot->graph(0)->setPen(pen);
     this->QPlot->graph(0)->setAntialiasedFill(false);

     this->QPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
     this->QPlot->xAxis->setDateTimeFormat("hh:mm:ss");
     this->QPlot->xAxis->setAutoTickStep(false);
     this->setRange(this->range);

     // make left and bottom axes transfer their ranges to right and top axes:
     connect(this->QPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->QPlot->xAxis2, SLOT(setRange(QCPRange)));
     connect(this->QPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->QPlot->yAxis2, SLOT(setRange(QCPRange)));

}

void KRealPlot::setPen(QPen pen)
{
    if(this->isAttached) this->QPlot->graph(0)->setPen(pen);
}

void KRealPlot::setRange(unsigned int seconds)
{
    unsigned int tick_step = this->range/5;
    if(!tick_step) tick_step = 1;
    this->range=seconds;
    this->QPlot->xAxis->setTickStep(tick_step);
    this->QPlot->axisRect()->setupFullAxesBox();
}

void KRealPlot::clear()
{
    this->QPlot->graph(0)->clearData();
}

void KRealPlot::feed(double y)
{
    double key;

    if(this->isAttached)
    {
        key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;


        this->QPlot->graph(0)->addData(key, y);
        this->QPlot->graph(0)->removeDataBefore(key-this->range);
        this->QPlot->graph(0)->rescaleValueAxis();
        // make key axis range scroll with the data (at a constant range size of 8):
        this->QPlot->xAxis->setRange(key+(this->range/8), this->range, Qt::AlignRight);
        this->QPlot->replot();
    }
}

