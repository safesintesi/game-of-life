#ifndef UTILS_H_
#define UTILS_H_
#include <stdlib.h>

/**
 * @file utils.h
 * Header che contine le funzioni di popolazione e stampa.
 *
 *
 */
/// Funzione che popola una tabella leggendo da file.
/**
 * Una volta richiamata apre il file che gli viene passato ed inizia
 * a leggere i valori dei singoli elementi della cella riga per riga.
 * Una volta terminato restituisce il numero di colonne e righe della
 * tabella tramite i puntatori e realloca la tabella.
 *
 * @param pointer Puntatore alla tabella originale.
 * @param file Stringa contenente il nome del file.
 * @param col Puntatore a numero colonne.
 * @param row Puntatore a numero righe.
 */
size_t popola_file(char **pointer, char const *const file, int *col, int *row);

/// Funzione che genera una tabella random.
/**
 * Nel caso non esista un file assegnato come input viene chiamata questa
 * funzione che genera casualmente il contenuto di una tabella di dimensioni
 * stndard hardcoded.
 *
 * @param col Numero di colonne
 * @param row Numero di righe
 */
char *popola_random(int col, int row);

/// Funzione che stampa la tabella puntata da pointer
/**
 * Tutto qui: prende la tabella di col colonne puntata da
 * pointer e la stampa sulla console.
 *
 * @param pointer Puntatore alla memoria allocata per la tabella.
 * @param np Dimendione della tabella.
 * @param col Numero di colonne della tabella.
 */
void stampa_tabella(char *pointer, size_t np, int col);

#ifdef _WIN32
#include <Windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP() Sleep(1000)
#else
#include <unistd.h>
#define CLEAR_SCREEN() printf("\e[1;1H\e[2J")
#define SLEEP() sleep(1)
#endif

#endif
