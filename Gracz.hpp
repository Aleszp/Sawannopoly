#ifndef GRACZ_HPP_
#define GRACZ_HPP_

//Standardowe nagłówki C/C++
#include <cstdint>
#include <cstdbool>
#include <list>
#include <string>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"

class Pole;

class Gracz
{
    private:
		std::string imie_;
		uint64_t gotowka_;
		uint8_t polozenie_;
		std::list<uint8_t> nieruchomosci_;
		uint8_t wygnany_;
		uint8_t licznikDubletu_;

	public:
		explicit Gracz();
		explicit Gracz(std::string imie, uint64_t gotowka);
		~Gracz();
		
		void rusz_o_n_krokow(int8_t n);
		void idz_do_pola(uint8_t cel);
		void zabierzPole(uint8_t id);
		void dajPole(uint8_t id);
		void zaplac(uint16_t kwota);
		void ustawWygnanie(bool wygnany);
		void rzutKoscia();
		
		bool czyMaPole(uint8_t id);
		
		inline uint8_t gdzieJest(){return polozenie_;}
		inline std::string podajImie(){return imie_;}
		inline uint8_t podajWygnanie(){return wygnany_;}
		inline void obnizWygnanie(){wygnany_--; if(wygnany_==0) ustawWygnanie(false);}
};

#endif
