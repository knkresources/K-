#include "KRecorder.h"

KRecorder::KRecorder()
{

}

void KRecorder::newLog(QString file_path)
{

    mFile = new QFile(file_path);

    if(!mFile->open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() <<"nie mozna otworzyc do odczytu";
return;
    }
}

void KRecorder::writeRecord(QString record)
{


            QTextStream out (mFile);
            out << record<<"\r\n";


            mFile->flush();



}

void KRecorder::closeLog()
{
     mFile->close();
     delete mFile;
}

