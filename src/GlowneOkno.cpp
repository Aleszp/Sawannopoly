//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "GlowneOkno.hpp"
#include "TypyWyliczeniowe.hpp"
#include "WyborTrybu.hpp"


GlowneOkno::GlowneOkno(std::string sciezka, QWidget* parent):QMainWindow(parent)
{
    sciezka_=sciezka;
    char tmp[128];
    strcpy(tmp,(sciezka_+"/res/test.png").c_str());
    std::cout<<tmp<<std::endl;
    WyborTrybu wybor(this);
    setupOkno();

    glownyRozmieszczacz_->addWidget(&wybor);


    tryb_=wybor.exec();

    image_ = new QLabel(this);


    mypix_ = new QPixmap(tmp);
    image_->setPixmap(*mypix_);
    glownyRozmieszczacz_->addWidget(image_);
    image_->show();
    update();
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
	okno_->resize(1024,768);
	okno_->setWindowTitle("Sawannopoly");
    okno_->setAttribute( Qt::WA_DeleteOnClose );
    glownyRozmieszczacz_=new QVBoxLayout();
    okno_->setLayout(glownyRozmieszczacz_);
    okno_->show();
}

