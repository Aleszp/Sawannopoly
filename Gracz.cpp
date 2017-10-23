//Standardowe nagłówki C/C++
#include <iostream>
#include <algorithm>

//Nagłówki z katalogu programu
#include "Gracz.hpp"
#include "Pole.hpp"

Gracz::Gracz()
{
	imie_="???";
	gotowka_=0;
	polozenie_=0;
	wygnany_=false;
}

Gracz::Gracz(std::string imie, uint64_t gotowka)
{
	imie_=imie;
	gotowka_=gotowka;
	polozenie_=0;
	wygnany_=false;
}

Gracz::~Gracz()
{
	
}

void Gracz::rusz_o_n_krokow(int8_t n)
{
	polozenie_+=n;
	if(polozenie_>=39)
	{
		gotowka_+=20;
		polozenie_-=40;
	}
	pola[polozenie_].akcja(this);
	std::cerr<<imie_<<" stanął(ęła) na polu "<<(pola[polozenie_].podajNazwe())<<" mając "<<gotowka_<<" żuczków."<<std::endl;
}

void Gracz::idz_do_pola(uint8_t cel)
{
	polozenie_=cel;
	pola[polozenie_].akcja(this);
}

void Gracz::zabierzPole(uint8_t id)
{
	nieruchomosci_.remove(id);
}

void Gracz::dajPole(uint8_t id)
{
	nieruchomosci_.remove(id);
	nieruchomosci_.push_back(id);
}

void Gracz::zaplac(uint16_t kwota)
{
	
}

void Gracz::ustawWygnanie(bool wygnany)
{
	if(wygnany) 
		wygnany_=3; 
	else 
	{
		wygnany_=0;
		idz_do_pola(10);
	}
}

bool Gracz::czyMaPole(uint8_t id)
{
	std::list<uint8_t>::iterator it = find (nieruchomosci_.begin(), nieruchomosci_.end(), id);
	if (it != nieruchomosci_.end())
		return true;
	else
		return false;
}
