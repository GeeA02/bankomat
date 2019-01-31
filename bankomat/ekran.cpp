#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include "ekran.h"
#include "konto.h"

using namespace std;


HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO buffer;
COORD pozycja;
int szerokosc;
int wysokosc;


void rozmiarOkna()
{
	SetConsoleTextAttribute(out, 23);
	system("cls");
	GetConsoleScreenBufferInfo(out, &buffer);
	szerokosc = buffer.srWindow.Right - buffer.srWindow.Left + 1;
	wysokosc = buffer.srWindow.Bottom - buffer.srWindow.Top + 1;
}

void pozycjaKursora()
{
	GetConsoleScreenBufferInfo(out, &buffer);
		pozycja = buffer.dwSize;
}

void ukryjKursor()
{
	CONSOLE_CURSOR_INFO kursorInfo;
	GetConsoleCursorInfo(out, &kursorInfo);
	kursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(out, &kursorInfo);
}

void gotoxy(int x, int y)
{
	COORD pozycja = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pozycja);

}


void ramka()
{
	int w = wysokosc - 1;
	int s = szerokosc - 1;
	for (int i = 0; i < szerokosc; i++)
	{
		gotoxy(i, 0);
		cout << "#";
		gotoxy(i, w);
		cout << "#";
	}
	for (int i = 0; i < wysokosc; i++)
	{
		gotoxy(0, i);
		cout << "#";
		gotoxy(s, i);
		cout << "#";
	}
}

void clean()
{
	int w = wysokosc - 5;
	int s = szerokosc - 5;
	for (int i = 1; i < s; i++)
	{
		for (int j = 1; j < w; j++)
		{
			gotoxy(i, j);
			cout << "     ";
		}
	}
}

int srodekTekstu(int x, int dlugoscTekstu)
{
	return (x - dlugoscTekstu) / 2;
}

void wypiszTekst(string tekst, int y)
{
	unsigned int dlugoscTekstu = tekst.length();
	gotoxy(srodekTekstu(pozycja.X, dlugoscTekstu), (wysokosc - 1) / 2 + y);
	cout << tekst;
}

void wypiszEnter(int y)
{
	string enter = "[Enter]";
	wypiszTekst(enter, y);
	_getch();
}

void wypiszMenu(string imie)
{
	clean();
	wypiszTekst("Witaj, " + imie, 0);
	wypiszTekst("Stan konta     ", 2);
	wypiszTekst("Wyplata gotowki", 3);
	wypiszTekst("Wplata gotowki ", 4);
	wypiszTekst("Wyjscie        ", 5);
}

void kursorMenu(int poprzedniWybor, int wybor)
{

	gotoxy(srodekTekstu(szerokosc, 17), (wysokosc - 1) / 2 + poprzedniWybor);
	cout << " ";
	gotoxy(srodekTekstu(szerokosc, 17), (wysokosc - 1) / 2 + wybor);
	cout << ">";
}

void wyswietlStan(float stanKonta)
{
	clean();
	wypiszTekst("Saldo: ", 1);
	cout << stanKonta;
	wypiszEnter(2);
}

void koniec()
{
	clean();
	wypiszTekst("Dziekujemy za skorzstanie z naszch uslug", 1);
	Sleep(3600);
}