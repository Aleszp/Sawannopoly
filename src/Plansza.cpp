//Standardowe nagłówki C/C++
#include <iostream>

//Nagłówki z katalogu programu
#include "Plansza.hpp"
#include "PoleGraficzne.hpp"

Plansza::Plansza(Silnik* silnik, QWidget* parent) : QWidget(parent)
{
    setFixedSize(1000,1000);
    silnik_=silnik;
    glownyRozmieszczacz_ = new QGridLayout(this);
    glownyRozmieszczacz_->setSpacing(0);
    this->setLayout(glownyRozmieszczacz_);

    pola_ = new PoleGraficzne*[40];

    for(uint8_t ii=0;ii<40;ii++)//stwórz wszystkie pola
    {
        pola_[ii]=new PoleGraficzne(this,ii);
    }
    uint8_t ii=0;
    glownyRozmieszczacz_->addWidget(pola_[0],11,11,2,2);
    for(ii=1;ii<10;ii++)//dolny rząd
    {
        glownyRozmieszczacz_->addWidget(pola_[ii],11,11-ii,2,1);
    }
    glownyRozmieszczacz_->addWidget(pola_[10],11,0,2,2);
    for(ii=11;ii<20;ii++)//lewa kolumna
    {
        glownyRozmieszczacz_->addWidget(pola_[ii],21-ii,0,1,2);
    }
    glownyRozmieszczacz_->addWidget(pola_[20],0,0,2,2);
    for(ii=21;ii<30;ii++)//górny rząd
    {
        glownyRozmieszczacz_->addWidget(pola_[ii],0,ii-19,2,1);
    }
    glownyRozmieszczacz_->addWidget(pola_[30],0,11,2,2);
    for(ii=31;ii<40;ii++)//prawa kolumna
    {
        glownyRozmieszczacz_->addWidget(pola_[ii],ii-29,11,1,2);
    }

    //std::cout<<glownyRozmieszczacz_->rowCount()<<"x"<<glownyRozmieszczacz_->columnCount()<<std::endl;
    update();
}

Plansza::~Plansza()
{
    delete[] pola_;
}


