#ifndef KSERIAL_H
#define KSERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QByteArray>
#include <QList>

#include "KSerialSettings.h"

class KSerial : public QSerialPort
{
    Q_OBJECT

    private:

        QByteArray rxBuffer;
        QByteArray starter;
        QByteArray terminator;

        bool use_starter;
        bool use_terminator;



    public:
        explicit KSerial(QObject * parent=0);

        int findSubString(QByteArray & str,QByteArray sub_str, int from_position=0);
        QByteArray copyBytes(QByteArray & str,int start_position,int end_position);


        bool openPort(QString name, int baud_rate);
        void closePort(void);
        void setStartCondition(QByteArray dataStart);
        void useStartCondition(bool state);
        void setEndCondition(QByteArray dataEnd);
        void useEndCondition(bool state);
        void writeString(QString data);

        void attachSettingsPanel(KSerialSettings * settingsPanel);


        QList<QSerialPortInfo> availablePorts(void);

    public slots:

        void readData(void);
        void requestOpen(QString name, QString baud_rate);
        void requestClose(void);

    signals:

        void newDataRecieved(QByteArray);
        void portOpen(void);
        void portClosed(void);

};


#endif // KSERIAL_H
