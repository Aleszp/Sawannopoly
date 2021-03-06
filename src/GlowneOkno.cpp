//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "GlowneOkno.hpp"
#include "TypyWyliczeniowe.hpp"
#include "WyborTrybu.hpp"
#include "Silnik.hpp"
#include "Plansza.hpp"

class silnik;

GlowneOkno::GlowneOkno(Silnik* silnik, std::string sciezka, QWidget* parent):QMainWindow(parent)
{
    //showFullScreen();
    silnik_=silnik;
    sciezka_=sciezka;
    setupOkno();

    tryb_=BRAK_TRYBU;
}

GlowneOkno::~GlowneOkno()
{
    //delete mypix_;
    //delete image_;
    //delete okno_;
}

void GlowneOkno::setupOkno(void)
{
	okno_=new QWidget();
    okno_->resize(1920,1080);
	okno_->setWindowTitle("Sawannopoly");
    okno_->setAttribute( Qt::WA_DeleteOnClose );
    rozmieszczacz_=new QBoxLayout(QBoxLayout::TopToBottom);
    okno_->setLayout(rozmieszczacz_);
    okno_->showFullScreen();
}

void GlowneOkno::wlaczMenuGlowne()
{
    rozmieszczacz_->setDirection(QBoxLayout::TopToBottom);
    wybor_=new WyborTrybu(this);
    rozmieszczacz_->addWidget(wybor_);
    tryb_=wybor_->exec();
    delete wybor_;
    silnik_->zmienTryb(tryb_);
}

void GlowneOkno::wlaczGoraceKrzeslo()
{
    /*image_ = new QLabel(this);

    char tmp[128];
    strcpy(tmp,(sciezka_+"/res/test.png").c_str());
    mypix_ = new QPixmap(tmp);
    image_->setPixmap(*mypix_);
    rozmieszczacz_->addWidget(image_);
    image_->show();*/

    rozmieszczacz_->setDirection(QBoxLayout::LeftToRight);
    plansza_=new Plansza(silnik_,this);
    rozmieszczacz_->addWidget(plansza_);
    panel_=new Panel;
    panel_->setParent(this);
    rozmieszczacz_->addWidget(panel_);
    update();
}
