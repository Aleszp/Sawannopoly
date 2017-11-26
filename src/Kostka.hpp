#ifndef KOSTKA_HPP
#define KOSTKA_HPP

//Standardowe nagłówki C/C++
#include <cstdint>

class Kostka
{
    private:
        uint8_t wartosc_;
    public:
        Kostka();
        void ustaw(uint8_t wartosc);
};

#endif // KOSTKA_HPP
