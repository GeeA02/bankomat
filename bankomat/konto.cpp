#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "konto.h"

using namespace std;


konta listaKont;
konto* dane;
unsigned int tmpPin;
bool operacja;
bool menu = true;

bool konta::wczytaj()
{
	ifstream dane;
	dane.open("dane.txt");
	if (dane.good())
	{
		if(listaKont.pierwsze==nullptr)
			listaKont.pierwsze = new konto;
		string tmpDane;
		konto* tmpKonta = listaKont.pierwsze;
		dane >> tmpDane;
		tmpKonta->pin = atoi(tmpDane.c_str());
		dane >> tmpDane;
		tmpKonta->stanKonta = stof(tmpDane);
		dane >> tmpKonta->imie;
		dane >> tmpKonta->nazwisko;
		while (!dane.eof())
		{
			tmpKonta->nastepna = new konto;
			tmpKonta = tmpKonta->nastepna;
			dane >> tmpDane;
			tmpKonta->pin = atoi(tmpDane.c_str());
			dane >> tmpDane;
			tmpKonta->stanKonta=stof(tmpDane);
			dane >> tmpKonta->imie;
			dane >> tmpKonta->nazwisko;
		}
		dane.close();
		return true;
	}
	else
	{
		cout << "Nie udalo sie poprawnie zaladowac pliku. Nacisnij klawisz aby kontynuowac...";
		getchar();
		return false;
	}
}


int konta::aktualizacja(konto* tmpDane)
{
	ofstream dane;
	dane.open("dane.txt", ios::trunc);
	if (dane.good())
	{
		konto* tmpKonta = listaKont.pierwsze;
		dane <<  tmpKonta->pin << " " << tmpKonta->stanKonta << " " << tmpKonta->imie << " " << tmpKonta->nazwisko;
		tmpKonta = tmpKonta->nastepna;
		while (tmpKonta != nullptr)
		{
			dane << endl << tmpKonta->pin << " " << tmpKonta->stanKonta << " " << tmpKonta->imie << " " << tmpKonta->nazwisko;
			tmpKonta = tmpKonta->nastepna;
		}

	}
	else
	{
		cout << "Nie udalo sie poprawnie zaladowac pliku. Nacisnij klawisz aby kontynuowac...";
		getchar();
	}
	dane.close();
	return 0;
}

 konto* konta::poprawnyPin(unsigned int PIN)
{
	konto* tmpKonta = listaKont.pierwsze;
	while (tmpKonta != nullptr)
	{
		if (PIN == tmpKonta->pin)
		{
			return tmpKonta;
		}
		tmpKonta = tmpKonta->nastepna;
	}
	return nullptr;
}


void konta::wyswietl()
{
	konto* tmpKonta = listaKont.pierwsze;
	while (tmpKonta != nullptr)
	{
		cout << tmpKonta->imie << " " << tmpKonta->nazwisko << " " << tmpKonta->stanKonta << " " << tmpKonta->pin << endl;
		tmpKonta = tmpKonta->nastepna;
	}

}

bool wyplata(konto* dane, unsigned int kwota)
{
	if (dane->stanKonta > kwota && (kwota % 20 == 0 || kwota % 50 == 0) && kwota != 0)
	{
		dane->stanKonta -= kwota;
		listaKont.aktualizacja(dane);
		return true;
	}
	else
		return false;
}

bool wplata(konto* dane, unsigned int kwota)
{
	if ((kwota % 20 == 0 || kwota % 50 == 0) && kwota != 0) 
	{
		dane->stanKonta += kwota;
		listaKont.aktualizacja(dane);
		return true;
	}
	else
		return false;
}


void start()
{
	rozmiarOkna();
	ukryjKursor();
	pozycjaKursora();
	ramka();
	if (listaKont.wczytaj())
	{

		bool czyPoprawnyPin;
		string podajPin = "Podaj pin: ";
		string niePoprawny = "Niepoprwany pin. Sprobuj ponownie. ";

		do {
			wypiszTekst(podajPin, 1);
			cin >> tmpPin;
			dane = listaKont.poprawnyPin(tmpPin);
			if (dane != nullptr)
			{
				czyPoprawnyPin = true;
			}
			else
			{
				clean();
				wypiszTekst(niePoprawny, 0);
			}
			cin.clear();
			cin.ignore(1000, '\n');
		} while (tmpPin < 1000 || tmpPin > 9999 || dane == nullptr);

		clean();
		startMenu();
	}
}

