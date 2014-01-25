#include "ads.h"

Ads::Ads(QWidget *parent) :
    QWidget(parent)
{
    createComponent();
    input();
}

void Ads::createComponent()
{
    lTitle = new QLabel(tr("Seja bem-vindo!"),this);
}

void Ads::input()
{
    QFont f;
    f.setPointSize(40);
    lTitle->setStyleSheet("color: rgba(0,0,0,130);");
    lTitle->setAlignment(Qt::AlignCenter);
    lTitle->setFont(f);
}

void Ads::resizeEvent(QResizeEvent *)
{
    lTitle->setGeometry(0,this->height()/2-40,this->width(),80);
}

