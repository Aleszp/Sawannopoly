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

    char tmp[128];
    /*strcpy(tmp,(sciezka+"bank"+".png").c_str());
    wlasciciel_=new QLabel(this);
    wlasciciel_map_=new QPixmap(tmp);
    wlasciciel_->setPixmap(*wlasciciel_map_);*/

    ilustracja_=new QLabel(this);
    strcpy(tmp,(sciezka+std::to_string(id)+".png").c_str());
    ilustracja_map_=new QPixmap(tmp);
    ilustracja_->setPixmap(*ilustracja_map_);

    /*for(uint8_t ii=0;ii<4;ii++)
    {
        gracz_[ii]=new QLabel(this);
        strcpy(tmp,(sciezka+"puste"+".png").c_str());
        gracz_map_[ii]=new QPixmap(tmp);
        gracz_[ii]->setPixmap(*gracz_map_[ii]);
    }*/
    if((id>0&&id<10)||(id>20&&id<30))       //rzędy
    {
        setFixedSize(90,180);
    }
    else
    {
        if((id>10&&id<20)||(id>30&&id<40))       //kolumny
        {
            setFixedSize(180,90);
        }
        else //narożne
        {
            setFixedSize(180,180);
        }
    }
}
