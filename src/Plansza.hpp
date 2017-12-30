#ifndef PLANSZA_HPP
#define PLANSZA_HPP

//Nagłówki z katalogu Qt
#include <QWidget>

//Nagłówki z katalogu QtGui
#include <QtGui/QPixmap>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

//Nagłówki z katalogu programu
#include "Pole.hpp"
#include "Silnik.hpp"

class PoleGraficzne;

class Plansza : public QWidget
{
    Q_OBJECT
    private:
        Silnik* silnik_;
        QGridLayout* glownyRozmieszczacz_;
        PoleGraficzne** pola_;

    public:
        explicit Plansza(Silnik* silnik, QWidget* parent = 0);
        ~Plansza();
        Silnik* podajSilnik(){return silnik_;}
        std::string podajSciezke(){return silnik_->podajSciezke();}
    signals:

    public slots:
};

#endif // PLANSZA_HPP
