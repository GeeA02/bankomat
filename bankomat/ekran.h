#pragma once
#include <string>
#include "konto.h"


void rozmiarOkna();
void pozycjaKursora();
void ukryjKursor();
void gotoxy(int, int);
void ramka();
void clean();
int srodekTekstu(int, int);
void wypiszTekst(std::string, int);
void wypiszEnter(int);
void wypiszMenu(std::string);
void kursorMenu(int , int);

void wyswietlStan(float stanKonta);
void koniec();
