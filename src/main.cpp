/*************************************
 * Sawannopoly                       *
 * Autor: IbilisSLZ                  *
 * Wersja: Pre-alfa-9   			 *
 *************************************/

//Standardowe nagłówki C/C++
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtCore/QCoreApplication>
#include <QtCore/QString>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"
#include "Silnik.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	srand (time (NULL));
    QApplication Aplikacja(argc, argv);
	
	std::string sciezka=Aplikacja.applicationDirPath().toStdString();	//Pozyskaj ścieżkę do katalogu pliku wykonywalnego

    Silnik silnik(sciezka);
    silnik.run();
    silnik.wait();

	std::cerr<<"Koniec"<<std::endl;
    
    return Aplikacja.exec();
}

