#include "KSerial.h"

#include <QDebug>


int KSerial::findSubString(QByteArray &str, QByteArray sub_str, int from_position)
{
    int i,j;
    int str_bytes = str.count();
    int sub_str_bytes = sub_str.count();

    i=from_position;
    while(i<str_bytes)
    {
        if(str.at(i) != sub_str.at(0))
        {
            i++;
        }else
        {
            for(j=1;j<sub_str_bytes;j++)
            {
                i++;
                if(i<str_bytes)
                {
                    if(str.at(i) != sub_str.at(j)) break;

                }else break;
            }

            if(j==sub_str_bytes) return (i+1-sub_str_bytes);

        }
    }

    return -1;
}

QByteArray KSerial::copyBytes(QByteArray &str, int start_position, int end_position)
{
    int i;
    QByteArray res;
    for(i=start_position;i<end_position;i++)
    {
        res.append(str.at(i));
    }
    return res;
}

KSerial::KSerial(QObject *parent) : QSerialPort(parent)
{
    this->use_starter = false;
    this->use_terminator = false;

    this->starter = "$";
    this->terminator = "\r\n";

    this->connect(this,SIGNAL(readyRead()),this,SLOT(readData()));

}

bool KSerial::openPort(QString name, int baud_rate)
{
    if(this->isOpen()) this->close();

    this->setPortName(name);
    this->setBaudRate(baud_rate);
    this->setDataBits(Data8);
    this->setParity(NoParity);
    this->setStopBits(OneStop);
    this->setFlowControl(NoFlowControl);

    return this->open(QIODevice::ReadWrite);
}

void KSerial::closePort()
{
    this->close();
}

void KSerial::setStartCondition(QByteArray dataStart)
{
    this->starter = dataStart;
}

void KSerial::useStartCondition(bool state)
{
    this->use_starter = state;
}

void KSerial::setEndCondition(QByteArray dataEnd)
{
    this->terminator = dataEnd;
}

void KSerial::useEndCondition(bool state)
{
    this->use_terminator = state;
}

void KSerial::readData()
{
    QByteArray bytes = this->readAll();
    QByteArray data = this->rxBuffer + bytes;


    int n = data.count();
    int n_t = this->terminator.count();
    int n_s = this->starter.count();


    int pos;
    int pos2;
    int i=0;
    int j;


    if(!this->use_starter && !this->use_terminator)
    {
        emit this->newDataRecieved(bytes);
        return;
    }
    if(this->use_terminator && !this->use_starter)
    {
        while(1)
        {
            pos = this->findSubString(data,this->terminator,i);

            if(pos == -1) break;

            emit this->newDataRecieved(this->copyBytes(data,i,pos));

            i=pos+n_t;
            if(i >= n) break;
        }
        if((n-i) < (2048+1)) this->rxBuffer = this->copyBytes(data,i,n);
        else this->rxBuffer.clear();
    }
    if(!this->use_terminator && this->use_starter)
    {
        pos = this->findSubString(data,this->starter,i);
        if(pos != -1)
        {
            i=pos+n_s;
            while(1)
            {
                pos = this->findSubString(data,this->starter,i);
                if(pos == -1) break;

                emit this->newDataRecieved(this->copyBytes(data,i,pos));

                i=pos+n_t;
                if(i >= n) break;
            }
        }

        if((n-i) < (2048+1)) this->rxBuffer = this->copyBytes(data,i,n);
        else this->rxBuffer.clear();
    }

    if(this->use_terminator && this->use_starter)
    {      
        while(1)
        {
            pos = this->findSubString(data,this->terminator,i);

            if(pos == -1) break;

            bytes = this->copyBytes(data,i,pos);

            pos2 = this->findSubString(bytes,this->starter);

            if(pos2 != -1)
            {
                pos2 += n_s;
                emit this->newDataRecieved(this->copyBytes(bytes,pos2,pos-i));
            }



            i=pos+n_t;
            if(i >= n) break;
        }
        if((n-i) < (2048+1)) this->rxBuffer = this->copyBytes(data,i,n);
        else this->rxBuffer.clear();
    }

}

void KSerial::requestOpen(QString name, QString baud_rate)
{
    int baud = baud_rate.toInt();
    bool res;

    res = this->openPort(name,baud);

    if(res)
    {
        emit this->portOpen();
    }else
    {
        emit this->portClosed();
    }
}

void KSerial::requestClose()
{
    this->closePort();
    emit this->portClosed();
}

void KSerial::writeString(QString data)
{
    this->write(data.toStdString().c_str());
}

void KSerial::attachSettingsPanel(KSerialSettings *settingsPanel)
{
    connect(settingsPanel,SIGNAL(connectionRequest(QString,QString)),this,SLOT(requestOpen(QString,QString)));
    connect(settingsPanel,SIGNAL(disconnectRequest()),this,SLOT(requestClose()));

    connect(this,SIGNAL(portOpen()),settingsPanel,SLOT(displayConnected()));
    connect(this,SIGNAL(portClosed()),settingsPanel,SLOT(displayDisconnected()));
}

QList<QSerialPortInfo> KSerial::availablePorts()
{
    return QSerialPortInfo::availablePorts();
}
