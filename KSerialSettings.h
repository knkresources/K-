#ifndef KSERIALSETTINGS_H
#define KSERIALSETTINGS_H

    #include <QWidget>
    #include <QPushButton>
    #include <QComboBox>
    #include <QHBoxLayout>

class KSerialSettings : public QWidget
{
    Q_OBJECT

    private:

        QPushButton * connectButton;
        QPushButton * rescanButton;

        QComboBox * serialList;
        QComboBox * baudList;

        QHBoxLayout * horizonLayout;

        bool connected;

    public:
        explicit KSerialSettings(QWidget *parent = 0);
        void rescan(void);

    private slots:

        void rescanHandler(bool checked);
        void connectionHandler(bool checked);

    public slots:

        void displayDisconnected(void);
        void displayConnected(void);

    signals:

        void connectionRequest(QString serialName,QString baudrate);
        void disconnectRequest(void);

};

#endif // KSERIALSETTINGS_H
