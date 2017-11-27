#ifndef SILNIK_HPP_
#define SILNIK_HPP_

//Standardowe nagłówki C/C++
#include <list>
#include <vector>

//Nagłówki z katalogu QtCore
#include <QtCore/QThread>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"
#include "GlowneOkno.hpp"
#include "Gracz.hpp"
#include "Pole.hpp"
#include "Karta.hpp"
#include "Kostka.hpp"

class Silnik : public QThread
{
    Q_OBJECT

    private:
        TrybyGry tryb_;
        GlowneOkno* glowneOkno_;
        std::string sciezka_;

        Kostka kostki_[2];
        Gracz* gracze_;
        Gracz* bank_;
        std::list<Karta>karty[2];
        std::vector<Pole> pola;

    public:
        Silnik(std::string sciezka);
        ~Silnik();

        void run();

        void wczytajKarty();
        void przetasujKarty(TypKarty talia);
        void pobierzKarte(TypKarty talia, Gracz* gracz);
        void uzyjKarty(Karta karta, Gracz* gracz);


        void utworzPola();
        bool sprawdz_kompletnosc_terytorium(const Pole* const pole);

        inline void ustawKostki(uint8_t k1,uint8_t k2){kostki_[0].ustaw(k1);kostki_[1].ustaw(k2);}
        inline Gracz* podajBank(){return bank_;}
        inline Pole* podajPole(uint8_t polozenie){return &pola[polozenie];}

        uint8_t policzWszystkieZiemie(Gracz *gracz);
        uint8_t policzWszystkieLwice(Gracz *gracz);

    public slots:
        void zmienTryb(TrybyGry tryb);
};

#endif
