//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <iterator>

//Nagłówki z katalogu programu
#include "Karta.hpp"
#include "Gracz.hpp"
#include "Bank.hpp"
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

void pobierzKarte(TypKarty talia, Gracz* gracz)
{
	
	Karta karta=karty[talia].front();	//pobierz kartę z początku
	karty[talia].pop_front();
	
	std::cout<<"Pobrana karta: "<<karta.podajOpis()<<std::endl;
	
	uzyjKarty(karta, gracz);
	
	std::cout<<"Odkładam na koniec kartę: "<<karta.podajOpis()<<std::endl;
	
	karty[talia].push_back(karta);	//umieść kartę na sam koniec listy
}

void uzyjKarty(Karta karta, Gracz* gracz)
{
	//tu umieść interpreter (z trzema iteracjami)
	
	for(uint8_t ii=0;ii<3;ii++)
	{
		switch(karta.podajEfekt(ii))
		{
			case BRAK_EFEKTU:
				//Nie rób nic
			break;
			case ZMIANA_GOTOWKI:
				if(karta.podajLiczbe(ii)>0)
					gracz->dodajGotowke(karta.podajLiczbe(ii));
				else
					gracz->zaplac((-1)*karta.podajLiczbe(ii),&bank);	//zmiana liczby z ujemnej na dodatnią, bo metoda zaplac pracuje na liczbach dodatnich (liczba ujemna traktowana jest jak bardzo duża liczba dodatnia ze względu na sposób reprezentacji liczb całkowitych
			break;
			case ZMIANA_LICZBY_LWIC:
					if(karta.podajLiczbe(ii)>0)
						gracz->dodajLwice(karta.podajLiczbe(ii));
					else
						gracz->zabierzLwice((-1)*karta.podajLiczbe(ii));	//zmiana liczby z ujemnej na dodatnią, bo metoda zaplac pracuje na liczbach dodatnich (liczba ujemna traktowana jest jak bardzo duża liczba dodatnia ze względu na sposób reprezentacji liczb całkowitych
			
			break;
			case PRZESUN:
				gracz->rusz_o_n_krokow(karta.podajLiczbe(ii)-gracz->podajPolozenie());
			break;
			case WYGNAJ:
				gracz->ustawWygnanie(true);
			break;
			case KARTA_POWROTU_Z_WYGNANIA:
				gracz->ustawKartePowrotu(true);
			break;			
			default:
				std::cerr<<"Nieprawidłowy efekt karty."<<std::endl;
			break;
		}
	}
}

void Karta::opisz()
{
	for(uint8_t ii=0;ii<3;ii++)
	{
		std::cout<<"Efekt["<<(uint16_t)ii<<"]: "<<(uint16_t)efekty_[ii]<<", liczba["<<(uint16_t)ii<<"]: "<<(uint16_t)liczby_[ii]<<"; ";
	}		
	std::cout<<"OPIS: "<<opis_<<std::endl;
	
}

void wczytajKarty(std::string sciezka)
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
	
	przetasujKarty(KARTY_LATWEJ_ZDOBYCZY);
	przetasujKarty(KARTY_DLA_DOBRA_STADA);
	
	fclose(daneKart);
}

void przetasujKarty(TypKarty talia)
{
	std::list<Karta>tmp_talia(karty[talia]);
	
	karty[talia].clear();
	
	auto iterator = tmp_talia.begin();	
	uint16_t ii=0;
	
	while(tmp_talia.size()>0)
	{
		ii=rand()%(tmp_talia.size());
		
		iterator = tmp_talia.begin();
		std::advance(iterator, ii);
		
		karty[talia].push_back(*iterator);
		tmp_talia.erase(iterator);
	}
	
	
	//potasuj karty, np. tworząc tymczasową listę, przenosząc dane do niej i kopiując do początkowej listy w losowej kolejności
}
