/*
 * Projekt: Fronta - cviko ve škole
 * Autor: Roman Grmela
 * Datum: 20.10. 2023
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false


typedef struct _prvek Tprvek;

struct _prvek {
float hodnota;
Tprvek * dalsi;
};


typedef struct {
Tprvek* prvni;
Tprvek* posledni;
int delka;
int maxDelka;
} Tfronta;


/*TISK funguje*/
void tisk(Tfronta* q){
  for(Tprvek* pom=q->prvni; pom != NULL; pom=pom->dalsi){
    printf("%.2f\n", pom->hodnota);
  }
}


/*inicializace fronty funguje*/
Tfronta* frontaInit(int maxDelka){
  Tfronta* q=malloc(sizeof(Tfronta));
  if(q == NULL){
    printf("Chyba alokace..\n");
    return NULL;
  }
  q->prvni=NULL;
  q->posledni=NULL;

  q->delka=0;
  q->maxDelka=maxDelka;

  return q;
}



/*ENQUEUE - funguje..pozor na vkladani prvniho!!*/
bool frontaEnqueue(Tfronta* q, float data){
  // Vyrob nový prvek, když to nejde vrať false.
  Tprvek* novy = malloc(sizeof(Tprvek));
  if(novy == NULL){
    printf("Chyba alokace noveho prvku..\n");
    return false; //NEZAPOMEN VRACET FALSE
  }

//Kopíruj data do prvku. Nový >další nastav na NULL
  novy->hodnota=data;
  novy->dalsi=NULL;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Poslední >další ať ukazuje na nový...TO PLATI POUZE KDYZ JE FRONTA PLNA....
if(q->posledni == NULL){
    q->posledni=novy;
}
else{
 q->posledni->dalsi=novy; //TADY BY TO SPADLO..LEZL BYCH DO DALSIHO, KTERY NEEXISTUJE
//Poslední ať ukazuje na nový prvek.
q->posledni=novy;
}

//Je-li první prázdný, ať ukazuje na nový prvek.
if(q->prvni == NULL){
    q->prvni=novy;
}

q->delka++;
return true;
}

/*dequeue funguje*/
bool frontaDequeue(Tfronta* f, float* data){
  //Je-li fronta prázdná, vrať false.
  if(f->prvni == NULL){
    return false;
  }

//Pamatuj si ukazatel na první prvek.
Tprvek* pom=f->prvni;
//Ukazatel na první nastav na první >další.
f->prvni=pom->dalsi;

//Kopíruj data prvního do parametru data.
//Uvolni zapamatovaný prvek.
*data = pom->hodnota;
free(pom);
//Je-li první NULL, nastav poslední na NULL.
if(f->prvni == NULL){
    f->posledni = NULL;
}

f->delka--;
return true;
}


/*FREE: funguje..uvolní pamět pro frontu*/
void frontaFree(Tfronta* fronta){
  float hodnota;
  while(frontaDequeue(fronta, &hodnota));

  free(fronta);
}



/*fce pro nacteni ze souboru...*/
void nacti(FILE *vstup, Tfronta* f, int n){

  int delkaSouboru;
  if(fscanf(vstup, "%d", &delkaSouboru) != 1){
    printf("Nenacetl delku ze souboru..\n");
  }
  float data; //pro ulozeni hodnoty co mi vrati dequeue...POZOR NA DATOVY TYP...JE TO FLOAT!!!NE INT
  float cislo; //pro poslani dat do enqueue
  for(int i=0; i<delkaSouboru; i++){
    if(fscanf(vstup, "%f", &cislo) != 1){
      printf("Konec..\n");
    }
    if(f->delka == n){
      frontaDequeue(f, &data);
    }
    frontaEnqueue(f, cislo);
    /*NEBO..
    if(f->delka < f->maxDelka){
      frontaEnqueue(f, cislo);
    }
    else{
      frontaDequeue(f, &data);
      frontaEnqueue(f, cislo);
    }
    */
  }//konec cyklu for
}





int main(void)
{

  int n;
  printf("Kolik poslednich prvku chces vypsat? ");
  scanf("%d", &n);
  printf("-------------------------------------\n");


  FILE* vstup=fopen("data10k.txt", "r");
  if(vstup == NULL){
    printf("Neotevrel soubor..\n");
    return -1;
  }

  Tfronta* q=frontaInit(n);
  //melo by se vse overit..jestli q neni null..nebo jestli fce bool fraci false...atd..
  if(q == NULL){
    printf("Chyba alokace fronty...\n");
    return -2;
  }

  nacti(vstup, q, n);


  /*overeni ze enqueue funguje..
  frontaEnqueue(q, 2.2);
  frontaEnqueue(q, 3.2);
  frontaEnqueue(q, 33.2);
  frontaEnqueue(q, 11.2);*/



  /* OVERENI JESTLI FUNGUJE DEQUEUE
  float data;
  frontaDequeue(q, &data);
  printf("Data prvniho odstraneneho prvku: %.2f\n", data);*/


  //tisk(q);

  float dataNaVypsani;
  while(q->delka > 0){
    frontaDequeue(q, &dataNaVypsani);
    printf("%.2f\n", dataNaVypsani);
  }


  fclose(vstup);
  frontaFree(q);
  return 0;
}
