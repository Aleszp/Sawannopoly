//Standardowe nagłówki C/C++
#include <iostream>
#include <algorithm>

//Nagłówki z katalogu programu
#include "Gracz.hpp"
#include "Bank.hpp"
#include "Pole.hpp"

Gracz::Gracz(std::string imie="???", uint64_t gotowka=0)
{
	imie_=imie;
	gotowka_=gotowka;
	polozenie_=0;
	wygnany_=false;
	licznikDubletu_=0;
	wolneLwice_=0;
	kartaPowrotuZWygnania_=false;
}

Gracz::~Gracz()
{
	
}

void Gracz::ruszNKrokow(int8_t n)
{
	polozenie_+=n;
	if(polozenie_>39)
	{
		gotowka_+=20;
		polozenie_-=40;
	}
    std::cout<<imie_<<" stanął(ęła) na polu "<<(uint16_t)polozenie_<<" ("<<(pola[polozenie_].podajNazwe())<<") z terytorium "<<(uint16_t)pola[polozenie_].podajTerytorium()<<" mając "<<gotowka_<<" żuczków i "<<(uint16_t)podajLiczbeWolnychLwic()<<" wolną(e/ych) lwic."<<std::endl;
	pola[polozenie_].akcja(this);
}

void Gracz::idzDoPola(uint8_t cel)
{
	polozenie_=cel;
	pola[polozenie_].akcja(this);
}

void Gracz::zabierzPole(uint8_t id, Gracz* nowyWlasciciel=&bank)
{
	pola[id].ustawWlasciciela(nowyWlasciciel);
}

void Gracz::dajPole(uint8_t id)
{
	pola[id].ustawWlasciciela(this);
}

void Gracz::ustawWygnanie(bool wygnany)
{
	if(wygnany) 
	{
		idzDoPola(40);
		wygnany_=3; 
	}
	else 
	{
		wygnany_=0;
		idzDoPola(10);
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
	ruszNKrokow(wynik[0]+wynik[1]);
}

void Gracz::zaplac(uint16_t kwota, Gracz* komu)
{
	if(gotowka_>=kwota)
	{
		gotowka_-=kwota;
		if(komu!=&bank)
			komu->dodajGotowke(kwota);
	}
	else
	{
		if(wymusGotowke(kwota))
		{	
			gotowka_-=kwota;
			if(komu!=&bank)
				komu->dodajGotowke(kwota);
		}
		else
		{
			bankrutuj_na_rzecz(komu);
		}
	}
}

void Gracz::bankrutuj_na_rzecz(Gracz* komu)
{
	
}

void Gracz::zabierzLwice(uint8_t ile)
{
	while(true)
	{
		if(wolneLwice_>=ile)
		{	
			wolneLwice_-=ile;
			return;
		}
		else
		{
			wymusLwice(ile);
		}
	}
}

uint8_t Gracz::policzWszystkieLwice()
{
	uint8_t liczbaLwic=wolneLwice_;
	
	for (std::vector<Pole>::const_iterator it = pola.begin();it != pola.end(); ++it)
	{
		if(it->podajWlasciciela()==this)
			liczbaLwic+=it->podajLiczbeLwic();
	}	
	return liczbaLwic;
}

uint8_t Gracz::policzWszystkieZiemie()
{
	uint8_t liczbaPol=0;
	
	for (std::vector<Pole>::const_iterator it = pola.begin();it != pola.end(); ++it)
	{
		if(it->podajWlasciciela()==this)
			liczbaPol++;
	}	
	return liczbaPol;
}

bool Gracz::wymusGotowke(uint16_t kwota)
{
	while(gotowka_<=kwota)
	{
		//zezwól wyłącznie na akcje zdejmowania lwic z pól, odprawiania lwic, zastawiania terytorium lub sprzedarzy terytorium innym graczom
	}
	return false;
}

bool Gracz::wymusLwice(uint8_t ile)
{
	while(wolneLwice_<=ile)
	{
		//zezwól wyłącznie na akcje zdejmowania lwic z pól
	}
	return false;
}

bool Gracz::czyMaPole(uint8_t id) 
{
	if(pola[id].podajWlasciciela()==this)
		return true;
	else
		return false;
}