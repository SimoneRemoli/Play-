#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define N 10
void views_campo(int *);
void create_campo(int *);
int numero_mine(void);
int generate_random_rows_and_columns(int,int *,int *);
void modify_campo(int,int,int *);
void views_vettori(int *,int *,int);
int scopri_cella(int*,int*,int*,int);
int check_vittoria(int *,int*,int*,int);
/*
When passing an array as a parameter, this

void arraytest(int a[])

means exactly the same as

void arraytest(int *a)
*/
int main(int argc, char *argv[])
{	
	srand((unsigned int)time(NULL));
	int *ptr = malloc(100*sizeof(int)),scelta=0;
	////Valori tra 5 e 100
	//n = ( rand() % 96 ) + 5;
	  //tra 3 e 10
	//int *ptr = &campo[0][0];
	create_campo(ptr);
	int numero_mine_nel_campo;
	numero_mine_nel_campo = numero_mine();
	int *riga = malloc(numero_mine_nel_campo*sizeof(int)); //gestire il problema dei dobppioni valori ch genera la bomba
	int *colonna = malloc(numero_mine_nel_campo*sizeof(int));
	numero_mine_nel_campo = generate_random_rows_and_columns(numero_mine_nel_campo,riga,colonna);
	views_campo(ptr);
	views_vettori(riga,colonna,numero_mine_nel_campo);	
	int a;
	bool fine = false;
	do{
		printf("\n Benvenuto. Scegli la tua mossa.");
		printf("\n 1. Scopri Cella [*]");
		printf("\n 2. Visualizza Campo [*]");
		printf("\n 3. Controllo Vincita [*]");
		printf("\n 4. Fine [*]");
		printf("\n >> ");
		scanf("%d",&scelta); 
		switch(scelta)
		{
			case 1:
			{
				a = scopri_cella(ptr,riga,colonna,numero_mine_nel_campo);
				if(a==1)
					fine=true;
				
			}break;
			case 2:
			{
				views_campo(ptr);
			}break;
			case 3:
			{
				if(check_vittoria(ptr,riga,colonna,numero_mine_nel_campo) == 1)
				{
					printf("\n Complimenti, hai vinto la partita [*] !! \n");
					fine = true;
				}
				else
				{
					printf("\n Rimangono celle da scoprire ! \n ");
				}
			}break;
			case 4:
			{
				fine = true;
			}break;
		}
	}while(fine==false);	
	free(ptr);
	free(riga);
	free(colonna);
	return 0;
}
int check_vittoria(int *ptr,int *riga,int *colonna,int n)
{
	int check = 0;
	int i=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(*(ptr+i*N+j)==9) // vale 9 
			{
				for(int l=0;l<n;l++)
				{
					if((*(riga + l) ==i) && (*(colonna + l) ==j)) //e contiene una bomba
					{
						check = 1;
					}
				}
				if(check == 0)
					return 0;
				check = 0;
			}
		}
	}
	return 1;
}
int scopri_cella(int *ptr,int *riga,int *colonna,int n)
{
	bool bomba_trovata = false;
	int ii,jj;
	int cella_da_scoprire = 0,contatore_adiacenze=0;
	do{
		printf("[1,100]\n");
		printf("Seleziona la coordinata della cella da scoprire : ");
		printf("Riga : ");
		scanf("%d",&ii);
		printf("Colonna : ");
		scanf("%d",&jj);
	}while((cella_da_scoprire>100)||(cella_da_scoprire<0));
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(((i==ii))&&(j==jj))
			{
				for(int l = 0;l<n;l++)
				{
					if((*(riga + l)== i)&&(*(colonna + l)==j))
					{
						printf("\n| | |Bomba trovata | | |\n "); //alloranon devi fare else
						bomba_trovata = true;
						return 1;
					}
				}
				if(bomba_trovata==false)
				{
					//(ptr+i*N+j)=0; //ho la coordinata attuale
					for(int l=0;l<n;l++)
					{
						if((*(riga + l )== i-1)&&(*(colonna + l)==j)) 
							contatore_adiacenze++;
						if((*(riga + l )== i-1)&&(*(colonna + l)==j-1)) 
							contatore_adiacenze++;
						if((*(riga + l )== i-1)&&(*(colonna + l)==j+1)) 
							contatore_adiacenze++;
						if((*(riga + l )== i)&&(*(colonna + l)==j-1)) 
							contatore_adiacenze++;
						if((*(riga + l )== i)&&(*(colonna + l)==j+1)) 
							contatore_adiacenze++;
						if((*(riga + l )== i+1)&&(*(colonna + l)==j-1)) 
							contatore_adiacenze++;
						if((*(riga + l )== i+1)&&(*(colonna + l)==j)) 
							contatore_adiacenze++;
						if((*(riga + l )== i+1)&&(*(colonna + l)==j+1)) 
							contatore_adiacenze++;
					}
					*(ptr + i*N + j) = contatore_adiacenze;
				}
			}
		}
	}
	return 0;
}
void views_vettori(int *riga,int *colonna,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d \t",* (riga + i));
		
	}
	printf("\n");
	for(int i=0;i<n;i++)
	{
		printf("%d \t",* (colonna + i));
	}
	printf("\n");
}
int generate_random_rows_and_columns(int numero_mine_nel_campo,int *riga,int *colonna)
{
	int riga_int=0,colonna_int=0;
	for(int i=0;i<numero_mine_nel_campo;i++)
	{
		riga_int=rand()%10;
		colonna_int=rand()%10;
		* (riga + i ) = riga_int;
		* (colonna + i ) = colonna_int;
		riga_int = 0;
		colonna_int = 0;
	}
	for(int i=0;i<numero_mine_nel_campo;i++) //all differents bombs
	{
		for(int j=i+1;j<numero_mine_nel_campo;j++)
		{
			if(((*(riga + i)==((*(riga + j)))))&&((*(colonna + i)==((*(colonna + j))))))
			{
				for(int k=j;k<numero_mine_nel_campo;k++)
				{
					*(riga+k) = (*(riga+(k+1)));
					*(colonna+k)= (*(colonna+(k+1)));
				}
				numero_mine_nel_campo--;
				j--;

			}
		}
	}
	return numero_mine_nel_campo;
}
int numero_mine()
{
	srand((unsigned int)time(NULL));
	int numero_mine = 0;
	numero_mine = (rand()%8)+3;
	return numero_mine;
}
void views_campo(int *ptr)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			printf(" %d \t ",*(ptr + i * N + j));
		}
		printf("\n");
	}
	printf("\n");
}
void create_campo(int *ptr)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			*(ptr + i * N + j) = 9;
		}
	}
}

/*
La cifra 9 la indico come valore da scoprire, al quale bisogna accervi tramite la coordinata della matrice 10x10, assegnando a runtime 
il valore dell'indice della riga i-esima e della colonna j-esima.
la posizione [i][j] sarà gestita da un puntatore che accederà a quell'area di memoria per modificare il valore della cella.
*/