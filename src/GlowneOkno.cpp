//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "GlowneOkno.hpp"
#include "TypyWyliczeniowe.hpp"
#include "WyborTrybu.hpp"


GlowneOkno::GlowneOkno(QWidget* parent):QMainWindow(parent)
{
    WyborTrybu wybor;
    tryb_=(TrybyGry)wybor.exec();
	setupOkno();
	okno_->show();
}

GlowneOkno::~GlowneOkno()
{
	delete okno_;
}

void GlowneOkno::setupOkno(void)
{
	okno_=new QWidget();
	okno_->resize(1024,768);
	okno_->setWindowTitle("Sawannopoly");
}

