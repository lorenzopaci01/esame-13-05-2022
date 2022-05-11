/* Esame di informatica del 13\05\2022, di Lorenzo Paci, maticola numero N35004511*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funzione di controllo
bool controlloLunghezzaStringa(char*testo, int lunghezzaMax) //controllo lunghezza  stringa
{
	if (strlen(testo) >= lunghezzaMax)  
	{
		printf("Errore: stringa troppo lunga, consentiti massimo %d caratteri\n\n", lunghezzaMax) ;
		return false;
	} 
	if (strlen(testo) == 0) 
	{
		printf("Errore: stringa troppo corta, inserire almeno 1 carattere\n\n") ;
		return false; 
	}
	return true;
}

//main 
int main(void)
{
	const int MAX = 100; // numero massimo di voci 
	const int LUNN = 40; // lunghezza del nome 
	const int LUNT = 20; // lunghezza numero telefono 

	char nome[MAX][LUNN+1];
	char tel[MAX][LUNT+1];
	int n = 0; // numero di voci memorizzate
	
//Variabili di appoggio
	int comando; // comandi 0-6 
	char riga[200];
	char sn[LUNN+1];
	char st[LUNT+1];
	int i, pos;
	
	// uso do while, perche' il programma prevede che tu possa compiere piu' comandi consecutivamente. senza (solo con lo switch case), alla fine di ogni comando sarebbe uscito dal programma e si sarebbero eliminati i dati.  
	do 
	{
		// Stampa del menu
 		puts("1) Aggiungi nuova voce in rubrica"); 
		puts("2) Ricerca mirata per nome");
		puts("3) Ricerca generica per nome");
		puts("4) Stampa completa rubrica");
		puts("5) Modifica contatto");
		puts("6) Svuota rubrica");
		puts("0) Esci dal programma");

		// Lettura del comando
		printf("Inserisci il comando: ");
		gets(riga); // l'input inserito dall'utente verra' salvato nel variabile riga
		comando = atoi(riga); // converto la stringa riga in numero intero, non fallisce (se inserisco qualcosa che non e' un numero, mi ritorna 0 e quindi esce dal programma) 

		// Esecuzione del comando 
		switch (comando)
		{
			case 1:
			{
 				// Acquisizione dati 
				printf("Inserisci il nome da aggiungere: ");
				gets(sn); // l'input inserito dall'utente verra' salvato nel variabile sn	
				// richiamo funzione di controllo stringa, ! perche il ritorno della funzione e' un booleano
				if (!controlloLunghezzaStringa(sn,LUNN)) 
				{
					break;
				}
				printf("Inserisci il numero di telefono corrispondente: ");
				gets(st); 
				if (!controlloLunghezzaStringa(st,LUNT)) 
				{
					break;
				}

				// Verifica validita' dati
				if (n == MAX)
				{
					puts("ERRORE: rubrica piena");
 					break;
				}
				bool nuovoNome = true; 
				// appena so che esiste un duplicato, interrompo il ciclo
				for (i = 0 ; i < n ; i++) 
				{
 					if (strcmp(sn, nome[i]) == 0) // strcmp mi dice se il nome sulla variabile sn e' uguale a quello su i
					{
						nuovoNome = false;
						puts("ERRORE: nome duplicato");
						break;
					}
				}
				if (nuovoNome)
				{
					// Aggiunta nuovo nome in rubrica 
 					strcpy(nome[n], sn); // strcpy copia una stringa da una locazione ad un'altra
					strcpy(tel[n], st);
					n++;
				}
				break;
			}
			case 2: 
			{	// ricerca esatta 
				printf("Inserisci il nome da ricercare: ");
				gets(sn); 
				if (!controlloLunghezzaStringa(sn,LUNN)) 
				{
					break;
				}
				
 				bool trovato = false;
				for (i = 0 ; i < n; i++)
				{
					if ( strcmp(sn, nome[i] ) == 0)
					{
 						trovato = true;
						pos = i; // salvo la posizione del nome preso in input all'interno della variabile pos 
						break;
					}
				}
 				if (trovato)
				{
					printf("Il telefono di %s e: %s\n",	sn, tel[pos] );
				}
 				else
				{
					printf("Nessun %s e presente in rubrica\n", sn);
				}
			 	break;
 			}
			case 3:
			{ // ricerca generica 
				printf("Inserisci una parte del nome da ricercare: ");
				gets(sn);
				if (!controlloLunghezzaStringa(sn,LUNN)) 
				{
					break;
				}
				
				bool trovato = false;
				for (i = 0 ; i < n ; i++)
				{
					if (strstr( nome[i], sn ) != NULL) // strstr serve per controllare se la stringa immessa sia contenuta in nome
 					{
					 	// ogni volta che trova una corrispondenza, mi stampa la corrispondenza (non si ferma una volta trovata (non c'e' il break))			
						printf("%s: %s\n", nome[i], tel[i]); 
						trovato = 1;
					}
				}

				if (!trovato)
				{
					printf("Non trovato...\n");
				}
				break;
			}
 			case 4: 
				printf("CONTENUTO DELLA RUBRICA (%d VOCI)\n", n);
				for (i = 0 ; i < n ; i++)
				{
					printf("%s: %s\n", nome[i], tel[i]);
				}
 				break;
 			case 5:
 			{
 				printf("Inserisci il nome da ricercare: \n");
				gets(sn); 
				if (!controlloLunghezzaStringa(sn,LUNN)) 
				{
					break;
				}
				
 				bool trovato = false;
				for (i = 0 ; i < n; i++)
				{
					if (strcmp( sn, nome[i] ) == 0)
					{
 						trovato = true;
						pos = i; // salvo la posizione del nome preso in input all'interno della variabile pos 
						break;
					}
				}
 				if ( !trovato )
				{
					printf("Nessun %s e' presente in rubrica\n", sn);
					break;
				}
				int correzione;
				do
				{
					// Stampa del menu 
 					puts("1) Modifica nome :");
					puts("2) Modifica numero di telefono :");
					puts("0) Torna al menu precedente");
					
					// Lettura del comando 
					printf("Inserisci il comando: ");
					gets(riga);
					correzione = atoi(riga); // atoi converte stringa-intero e salva l'intero all'interno di correzione (correzione e' il comando inserito)
					
					// Esecuzione del comando 
					switch ( correzione )
					{
					// sovrascrizione nome
					case 1: 
						printf("Inserisci nuovo nome: ");
						gets(sn);
						if (!controlloLunghezzaStringa(sn,LUNN)) 
						{
							break;
						}
						strcpy(nome[pos], sn); // copio il nuovo nome sulla posizione del precedente (sovrascrizione)
						break; 
					case 2:
						printf("Inserisci nuovo numero di telefono: ");
						gets(st);
						if (!controlloLunghezzaStringa(st,LUNT)) 
						{
							break;
						}
						strcpy(tel[pos], st); 
						break;
					case 0:
						puts("Indietro");
						break;
					// se non immetto un valore numerico gestito, va in default
					default: 
						printf("ERRORE NEL PROGRAMMA (correzione=%d)\n", correzione);
					}
				}
				// quando il valore e' diverso da 0, rieseguo lo switch case, altirmenti esco dal do while (torno indietro)
				while (correzione != 0); 
				
 				break;
 			}
 			case 6:
 				n = 0;
 				printf("La rubrica e vuota\n");
				break; 
			case 0:
				puts("Arrivederci");
				break;

				default:
					printf("ERRORE NEL PROGRAMMA (comando=%d)\n", comando);
		}
	}
	while (comando != 0); 
		exit(0);
}

