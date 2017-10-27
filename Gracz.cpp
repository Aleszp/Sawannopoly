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
	wygnany_=0;
	licznikDubletu_=0;
}

Gracz::Gracz(std::string imie, uint64_t gotowka)
{
	imie_=imie;
	gotowka_=gotowka;
	polozenie_=0;
	wygnany_=false;
	licznikDubletu_=0;
}

Gracz::~Gracz()
{
	
}

void Gracz::rusz_o_n_krokow(int8_t n)
{
	polozenie_+=n;
	if(polozenie_>39)
	{
		gotowka_+=20;
		polozenie_-=40;
	}
	std::cerr<<imie_<<" stanął(ęła) na polu "<<(uint16_t)polozenie_<<" ("<<(pola[polozenie_].podajNazwe())<<") z terytorium "<<(uint16_t)pola[polozenie_].podajTerytorium()<<" mając "<<gotowka_<<" żuczków."<<std::endl;
	pola[polozenie_].akcja(this);
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

void Gracz::rzutKoscia()
{
	uint8_t wynik[2];
	wynik[0]=rand()%6+1;
	wynik[1]=rand()%6+1;
	
	std::cout<<"Wyrzucono: "<<(uint16_t)wynik[0]<<" i "<<(uint16_t)wynik[1]<<"! ";
	
	if(wynik[0]==wynik[1])
	{
		licznikDubletu_++;
		std::cout<<"Dublet!";
		if(licznikDubletu_==3)
		{
			std::cout<<"Wygnanie za potrójny dublet!"<<std::endl;
			idz_do_pola(40);
			ustawWygnanie(true);
			licznikDubletu_=0;
			return;
		}
	}
	else
	{
		licznikDubletu_=0;
	}
	std::cout<<std::endl;
	rusz_o_n_krokow(wynik[0]+wynik[1]);
}

void Gracz::zaplac(uint16_t kwota, Gracz* komu)
{
	if(gotowka_>=kwota)
	{
		gotowka_-=kwota;
		komu->dodajGotowke(kwota);
	}
	else
	{
		//wymuś pozyskanie gotówki
		//lub ogłoś bankructwo
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
