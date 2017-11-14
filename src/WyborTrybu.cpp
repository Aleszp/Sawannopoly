//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "WyborTrybu.hpp"
#include "TypyWyliczeniowe.hpp"

WyborTrybu::WyborTrybu(QWidget* parent):QWidget(parent)
{
    tryb_=BRAK_TRYBU;
    setupWybor();
    this->show();
}

WyborTrybu::~WyborTrybu()
{
    delete gorace_krzeslo_;
    delete tytul_;
    delete rozmieszczacz_;
}

void WyborTrybu::setupWybor(void)
{
    rozmieszczacz_=new QVBoxLayout(this);
    this->setLayout(rozmieszczacz_);

    tytul_=new QLabel("MENU GŁÓWNE");
    rozmieszczacz_->addWidget(tytul_);

    gorace_krzeslo_=new QPushButton("Tryb \"Gorące Krzesło\"");
    rozmieszczacz_->addWidget(gorace_krzeslo_);
    gorace_krzeslo_->show();
    QObject::connect(gorace_krzeslo_, SIGNAL(clicked(bool)),this, SLOT(trybGorocegoKrzesla(bool)));
}

void WyborTrybu::trybGorocegoKrzesla(bool a)
{
    tryb_=GORACE_KRZESLO;
    loop_->quit();
}

TrybyGry WyborTrybu::exec()
{
    loop_=new QEventLoop(this);
    loop_->exec();
    delete loop_;
    return tryb_;
}
