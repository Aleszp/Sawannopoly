//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>

//Nagłówki z katalogu programu
#include "Karta.hpp"
#include "inne.hpp"

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

void losujKarte(TypKarty talia, Gracz* gracz)
{
	
	Karta karta;
	//losuj
	
	uzyjKarty(karta, gracz);
}

void uzyjKarty(Karta karta, Gracz* gracz)
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

void wczytajKarty()
{
	FILE* daneKart=fopen(SCIEZKA_DO_DANYCH_KART,"r");
	
	//sprawdź czy istnieje plik
	if(daneKart==NULL)
	{
		fprintf(stderr,"Błąd otwarcie pliku bazy danych kart.\n");
		fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",SCIEZKA_DO_DANYCH_KART);
		exit(3);
	}
	
	char tmp[1024];
	std::string tmpString;
	TypKarty tmpTyp;
	EfektKarty tmpEfekty[3];
	int16_t tmpLiczby[3];
	std::string tmpOpis;
	
	//dane w formacie: TypKarty, dla i=0..2 (Efekt[i], Liczba[i]), opis
	
	while(!feof(daneKart))
	{
		
		//tu odczyt danych o karcie
		
		fgets(tmp,1024,daneKart);
		if(tmp[0]=='#')	//jeśli linijka stanowi komentarz
			continue;
			
		tmpString=wytnij(tmp);
		tmpTyp=static_cast<TypKarty>(atoi(tmpString.c_str()));
		
		for(uint8_t ii=0;ii<3;ii++)
		{
			tmpString=wytnij(tmp);
			tmpEfekty[ii]=static_cast<EfektKarty>(atoi(tmpString.c_str()));
			tmpString=wytnij(tmp);
			tmpLiczby[ii]=atoi(tmpString.c_str());
		}		
		tmpOpis=tmp;
		
		karty[tmpTyp].push_back(Karta(tmpEfekty,tmpLiczby,tmpOpis));
	}
	
	fclose(daneKart);
}
