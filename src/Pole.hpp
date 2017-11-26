#ifndef POLE_HPP_
#define POLE_HPP_

//Standardowe nagłówki C/C++
#include <cstdint>
#include <cstdbool>
#include <string>
#include <list>
#include <vector>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"
#include "Gracz.hpp"

class Silnik;

const uint8_t KOSZT_USTAWIENIA_LWICY=15;

//Deklaracja istnienia klasy Gracz

class Pole
{
    private:
		TypPola typ_;
		std::string nazwa_;
		uint16_t wartosc_;
		uint16_t cenaWywolawcza_;
		uint16_t czynsze_[6];	//wysokości opłat gdy gracz ma: 1 pole z dzielnicy, wszystkie pola z dzielnicy, jedną lwicę, dwie lwice, trzy lwice, cztery lwice
		uint8_t lwice;
		uint8_t id_;
		uint8_t terytorium_;
		uint8_t lwice_;
		bool zastawione_;
		Gracz* wlasciciel_;
		std::list<Gracz*> obecniGracze_;	//lista wskaźników na aktualnie stojących tu graczy
        Silnik* silnik_;
		
	public:
        explicit Pole();
        explicit Pole(Silnik* silnik,TypPola typ, std::string nazwa, uint16_t wartosc, uint16_t cena_wywolawcza, uint16_t* czynsze, uint8_t terytorium);
		~Pole();
		
		void akcja(Gracz* gracz);
		void pozyskajLwice();
		void zwolnijLwice();
		void dodajLwice();
		void odejmijLwice();
		void wykup();
		void zastaw();
		
		bool czyMoznaDodacLwice();
		
		inline uint8_t podajId()const{return id_;}
		inline uint8_t podajLiczbeLwic()const{return lwice_;}
		inline uint8_t podajTerytorium()const{return terytorium_;}
		inline uint16_t podajWartosc()const{return wartosc_;}
		inline uint16_t podajCeneWywolawcza()const{return cenaWywolawcza_;}
		inline uint16_t podajCzynsz(uint8_t ktory=0)const{return czynsze_[ktory];}
		inline std::string podajNazwe()const{return nazwa_;}
		inline Gracz* podajWlasciciela()const{return wlasciciel_;}
		inline bool podajZastawione()const{return zastawione_;}
		
		inline void ustawWlasciciela(Gracz* wlasciciel){wlasciciel_=wlasciciel;}
		inline void ustawLwice(uint8_t lwice){lwice_=lwice;}
		friend std::ostream& operator<<(std::ostream&, Pole&);
};


extern uint8_t licznikPol;


#endif
