#ifndef KARTY_HPP_
#define KARTY_HPP_

//Standardowe nagłówki C/C++
#include <cstdint>
#include <list>
#include <string>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"

#define SCIEZKA_DO_DANYCH_KART "/home/aleszp/Documents/programowanie/C++/Sawannopoly/karty.csv"

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
};

void losujKarte(TypyKart talia, Gracz* gracz);
void uzyjKarty(Karta karta, Gracz* gracz);

void wczytajKarty();

extern std::list<Karta>karty[2];

#endif
