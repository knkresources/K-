#ifndef KRCVIEWER_H
#define KRCVIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QGraphicsRectItem>

class KRCViewer : public QWidget
{
    Q_OBJECT

    QGraphicsView * viewPort;
    QGraphicsScene * scene;
    QLabel * nameLabel;

    QSpacerItem * leftSpacer;
    QSpacerItem * rightSpacer;

    QHBoxLayout * horizonLayout;
    QVBoxLayout * verticalLayout;

    QGraphicsRectItem * myRect;


    double max_f;
    double min_f;
    double scale;

protected:

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

public:
    explicit KRCViewer(QWidget *parent = 0);
    void setInputRange(double min_value, double max_value);
    void setName(QString name);
    void setColor(QBrush color);

signals:


public slots:

    void updateValue(double value);

};

#endif // KRCVIEWER_H
