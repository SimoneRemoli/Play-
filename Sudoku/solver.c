#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void solve(unsigned char (*problem)[9][9])
{
	resolution(problem);
	return;
}
bool trova_celle_vuote(unsigned char(*problem)[9][9], int *riga, int *colonna)
{
  for (int i=0;i<9;i++)
    for (int j=0;j<9;j++)
    {
      if((*problem)[i][j]==0)
      {
        *riga = i;
        *colonna = j;
        return true; 
      }
    }
  return false;
}
bool check_sottomatrice(unsigned char(*problem)[9][9], int *riga, int *colonna, int val)
{
  int x = *riga-*riga%3; 
  int y = *colonna-*colonna%3; 

  for (int i=0;i<9;i++)
  {
    if ((*problem)[x +(i%3)][y+(i/3)]==val)
    	return false;
  }
  return true;
}

bool check_colonna(unsigned char(*problem)[9][9],int *column,int number)
{	
	for(int i=0;i<9;i++)
	{
		if((*problem)[i][*column]==number)
		{
			return false;
		}
	}
	return true;
}
bool check_riga(unsigned char(*problem)[9][9],int *rows,int number)
{
	for(int j=0;j<9;j++)
	{
		if((*problem)[*rows][j]==number)
		{
			return false;
		}
	}
	return true;
}
int resolution(unsigned char(*problem)[9][9])
{
	int righe=0,colonne=0;
	int *puntatore_a_riga = &righe;
	int *puntatore_a_colonna = &colonne;

	if((trova_celle_vuote(problem, puntatore_a_riga, puntatore_a_colonna))==false) 
		return 1;	
	for (int val=1; val<10; val++)
	{
		if((check_colonna(problem,puntatore_a_colonna,val))&&(check_riga(problem,puntatore_a_riga,val))&&(check_sottomatrice(problem,puntatore_a_riga,puntatore_a_colonna,val)))
	    {
			(*problem)[righe][colonne] = val;
			if(resolution(problem)) //all'inizio esce 0
				return 1;
			(*problem)[righe][colonne] = 0;
	    }
	}
	return 0;
}
