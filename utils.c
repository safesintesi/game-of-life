/**
 * @file utils.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NOSIZE ((size_t) -1)
#define CHUNCK 1024

char * popola_random(int col, int row) {
	srand(time(0));
    char * pointer;
	if ((pointer = (char *) calloc(col*row, sizeof(char))) == NULL) {
        printf("Popolazione random fallita");
        exit(1);
    }
	for (int i=0; i<col*row; i++) {
		pointer[i] = rand() % 2;
		printf("%d", i[pointer]);
		if (i % col == col - 1) {printf("\n");}
	}
	printf("\n");
	return pointer;
}

int popola_file(char ** pointer, char const * const file, int * columns, int * rows) {

    // Controllo puntatori non nulli.
    if ((pointer == NULL) || (file == NULL) || (columns == NULL) || (rows == NULL )) {
        printf("Errore di puntatore");
        exit(1);
    }

    char * line;
    size_t len = 0;
    size_t read;
    FILE * fp = fopen(file, "r");
    int col = 0;
    int row = 0;
    int size_buffer = CHUNCK;
    char * buffer;
    if ((buffer = (char *) malloc(size_buffer)) == NULL) {
        printf("Errore 01: memoria insufficiente");
        exit(1);
    }
    if (fp) {
        while ((read = (size_t) getline(&line, &len, fp)) != NOSIZE) {
            col = read - 1;

            // Amplia dimensioni buffer nel caso non basti
            while (((row+1)*col) >= size_buffer) {
                size_buffer *= 2;
                if ((buffer = (char *) realloc(buffer, size_buffer + 1)) == NULL) {
                    printf("Errore di memoria");
                    exit(1);
                }
            }

            // Copia la linea letta nel buffer
            for (int i = 0; i < col; i++) {
                buffer[col*row + i] = ((char) line[i]);
            }

            row++;
            buffer[col*row] = '\0';
        }
        free(line);
        fclose(fp);        
    } else
    {
        printf("File non trovato");
        exit(1);
    }
    *columns = col;
    *rows = row;
    
    if ((*pointer = realloc(buffer, row*col + 1)) == NULL) {
		printf("Errore di memoria");
		exit(1);
	}
    free(buffer);
    return row*col;
}

void stampa_tabella(char * pointer, size_t np, int col) {
    for (int i = 0; i < np; i++) {
        printf("%c", pointer[i]);
        if (i % col == col-1) {printf("\n");}
    }
    printf("\n");
}