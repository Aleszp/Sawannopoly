#ifndef POLEGRAFICZNE_HPP
#define POLEGRAFICZNE_HPP

//Nagłówki z katalogu programu
#include "Plansza.hpp"

class PoleGraficzne : public QWidget
{
    Q_OBJECT
    private:
        Plansza* rodzic_;
        uint8_t id_;

        QLabel* wlasciciel_;
        QPixmap* wlasciciel_map_;

        QLabel* ilustracja_;
        QPixmap* ilustracja_map_;

        QLabel* gracz_[4];
        QPixmap* gracz_map_[4];

    public:
        explicit PoleGraficzne(Plansza* rodzic, uint8_t id_);
        ~PoleGraficzne(){}
        inline Pole* podajPole(){return rodzic_->podajSilnik()->podajPole(id_);}
    signals:

};

#endif // POLEGRAFICZNE_HPP