void startMenu()
{
	wypiszMenu(dane->imie);

	int wybor = 2;
	int poprzedniWybor = 2;
	int poczatekMenu = 2;
	int iloscMenu = 5;

	while (menu)
	{
		kursorMenu(poprzedniWybor, wybor);

		switch (_getch())
		{
		case 80:
			poprzedniWybor = wybor;
			if (wybor < iloscMenu)
				wybor++;
			else
				wybor = poczatekMenu;
			break;

		case 72:
			poprzedniWybor = wybor;
			if (wybor > poczatekMenu)
				wybor--;
			else
				wybor = iloscMenu;
			break;

		case 13:
			switch (wybor)
			{
			case 2:
				wyswietlStan(dane->stanKonta);
				wypiszMenu(dane->imie);
				break;
			case 3:
				wyplataEkran();
				wypiszMenu(dane->imie);
				break;
			case 4:
				wplataEkran();
				wypiszMenu(dane->imie);
				break;
			case 5:
				menu = false;
				koniec();
				break;
			}
			break;
		}
	}
}


bool wpisywanieKwoty(unsigned int kwota, bool *operacja, bool *powrot)
{
	string tmpKwota{};

	bool menu = true;
	while (menu)
	{
		switch (_getch())
		{
		case 48:
			cout << "0";
			tmpKwota += "0";
			break;
		case 49:
			cout << "1";
			tmpKwota += "1";
			break;
		case 50:
			cout << "2";
			tmpKwota += "2";
			break;
		case 51:
			cout << "3";
			tmpKwota += "3";
			break;
		case 52:
			cout << "4";
			tmpKwota += "4";
			break;
		case 53:
			cout << "5";
			tmpKwota += "5";
			break;
		case 54:
			cout << "6";
			tmpKwota += "6";
			break;
		case 55:
			cout << "7";
			tmpKwota += "7";
			break;
		case 56:
			cout << "8";
			tmpKwota += "8";
			break;
		case 57:
			cout << "9";
			tmpKwota += "9";
			break;
		case 8:
			if (tmpKwota.length() > 0)
			{
				tmpKwota.resize(tmpKwota.length() - 1);
				clean();
				wypiszTekst("Wyplata", 0);
				wypiszTekst("[Esc] [Enter]", 4);
				wypiszTekst("Kwota: ", 2);
				cout << tmpKwota;
			}
			break;
		case 27:
			*powrot = true;
			return true;
		case 13:
			if (tmpKwota.length() > 0 && tmpKwota.length() < 11)
			{
				kwota = stoi(tmpKwota);
				if (*operacja == true)
					return wyplata(dane, kwota);
				else
					return wplata(dane, kwota);
			}
			else
				return false;
		}
	}
}

void wyplataEkran()
{
	bool czyWyplata{};
	bool czyPowrot = false;
	operacja = true;
	do {
		clean();

		wypiszTekst("Wplata", 0);
		wypiszTekst("[Esc] [Enter]", 4);
		wypiszTekst("Kwota: ", 2);
		unsigned int kwota{};
		czyWyplata = wpisywanieKwoty(kwota, &operacja, &czyPowrot);
		if (czyWyplata == false)
		{
			kwota = 0;
			clean();
			wypiszTekst("Prosze, wprowadzic wielokrotnosc 20 lub 50.", 1);
			wypiszEnter(2);
		}
	} while (!czyWyplata);

	if (!czyPowrot)
	{
		clean();
		wypiszTekst("Usluga zostala wykonana pomyslnie", 1);
		wypiszEnter(2);
	}
}



void wplataEkran()
{
	bool czyWplata;
	bool czyPowrot = false;
	operacja = false;
	do
	{
		clean();
		wypiszTekst("Wplata", 0);
		wypiszTekst("[Esc] [Enter]", 4);
		wypiszTekst("Kwota: ", 2);

		unsigned int kwota{};
		czyWplata = wpisywanieKwoty(kwota, &operacja, &czyPowrot);
		if (czyWplata == false)
		{
			kwota = 0;
			clean();
			wypiszTekst("Prosze, wprowadzic wielokrotnosc 20 lub 50.", 1);
			wypiszEnter(2);
		}
	} while (!czyWplata);

	if (!czyPowrot)
	{
		clean();
		wypiszTekst("Usluga zostala wykonana pomyslnie", 1);
		wypiszEnter(2);
	}
}