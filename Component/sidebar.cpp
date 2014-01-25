/*
Copyright (c) 2013, Luiz Cândido da Silva Júnior, heron@jaguati.com.br

Copyright (c) 2013, Jonathan,  jonathan@jaguati.com.br
 All rights reserved. 

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 

 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 

 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 

 Neither the name of Pedyrum may be used to endorse or promote products derived from this software without specific prior written permission. 

 THIS SOFTWARE IS PROVIDED BY {{THE COPYRIGHT HOLDERS AND CONTRIBUTORS}} "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL {{THE COPYRIGHT HOLDER OR CONTRIBUTORS}} BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "sidebar.h"
#include <QDebug>
#include <QPropertyAnimation>

sideBar::sideBar(QWidget *parent) :
    QWidget(parent)
{
    createComponent();    
    input();
    connections();
}

void sideBar::createComponent()
{
    background = new QLabel(this);

    wScrool = new QWidget(this);

    pbUp = new QPushButton(this);
    pbDown = new QPushButton(this);

    lTreatment = new Label(wScrool,true,100);
    lClient = new Label(wScrool,true,100);
    lStock = new Label(wScrool,true,100);
    lOrdered = new Label(wScrool,true,100);    
    lFinance = new Label(wScrool,true,100);
    lConfigure = new Label(wScrool,true,100);
    lJaguati = new Label(wScrool,true,100);
    lWeb = new Label(wScrool,true,100);

    effects = new GraphicEffects(this);
}

void sideBar::adjustLayout()
{
    if(this->height() > 0)
        this->setGeometry(0,this->y(),this->width(),this->height());
    else
        this->setGeometry(0,this->y(),this->width(),0);

    background->setGeometry(0,0,this->width(),this->height());

    pbUp->setGeometry(0,0,this->width()-1,25);

    pbDown->setGeometry(0,this->height() - pbUp->height(),this->width()-1,25);

    if(countItens == 0)
        countItens = 7;
    else
        wScroolHeight = (SIZE_BUTTON + SPACING) * countItens;

    wScrool->setGeometry(0,wScroolY,this->width(),wScroolHeight);

    // adjustLayout dos botões //

    short int positionX = width() / 2 - SIZE_BUTTON/2;
    short int count = 0;

    if(lWeb->isVisible())
       count ++;

    lWeb->setGeometry(positionX, (SPACING * count), SIZE_BUTTON, SIZE_BUTTON);

    if(lTreatment->isVisible())
        count ++;

    lTreatment->setGeometry(positionX, (SPACING * count) + (SIZE_BUTTON * (count - 1)), SIZE_BUTTON, SIZE_BUTTON);

    if(lClient->isVisible())
        count ++;

    lClient->setGeometry(positionX,(SPACING * count) + (SIZE_BUTTON * (count - 1)) , SIZE_BUTTON, SIZE_BUTTON);

    if(lStock->isVisible())
        count ++;

    lStock->setGeometry(positionX,(SPACING * count) + (SIZE_BUTTON * (count - 1)) , SIZE_BUTTON, SIZE_BUTTON);

    if(lOrdered->isVisible())
        count ++;

    lOrdered->setGeometry(positionX, (SPACING * count) + (SIZE_BUTTON * (count - 1)) , SIZE_BUTTON, SIZE_BUTTON);

    if(lFinance->isVisible())
        count ++;

    lFinance->setGeometry(positionX, (SPACING * count) + (SIZE_BUTTON * (count - 1)), SIZE_BUTTON, SIZE_BUTTON);

    if(lConfigure->isVisible())
        count ++;

    lConfigure->setGeometry(positionX, (SPACING * count) + (SIZE_BUTTON * (count - 1)), SIZE_BUTTON, SIZE_BUTTON);

    if(lJaguati->isVisible())
        count ++;

    lJaguati->setGeometry(positionX, (SPACING * count) + (SIZE_BUTTON * (count - 1)), SIZE_BUTTON, SIZE_BUTTON);

    checkEnableButtons();

    countItens = count;
}

void sideBar::input()
{
    countItens = 9;

    wScroolHeight = (SIZE_BUTTON + SPACING) * countItens;

    wScroolY = 25;

    background->setStyleSheet("background-color: white;"
                              "border-right: 1px solid rgba(50,50,50,50);");


    pbUp->setToolTip(tr("Subir"));
    pbUp->setObjectName("pbUp");
    pbUp->setIcon(QIcon(":/sideBar/up"));
    pbUp->setIconSize(QSize(this->width(),25));

    pbDown->setToolTip(tr("Descer"));
    pbDown->setObjectName("pbDown");
    pbDown->setIcon(QIcon(":/sideBar/down"));
    pbDown->setIconSize(QSize(this->width(),25));

    lTreatment->setImage(":/sideBar/treatment");
    lTreatment->setHover("");
    lTreatment->setAlternateImage("");
    lTreatment->setToolTip(tr("Atendimento"));

    lClient->setImage(":/sideBar/client");
    lClient->setHover("");
    lClient->setAlternateImage("");
    lClient->setToolTip(tr("Cliente"));

    lStock->setImage(":/sideBar/product");
    lStock->setHover("");
    lStock->setAlternateImage("");
    lStock->setToolTip(tr("Produto"));

    lOrdered->setImage(":/sideBar/ordered");
    lOrdered->setHover("");
    lOrdered->setAlternateImage("");
    lOrdered->setToolTip(tr("Pedidos"));

    lFinance->setImage(":/sideBar/finance");
    lFinance->setHover("");
    lFinance->setAlternateImage("");
    lFinance->setToolTip(tr("Financeiro"));

    lConfigure->setImage(":/sideBar/config");
    lConfigure->setHover("");
    lConfigure->setAlternateImage("");
    lConfigure->setToolTip(tr("Configuração"));

    lJaguati->setImage(":/sideBar/about");
    lJaguati->setHover("");
    lJaguati->setAlternateImage("");
    lJaguati->setToolTip(tr("Jaguati"));

    lWeb->setImage(":/sideBar/buy");
    lWeb->setHover("");
    lWeb->setAlternateImage("");
    lWeb->setToolTip(tr("Novidades"));

    QFont f;

#if defined(Q_WS_X11)
    {
        f.setFamily("Sans Serif");
        f.setPointSize(12);
    }
#endif

#if defined(Q_WS_WIN)
    {
        f.setFamily("MS Shell Dlq 2");
        f.setPointSize(14);
    }
#endif

    pbUp->setCursor(Qt::PointingHandCursor);
    pbDown->setCursor(Qt::PointingHandCursor);

}

void sideBar::resizeEvent(QResizeEvent *)
{
    adjustLayout();
}

void sideBar::onClick_Treatment()
{
    emit goToPanel(3);
}

void sideBar::onClick_Client()
{
    emit goToPanel(4);
}

void sideBar::onClick_Stock()
{
    emit goToPanel(5);
}

void sideBar::onClick_Ordered()
{
    emit goToPanel(6);
}

void sideBar::onClick_Finance()
{
    emit goToPanel(9);
}

void sideBar::onClick_Configure()
{
    emit goToPanel(10);
}

void sideBar::onClick_Jaguati()
{
    emit goToPanel(11);
}

void sideBar::onClick_Web()
{
    emit goToPanel(12);
}


void sideBar::onClick_pbDown()
{
    wScroolY = (this->height() - pbUp->height() *2) -  wScrool->height();
    moveScrool(false);
}

void sideBar::onClick_pbUp()
{
    wScroolY = pbUp->height();
    moveScrool(true);
}

void sideBar::connections()
{
    connect(pbUp,SIGNAL(clicked()),SLOT(onClick_pbUp()));

    connect(pbDown,SIGNAL(clicked()),SLOT(onClick_pbDown()));

    connect(lClient,SIGNAL(onClick()),this,SLOT(onClick_Client()));

    connect(lTreatment,SIGNAL(onClick()),this,SLOT(onClick_Treatment()));

    connect(lStock,SIGNAL(onClick()),this,SLOT(onClick_Stock()));

    connect(lOrdered,SIGNAL(onClick()),this,SLOT(onClick_Ordered()));

    connect(lFinance,SIGNAL(onClick()),this,SLOT(onClick_Finance()));

    connect(lConfigure,SIGNAL(onClick()),this,SLOT(onClick_Configure()));

    connect(lJaguati,SIGNAL(onClick()),this,SLOT(onClick_Jaguati()));

    connect(lWeb,SIGNAL(onClick()),this,SLOT(onClick_Web()));
}

void sideBar::checkEnableButtons()
{
    if((this->height() - pbUp->height() *2) >= wScrool->height() && wScroolY > 0)
    {
        pbUp->setEnabled(false);

        pbDown->setEnabled(false);
    }
    else
    {
        if(wScrool->height() + wScroolY <= pbDown->y())
        {
            pbDown->setEnabled(false);
        }
        else
        {
            pbDown->setEnabled(true);
        }

        if(wScroolY == (pbUp->y() + pbUp->height()))
        {
            pbUp->setEnabled(false);
        }
        else
        {
            pbUp->setEnabled(true);
        }
    }
}


void sideBar::moveScrool(bool up)
{
    QPropertyAnimation *animacao;

    if(up)
    {
        animacao = effects->createAnimation(wScrool,QRect(wScrool->x(),wScroolY,
                                                          wScrool->width(),wScrool->height()),300,QEasingCurve::Linear);
    }
    else
    {
        animacao = effects->createAnimation(wScrool,QRect(wScrool->x(),wScroolY,
                                                          wScrool->width(),wScrool->height()),300,QEasingCurve::Linear);
    }

    animacao->start();

    connect(animacao,SIGNAL(finished()),SLOT(checkEnableButtons()));
}


int sideBar::countAlerts()
{
    return countAlert;
}

void sideBar::setVisibleItens(short index, bool visible)
{
    switch(index)
    {

    case 0:lTreatment->setVisible(visible);
        break;

    case 1:lClient->setVisible(visible);
        break;

    case 2:lStock->setVisible(visible);
        break;

    case 3:lOrdered->setVisible(visible);
        break;

    case 4:lFinance->setVisible(visible);
        break;

    case 5:lConfigure->setVisible(visible);
        break;

    case 6:lJaguati->setVisible(visible);
        break;

    case 7:lWeb->setVisible(visible);
        break;
    }

    if(visible == false)
        countItens --;
    else
        countItens ++;
}
