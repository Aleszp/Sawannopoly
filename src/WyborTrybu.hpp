#ifndef WYBOR_TRYBU_HPP_
#define WYBOR_TRYBU_HPP_

//Nagłówki z katalogu QtCore
#include <QtCore/QtGlobal>
#include <QtCore/QVector>
#include <QtCore/QEventLoop>

//Nagłówki z katalogu QtWidgets
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>

//Nagłówki z katalogu programu
#include "TypyWyliczeniowe.hpp"

namespace Ui 
{
    class WyborTrybu;
}

class WyborTrybu : public QWidget
{
    Q_OBJECT
    
    private:
        Ui::WyborTrybu *ui;
        QVBoxLayout* rozmieszczacz_;
        QPushButton* gorace_krzeslo_;
        QEventLoop* loop_;
        TrybyGry tryb_;
		
        void setupWybor(void);

	public:
        explicit WyborTrybu(QWidget* parent = nullptr);
        ~WyborTrybu();
        inline TrybyGry podajTrybGry()const{return tryb_;}
        TrybyGry exec();
		
		
    public slots:
        void trybGorocegoKrzesla(bool a);
};

#endif

