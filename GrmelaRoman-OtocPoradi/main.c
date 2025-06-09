/*
 * Projekt: úloha na doma - otoč pořadí
 * Autor: Roman Grmela
 * Datum: 22.10. 2023
 */

#include "gvid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false

typedef struct _prvek Tprvek;

struct _prvek{
float hodnota;
Tprvek* dalsi;
};

/*Úkol č. 1 – nový prvek

Vytvoř funkci novyPrvek, která dynamicky alo-
kuje jeden prvek seznamu a vloží do něj za-
danou hodnotu – zde desetinné číslo. Funkce
bude vracet ukazatel na nově alokovaný prvek
nebo NULL, když se to nepovede.
Ukazatel na další prvek nezapomeň inicia-
lizovat hodnotou NULL.*/

Tprvek* novyPrvek(float data){
 Tprvek* novy=malloc(sizeof(Tprvek));
 if(novy != NULL){
  novy->hodnota = data;
  novy->dalsi = NULL;
 }
 return novy;
}

/*Úkol č. 2 – vložení na začátek seznamu

Vytvoř funkci vlozNaZacatek, která dostane
jako parametry číselnou hodnotu, kterou chci
vložit na začátek seznamu a ukazatel na první
prvek seznamu (může být i NULL, když chci
vkládat do prázdného seznamu).
Funkce vyrobí nový prvek a za něj připojí
původní seznam. Vrátí ukazatel na tento nový
prvek a tedy na upravený seznam.*/

Tprvek* vlozNaZacatek(float cislo, Tprvek* prvni){
  Tprvek* novy=malloc(sizeof(Tprvek));
  if(novy == NULL){
    return NULL;
  }
  novy->hodnota=cislo;
  novy->dalsi=NULL;//ASI NENI POTREBA..

  novy->dalsi=prvni;

  return novy;
}

/*Úkol č. 3 – výpis seznamu

Vytvoř funkci vypisPrvky, která dostane uka-
zatel na první prvek seznamu, projde všechny
prvky seznamu a vypíše na výstup hodnoty
všech prvků seznamu. Zastaví se až na prvku,
jehož ukazatel na další prvek obsahuje hodno-
tu NULL.*/

void vypisPrvky(Tprvek* prvni){
 for(Tprvek* pom=prvni; pom!=NULL; pom=pom->dalsi){
  printf("%.2f\n", pom->hodnota);
 }
}

/*
Úkol č. 4 – zrušení seznamu

Vytvoř funkci zrusSeznam, která dostane uka-
zatel na první prvek seznamu a postupně
všechny prvky seznamu uvolní pomocí funkce
free.*/

void zrusSeznam(Tprvek* prvni){
 for(Tprvek* pom=prvni; pom != NULL; pom=prvni->dalsi/*POZOR!!!!!*/){
  prvni=pom->dalsi;//PREMOSTENI!!!
  free(pom); //prvne se to uvolni a az pak se provede 3. prikaz v cyklu...
 }
 //NEMAME ZASTRESUJICI STRUKTURU, TAK NENI POTREBA NIC DALSIHO UVOLNIT :)...
}

/*
Úloha – otoč pořadí

Pomocí podprogramů z předchozích úkolů vy-
tvoř program, který

• zpracuje vstup s předem neznámým po-
čtem prvků (desetinná čísla), přičemž
vstupem může být i soubor.

• vypíše načtené prvky v opačném pořadí,
než v jakém byly načteny.*/



int main(void)
{

  printf("YES!!!!!!!!!!\n\n");

  FILE* vstup = fopen("cviceni-pr5-02-data.txt", "r");

  if(vstup == NULL){
    printf("Neotevrel soubor..\n");
    return -1;
  }

  float cislo;
  if(fscanf(vstup, "%f", &cislo) != 1){
    printf("Nenacetl cislo..\n");
    return -2;
  }

  Tprvek* seznam=novyPrvek(cislo);
  if(seznam == NULL){
    printf("Neplatny ukazatel...\n");
    return -3;
  }


  while(fscanf(vstup, "%f", &cislo) == 1){
    seznam=vlozNaZacatek(cislo, seznam);
  }

  vypisPrvky(seznam);//AUTOMATICKY SE VYPISOU V OPACNEM PORADI...

  printf("\n\nYES!!!!!!!!!!\n");

  //osetrit free seznam
  zrusSeznam(seznam);
  fclose(vstup);
  return 0;
}
