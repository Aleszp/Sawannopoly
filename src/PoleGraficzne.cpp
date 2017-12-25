//Nagłówki z katalogu programu
#include "PoleGraficzne.hpp"

PoleGraficzne::PoleGraficzne(Plansza* rodzic, uint8_t id) : QWidget(rodzic)
{
    rodzic_=rodzic;
    id_=id;

    std::string sciezka=rodzic_->podajSciezke();
    sciezka+="/res/";

    char tmp[128];
    strcpy(tmp,(sciezka+std::to_string(id)+".png").c_str());

    wlasciciel_=new QLabel(this);
    wlasciciel_map_=new QPixmap(tmp);
    wlasciciel_->setPixmap(*wlasciciel_map_);

    ilustracja_=new QLabel(this);
    strcpy(tmp,(sciezka+"bank"+".png").c_str());
    ilustracja_map_=new QPixmap(tmp);
    ilustracja_->setPixmap(*ilustracja_map_);

    for(uint8_t ii=0;ii<4;ii++)
    {
        gracz_[ii]=new QLabel(this);
        strcpy(tmp,(sciezka+"puste"+".png").c_str());
        gracz_map_[ii]=new QPixmap(tmp);
        gracz_[ii]->setPixmap(*gracz_map_[ii]);
    }

    update();
}
