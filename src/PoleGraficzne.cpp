//Nagłówki z katalogu Qt
#include <QColor>

//Standardowe nagłówki C/C++
#include <iostream>

//Nagłówki z katalogu programu
#include "PoleGraficzne.hpp"

PoleGraficzne::PoleGraficzne(Plansza* rodzic, uint8_t id) : QWidget(rodzic)
{
    rodzic_=rodzic;
    id_=id;

    //setStyleSheet(id%2?"background-color:black;":"background-color:white;");

    std::string sciezka=rodzic_->podajSciezke();
    sciezka+="/res/";

    //char tmp[128];
    /*strcpy(tmp,(sciezka+"bank"+".png").c_str());
    wlasciciel_=new QLabel(this);
    wlasciciel_map_=new QPixmap(tmp);
    wlasciciel_->setPixmap(*wlasciciel_map_);*/

    ilustracja_=new QLabel(this);
    //strcpy(tmp,(sciezka+std::to_string(id)+".png").c_str());
    //ilustracja_map_=new QPixmap(tmp);
    if((id>0&&id<10)||(id>20&&id<30))       //rzędy
    {
        setFixedSize(75,150);
        ilustracja_map_=new QPixmap(75,150);
    }
    else
    {
        if((id>10&&id<20)||(id>30&&id<40))       //kolumny
        {
            setFixedSize(150,75);
            ilustracja_map_=new QPixmap(150,75);
        }
        else //narożne
        {
            setFixedSize(150,150);
            ilustracja_map_=new QPixmap(150,150);
        }
    }
    ilustracja_map_->fill(id%2?QColor(255,255,255):QColor(0,0,0));
    ilustracja_->setPixmap(*ilustracja_map_);

    /*for(uint8_t ii=0;ii<4;ii++)
    {
        Pionek_[ii]=new QLabel(this);
        strcpy(tmp,(sciezka+"puste"+".png").c_str());
        Pionek_map_[ii]=new QPixmap(tmp);
        Pionek_[ii]->setPixmap(*Pionek_map_[ii]);
    }*/
}
