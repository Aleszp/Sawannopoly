//Standardowe nagłówki C/C++
#include <iostream>

//Nagłówki z katalogu programu
#include "Silnik.hpp"
#include "inne.hpp"

Silnik::Silnik(std::string sciezka)
{
    sciezka_=sciezka;

    glowneOkno_= new GlowneOkno(this, sciezka_);
    bank_=new Pionek(this,"Bank", UINT64_MAX/2);
    utworzPola();
    wczytajKarty();

    zmienTryb(BRAK_TRYBU);
}

Silnik::~Silnik()
{
    delete bank_;
}

void Silnik::run()
{
    Pionek test(this,"Test",1000);

    for(uint8_t ii=0;ii<10;ii++)
    {
        std::cout<<(uint16_t)ii<<": ";
        if(test.podajWygnanie())
        {
            test.obnizWygnanie();
            std::cout<<"Pionek "<<test.podajImie()<<" jest na wygnaniu."<<std::endl;
            continue;
        }
        test.rzutKoscia();
    }
}

void Silnik::pobierzKarte(TypKarty talia, Pionek* Pionek)
{
    Karta karta=karty[talia].front();	//pobierz kartę z początku
    karty[talia].pop_front();

    std::cout<<"Pobrana karta: "<<karta.podajOpis()<<std::endl;

    uzyjKarty(karta, Pionek);

    std::cout<<"Odkładam na koniec kartę: "<<karta.podajOpis()<<std::endl;

    karty[talia].push_back(karta);	//umieść kartę na sam koniec listy
}

void Silnik::uzyjKarty(Karta karta, Pionek* Pionek)
{
    //tu umieść interpreter (z trzema iteracjami)

    for(uint8_t ii=0;ii<3;ii++)
    {
        switch(karta.podajEfekt(ii))
        {
            case BRAK_EFEKTU:
                //Nie rób nic
            break;
            case ZMIANA_GOTOWKI:
                if(karta.podajLiczbe(ii)>0)
                    Pionek->dodajGotowke(karta.podajLiczbe(ii));
                else
                    Pionek->zaplac((-1)*karta.podajLiczbe(ii),bank_);	//zmiana liczby z ujemnej na dodatnią, bo metoda zaplac pracuje na liczbach dodatnich (liczba ujemna traktowana jest jak bardzo duża liczba dodatnia ze względu na sposób reprezentacji liczb całkowitych
            break;
            case ZMIANA_LICZBY_LWIC:
                    if(karta.podajLiczbe(ii)>0)
                        Pionek->dodajLwice(karta.podajLiczbe(ii));
                    else
                        Pionek->zabierzLwice((-1)*karta.podajLiczbe(ii));	//zmiana liczby z ujemnej na dodatnią, bo metoda zaplac pracuje na liczbach dodatnich (liczba ujemna traktowana jest jak bardzo duża liczba dodatnia ze względu na sposób reprezentacji liczb całkowitych

            break;
            case PRZESUN:
                Pionek->ruszNKrokow(karta.podajLiczbe(ii)-Pionek->podajPolozenie());
            break;
            case WYGNAJ:
                Pionek->ustawWygnanie(true);
            break;
            case KARTA_POWROTU_Z_WYGNANIA:
                Pionek->ustawKartePowrotu(true);
            break;
            case GLOD:
                if(karta.podajLiczbe(ii)>0)
                    Pionek->zaplac((uint16_t)(Pionek->policzWszystkieLwice()*karta.podajLiczbe(ii)),bank_);
                else
                    Pionek->dodajGotowke((uint16_t)(Pionek->policzWszystkieLwice()*karta.podajLiczbe(ii)));
            break;
            case KOSZT_ZIEM:
                if(karta.podajLiczbe(ii)>0)
                    Pionek->zaplac((uint16_t)(Pionek->policzWszystkieZiemie()*karta.podajLiczbe(ii)),bank_);
                else
                    Pionek->dodajGotowke((uint16_t)(Pionek->policzWszystkieZiemie()*karta.podajLiczbe(ii)));
            break;
            default:
                std::cerr<<"Nieprawidłowy efekt karty."<<std::endl;
            break;
        }
    }
}

void Silnik::wczytajKarty()
{
    FILE* daneKart=fopen(((sciezka_+"/data/karty.csv").c_str()),"r");

    //sprawdź czy istnieje plik
    if(daneKart==NULL)
    {
        fprintf(stderr,"Błąd otwarcie pliku bazy danych kart.\n");
        fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",((sciezka_+"/data/karty.csv").c_str()));
        exit(BRAK_DANYCH_KART);
    }

    char tmp[1024];
    std::string tmpString;
    TypKarty tmpTyp;
    EfektKarty tmpEfekty[3];
    int16_t tmpLiczby[3];
    std::string tmpOpis;

    //dane w formacie: TypKarty, dla i=0..2 (Efekt[i], Liczba[i]), opis
    while(!feof(daneKart))
    {
        //tu odczyt danych o karcie
        fgets(tmp,1024,daneKart);
        if(tmp[0]=='#')	//jeśli linijka stanowi komentarz
            continue;

        tmpString=wytnij(tmp);
        tmpTyp=static_cast<TypKarty>(atoi(tmpString.c_str()));

        for(uint8_t ii=0;ii<3;ii++)
        {
            tmpString=wytnij(tmp);
            tmpEfekty[ii]=static_cast<EfektKarty>(atoi(tmpString.c_str()));
            tmpString=wytnij(tmp);
            tmpLiczby[ii]=atoi(tmpString.c_str());
        }
        tmpOpis=tmp;
        karty[tmpTyp].push_back(Karta(tmpEfekty,tmpLiczby,tmpOpis));
    }
    przetasujKarty(KARTY_LATWEJ_ZDOBYCZY);
    przetasujKarty(KARTY_DLA_DOBRA_STADA);

    fclose(daneKart);
}

