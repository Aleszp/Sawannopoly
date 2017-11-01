//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>

//Nagłówki z katalogu programu
#include "Pole.hpp"
#include "Bank.hpp"
#include "Karta.hpp"
#include "inne.hpp"

uint8_t licznikPol=0;
std::vector<Pole> pola;

Pole::Pole()
{
	id_=licznikPol;
	typ_=STANDARDOWE;
	nazwa_="???";
	wartosc_=0;
	cena_wywolawcza_=0;
	terytorium_=0;
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=(uint8_t)0;
	zastawione_=false;
	wlasciciel_=&bank;
	lwice_=0;
	
	licznikPol++;
}

Pole::Pole(TypPola typ, std::string nazwa, uint16_t wartosc, uint16_t cena_wywolawcza, uint16_t* czynsze, uint8_t terytorium)
{
	id_=licznikPol;
	typ_=typ;
	nazwa_=nazwa;
	wartosc_=wartosc;
	cena_wywolawcza_=cena_wywolawcza;
	terytorium_=terytorium;
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=czynsze[ii];
	zastawione_=false;
	wlasciciel_=&bank;
	lwice_=0;
	
	licznikPol++;
}


Pole::~Pole()
{

}

std::ostream& operator<<(std::ostream& wyjscie, Pole& p)
{
	wyjscie<<static_cast<uint16_t>(p.id_)<<": "<<static_cast<uint16_t>(p.typ_)<<", "<<p.nazwa_;
	for(uint8_t ii=0;ii<6;ii++)
		wyjscie<<", "<<p.czynsze_[ii];	
	wyjscie<<", "<<p.terytorium_;
	return wyjscie;
}

void Pole::akcja(Gracz* gracz)
{
	if(podajWlasciciela()==gracz)
	{
		std::cout<<"To pole należy do gracza "<<wlasciciel_->podajImie()<<"."<<std::endl;
	}
	else
	{
		if(podajWlasciciela()!=&bank)
		{
			std::cout<<"To pole należy do gracza "<<wlasciciel_->podajImie()<<"."<<std::endl;
		}
		switch(typ_)
		{
			case STANDARDOWE:
			{
				if(wlasciciel_==&bank) 	//jeśli niczyje - dać wybór między kupnem a licytacją
				{
					
				}
				else //jeśli innego gracza pobrać czynsz (z uwzględnieniem kompletności terytoriów oraz liczby lwic)
				{
					
					uint16_t kwota=czynsze_[0];
					
					if(sprawdz_kompletnosc_terytorium(this))
					{
						std::cout<<"To pole stanowi kompletne terytorium ";
						if(lwice_>0)
							std::cout<<"obstawione przez "<<(uint16_t)podajLiczbeLwic()<<" lwice(ę).";
						std::cout<<std::endl;
						kwota=czynsze_[1+lwice_];
					}
					std::cout<<"Kwota do zapłaty wynosi "<<kwota<<" żuczki(ów)."<<std::endl;
					gracz->zaplac(kwota, wlasciciel_);
				}
			}
			break;
			case START:	
				//gotówkę zwiększa funkcja przesuwająca, więc tu nic się nie dzieje
			break;
			case LATWA_ZDOBYCZ:
			{
				pobierzKarte(KARTY_LATWEJ_ZDOBYCZY, gracz);
				//wywołać obsługę Łatwej zdobyczy
			}
			break;
			case DLA_DOBRA_STADA:
			{
				//wywołać obsługę Dla dobra stada
				pobierzKarte(KARTY_DLA_DOBRA_STADA, gracz);
			}
			break;
			case POSILEK:
				gracz->zaplac(wartosc_,&bank);
			break;
			case UZYTECZNOSC:
			{
				//jeśli niczyje - dać wybór między kupnem a licytacją
				//jeśli innego gracza pobrać czynsz (z uwzględnieniem posiadania będź nie obu ujęć)
			}
			break;
			case GRANICA:
			{
				//jeśli niczyje - dać wybór między kupnem a licytacją
				//jeśli innego gracza pobrać czynsz (z uwzględnieniem posiadania poszczególnych granic)
			}
			break;
			case WYGNANIE:
				//tu nic się nie dzieje
			break;
			case POGRANICZE:
				//tu nic się nie dzieje
			break;
			case UDAJ_SIE_NA_WYGNANIE:
			{
				gracz->ustawWygnanie(true);
			}
			break;
			case BEZTROSKI_BAOBAB:
				//tu nic się nie dzieje
			break;
			default:
				std::cerr<<"Gracz "<<gracz->podajImie()<<" stanął na nieobsługiwanym polu o id: "<<id_<<"."<<std::endl;
			break;
		}
	}
}

void Pole::wykup()
{
	if(wlasciciel_->podajGotowke()>=(wartosc_*3)/5)
		{
			wlasciciel_->zaplac((wartosc_*3)/5,&bank);
		}
}

void Pole::zastaw()
{
	while(lwice_>0)
	{
		odejmijLwice();
	}
	if(podajZastawione())
		return; 
	wlasciciel_->dodajGotowke(wartosc_/2);
	zastawione_=true;
}
void Pole::dodajLwice()
{
	if(czyMoznaDodacLwice())
	{
		lwice_++;
		wlasciciel_->dodajLwice(-1);
		wlasciciel_->zaplac(KOSZT_USTAWIENIA_LWICY,&bank);
	}
	else
	{
		
	}
}

void Pole::odejmijLwice()
{
	if(lwice_>0)
	{
		lwice_--;
		wlasciciel_->dodajLwice(+1);
		wlasciciel_->dodajGotowke((KOSZT_USTAWIENIA_LWICY*4)/5);
	}
}
		
bool Pole::czyMoznaDodacLwice()
{
	if((wlasciciel_->podajGotowke()>KOSZT_USTAWIENIA_LWICY) && (wlasciciel_->podajLiczbeWolnychLwic()>0) && (lwice_<4))
		return true;
	else	
		return false;
}

/*********************************************************************/

void utworzPola()
{
	FILE* danePol=fopen(SCIEZKA_DO_DANYCH_POL,"r");
	
	//sprawdź czy istnieje plik
	if(danePol==NULL)
	{
		fprintf(stderr,"Błąd otwarcie pliku bazy danych nieruchomości.\n");
		fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",SCIEZKA_DO_DANYCH_POL);
		exit(1);
	}
	
	char tmp[128];
	std::string tmpString;
	
	TypPola tmpTyp=static_cast<TypPola>(0);
	char tmpNazwa[64];
	uint16_t tmpWartosc;
	uint16_t tmpCenaWywolawcza;
	uint8_t tmpTerytorium;
	uint16_t tmpCzynsze[6];
	//Wczytaj dane w formacie: TypPola, Nazwa pola, Wartość, Cena wywoławcza, czynsze[0-6]
	while(licznikPol<41)
	{
		if(feof(danePol))
		{
			fprintf(stderr,"Niekompletna tablica danych o nieruchomościach.\n");
			fprintf(stderr,"Sprawdź, czy plik %s jest kompletny.\n",SCIEZKA_DO_DANYCH_POL);
			
			fclose(danePol);
			exit(2);
		}
		
		fgets(tmp,128,danePol);
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
	}
	
	
	fclose(danePol);
}


bool sprawdz_kompletnosc_terytorium(const Pole* const  pole)
{
	for(uint8_t ii=0;ii<40;ii++)
	{
		if(pola[ii].podajTerytorium()==pole->podajTerytorium())
		{
			if(pola[ii].podajWlasciciela()!=pole->podajWlasciciela())
			{
				return false;
			}
		}
	}
	return true;
}
