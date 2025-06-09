/*
 * Projekt: vypis prvne slova ktera zacinaji velkym pismenem
 * Autor: Grmela Roman + detekce chyb CHATGPT
 * Datum: 23.11
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false


typedef struct _prvek Tprvek;

struct _prvek {
char hodnota[20];
Tprvek * dalsi;
};


typedef struct {
Tprvek* prvni;
Tprvek* posledni;
} Tfronta;


/*inicializace fronty funguje*/
Tfronta* frontaInit(){
  Tfronta* q=malloc(sizeof(Tfronta));
  if(q == NULL){
    printf("Chyba alokace..\n");
    return NULL;
  }
  q->prvni=NULL;
  q->posledni=NULL;
  return q;
}



/*ENQUEUE - funguje..pozor na vkladani prvniho!!*/
bool frontaEnqueue(Tfronta* q, char data[]){
  Tprvek* novy = malloc(sizeof(Tprvek));
  if(novy == NULL){
    printf("Chyba alokace noveho prvku..\n");
    return false; //NEZAPOMEN VRACET FALSE
  }

  strcpy(novy->hodnota, data);
  novy->dalsi=NULL;

if(q->posledni == NULL){
    q->posledni=novy;
}
else{
 q->posledni->dalsi=novy;
q->posledni=novy;
}

if(q->prvni == NULL){
    q->prvni=novy;
}


return true;
}

/*dequeue funguje*/
bool frontaDequeue(Tfronta* f, char* data){
  //Je-li fronta prázdná, vrať false.
  if(f->prvni == NULL){
    return false;
  }

Tprvek* pom=f->prvni;
f->prvni=pom->dalsi;

strcpy(data, pom->hodnota);
free(pom);

if(f->prvni == NULL){
    f->posledni = NULL;
}

return true;
}


void frontaFree(Tfronta* fronta){
  char hodnota[20];
  while(frontaDequeue(fronta, hodnota));

  free(fronta);
}


void fce(FILE* in, FILE* out){
  Tfronta* f=frontaInit();
  if(f == NULL)return;

  char slovo[15];
  char slovoNaDeq[15];
  while(fscanf(in, "%14s", slovo) == 1){
    if(slovo[0] >= 'A' && slovo[0] <= 'Z'){
      fprintf(out, "%s\n", slovo);
    }
    else{
      frontaEnqueue(f, slovo);
    }
  }//while

  fprintf(out, "\n\n");


  while(frontaDequeue(f, slovoNaDeq)){
    fprintf(out, "%s\n", slovoNaDeq);
  }

  frontaFree(f);
}



//int main(int argc, char *argv[])  // pro parametry prikazoveho radku
int main(void)
{

  char nazev[20];
  printf("Zadej nazev souboru: ");
  scanf("%19s", nazev);

  FILE* f=fopen(nazev, "r");
  FILE* vystup=fopen("Hotovo.txt", "w");

  if(f == NULL || vystup == NULL){
    printf("Neotevrel..\n");
    return -1;
  }

  fce(f, vystup);


  fclose(f);
  fclose(vystup);
  return 0;
}
