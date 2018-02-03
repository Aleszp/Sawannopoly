#ifndef GLOWNE_OKNO_HPP_
#define GLOWNE_OKNO_HPP_

//Nagłówki z katalogu QtCore
#include <QtCore/QtGlobal>
#include <QtCore/QVector>

//Nagłówki z katalogu QtGui
#include <QtGui/QPixmap>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"
#include "WyborTrybu.hpp"
#include "Panel.hpp"

class Plansza;

namespace Ui 
{
	class GlowneOkno;
}

class Silnik;

class GlowneOkno : public QMainWindow
{
    Q_OBJECT
    
    private:
		Ui::GlowneOkno *ui;
        TrybyGry tryb_;
        std::string sciezka_;

        QBoxLayout* rozmieszczacz_;
        QWidget* okno_;
        Silnik* silnik_;
        WyborTrybu* wybor_;

        QLabel* image_;
        QPixmap* mypix_;

        Plansza* plansza_;
        Panel* panel_;

		void setupOkno(void);

	public:
        explicit GlowneOkno(Silnik* silnik,std::string sciezka, QWidget* parent = nullptr);
		~GlowneOkno();
        void wlaczMenuGlowne();
        void wlaczGoraceKrzeslo();

        inline void ustawKostki(uint8_t k1,uint8_t k2){panel_->ustawKostki(k1,k2);}
        inline void ustawTryb(TrybyGry tryb){tryb_=tryb;}
        inline std::string podajSciezke(){return sciezka_;}

		
	//public slots:


};

#endif

