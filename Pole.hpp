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

//Deklaracja istnienia klasy Gracz
class Gracz;

class Pole
{
    private:
		TypPola typ_;
		std::string nazwa_;
		uint16_t* czynsze_;	//wysokości opłat gdy gracz ma: 1 pole z dzielnicy, wszystkie pola z dzielnicy, jedną lwicę, dwie lwice, trzy lwice, cztery lwice
		uint8_t lwice;
		uint8_t id_;
		bool zastawione_;
		Gracz* wlasciciel_;
		std::list<Gracz*> obecniGracze_;	//lista wskaźników na aktualnie stojących tu graczy
		
	public:
		explicit Pole();
		explicit Pole(TypPola typ, std::string nazwa, uint16_t* czynsze);
		~Pole();
		
		inline uint8_t podajId(){return id_;}
		
};


extern uint8_t licznikPol;
extern std::vector<Pole> pola;

void utworzPola();

#endif