void Silnik::przetasujKarty(TypKarty talia)
{
    std::list<Karta>tmp_talia(karty[talia]);

    karty[talia].clear();

    auto iterator = tmp_talia.begin();
    uint16_t ii=0;

    while(tmp_talia.size()>0)
    {
        ii=rand()%(tmp_talia.size());

        iterator = tmp_talia.begin();
        std::advance(iterator, ii);

        karty[talia].push_back(*iterator);
        tmp_talia.erase(iterator);
    }
}

/*********************************************************************/

void Silnik::utworzPola()
{
    FILE* danePol=fopen(((sciezka_+"/data/pola.csv").c_str()),"r");

    //sprawdź czy istnieje plik
    if(danePol==NULL)
    {
        fprintf(stderr,"Błąd otwarcie pliku bazy danych nieruchomości.\n");
        fprintf(stderr,"Sprawdź, czy plik %s istnieje.\n",((sciezka_+"/data/pola.csv").c_str()));
        exit(BRAK_DANYCH_POL);
    }

    char tmp[128];
    std::string tmpString;

    TypPola tmpTyp=static_cast<TypPola>(0);
    char tmpNazwa[64];
    uint16_t tmpWartosc;
    uint16_t tmpCenaWywolawcza;
    uint8_t tmpTerytorium;
    uint16_t tmpCzynsze[6];
    //Wczytaj dane w formacie: TypPola, Nazwa pola, Wartość, Cena wywoławcza, czynsze[0-6]
    while(licznikPol<41)
    {
        if(feof(danePol))
        {
            fprintf(stderr,"Niekompletna tablica danych o nieruchomościach.\n");
            fprintf(stderr,"Sprawdź, czy plik %s jest kompletny.\n",((sciezka_+"/data/pola.csv").c_str()));

            fclose(danePol);
            exit(NIEKOMPLETNE_DANE_POL);
        }

        fgets(tmp,128,danePol);
        if(tmp[0]=='#')	//jeśli linijka stanowi komentarz
            continue;

        tmpString=wytnij(tmp);
        tmpTyp=static_cast<TypPola>(atoi(tmpString.c_str()));
        tmpString=wytnij(tmp);
        strcpy(tmpNazwa, tmpString.c_str());

        tmpString=wytnij(tmp);
        tmpWartosc=atoi(tmpString.c_str());

        tmpString=wytnij(tmp);
        tmpCenaWywolawcza=atoi(tmpString.c_str());

        tmpString=wytnij(tmp);
        tmpTerytorium=atoi(tmpString.c_str());

        for(uint8_t ii=0;ii<6;ii++)
        {
            tmpString=wytnij(tmp);
            tmpCzynsze[ii]=atoi(tmpString.c_str());
        }

        pola_.push_back(Pole(this,tmpTyp, tmpNazwa, tmpWartosc, tmpCenaWywolawcza, tmpCzynsze,tmpTerytorium));
    }


    fclose(danePol);
}

bool Silnik::sprawdz_kompletnosc_terytorium(const Pole* const  pole)
{
    for(uint8_t ii=0;ii<40;ii++)
    {
        if(pola_[ii].podajTerytorium()==pole->podajTerytorium())
        {
            if(pola_[ii].podajWlasciciela()!=pole->podajWlasciciela())
            {
                return false;
            }
        }
    }
    return true;
}

uint8_t Silnik::policzWszystkieLwice(Pionek* Pionek)
{
    uint8_t liczbaLwic=Pionek->podajLiczbeWolnychLwic();

    for (std::vector<Pole>::const_iterator it = pola_.begin();it != pola_.end(); ++it)
    {
        if(it->podajWlasciciela()==Pionek)
            liczbaLwic+=it->podajLiczbeLwic();
    }
    return liczbaLwic;
}

void Silnik::zmienTryb(TrybyGry tryb)
{
    //Posprzątaj
    switch(tryb_)
    {
        case BRAK_TRYBU:
            //nie rób nic
        break;
        case GORACE_KRZESLO:
            //sprzątnij tryb gorącego krzesła
        break;
        default:
            //nie rób nic
        break;
    }

    tryb_=tryb;
    glowneOkno_->ustawTryb(tryb_);
    switch(tryb_)
    {
        case BRAK_TRYBU:
            glowneOkno_->wlaczMenuGlowne();
        break;
        case GORACE_KRZESLO:
            glowneOkno_->wlaczGoraceKrzeslo();
        break;
        default:
            glowneOkno_->wlaczMenuGlowne();
        break;
    }
}

uint8_t Silnik::policzWszystkieZiemie(Pionek* Pionek)
{
    uint8_t liczbaPol=0;

    for (std::vector<Pole>::const_iterator it = pola_.begin();it != pola_.end(); ++it)
    {
        if(it->podajWlasciciela()==Pionek)
            liczbaPol++;
    }
    return liczbaPol;
}
