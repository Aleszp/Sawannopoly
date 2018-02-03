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
#include "Pionek.hpp"
#include "Pole.hpp"
#include "Karta.hpp"

class Silnik : public QThread
{
    Q_OBJECT

    private:
        TrybyGry tryb_;
        GlowneOkno* glowneOkno_;
        std::string sciezka_;

        Pionek* pionki_;
        Pionek* bank_;
        std::list<Karta>karty[2];
        std::vector<Pole> pola_;

    public:
        Silnik(std::string sciezka);
        ~Silnik();

        void run();

        void wczytajKarty();
        void przetasujKarty(TypKarty talia);
        void pobierzKarte(TypKarty talia, Pionek* Pionek);
        void uzyjKarty(Karta karta, Pionek* Pionek);

        void utworzPola();
        bool sprawdz_kompletnosc_terytorium(const Pole* const pole);

        inline void ustawKostki(uint8_t k1,uint8_t k2){glowneOkno_->ustawKostki(k1,k2);}
        inline Pionek* podajBank(){return bank_;}
        inline Pole* podajPole(uint8_t polozenie){return &pola_[polozenie];}
        inline std::string podajSciezke(){return glowneOkno_->podajSciezke();}

        uint8_t policzWszystkieZiemie(Pionek *Pionek);
        uint8_t policzWszystkieLwice(Pionek *Pionek);

    public slots:
        void zmienTryb(TrybyGry tryb);
};

#endif
