//Standardowe nagłówki C/C++
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//Nagłówki z katalogu programu
#include "GlowneOkno.hpp"
#include "TypyWyliczeniowe.hpp"

GlowneOkno::GlowneOkno(QWidget* parent):QMainWindow(parent)
{
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

