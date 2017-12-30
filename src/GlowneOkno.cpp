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
    delete mypix_;
    delete image_;
    //delete okno_;
}

void GlowneOkno::setupOkno(void)
{
	okno_=new QWidget();
    okno_->resize(1920,1080);
	okno_->setWindowTitle("Sawannopoly");
    okno_->setAttribute( Qt::WA_DeleteOnClose );
    glownyRozmieszczacz_=new QVBoxLayout();
    okno_->setLayout(glownyRozmieszczacz_);
    okno_->showFullScreen();
}

void GlowneOkno::wlaczMenuGlowne()
{
    wybor_=new WyborTrybu(this);
    glownyRozmieszczacz_->addWidget(wybor_);
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
    glownyRozmieszczacz_->addWidget(image_);
    image_->show();*/
    plansza_=new Plansza(silnik_,this);
    glownyRozmieszczacz_->addWidget(plansza_);

    update();
}
