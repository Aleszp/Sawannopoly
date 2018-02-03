#include "Kostka.hpp"

//Nagłówki z katalogu QtWidgets
#include <QtCore/QString>
#include <QtCore/QVariant>

Kostka::Kostka()
{
    wartosc_=1;
    setText("1");
}

void Kostka::ustaw(uint8_t wartosc)
{
    wartosc_=wartosc;
    setText(QVariant(wartosc).toString());
}
