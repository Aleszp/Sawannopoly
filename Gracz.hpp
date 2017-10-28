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
		uint8_t wolne_lwice_;
		bool karta_powrotu_z_wygnania_;

	public:
		explicit Gracz(std::string imie, uint64_t gotowka);
		~Gracz();
		
		void rusz_o_n_krokow(int8_t n);
		void idz_do_pola(uint8_t cel);
		void zabierzPole(uint8_t id);
		void dajPole(uint8_t id);
		void ustawWygnanie(bool wygnany);
		void rzutKoscia();
		void zaplac(uint16_t kwota, Gracz* komu);
		void bankrutuj_na_rzecz(Gracz* komu);
		
		bool wymus_gotowke(uint16_t kwota);
		bool czyMaPole(uint8_t id);

		inline uint8_t podajLiczbeWolnychLwic(){return wolne_lwice_;}
		inline uint8_t gdzieJest()const{return polozenie_;}
		inline uint8_t podajWygnanie()const{return wygnany_;}
		inline uint8_t podajGotowke()const{return gotowka_;}
		inline std::string podajImie()const{return imie_;}
		
		inline void obnizWygnanie(){wygnany_--; if(wygnany_==0) ustawWygnanie(false);}
		inline void dodajGotowke(int16_t kwota){gotowka_+=kwota;}
		inline void dodajLwice(int8_t ile){wolne_lwice_+=ile;}
};

#endif
