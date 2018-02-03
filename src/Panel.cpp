#include "Panel.hpp"

Panel::Panel()
{
    rozmieszczacz_=new QGridLayout(this);
    setLayout(rozmieszczacz_);
    rozmieszczacz_->setSpacing(0);

    Kostki_=new Kostka[2];
    Kostki_[0].setParent(this);
    Kostki_[1].setParent(this);
    rozmieszczacz_->addWidget(&(Kostki_[0]),0,0);
    rozmieszczacz_->addWidget(&(Kostki_[1]),0,1);
}

Panel::~Panel()
{
    delete[] Kostki_;
    delete rozmieszczacz_;
}

void Panel::ustawKostki(uint8_t k1, uint8_t k2)
{
    Kostki_[0].ustaw(k1);
    Kostki_[1].ustaw(k2);
}
