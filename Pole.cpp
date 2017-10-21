//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>

//Nagłówki z katalogu programu
#include "Pole.hpp"
#include "Bank.hpp"

uint8_t licznikPol=0;
std::vector<Pole> pola;

Pole::Pole()
{
	typ_=STANDARDOWE;
	nazwa_="???";
	wartosc_=0;
	cena_wywolawcza_=0;
	terytorium_=0;
	czynsze_=new uint16_t[6];
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=(uint8_t)0;
	zastawione_=false;
	wlasciciel_=bank;
	id_=licznikPol;
	
	licznikPol++;
}

Pole::Pole(TypPola typ, std::string nazwa, uint16_t wartosc, uint16_t cena_wywolawcza, uint16_t* czynsze, uint8_t terytorium)
{
	typ_=typ;
	nazwa_=nazwa;
	wartosc_=wartosc;
	cena_wywolawcza_=cena_wywolawcza;
	terytorium_=terytorium_;
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
	//delete[] czynsze_;
}

void Pole::akcja(Gracz* gracz)
{
	
}

std::ostream& operator<<(std::ostream& wyjscie, Pole& p) 
{
	wyjscie<<static_cast<uint16_t>(p.typ_)<<", "<<p.nazwa_;
	for(uint8_t ii=0;ii<6;ii++)
		wyjscie<<", "<<p.czynsze_[ii];	
	wyjscie<<", "<<p.terytorium_;
	return wyjscie;
}

/*********************************************************************/

void utworzPola()
{
	FILE* DanePol=fopen(SCIEZKA_DO_DANYCH_POL,"r");
	
	//sprawdź czy istnieje plik
	if(DanePol==NULL)
	{
		fprintf(stderr,"Błąd otwarcie pliku bazy danych nieruchomości.\n");
		fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",SCIEZKA_DO_DANYCH_POL);
		exit(1);
	}
	
	//pola.reserve(40);
	
	char tmp[128];
	std::string tmpString;
	
	TypPola tmpTyp=static_cast<TypPola>(0);
	char tmpNazwa[64];
	uint16_t tmpWartosc;
	uint16_t tmpCenaWywolawcza;
	uint8_t tmpTerytorium;
	uint16_t tmpCzynsze[6];
	//Wczytaj dane w formacie: TypPola, Nazwa pola, Wartość, Cena wywoławcza, czynsze[0-6]
	while(licznikPol<42)
	{
		if(feof(DanePol))
		{
			fprintf(stderr,"Niekompletna tablica danych o nieruchomościach.\n");
			fprintf(stderr,"Sprawdź, czy plik %s jest kompletny.\n",SCIEZKA_DO_DANYCH_POL);
			
			fclose(DanePol);
			exit(2);
		}
		
		fgets(tmp,128,DanePol);
		if(tmp[0]=='#')	//jeśli linijka stanowi komentarz
			continue;
			
		tmpString=wytnij(tmp);
		tmpTyp=static_cast<TypPola>(atoi(tmpString.c_str()));
		tmpString=wytnij(tmp);
		strcpy(tmpNazwa, tmpString.c_str());
		
		tmpString=wytnij(tmp);
		tmpWartosc=atoi(tmpString.c_str());
		
		tmpString=wytnij(tmp);
		tmpCenaWywolawcza=atoi(tmpString.c_str());
		
		tmpString=wytnij(tmp);
		tmpTerytorium=atoi(tmpString.c_str());
		
		for(uint8_t ii=0;ii<6;ii++)
		{
			tmpString=wytnij(tmp);
			tmpCzynsze[ii]=atoi(tmpString.c_str());
		}
		
		pola.push_back(Pole(tmpTyp, tmpNazwa, tmpWartosc, tmpCenaWywolawcza, tmpCzynsze,tmpTerytorium));
		std::cout<<pola.back()<<std::endl;
	}
	
	
	fclose(DanePol);
}

std::string wytnij(char* zrodlo)
{
	std::string tmpString(zrodlo);
	size_t przesuniecie=tmpString.find(",");
	
	std::string outString(tmpString,0,przesuniecie);
	tmpString=tmpString.substr(przesuniecie+1);
	
	strcpy(zrodlo, tmpString.c_str());
	return outString;
}
