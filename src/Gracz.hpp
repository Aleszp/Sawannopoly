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
		uint8_t wygnany_;
		uint8_t licznikDubletu_;
		uint8_t wolneLwice_;
		bool kartaPowrotuZWygnania_;

	public:
		explicit Gracz(std::string imie, uint64_t gotowka);
		~Gracz();
		
		void ruszNKrokow(int8_t n);
		void idzDoPola(uint8_t cel);
		void zabierzPole(uint8_t id, Gracz* nowyWlasciciel);
		void dajPole(uint8_t id);
		void ustawWygnanie(bool wygnany);
		void rzutKoscia();
		void zaplac(uint16_t kwota, Gracz* komu);
		void bankrutuj_na_rzecz(Gracz* komu);
		void zabierzLwice(uint8_t ile);
		
		uint8_t policzWszystkieLwice();
		uint8_t policzWszystkieZiemie();
		bool wymusGotowke(uint16_t kwota);
		bool wymusLwice(uint8_t ile);
		bool czyMaPole(uint8_t id);

		inline uint8_t podajLiczbeWolnychLwic(){return wolneLwice_;}
		inline uint8_t podajPolozenie()const{return polozenie_;}
		inline uint8_t podajWygnanie()const{return wygnany_;}
		inline uint64_t podajGotowke()const{return gotowka_;}
		inline std::string podajImie()const{return imie_;}
		
		inline void obnizWygnanie(){wygnany_--; if(wygnany_==0) ustawWygnanie(false);}
		inline void dodajGotowke(int16_t kwota){gotowka_+=kwota;}
		inline void dodajLwice(uint8_t ile){wolneLwice_+=ile;}
		inline void ustawKartePowrotu(bool stan){kartaPowrotuZWygnania_=stan;}
};

#endif