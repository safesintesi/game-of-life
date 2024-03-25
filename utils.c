/**
 * @file utils.c
 * File contenente le funzioni di popolazione della tabella e stampa.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NOSIZE ((size_t)-1)
#define CHUNCK 1024

char *popola_random(int col, int row) {
  srand(time(0));
  char *pointer = (char *)calloc(col * row + 1, sizeof(char));
  // Controlla l'allocazione sia andata a buon fine
  if (!pointer) {
    printf("Popolazione random fallita");
    exit(1);
  }
  // Popola in maniera randomica
  for (int i = 0; i < col * row; i++) {
    pointer[i] = (rand() % 2) ? '*' : '-';
    printf("%c", i[pointer]);
    if (i % col == col - 1) {
      printf("\n");
    }
  }
  printf("\n");
  pointer[col * row] = '\0';
  return pointer;
}

int popola_file(char **pointer, char const *const file, int *columns,
                int *rows) {

  // Controllo puntatori non nulli.
  if ((!pointer) || (!file) || (!columns) || (!rows)) {
    printf("Errore di puntatore");
    exit(1);
  }

  char *line;
  size_t len = 0;
  size_t read;
  int col = 0;
  int row = 0;
  int size_buffer = CHUNCK;
  char *buffer = (char *)malloc(size_buffer);
  // Controlla l'allocazione sia andata a buon fine
  if (!buffer) {
    printf("Errore 01: memoria insufficiente");
    exit(1);
  }

  FILE *fp = fopen(file, "r");
  if (!fp) {
    // File inesistente
    printf("File non trovato");
    exit(1);
  }

  while ((read = (size_t)getline(&line, &len, fp)) != NOSIZE) {
    col = read - 1;

    // Amplia dimensioni buffer nel caso non basti
    while (((row + 1) * col) >= size_buffer) {
      size_buffer *= 2;
      buffer = (char *)realloc(buffer, size_buffer + 1);
      if (!buffer) {
        printf("Errore di memoria");
        exit(1);
      }
    }

    // Copia la linea letta nel buffer
    for (int i = 0; i < col; i++) {
      buffer[col * row + i] = ((char)line[i]);
    }

    row++;
    buffer[col * row] = '\0';
  }
  free(line);
  fclose(fp);
  *columns = col;
  *rows = row;

  // Controlla l'allocazione sia andata a buon fine
  *pointer = realloc(buffer, row * col + 1);
  if (!(*pointer)) {
    printf("Errore di memoria");
    exit(1);
  }
  return row * col;
}

void stampa_tabella(char *pointer, size_t np, int col) {
  for (int i = 0; i < np; i++) {
    printf("%c", pointer[i]);
    if (i % col == col - 1) {
      printf("\n");
    }
  }
  printf("\n");
}
