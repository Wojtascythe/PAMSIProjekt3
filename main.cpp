#include <cstdlib>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
	int const sizee=3;//Wielkoœæ tablicy
	int const wyg=3;//iloœæ potrzebna do wygrania


	int const deep=3;

int punktacja(int plansza[sizee][sizee], int p)//funkcja liczy punkty gry
{
	int punkty=0;
	int tplanszy[sizee+2][sizee+2];
	for (int i=0; i<sizee+2; i++) for (int j=0; j<sizee+2; j++) tplanszy[i][j]=0;
	for (int i=0; i<sizee; i++) for (int j=0; j<sizee; j++) tplanszy[i+1][j+1]=plansza[i][j];

	for (int i=1; i<sizee+1; i++)
		for (int j=1; j<sizee+1; j++)
		{
			if(tplanszy[i+1][j]==p) punkty+=2;
			if(tplanszy[i+1][j+1]==p) punkty+=2;
			if(tplanszy[i+1][j-1]==p) punkty+=2;
			if(tplanszy[i-1][j]==p) punkty+=2;
			if(tplanszy[i-1][j+1]==p) punkty+=2;
			if(tplanszy[i-1][j-1]==p) punkty+=2;
			if(tplanszy[i][j+1]==p) punkty+=2;
			if(tplanszy[i][j-1]==p) punkty+=2;
			if(tplanszy[i+1][j]==-p) punkty--;
			if(tplanszy[i+1][j+1]==-p) punkty--;
			if(tplanszy[i+1][j-1]==-p) punkty--;
			if(tplanszy[i-1][j]==-p) punkty--;
			if(tplanszy[i-1][j+1]==-p) punkty--;
			if(tplanszy[i-1][j-1]==-p) punkty--;
			if(tplanszy[i][j+1]==-p) punkty--;
			if(tplanszy[i][j-1]==-p) punkty--;
			if(tplanszy[i+1][j]==0) punkty++;
			if(tplanszy[i+1][j+1]==0) punkty++;
			if(tplanszy[i+1][j-1]==0) punkty++;
			if(tplanszy[i-1][j]==0) punkty++;
			if(tplanszy[i-1][j+1]==0) punkty++;
			if(tplanszy[i-1][j-1]==0) punkty++;
			if(tplanszy[i][j+1]==0) punkty++;
			if(tplanszy[i][j-1]==0) punkty++;
		}
	return punkty;
}

int spr_wygr(int plansza[sizee][sizee], int p)//podlicza punkty do wygranej
{
	for (int i=0; i<sizee; i++)
	{
		int win=1;
		vector<int> count;
		for (int j=0; j<sizee; j++) if (plansza[i][j]==p) count.push_back(j);
		if (count.size()>=wyg)
		{
			for (int j=1; j<wyg; j++)
			{
				if (count[j]-count[j-1]==1) win+=1;
				else win-=1;
			}
		}
		if (win==wyg) return p;
	}
	for (int i=0; i<sizee; i++)
	{
		int win=1;
		vector<int> count;
		for (int j=0; j<sizee; j++) if (plansza[j][i]==p) count.push_back(j);
		if (count.size()>=wyg)
		{
			for (int j=1; j<wyg; j++)
			{
				if (count[j]-count[j-1]==1) win+=1;
				else win-=1;
			}
		}
		if (win==wyg) return p;
	}
	int tplanszy[sizee*3][sizee*3];
	for (int i=0; i<sizee*3; i++) for (int j=0; j<sizee*3; j++) tplanszy[i][j]=0;
	for (int i=sizee; i<sizee*2; i++) for (int j=0; j<sizee; j++) tplanszy[i][j]=plansza[i-sizee][j];
	for (int i=sizee; i<sizee*2; i++)
	{
		for (int j=0; j<sizee; j++)
		{
			int win=0;
			for (int k=0; k<wyg; k++) if (tplanszy[i+k][j+k]==p) win++;
			if (win==wyg) return p;
			win=0;
			for (int k=0; k<wyg; k++) if (tplanszy[i-k][j+k]==p) win++;
			if (win==wyg) return p;
		}
	}
	return 0;
}

int spr_wygr_w(int plansza[sizee][sizee])//sprawdza czy spe³niono warunek wygranej
{
	int k=spr_wygr(plansza, -1);
	if (k==0) return spr_wygr(plansza,1);
	return k;
}

