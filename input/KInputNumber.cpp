#include "KInputNumber.h"


void KInputNumber::spinChanged(double value)
{
    Q_UNUSED(value);

    this->applyButton->setEnabled(true);
}

void KInputNumber::stepChanged(double value)
{
    this->spinBoxValue->setSingleStep(value);
}

void KInputNumber::applyClicked(bool checked)
{
    Q_UNUSED(checked);

    emit this->valueChanged(this->spinBoxValue->value());
}

KInputNumber::KInputNumber(QWidget *parent) : QWidget(parent)
{


    this->labelName = new QLabel("Value");
    this->labelStep = new QLabel("step");
    this->applyButton = new QPushButton("Update");

    this->spinBoxValue = new QDoubleSpinBox;
    this->spinBoxStep = new QDoubleSpinBox;


    this->applyButton->setMaximumWidth(70);
    this->spinBoxValue->setMaximumWidth(100);
    this->spinBoxStep->setMaximumWidth(100);
    this->labelName->setMaximumWidth(150);
    this->labelStep->setMaximumWidth(30);
    this->setMaximumWidth(480);



    this->labelStep->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    this->labelName->setAlignment(Qt::AlignRight | Qt::AlignCenter);

    this->horizonLayout = new QHBoxLayout();



    this->horizonLayout->addWidget(labelName);
    this->horizonLayout->addWidget(spinBoxValue);
    this->horizonLayout->addWidget(labelStep);
    this->horizonLayout->addWidget(spinBoxStep);
    this->horizonLayout->addWidget(applyButton);

    this->setLayout(this->horizonLayout);


    this->spinBoxValue->setMaximum(1000000000);
    this->spinBoxValue->setMinimum(-1000000000);

    connect(this->spinBoxValue,SIGNAL(valueChanged(double)),this,SLOT(spinChanged(double)));
    connect(this->spinBoxStep,SIGNAL(valueChanged(double)),this,SLOT(stepChanged(double)));
    connect(this->applyButton,SIGNAL(clicked(bool)),this,SLOT(applyClicked(bool)));
}

void KInputNumber::setName(QString name)
{
    this->labelName->setText(name);
}

void KInputNumber::setDecimals(unsigned int decimals)
{
    this->spinBoxStep->setDecimals(decimals);
    this->spinBoxValue->setDecimals(decimals);
}

void KInputNumber::setStep(double step)
{
    if(step >= 0)
    {
        this->spinBoxStep->setValue(step);
    }
}

double KInputNumber::currentValue()
{
    return this->spinBoxValue->value();
}

void KInputNumber::valueUpdated()
{
    this->applyButton->setDisabled(true);
}
