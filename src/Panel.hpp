#ifndef PANEL_HPP
#define PANEL_HPP

//Nagłówki z katalogu QtCore
#include <QtCore/QtGlobal>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

//Nagłówki z katalogu programu
#include "Kostka.hpp"

class Panel : public QWidget
{
    private:
        QGridLayout* rozmieszczacz_;
        QPushButton* rzut_koscia_;
        Kostka* Kostki_;
    public:
        Panel();
        ~Panel();

        void ustawKostki(uint8_t k1, uint8_t k2);
};

#endif // PANEL_HPP
