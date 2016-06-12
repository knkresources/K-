#ifndef KINPUTPIDSETTINGS_H
#define KINPUTPIDSETTINGS_H

    #include <QWidget>
    #include <QVBoxLayout>
    #include <QLabel>
    #include <QGroupBox>
    #include "KInputNumber.h"



class KInputPIDSettings : public QGroupBox
{
    Q_OBJECT

    KInputNumber * inputKp;
    KInputNumber * inputKd;
    KInputNumber * inputKi;
    KInputNumber * integralLimitMin;
    KInputNumber * integralLimitMax;
    KInputNumber * outputLimitMax;
    KInputNumber * outputLimitMin;
    KInputNumber * derivT;

    QVBoxLayout * verticalLayout;

private slots:

    void value_changed(double val);

public:
    explicit KInputPIDSettings(QWidget * parent=0);
    void setName(QString name);
public slots:

    void settingsUpdated(void);

signals:

    void settingsChanged(double,double,double,double,double,double,double,double);

};

#endif // KINPUTPIDSETTINGS_H
