#ifndef TYPY_WYLICZENIOWE_HPP_
#define TYPY_WYLICZENIOWE_HPP_

enum KodyWyjsciowe {OK=0};
enum StanyMaszyny {NORMALNY_RUCH=0, WYMUS_GOTOWKE, WYMUS_LWICE};
enum TypPola {STANDARDOWE=0, START=1, LATWA_ZDOBYCZ=2, DLA_DOBRA_STADA=3, POSILEK=4, UZYTECZNOSC=5, GRANICA=6, WYGNANIE=7, POGRANICZE=8, UDAJ_SIE_NA_WYGNANIE=9, BEZTROSKI_BAOBAB=10};
enum TypKarty {KARTY_LATWEJ_ZDOBYCZY=0, KARTY_DLA_DOBRA_STADA=1};
enum EfektKarty {BRAK_EFEKTU=0, ZMIANA_GOTOWKI=1, ZMIANA_LICZBY_LWIC=2, PRZESUN=3, WYGNAJ=4, KARTA_POWROTU_Z_WYGNANIA=5};

#endif

