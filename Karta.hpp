#ifndef KARTY_HPP_
#define KARTY_HPP_

//Standardowe nagłówki C/C++
#include <cstdint>
#include <list>
#include <string>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"

#define SCIEZKA_DO_DANYCH_KART ((sciezka+"/data/karty.csv").c_str())

class Gracz;
class Pole;

class Karta
{
	private:
		EfektKarty efekty_[3];
		int16_t liczby_[3];
		std::string opis_;
	
	public:
		explicit Karta();
		explicit Karta(EfektKarty* efekty, int16_t* liczby, std::string opis);
		~Karta();
		
		void opisz();
		
		inline std::string podajOpis()const{return opis_;}
		inline EfektKarty podajEfekt(uint8_t ii)const{return efekty_[ii];}
		inline int16_t podajLiczbe(uint8_t ii)const{return liczby_[ii];}
};

void pobierzKarte(TypKarty talia, Gracz* gracz);
void uzyjKarty(Karta karta, Gracz* gracz);

void wczytajKarty(std::string sciezka);
void przetasujKarty(TypKarty talia);

extern std::list<Karta>karty[2];

#endif
