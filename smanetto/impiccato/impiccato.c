#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define N 1000
/*
Si vuole realizzare una variante interattiva del gioco dell’impiccato.In questo gioco, il giocatore
deve indovinare una parola, inserendo un carattere per volta, avendo a disposizione un numero LIMITATO di tentativi.

Il programma accetta in input (come unico parametro obbligatorio) il percorso ad un file di testo nel formato:  pAroLa;n

In ciascuna riga, prima del carattere ‘;’ si trova la parola da indovinare. 
Dopo il ‘;’ si trova il numero di tentativi aggiuntivi (“vite”) che si guadagnano qualora la parola sia stata indovinata (un numero
 intero positivo).

Ogni riga è un turno;

Il programma da realizzare quindi, deve seguire i seguenti passi:

1. Il file di configurazione viene analizzato ed i turni di gioco vengono caricati in memoria (in una struttura
dati a scelta dello studente);

2. Viene mostrata la parola, sostituendo ai caratteri in minuscolo dei trattini bassi (rispetto all’esempio
precedente, verrà mostrato: “_ A _ _ L _”);

3. Il giocatore inserisce un input da tastiera: se vengono inseriti più caratteri, soltanto il primo sarà
considerato come lettera da verificare;

4. Se la lettera inserita è tra quelle da indovinare, viene aggiunta all’insieme delle lettere indovinate (ad
esempio, se il giocatore digita ‘p’ o ‘P’, verrà mostrato “P A _ _ L _”);

5. Se la lettera inserita non è tra quelle da indovinare, o se è una lettera già indovinata in precedenza, si perde
un punto vita;

6. Se i punti vita sono terminati, il giocatore perde la partita;

7. Se la parola è stata indovinata, viene aggiunto n ai punti vita e si passa al turno successivo (ripartendo dal
punto 2);

8. Quando sono state indovinate tutte le parole, il giocatore ha vinto la partita.
*/
int gioco(char *,int,int);
void views(char *,int,int);
void copia_matrice(char *,char*);
int scelta(char *,char *,int,int,int,int,int,int);
int main(int argc, char *argv[])
{
	/*
	When working with files, you need to declare a pointer of type file. 
	This declaration is needed for communication between the file and the program.

	fgetc()– This function is used to read a single character from the file.
	fgets()– This function is used to read strings from files.
	*/
	FILE *fptr;
	int num,j=0;
	char ch,str[50];
	char a[N][N]={0};
	char copy[N][N] = {0};
	int parole = 0;
	fptr = fopen("/home/anonymous/Scrivania/smanetto/impiccato/config.txt","r");
	if(fptr == NULL)
   	{
      printf("Error!");   
      exit(1);             
   	}
	while (fgets(a[j], 100, fptr) != NULL)
	{
		j++; //legge una parola finchè non arriva a capo, str è la stringa.
		parole++;
	}

	char *ptr = &a[0][0];
	char *ptr_copy = &copy[0][0];
	copia_matrice(ptr_copy,ptr); //copia il puntatore della matrice originale alla matrice di copia
	bool fine = false;
	int i=0;

	int controllo = 0;

	while(i<=parole)
	{
		printf("i = %d",i);
		int count = 0;
		count = gioco(ptr,i,strlen(a[i])); //j è il numero della parole 
		controllo = scelta(ptr_copy,ptr,i,strlen(a[i]),count,strlen(a[i+1]),i+1,parole);
		if(controllo==1)
			i++;
		else if(controllo ==0)
		{
			printf("Ritenta :( .. \n ");
			printf("La parola era: %s",copy[i]);
			fclose(fptr);
			return 0;
		}
		else if(controllo == 2)
		{
			printf("Hai vinto [*]");
			return 0;
		}
	}
   	fclose(fptr);
	return 0;
}
void copia_matrice(char *ptr_copy, char *ptr) //mi copia la matrice d'appoggio
{
	for(int i = 0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			*(ptr_copy + i * N + j ) = *(ptr + i * N + j);
		}
	}
}
int scelta(char *ptr_copy, char *ptr , int i, int size_word, int count,int size_succ, int k,int parole)
{
	bool ritorna = true;
	bool check = false;
	char character;
	do{
	check = false;
    do{
	printf("Ci sono %d trattini ! ",count);
	printf(" Digita la lettera : ");
	scanf(" %c",&character);
	}while(isdigit(character));
	for(int l=0;l<size_word;l++)
	{
		if(((*(ptr_copy + i * N + l )== character)) && (*(ptr + i * N + l ) == '_'))
		{
			*(ptr + i * N + l) = character;
			count--;
			check = true;
		}
	}
	if(check == false)
	{

		printf("\n Non hai indovinato la lettera [*] ..\n");
		printf("Le vite decrementeranno !");
		for(int l = 0;l<size_word;l++)
		{
			if(isdigit(*(ptr + i * N + l)))
			{
				*(ptr + i * N + l) = *(ptr + i * N + l) - 1;
				if((*(ptr + i * N + l)) == '0')
				{
					ritorna = false;
				}
			}
		}
	}
	
	/*if(((*(ptr + i * N + (scegliamo-1 ) ) == '_')) && (*(ptr_copy + i * N + (scegliamo-1)) == character))
	{
		*(ptr + i * N + (scegliamo-1)) = character;
			count--;
	}*/
	printf(" Parole qua sta a = %d e i = %d ",parole,i);
	if((count == 0)&&(ritorna == true)) //se ho indovinato la parola senza perdere tutte le vite
	{
		if(i!=parole-1)
		{
		char n1;
		for(int l=0;l<size_word;l++)
		{
			if(isdigit(*(ptr + i * N + l)))
			{
				n1 = *(ptr + i * N + l);
				for(int j=0;j<size_succ;j++)
				{
					if(isdigit(*(ptr + k * N + j)))
					{
						*(ptr + k * N + j) += *(ptr + i * N + l) - '0'; //lo rende intero
						printf("Hai indovinato, aggiunti %c punti ! \n", *(ptr + i * N + l));
						views(ptr,i,size_word);
						return 1;
					}
				}
			}
		}
		}
		else
		{
			printf("Hai vinto il gioco ... [*] ");
			views(ptr,i,size_word);
			return 2;
		}
	}
	views(ptr,i,size_word);
	}while(ritorna != false);
	if(ritorna == false)
	{
		printf("Hai esaurito le vite ... Fine ! [*]\n");
		return 0;
	}
}
int gioco(char *ptr,int i,int size_word)
{
	unsigned int count = 0;
	for(int j=0;j<size_word;j++) 
	{
		if((!isupper(*(ptr + i * N + j)))&&(isalpha(*(ptr + i * N + j))))
		{
			*(ptr + i*N + j) = '_';
			count++;
		}
	}
	views(ptr,i,size_word);
	return count;
}
void views(char *ptr,int i, int size_word)
{
	for(int l = 0;l<size_word;l++)
	{
		printf(" %c ", *(ptr + i*N + l));
		if(isdigit(*(ptr + i * N + l)))
		{
			printf(" \n Vite attuali = %c",*(ptr + i * N + l));
		}
	}
	printf("\n");
}