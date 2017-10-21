/*************************************
 * Sawannopoly                       *
 * Autor: IbilisSLZ                  *
 * Wersja: DEV1.2					 *
 *************************************/

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
	utworzPola();
	QApplication Aplikacja(argc, argv);
	GlowneOkno Okno;
    
    Gracz test("Test", 150);
    for(uint8_t ii=0;ii<255;ii++)
		test.rusz_o_n_krokow(1);
    
    return Aplikacja.exec();
}

