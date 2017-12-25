//Standardowe nagłówki C/C++
#include <cstdio>
#include <iostream>
#include <cstring>

//Nagłówki z katalogu programu
#include "Pole.hpp"
#include "Karta.hpp"
#include "inne.hpp"
#include "Silnik.hpp"

uint8_t licznikPol=0;

Pole::Pole()
{
    silnik_=NULL;;
	id_=licznikPol;
	typ_=STANDARDOWE;
	nazwa_="???";
	wartosc_=0;
	cenaWywolawcza_=0;
	terytorium_=0;
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=(uint8_t)0;
	zastawione_=false;
    wlasciciel_=NULL;
	lwice_=0;
	
	licznikPol++;
}

Pole::Pole(Silnik* silnik,TypPola typ, std::string nazwa, uint16_t wartosc, uint16_t cena_wywolawcza, uint16_t* czynsze, uint8_t terytorium)
{
    silnik_=silnik;
	id_=licznikPol;
	typ_=typ;
	nazwa_=nazwa;
	wartosc_=wartosc;
	cenaWywolawcza_=cena_wywolawcza;
	terytorium_=terytorium;
	for(uint8_t ii=0;ii<6;ii++)
		czynsze_[ii]=czynsze[ii];
	zastawione_=false;
    wlasciciel_=silnik_->podajBank();
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
        if(podajWlasciciela()!=silnik_->podajBank())
		{
			std::cout<<"To pole należy do gracza "<<wlasciciel_->podajImie()<<"."<<std::endl;
		}
		switch(typ_)
		{
			case STANDARDOWE:
			{
                if(wlasciciel_==silnik_->podajBank()) 	//jeśli niczyje - dać wybór między kupnem a licytacją
				{
				}
				else //jeśli innego gracza pobrać czynsz (z uwzględnieniem kompletności terytoriów oraz liczby lwic)
				{
					uint16_t kwota=czynsze_[0];
					
                    if(silnik_->sprawdz_kompletnosc_terytorium(this))
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
            {
                //gotówkę zwiększa funkcja przesuwająca, więc tu nic się nie dzieje
            }
			break;
			case LATWA_ZDOBYCZ:
			{
                silnik_->pobierzKarte(KARTY_LATWEJ_ZDOBYCZY, gracz);
				//wywołać obsługę Łatwej zdobyczy
			}
			break;
			case DLA_DOBRA_STADA:
            {
				//wywołać obsługę Dla dobra stada
                silnik_->pobierzKarte(KARTY_DLA_DOBRA_STADA, gracz);
			}
			break;
			case POSILEK:
            {
                gracz->zaplac(wartosc_,silnik_->podajBank());
            }
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
            {
                //tu nic się nie dzieje
            }
			break;
			case POGRANICZE:
            {
                //tu nic się nie dzieje
            }
			break;
			case UDAJ_SIE_NA_WYGNANIE:
            {
				gracz->ustawWygnanie(true);
			}
			break;
			case BEZTROSKI_BAOBAB:
            {
				//tu nic się nie dzieje
            }
			break;
			default:
            {
				std::cerr<<"Gracz "<<gracz->podajImie()<<" stanął na nieobsługiwanym polu o id: "<<id_<<"."<<std::endl;
            }
			break;
		}
	}
}

void Pole::wykup()
{
	if(wlasciciel_->podajGotowke()>=(wartosc_*3)/5)
    {
        wlasciciel_->zaplac((wartosc_*3)/5,silnik_->podajBank());
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
        wlasciciel_->zaplac(KOSZT_USTAWIENIA_LWICY,silnik_->podajBank());
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

void Pole::zabierzGracza(Gracz* gracz)
{
    if(czyJestGracz(gracz))
    {
        for (std::list<Gracz*>::const_iterator it = obecniGracze_.begin();it != obecniGracze_.end(); ++it)
        {
            if(*it==gracz)
            {
                obecniGracze_.erase(it);
                it = obecniGracze_.begin();
            }
        }
        std::cout<<"Usunięto gracza "<<gracz->podajImie()<<" z pola "<<podajNazwe()<<std::endl;
    }
}

void Pole::dodajGracza(Gracz* gracz)
{
    if(!czyJestGracz(gracz))
    {
       obecniGracze_.push_back(gracz);
    }
    std::cout<<"Ustawiono gracza "<<gracz->podajImie()<<" na pole "<<podajNazwe()<<std::endl;
}

bool Pole::czyJestGracz(Gracz* gracz)
{
    for (std::list<Gracz*>::const_iterator it = obecniGracze_.begin();it != obecniGracze_.end(); ++it)
    {
        if(*it==gracz)
        {
            std::cout<<"Gracza "<<gracz->podajImie()<<" jest na polu "<<podajNazwe()<<std::endl;
            return true;
        }
    }
    std::cout<<"Nie ma gracza "<<gracz->podajImie()<<" na polu "<<podajNazwe()<<std::endl;
    return false;
}
