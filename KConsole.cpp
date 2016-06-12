#include "KConsole.h"


KConsole::KConsole(QWidget *parent) : QTextEdit(parent)
{
    this->max_length = 1024*32;
    this->use_CR_LF = true;

    this->setReadOnly(true);
    this->setTextInteractionFlags(0);

    this->useBackgroundColor(QColor(10,10, 10));
    this->useTextColor( QColor(20,230,20));
    this->useTextFont(QFont("Courier", 16,QFont::Bold));

    this->mode = KConsole::Ascii;


}

void KConsole::useBackgroundColor(QColor color)
{
    QPalette p = this->palette();
    p.setColor(QPalette::Base, color);
    this->setPalette(p);
}

void KConsole::useTextColor(QColor color)
{
    QPalette p = this->palette();
    p.setColor(QPalette::Text, color);
    this->setPalette(p);
}

void KConsole::useTextFont(QFont text_font)
{
    this->setFont(text_font);
}

void KConsole::setMode(KConsole::mode_type mod)
{
    this->mode = mod;
}

void KConsole::writeLine(QString line)
{
    if((this->toPlainText().length() + line.count()) > this->max_length)
    {
        this->clear();
    }

    this->insertPlainText(line);
    this->insertPlainText("\r\n");
    this->ensureCursorVisible();
}

void KConsole::writeData(QByteArray data)
{
    QString hexString;

    switch(mode)
    {
        case KConsole::Ascii:
            if((this->toPlainText().length() + data.count()) > this->max_length)
            {
                this->clear();
            }

            this->insertPlainText(data);

        break;
        case KConsole::Hex:
            hexString = data.toHex().toUpper();
            this->insertPlainText(hexString);
        break;
        default:

        break;
    }

    if(this->use_CR_LF) this->insertPlainText("\r\n");
    this->ensureCursorVisible();


}

void KConsole::lineSeparation(bool state)
{
    this->use_CR_LF = state;
}
