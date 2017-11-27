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

        QVBoxLayout* glownyRozmieszczacz_;
        QWidget* okno_;
        Silnik* silnik_;
        WyborTrybu* wybor_;

        QLabel* image_;
        QPixmap* mypix_;

		void setupOkno(void);

	public:
        explicit GlowneOkno(Silnik* silnik,std::string sciezka, QWidget* parent = nullptr);
		~GlowneOkno();
        void wlaczMenuGlowne();
        void wlaczGoraceKrzeslo();

        inline void ustawTryb(TrybyGry tryb){tryb_=tryb;}
		
	//public slots:


};

#endif

