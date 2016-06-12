#ifndef KCONSOLE_H
#define KCONSOLE_H

#include <QTextEdit>
#include <QDebug>

class KConsole : public QTextEdit
{
    Q_OBJECT

    private:

        int max_length;
        bool use_CR_LF;


    public:

        typedef enum
        {
            Ascii,
            Hex
        }mode_type;

    private:

        mode_type mode;

    public:

        explicit KConsole(QWidget *parent=0);

        void useBackgroundColor(QColor color);
        void useTextColor(QColor color);
        void useTextFont(QFont text_font);
        void setMode(mode_type mod);


    public slots:
        void writeLine(QString line);
        void writeData(QByteArray data);
        void lineSeparation(bool state);
};

#endif // KCONSOLE_H
