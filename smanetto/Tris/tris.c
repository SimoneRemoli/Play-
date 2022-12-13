#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define N 3
void set(char [][N]);
void views(char *);
void insertX(char *);
int check_vittoria(char *);
bool full(char *ptr);
void IA(char *);
/* Senza intelligenza artificiale */
/* Il cerchio "O" viene posizionato randomicamente */ 
/* Possibili implementazioni in arrivo */
int main(int argc, char *argv[])
{
	char *ptr = malloc(9*sizeof(char));
	set(ptr);
	views(ptr);
	int scelta,contatore = 0;
	bool fine = false;
	do
	{
		printf("\n Benvenuto nel gioco del TRIS. \n");
		printf("\n Effettua la tua scelta. \n");
		printf("\n 1. Inserisci la X. \n");
		printf("\n 2. Esci. \n");
		printf(">> ");
		scanf("%d",&scelta);

		switch(scelta)
		{
			case 1:
			{
				if(full(ptr))
				{
					insertX(ptr);					
					views(ptr);
					if(check_vittoria(ptr)==1)
					{
						fine = true;
					}
					else
					{
					printf("Partita finita in parità [*]\n");
					fine = true;
					}
				}
				else
				{
					insertX(ptr);
					IA(ptr); //se sono a 8 elementi pieni non devo effettuare la IA 
					views(ptr);
				}
				if(check_vittoria(ptr)==1)
				{
					printf("\n Hai vinto ! [*] \n");
					fine = true;
				}
				if(check_vittoria(ptr)==0)
				{
					printf("\n Hai perso ! :( \n");
					fine = true;
				}
			}break;
			case 2:
			{
				fine = true;
			}break;
		}
	}while(fine==false);
	return 0;
}
int check_vittoria(char *ptr)
{
	char a;
	if((*(ptr + 0)) == (*(ptr + 3))) //prima colonna 
		if(*(ptr + 3) == (*(ptr + 6)))
				a = (*(ptr + 3*0));
	if((*(ptr + 1)) == (*(ptr + 4))) //seconda colonna
		if(*(ptr + 4) == (*(ptr + 7)))
				a = (*(ptr + 1));
	if((*(ptr + 2)) == (*(ptr + 5))) // terza colonna
		if(*(ptr + 5) == (*(ptr + 8)))
				a = (*(ptr + 2));
	if((*(ptr + 0)) == (*(ptr + 1))) //prima riga
		if(*(ptr + 1) == (*(ptr + 2)))
				a = (*(ptr + 0));
	if((*(ptr + 3)) == (*(ptr + 4))) //seconda riga
		if(*(ptr + 4) == (*(ptr + 5)))
				a = (*(ptr + 3));
	if((*(ptr + 6)) == (*(ptr + 7))) //terza riga
		if(*(ptr + 7) == (*(ptr + 8)))
				a = (*(ptr + 6));
	if((*(ptr + 0)) == (*(ptr + 4))) //diagonale principale
		if(*(ptr + 4) == (*(ptr + 8)))
				a = (*(ptr + 0));
	if((*(ptr + 2)) == (*(ptr + 4))) //diagonale secondaria
		if(*(ptr + 4) == (*(ptr + 6)))
				a = (*(ptr + 2));
	if(a=='X')
	{
		return 1;
	}
	else if(a=='O')
	{
		return 0;
	}
}
bool full(char *ptr)
{
	int count = 0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if((*(ptr + i*N + j)=='X')||(*(ptr + i*N + j)=='O'))
				count++;
		}
	}
	if(count == (N*N)-1)
		return true;
	else
		return false;
}
void IA(char *ptr)
{
	srand((unsigned int)time(NULL));
	int riga,colonna;
	do{
		riga = rand()%3;
		colonna = rand()%3;
	}while(((*(ptr + riga * N + colonna)=='X') || (*(ptr + riga * N + colonna)=='O')));
	*(ptr + riga*N + colonna) = 'O';
	
}
void insertX(char *ptr)
{
	int x;
	printf("\n Scegli la casella dove inserire la X: ");
	scanf("%d",&x);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(*(ptr + i*N + j)==x+'0')
			{
				*(ptr + i*N + j) = 'X';
			}
		}
	}

}
void views(char *a)
{
	printf("\n");
	printf("------------\n");
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			printf(" %c |", *(a + i*N + j));
			if(j==2)
				printf("\n------------");
		}
		printf("\n");
	}
	printf("\n");
}
void set(char a[][N])
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j] = ((i*N+j)+1) + '0';
		}
	}
}