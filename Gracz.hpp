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
		uint8_t polozenie_;
		std::list<uint8_t> nieruchomosci_;	//lista wskaźników, każde pole jest obiektem

	public:
		explicit Gracz();
		explicit Gracz(std::string imie, uint64_t gotowka);
		~Gracz();
		
		void rusz_o_n_krokow(int8_t n);
		void idz_do_pola(uint8_t cel);
		void zabierzPole(uint8_t id);
		void dajPole(uint8_t id);
};

#endif
