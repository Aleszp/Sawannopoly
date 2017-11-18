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

namespace Ui 
{
	class GlowneOkno;
}

class GlowneOkno : public QMainWindow
{
    Q_OBJECT
    
    private:
		Ui::GlowneOkno *ui;
		QWidget* okno_;
        TrybyGry tryb_;
        QVBoxLayout* glownyRozmieszczacz_;
        std::string sciezka_;
        QLabel* image_;
        QPixmap* mypix_;

		void setupOkno(void);

	public:
        explicit GlowneOkno(std::string sciezka, QWidget* parent = nullptr);
		~GlowneOkno();
		
		
	//public slots:
		
};

#endif

