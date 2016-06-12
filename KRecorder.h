#ifndef KRECORDER_H
#define KRECORDER_H
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QObject>

class KRecorder
{
private:

    QFile * mFile;

public:
    KRecorder();
    void newLog(QString file_path);
    void writeRecord(QString record);
    void closeLog(void);
};

#endif // KRECORDER_H
