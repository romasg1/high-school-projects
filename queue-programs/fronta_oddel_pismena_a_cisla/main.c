/*
 * Projekt: Ukol ze sesitu: mam text kde jsou cisla..oddel je a vypis do souboru
 * Autor: Roman Grmela
 * Datum: 15.11. 2023
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false


typedef struct _prvek Tprvek;
struct _prvek {
char hodnota;
Tprvek * dalsi;
};


typedef struct {
Tprvek* vrsek;
Tprvek* spod;
} Tfronta;


Tfronta* frInit()
{
  Tfronta* fr= malloc(sizeof(Tfronta));
  if(fr==NULL)
    return NULL;

  fr->vrsek = NULL;
  fr->spod = NULL;

  return fr;
}


bool frEnqueue(Tfronta* fronta, char data)
{
  Tprvek* novy = malloc(sizeof(Tprvek));
  if(novy==NULL)
    return false;

  novy->hodnota = data;
  novy->dalsi=NULL;
  if(fronta->vrsek == NULL)
  {
    fronta->vrsek = novy;
    fronta->spod = novy;
  }
  else
  {
    fronta->spod->dalsi = novy;
    fronta->spod = novy;
  }

  return true;
}


bool frDequeue(Tfronta* fronta, char* data)
{
  if(fronta->vrsek == NULL)
  {
    return false;
  }
  Tprvek* pom= fronta->vrsek;
  *data = pom->hodnota;
  fronta->vrsek = pom->dalsi;
  free(pom);

  if(fronta->vrsek == NULL)
    fronta->spod=NULL;
  return true;
}


void fce(FILE* in, FILE* out){
  Tfronta*f=frInit();
  if(f==NULL)return;

  char znak;
  while(fscanf(in, "%c", &znak) == 1){
    if(znak >= '0' && znak <= '9'){
      fprintf(out, "%c", znak);
    }
    else{
      frEnqueue(f, znak);
    }
  }

  fprintf(out,"\n");
  while(frDequeue(f, &znak)){
    fprintf(out, "%c", znak);
  }

  free(f);
}



//int main(int argc, char *argv[])  // pro parametry prikazoveho radku
int main(void)
{

  FILE* vstup=fopen("fronta_kod_priklad.txt", "r");
  FILE*vystup=fopen("Hotovo.txt" , "w");

  if(vstup == NULL || vystup == NULL){
    printf("Neotevrel..\n");
    return -1;
  }


  fce(vstup, vystup);


  fclose(vstup);
  fclose(vystup);
  return 0;
}
