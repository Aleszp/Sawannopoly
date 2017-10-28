/*************************************
 * Sawannopoly                       *
 * Autor: IbilisSLZ                  *
 * Wersja: DEV2.9					 *
 *************************************/

//Standardowe nagłówki C/C++
#include <iostream>
#include <cstdlib>
#include <ctime>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

//Nagłówki z katalogu programu
#include "GlowneOkno.hpp"
#include "TypyWyliczeniowe.hpp"
#include "Pole.hpp"
#include "Gracz.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	srand (time (NULL));
	
	utworzPola();
	QApplication Aplikacja(argc, argv);
	GlowneOkno Okno;
    
    Gracz test("Test", 150);
    Gracz test2("Królowa", 150);
    
    pola[8].ustawWlasciciela(&test);
    pola[9].ustawWlasciciela(&test2);
    
    pola[1].ustawWlasciciela(&test2);
    pola[3].ustawLwice(1);
    pola[3].ustawWlasciciela(&test2);
    pola[13].ustawWlasciciela(&test2);
    for(uint8_t ii=0;ii<255;ii++)
    {
		if(test.podajWygnanie())
		{
			test.obnizWygnanie();
			std::cout<<"Gracz "<<test.podajImie()<<" jest na wygnaniu."<<std::endl;
			continue;
		}
		test.rzutKoscia();
	}
	
	std::cerr<<"Koniec"<<std::endl;
    
    return 0; //Aplikacja.exec();
}

