#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#define cleanScreen() printf("\e[1;1H\e[2J")

int main(int argc, char * argv[]) {
	cleanScreen();

	//valori standard per creazione random
	int columns = 140;
	int rows = 75;
	int elements = columns*rows;
	char * pointer;
	//char * temp = (char *) calloc(elements, sizeof(char));

	//check for file
	if (argc < 2) {
		//manca file, popola la tabella base a random
		pointer = popola_random(columns, rows);
	} else {
		//legge la tabella dal file e la carica
		pointer = popola_file(argv[1], &columns, &rows);
		elements = rows*columns;
	}	
	char * temp;
	if ((temp = (char *) calloc(elements, sizeof(char))) == NULL) {
		printf("Errore di memoria");
		exit(1);
	}

	_Bool sent = 1;
	while (sent) {
		cleanScreen();
		for (int i = 0; i < elements; i++) {
			i[temp] = 0; //giusto perche si
		}

		//calc vicini vivi
		for (int i = 0; i<elements; i++) {
			if (pointer[i] == '*') {
				//verso su
				if (i >= columns) {
					temp[i - columns]++;
					//diag sx
					if (i % columns) {
						temp[i - columns - 1]++;
					}
					//diag dx
					if (i % columns != columns-1) {
						temp[i - columns + 1]++;
					}
				}
				//verso giu
				if (i < elements - columns) {
					temp[i + columns]++;
					//diag sx
					if ((i%columns)) {
						temp[i + columns -1]++;
					}
					//diag dx
					if (i%columns != columns -1) {
						temp[i + columns + 1]++;
					}
				}
				//verso sinistra
				if (i % columns) {
					temp[i-1]++;
				}
				//verso destra
				if (i % columns != columns-1) {
					temp[i+1]++;
				}
			}
		}
		
		for (int i = 0; i < elements; i++) {
			printf("%d", temp[i]);
			if (i % columns == columns-1) {printf("\n");}
		}
		printf("\n");
		
		//decide vita, morte e miracoli
		sent = 0;
		for (int i = 0; i < elements; i++) {
			switch (temp[i])
			{
			case 2:
				break;
			case 3:
				pointer[i] = '*';
				sent = 1;
				break;
			default:
				pointer[i] = '-';
				sent = 1;
				break;
			}
			printf("%c", pointer[i]);
			if (i % columns == columns-1) {printf("\n");}
		}
		sleep(1);
	}
	free(pointer);
	free(temp);
	return 0;
}