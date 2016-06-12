#ifndef KINPUTNUMBER_H
#define KINPUTNUMBER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QFrame>

class KInputNumber : public QWidget
{

    Q_OBJECT

    private:

        QLabel * labelName;
        QLabel * labelStep;
        QPushButton * applyButton;
        QDoubleSpinBox * spinBoxValue;
        QDoubleSpinBox * spinBoxStep;

        QHBoxLayout * horizonLayout;

        bool updated;

    private slots:

        void spinChanged(double value);
        void stepChanged(double value);
        void applyClicked(bool checked);

    public:
        explicit KInputNumber(QWidget *parent = 0);
        void setName(QString name);
        void setDecimals(unsigned int decimals);
        void setStep(double step);
        double currentValue(void);

    public slots:

        void valueUpdated(void);

    signals:

        void valueChanged(double);

};

#endif // KINPUTNUMBER_H
