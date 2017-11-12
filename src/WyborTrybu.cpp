//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "WyborTrybu.hpp"
#include "TypyWyliczeniowe.hpp"

WyborTrybu::WyborTrybu(QWidget* parent):QDialog(parent)
{
    tryb_=BRAK_TRYBU;
    setupWybor();
	okno_->show();
}

WyborTrybu::~WyborTrybu()
{
    delete loop_;
    delete gorace_krzeslo_;
    delete rozmieszczacz_;
    delete okno_;
}

void WyborTrybu::setupWybor(void)
{
	okno_=new QWidget();
	okno_->resize(1024,768);
    okno_->setWindowTitle("Sawannopoly - menu główne");

    rozmieszczacz_=new QVBoxLayout(okno_);
    okno_->setLayout(rozmieszczacz_);

    gorace_krzeslo_=new QPushButton("Tryb \"Gorące Krzesło\"");
    rozmieszczacz_->addWidget(gorace_krzeslo_);
    gorace_krzeslo_->show();
    QObject::connect(gorace_krzeslo_, SIGNAL(clicked(bool)),this, SLOT(trybGorocegoKrzesla(bool)));
}

void WyborTrybu::trybGorocegoKrzesla(bool a)
{
    tryb_=GORACE_KRZESLO;
    loop_->quit();
    this->close();
}
