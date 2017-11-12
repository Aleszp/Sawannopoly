#ifndef GLOWNE_OKNO_HPP_
#define GLOWNE_OKNO_HPP_

//Nagłówki z katalogu QtCore
#include <QtCore/QtGlobal>
#include <QtCore/QVector>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

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
		
		void setupOkno(void);

	public:
        explicit GlowneOkno(QWidget* parent = nullptr);
		~GlowneOkno();
		
		
	//public slots:
		
};

#endif

