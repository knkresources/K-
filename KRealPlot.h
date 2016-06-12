#ifndef KREALPLOT_H
#define KREALPLOT_H

#include <QObject>
#include <qcustomplot.h>

class KRealPlot : public QObject
{
    Q_OBJECT

    QCustomPlot * QPlot;
    bool isAttached;
    unsigned int range;

public:




    explicit KRealPlot(QObject *parent = 0);

    void attach(QCustomPlot * plot);
    void setPen(QPen pen);
    void setRange(unsigned int seconds);

    void clear(void);

signals:

public slots:

    void feed(double y);
};

#endif // KREALPLOT_H
