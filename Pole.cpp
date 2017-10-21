//Nagłówki z katalogu programu
#include "Pole.hpp"
#include "Bank.hpp"

uint8_t licznikPol=0;

Pole::Pole()
{
	typ_=STANDARDOWE;
	nazwa_="???";
	czynsze_=new uint16_t[6];
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=(uint8_t)0;
	zastawione_=false;
	wlasciciel_=bank;
	id_=licznikPol;
	
	licznikPol++;
}

Pole::Pole(TypPola typ, std::string nazwa, uint16_t* czynsze)
{
	typ_=STANDARDOWE;
	nazwa_="???";
	czynsze_=new uint16_t[6];
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=czynsze[ii];
	zastawione_=false;
	wlasciciel_=bank;
	id_=licznikPol;
	
	licznikPol++;
}


Pole::~Pole()
{
	wlasciciel_->zabierzPole(id_);
	delete[] czynsze_;
}
