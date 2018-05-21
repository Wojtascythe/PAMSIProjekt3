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






int main()
{
	
}
