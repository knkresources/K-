#include "KRCViewer.h"
#include <QDebug>
#include <QResizeEvent>

void KRCViewer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->viewPort->fitInView(this->scene->sceneRect(),Qt::IgnoreAspectRatio);
}

KRCViewer::KRCViewer(QWidget *parent) : QWidget(parent)
{
    this->scene = new QGraphicsScene(this);
    this->viewPort = new QGraphicsView(this->scene,this);

    this->nameLabel = new QLabel("RC channel");


    this->viewPort->setMinimumHeight(50);
    this->viewPort->setMaximumHeight(300);
    this->viewPort->setMinimumWidth(40);
    this->viewPort->setMaximumWidth(50);


    this->nameLabel->setAlignment(Qt::AlignCenter | Qt::AlignTop);


    this->verticalLayout = new QVBoxLayout;
    this->horizonLayout = new QHBoxLayout;

    this->horizonLayout->addSpacerItem(new QSpacerItem(50,1));
    this->horizonLayout->addWidget(this->viewPort);
    this->horizonLayout->addSpacerItem(new QSpacerItem(50,1));

    this->verticalLayout->addLayout(this->horizonLayout);
    this->verticalLayout->addWidget(this->nameLabel);
    this->verticalLayout->addSpacerItem(new QSpacerItem(1,5));

    this->setLayout(this->verticalLayout);


    this->setMaximumWidth(120);
    this->setMaximumHeight(300);

    QPen outlinePen(Qt::NoPen);
    QBrush redBrush(Qt::blue);

    this->myRect = this->scene->addRect(0,-50,50,0,outlinePen,redBrush);
    this->scene->setSceneRect(0,-100,50,100);


    this->viewPort->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewPort->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewPort->fitInView(this->scene->sceneRect(),Qt::IgnoreAspectRatio);



    this->setInputRange(0,100);
    this->updateValue(0);
}

void KRCViewer::setInputRange(double min_value, double max_value)
{
    if(max_value <= min_value) return;

    this->min_f = min_value;
    this->max_f = max_value;

    this->scale = 100/(max_f-min_f);

}

void KRCViewer::setName(QString name)
{
    this->nameLabel->setText(name);
}

void KRCViewer::setColor(QBrush color)
{
    this->myRect->setBrush(color);
}

void KRCViewer::updateValue(double value)
{
    double temp = value - this->min_f;
    temp *= this->scale;

    if(temp > 100) temp = 100;
    if(temp < 0) temp = 0;

    myRect->setRect(0,-temp,50,temp);
    this->viewPort->fitInView(this->scene->sceneRect(),Qt::IgnoreAspectRatio);
}


