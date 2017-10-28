#ifndef KARTY_HPP_
#define KARTY_HPP_

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"

class Gracz;
class Pole;

class Karta
{
	TypyKart typ_;
	
};

void losujKarte(Karta* talia, Gracz* gracz);

//extern Karta* karty[2];

#endif