void gen_plansze(int plansza[sizee][sizee])//metoda ma wygenerowaæ planszê
{
	for (int i=0; i<sizee; i++)
		for (int j=0; j<sizee; j++) plansza[i][j]=0;
}

void pokaz_plansze(int plansza[sizee][sizee])//metoda ma wyœwietliæ planszê
{
	system("cls"); // ma za zadanie nadpisywaæ planszê w konsoli, a nie pokazywaæ now¹
	for (int i=0; i<sizee; i++)
	{
		for (int j=0; j<sizee; j++)
		{
			if (plansza[i][j]==0) cout<<". ";
			else if (plansza[i][j]==1) cout<<"x ";
			else cout<<"o ";
		}
		cout<<endl;
	}
}

int minimax(int plansza[sizee][sizee], int p1, int p2, int deep)//metoda minimax
{
	int naj_wyn=-9999;
    int wyn= 0;

    if (spr_wygr_w(plansza) == p1) return 1000;
    else if (spr_wygr_w(plansza) == p2) return -1000;
    else if (deep==0) return punktacja(plansza,p1);

    for (int i=0; i<sizee; i++)
	{
        for (int j=0; j<sizee; j++)
		{
            if (plansza[i][j]==0)
			{
                plansza[i][j]=p1;
                wyn=-(minimax(plansza, p2, p1,deep-1));
                plansza[i][j]=0;
                if (wyn>=naj_wyn) naj_wyn = wyn;
            }
        }
    }

    if (naj_wyn == -9999 || naj_wyn == 0) return 0;
    else if (naj_wyn < 0) return naj_wyn + 1;
    else if (naj_wyn > 0) return naj_wyn - 1;
}

int naj_ru(int plansza[sizee][sizee], int p1, int p2)// metoda okreœlaj¹ca najlepszy ruch do wykonania
{
	int naj_wyn = -9999;
    int naj_ru_wiersz = -9999;
    int naj_ru_kolumna = -9999;
    int wyn= 0;
	for (int i=0; i<sizee; i++)
	{
        for (int j=0; j<sizee; j++)
		{
            if (plansza[i][j]==0)
			{
                plansza[i][j]=p1;
                wyn=-(minimax(plansza, p2, p1,deep));
                plansza[i][j]=0;
                if (wyn>=naj_wyn)
				{
                    naj_wyn = wyn;
                    naj_ru_wiersz = i;
                    naj_ru_kolumna = j;
                }
            }
        }
    }
    return (100*naj_ru_wiersz + naj_ru_kolumna);
}

void ruch(int plansza[sizee][sizee])//ruch gracza
{
	int wiersz,kolumna;
	cout<<"Podaj kolumne i wiersz"<<endl;
	while(1)
	{
		cout<<"Wiersz: ";
		cin>>wiersz;
		cout<<"Kolumna: ";
		cin>>kolumna;
		if (kolumna>=1 && kolumna<=sizee && wiersz>=1 && wiersz<=sizee && plansza[wiersz-1][kolumna-1]==0)
		{
			plansza[wiersz-1][kolumna-1]=1;
			break;
		}
		else cout<<"Nie mozna wybrac tego pola, wybierz inne. Upewnij sie ze pole nie jest zajete."<<endl;
	}
}

void ruchSI(int plansza[sizee][sizee])
{
	int move=naj_ru(plansza,-1,1);
	int wier=move/100;
	int kol=move%100;
	plansza[wier][kol]=-1;
}

int main()
{
	int plansza[sizee][sizee];
	gen_plansze(plansza);
	char ext;
	int ruchy=0;

	while(ruchy<(sizee*sizee))
	{
		pokaz_plansze(plansza);
		if (ruchy%2==0) ruch(plansza);
		else ruchSI(plansza);
		ruchy++;
		pokaz_plansze(plansza);
		if(spr_wygr_w(plansza)!=0)
		{
			if (spr_wygr_w(plansza)==1) cout<<"Wygrales."<<endl;
			else cout<<"Przegrales."<<endl;
			ext=getch();
			exit(0);
		}
	}
	pokaz_plansze(plansza);
	cout<<"Remis."<<endl;
	ext=getch();
	exit(0);
}
