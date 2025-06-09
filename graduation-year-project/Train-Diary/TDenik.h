#ifndef TDENIK_H_INCLUDED
#define TDENIK_H_INCLUDED

#include <stdio.h>
#include <string.h> // Pro práci s řetězci
#include <stdlib.h>
#include <stdbool.h>

typedef struct _jednotka TJednotka;

/**
 * @struct TJednotka
 * @brief Struktura reprezentující tréninkovou jednotku.
 */
struct _jednotka {
    char datum[11];      ///< Datum ve formátu YYYY-MM-DD
    char aktivita[15];   ///< Typ aktivity (např. plavání, posilovna, atd.)
    int delkaTrvani;     ///< Délka trvání v minutách
    int narocnost;       ///< RPE (1-10)
    TJednotka* dalsi;    ///< Ukazatel na další jednotku v seznamu
};

/**
 * @struct TDenik
 * @brief Struktura reprezentující tréninkový deník.
 */
typedef struct _denik {
    TJednotka* prvni;    ///< Ukazatel na první jednotku v deníku
    TJednotka* posledni; ///< Ukazatel na poslední jednotku v deníku
    int pocetJednotek;   ///< Počet jednotek v deníku
} TDenik;

/**
 * @brief Inicializuje nový tréninkový deník.
 *
 * @return Ukazatel na inicializovaný deník.
 */
TDenik* denikInicializuj(void);

/**
 * @brief Uvolní paměť alokovanou pro deník a jeho jednotky.
 *
 * @param d Ukazatel na deník.
 */
void denikUvolni(TDenik* d);

/**
 * @brief Kontroluje, zda je deník prázdný.
 *
 * @param d Ukazatel na deník.
 * @return true pokud je deník prázdný, jinak false.
 */
bool denikJePrazdny(TDenik* d);

/**
 * @brief Přidá novou tréninkovou jednotku do deníku.  POZNÁMKA: NEŽ SE PŘIDÁ DO SEZNAMU, OTESTUJE SE
 *
 * Tato funkce přidá tréninkovou jednotku na konec seznamu v deníku.
 *
 * @param d Ukazatel na deník.
 * @param jednotka Ukazatel na tréninkovou jednotku, kterou chceme přidat.
 */
void denikPridatJednotku(TDenik* d, TJednotka* jednotka);

/**
 * @brief Odstraní tréninkovou jednotku z deníku na základě zadaného data.
 *
 * @param d Ukazatel na deník.
 * @param datum Datum tréninkové jednotky, kterou je potřeba odstranit (YYYY-MM-DD).
 */
void denikOdstranitJednotku(TDenik* d, const char* datum);

/**
 * @brief Vytiskne všechny tréninkové jednotky v deníku.
 * @param d Ukazatel na deník.
 */
void denikTiskni(TDenik* d);

/**
 * @brief Vytiskne všechny tréninkové jednotky z deníku do souboru.
 * Tato funkce prochází celý deník a zapisuje každou jednotku do souboru.
 * @param d Ukazatel na deník.
 * @param nazevSouboru Název souboru, do kterého budou tréninkové jednotky zapsány.
 */
void denikTiskniDoSouboru(TDenik* d, const char* nazevSouboru);

/**
 * @brief Načte tréninkové jednotky ze souboru a přidá je do deníku.
 * BUDE VOLAT FUNKCE VYTVORJEDNOTKU A OTESTUJJEDNOTKU A DENIKPRIDATJEDNOTKU
 * @param d Ukazatel na deník.
 * @param nazevSouboru Název souboru, ze kterého se mají načíst tréninkové jednotky.
 */
void denikNactiZeSouboru(TDenik* d, const char* nazevSouboru);



#endif // TDENIK_H_INCLUDED
