/**
 * @file main.c
 * File principale del programma.
 *
 */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Funzione main che implementa il gioco
 *
 * Chiede in input un file contenente una tabella e cicla per calcolare i
 * prossimi stati del gioco. Nel caso il file non sia passato come argomento
 * viene creata una tabella casuale tramite la funzione popola_random().
 * Dopodichè crea una tabella di supporto temp della stessa dimensione per
 * calcolare i vicini vivi. Inizia a ciclare:
 * - Azzera la tabella
 * - Calcola i vicini vivi per ogni cella
 * - Decide se allo stato successivo la cella nasce, vive o muore
 * - Stampa il risultato
 *
 * @param argv contiene il nome del file input in ingresso
 * @param pointer Memoria dove sono salvate le celle attive
 * @param temp Memoria per il calcolo dei vicini, ciclicamente azzerata
 */
int main(int argc, char *argv[]) {
  CLEAR_SCREEN();

  // valori standard per creazione random
  int columns = 0;
  int rows = 0;
  size_t elements = columns * rows;
  char *pointer; /* Puntatore alla tabella di gioco */

  // check for file
  if (argc < 2) {
    // manca file, popola la tabella base a random
    columns = 15;
    rows = 15;
    elements = columns * rows;
    pointer = popola_random(columns, rows);
  } else {
    // legge la tabella dal file e la carica
    elements = popola_file(&pointer, argv[1], &columns, &rows);
  }
  stampa_tabella(pointer, elements, columns);

  // Alloca la memoria per la tabella di supporto dove verrano calolati i vicini
  // per ogni cella
  char *temp = (char *)calloc(
      elements + 1,
      sizeof(char)); /* Puntatore alla tabella per calcoli di supporto */
  if (!temp) {
    printf("Errore di memoria");
    exit(1);
  }

  _Bool sent = 1;
  // Il gioco non prevede una fine ma se non ci sono cambiamenti tra
  // un'iterazzione e la successiva tanto vale fermarsi
  while (sent) {
    CLEAR_SCREEN();

    // La tabella di supporto viene ripulita
    for (int i = 0; i < elements; i++) {
      i[temp] = 0; // proprietà commutativa lol
    }

    // Calcolo vicini vivi per ogni cella
    for (int i = 0; i < elements; i++) {
      if (pointer[i] == '*') {
        // verso su
        if (i >= columns) {
          temp[i - columns]++;
          // diag sx
          if (i % columns) {
            temp[i - columns - 1]++;
          }
          // diag dx
          if (i % columns != columns - 1) {
            temp[i - columns + 1]++;
          }
        }
        // verso giu
        if (i < elements - columns) {
          temp[i + columns]++;
          // diag sx
          if ((i % columns)) {
            temp[i + columns - 1]++;
          }
          // diag dx
          if (i % columns != columns - 1) {
            temp[i + columns + 1]++;
          }
        }
        // verso sinistra
        if (i % columns) {
          temp[i - 1]++;
        }
        // verso destra
        if (i % columns != columns - 1) {
          temp[i + 1]++;
        }
      }
    }

    // Decide vita, morte e miracoli
    sent = 0;
    for (int i = 0; i < elements; i++) {
      switch (temp[i]) {
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
    }

    // Stampa la tabella risultante in console
    stampa_tabella(pointer, elements, columns);
    SLEEP();
  }
  free(pointer);
  free(temp);
  return 0;
}
