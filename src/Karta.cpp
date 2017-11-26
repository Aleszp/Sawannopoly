//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <iterator>

//Nagłówki z katalogu programu
#include "Karta.hpp"
#include "Gracz.hpp"
#include "inne.hpp"

Karta::Karta()
{
	for(uint8_t ii=0;ii<3;ii++)
	{
		efekty_[ii]=BRAK_EFEKTU;
		liczby_[ii]=0;
	}
	opis_="Pusta karta.";
}

Karta::Karta(EfektKarty* efekty, int16_t* liczby, std::string opis)
{
	for(uint8_t ii=0;ii<3;ii++)
	{
		efekty_[ii]=efekty[ii];
		liczby_[ii]=liczby[ii];
	}
	opis_=opis;
}

Karta::~Karta()
{
	
}

void Karta::opisz()
{
    for(uint8_t ii=0;ii<3;ii++)
    {
        std::cout<<"Efekt["<<(uint16_t)ii<<"]: "<<(uint16_t)efekty_[ii]<<", liczba["<<(uint16_t)ii<<"]: "<<(uint16_t)liczby_[ii]<<"; ";
    }
    std::cout<<"OPIS: "<<opis_<<std::endl;
}
