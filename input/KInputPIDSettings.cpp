#include "KInputPIDSettings.h"


void KInputPIDSettings::value_changed(double val)
{
    Q_UNUSED(val);

    double Kp,Kd,Ki,integralMax,integralMin,outMax,outMin,derivativeT;

    Kp = inputKp->currentValue();
    Kd = inputKd->currentValue();
    Ki = inputKi->currentValue();

    integralMax = integralLimitMax->currentValue();
    integralMin = integralLimitMin->currentValue();

    outMax = outputLimitMax->currentValue();
    outMin = outputLimitMin->currentValue();
    derivativeT = derivT->currentValue();

    emit this->settingsChanged(Kp,Kd,Ki,
                               integralMax,integralMin,
                               outMax,outMin,derivativeT);

}

KInputPIDSettings::KInputPIDSettings(QWidget *parent) : QGroupBox(parent)
{

    this->inputKp = new KInputNumber(this);
    this->inputKd = new KInputNumber(this);
    this->inputKi = new KInputNumber(this);

    this->integralLimitMax = new KInputNumber(this);
    this->integralLimitMin = new KInputNumber(this);

    this->outputLimitMax = new KInputNumber(this);
    this->outputLimitMin = new KInputNumber(this);

    this->derivT = new KInputNumber(this);


    inputKp->setName("Kp");
    inputKd->setName("Kd");
    inputKi->setName("Ki");

    integralLimitMax->setName("Integral max");
    integralLimitMin->setName("Integral min");

    outputLimitMax->setName("Output max");
    outputLimitMin->setName("Output min");

    derivT->setName("Derivative LPF T");


    this->verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(inputKp);
    verticalLayout->addWidget(inputKd);
    verticalLayout->addWidget(inputKi);
    verticalLayout->addWidget(integralLimitMax);
    verticalLayout->addWidget(integralLimitMin);
    verticalLayout->addWidget(outputLimitMax);
    verticalLayout->addWidget(outputLimitMin);
    verticalLayout->addWidget(derivT);

    this->setLayout(verticalLayout);
    this->setTitle("PID settings");

    this->setStyleSheet("QGroupBox {border: 1px solid gray; border-radius: 9px;margin-top: 0.5em;} QGroupBox::title {subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px;}");
    this->setMaximumWidth(500);


    connect(inputKp,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(inputKd,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(inputKi,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(integralLimitMax,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(integralLimitMin,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(outputLimitMax,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(outputLimitMin,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
    connect(derivT,SIGNAL(valueChanged(double)),this,SLOT(value_changed(double)));
}

void KInputPIDSettings::setName(QString name)
{
    this->setTitle(name);
}

void KInputPIDSettings::settingsUpdated()
{
    inputKp->valueUpdated();
    inputKd->valueUpdated();
    inputKi->valueUpdated();

    integralLimitMax->valueUpdated();
    integralLimitMin->valueUpdated();

    outputLimitMax->valueUpdated();
    outputLimitMin->valueUpdated();

    derivT->valueUpdated();
}

