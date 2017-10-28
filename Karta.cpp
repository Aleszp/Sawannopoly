//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>

//Nagłówki z katalogu programu
#include "Karta.hpp"

std::list<Karta>karty[2];

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

void losujKarte(TypyKart talia, Gracz* gracz)
{
	
	Karta karta;
	//losuj
	
	uzyjKarty(karta, gracz);
}

void uzyjKarty(Karta karta, Gracz* gracz)
{
	
}

void wczytajKarty()
{
	FILE* daneKart=fopen(SCIEZKA_DO_DANYCH_KART,"r");
	
	//sprawdź czy istnieje plik
	if(daneKart==NULL)
	{
		fprintf(stderr,"Błąd otwarcie pliku bazy danych kart.\n");
		fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",SCIEZKA_DO_DANYCH_KART);
		exit(2);
	}
	
	while(!feof(daneKart))
	{
		TypyKart tmpTyp=KARTY_LATWEJ_ZDOBYCZY;
		//tu odczyt danych o karcie
		Karta tmpKarta; //(dane tymczasowe)
		karty[tmpTyp].push_back(tmpKarta);
	}
	
	fclose(daneKart);
}
