#ifndef KOSTKA_HPP
#define KOSTKA_HPP

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QLabel>

//Standardowe nagłówki C/C++
#include <cstdint>

class Kostka : public QLabel
{
    private:
        uint8_t wartosc_;
    public:
        Kostka();
        void ustaw(uint8_t wartosc);
};

#endif // KOSTKA_HPP
