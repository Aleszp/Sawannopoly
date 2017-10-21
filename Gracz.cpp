//Standardowe nagłówki C/C++
#include <iostream>

//Nagłówki z katalogu programu
#include "Gracz.hpp"

Gracz::Gracz()
{
	imie_="???";
	gotowka_=0;
	polozenie_=0;
}

Gracz::Gracz(std::string imie, uint64_t gotowka)
{
	imie_=imie;
	gotowka_=gotowka;
	polozenie_=0;
}

Gracz::~Gracz()
{
	
}

void Gracz::rusz_o_n_krokow(int8_t n)
{
	polozenie_+=n;
	if(polozenie_>=41)
	{
		gotowka_+=20;
		polozenie_-=40;
	}
	//pola[polozenie_]->akcja(this);
	std::cerr<<imie_<<" stanął(ęła) na polu "<<(uint16_t)polozenie_<<" mając "<<gotowka_<<" żuczków."<<std::endl;
}

void Gracz::idz_do_pola(uint8_t cel)
{
	polozenie_=cel;
	pola[polozenie_].akcja(this);
}

void Gracz::zabierzPole(uint8_t id)
{
	
}

void Gracz::dajPole(uint8_t id)
{
	
}
