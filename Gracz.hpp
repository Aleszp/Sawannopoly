#ifndef GRACZ_HPP_
#define GRACZ_HPP_

//Standardowe nagłówki C/C++
#include <cstdint>
#include <list>
#include <string>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"
#include "Pole.hpp"

class Gracz
{
    private:
		std::string imie_;
		uint64_t gotowka_;
		Pole* polozenie_;
		std::list<Pole*> nieruchomosci_;	//lista wskaźników, każde pole jest obiektem

	public:
		explicit Gracz();
		explicit Gracz(std::string imie, uint64_t gotowka);
		~Gracz();
		void rusz_o_n_krokow(int8_t n);
		void idz_do_pola(Pole* cel);
};

#endif
