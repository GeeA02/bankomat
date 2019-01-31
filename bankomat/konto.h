#pragma once
#include <string>
#include "ekran.h"

struct konto {
	unsigned int pin;
	float stanKonta;
	std::string imie;
	std::string nazwisko;
	konto* nastepna = nullptr;
};

extern struct konta {
	konto* pierwsze=nullptr;
	void wczytaj();
	int aktualizacja(konto*);
	void wyswietl();
	konto* poprawnyPin(unsigned int );
} listaKont;



void start();
void startMenu();
bool wyplata(konto* , unsigned int );
bool wplata(konto*, unsigned int);
bool wpisywanieKwoty(unsigned int, bool*, bool*);
void wyplataEkran();
void wplataEkran();