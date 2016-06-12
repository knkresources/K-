#include "KSerialSettings.h"
#include <QPushButton>
#include <QList>
#include <QSerialPortInfo>
#include <QObject>

KSerialSettings::KSerialSettings(QWidget *parent) : QWidget(parent)
{
    this->connectButton = new QPushButton("Connect");
    this->rescanButton = new QPushButton("Rescan");
    this->serialList = new QComboBox;
    this->baudList = new QComboBox;


    this->connectButton->setMaximumWidth(100);
    this->rescanButton->setMaximumWidth(80);
    this->baudList->setMaximumWidth(80);
    this->serialList->setMaximumWidth(120);

    this->horizonLayout = new QHBoxLayout;

    this->horizonLayout->addWidget(this->serialList);
    this->horizonLayout->addWidget(this->baudList);
    this->horizonLayout->addWidget(this->rescanButton);
    this->horizonLayout->addWidget(this->connectButton);

    this->baudList->addItem("9600");
    this->baudList->addItem("57600");
    this->baudList->addItem("115200");


    this->setLayout(this->horizonLayout);

    this->setMaximumWidth(390);
    this->setMaximumHeight(50);
    this->setMinimumHeight(20);

    this->rescan();
    this->connected = false;

    connect(this->rescanButton,SIGNAL(clicked(bool)),this,SLOT(rescanHandler(bool)));
    connect(this->connectButton,SIGNAL(clicked(bool)),this,SLOT(connectionHandler(bool)));
}

void KSerialSettings::rescan()
{
    QList<QSerialPortInfo> inf = QSerialPortInfo::availablePorts();

    int i,n;
    n=inf.size();

    this->serialList->clear();

    for(i=0;i<n;i++)
    {
        this->serialList->addItem(inf.at(i).portName());
    }
}

void KSerialSettings::rescanHandler(bool checked)
{
    Q_UNUSED(checked);
    this->rescan();
}

void KSerialSettings::connectionHandler(bool checked)
{
    Q_UNUSED(checked);

    if(!connected)
    {
        if(this->serialList->count() > 0)
        {
            emit this->connectionRequest(this->serialList->currentText(),this->baudList->currentText());
        }

    }else
    {
        emit this->disconnectRequest();
    }

}

void KSerialSettings::displayDisconnected()
{
    this->connected = false;
    this->connectButton->setText("Connect");
    this->serialList->setEnabled(true);
    this->baudList->setEnabled(true);
    this->rescanButton->setEnabled(true);
}

void KSerialSettings::displayConnected()
{
    this->connected = true;
    this->connectButton->setText("Disconnect");
    this->serialList->setDisabled(true);
    this->baudList->setDisabled(true);
    this->rescanButton->setDisabled(true);

}

