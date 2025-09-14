#include <stdio.h>
#include <stdlib.h>

/*vyhledej zaka kdo ma petku ze vseho...serad od nejlepsiho zaka podle prumeru*/

typedef struct{
char jmeno[15];
int pohlavi, m, cj, f;
float prumer;
}TZAK;


int nacti(TZAK pole[], FILE *vstup, int n){
int i=0;
while(i<n/*NEZAPOMENOUT!!!*/ && fscanf(vstup, "%14s%d%d%d%d",
      pole[i].jmeno, &pole[i].pohlavi, &pole[i].m, &pole[i].cj, &pole[i].f) == 5){
        pole[i].prumer=(pole[i].m + pole[i].cj + pole[i].f)/3.;/*NEZAPOMENOUT NA POLE[I].PRUMER....NE JENOM PRUMER...musi to byt realna trojka...A MUSI TO BYT PRED TIMMMMMMM*/
        i++;

      }

      return i;
}



int najdiZaka(TZAK p[], int n, int klic){
int i=0;
/*MUSIM DAT DVOJTOU ZAVORKU...PROTOZE JINAK BY TO NEJELO....!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!§§*/
while(i<n && (p[i].m !=klic || p[i].cj !=klic || p[i].f !=klic)){/*FUNGUJE POUZE S NEBO...KDYBYCH TAM DAL &&, TAK BY TO FUNGOVALO POUZE POKUD BY TO BYL HNED TEN PRVNI STUDENT...*/
  i=i+1;
}

if(i<n){
  return i;
}

return -1;
}



void vypis(TZAK p[], int n, FILE *out){
int i;
printf("Jmeno      Pohlavi       M       Cj        F        Prumer\n");
for(i=0; i<n; i++){
  fprintf(out, "%-15s%d        %d         %d        %d      %.2f\n", p[i].jmeno, p[i].pohlavi, p[i].m, p[i].cj, p[i].f, p[i].prumer);
}
}


void serad(TZAK pole[], int n){
  int i, d;
  TZAK pom;
  for(d=0; d<n-1; d++){
    for(i=n-1; i>d; i--){
      if(pole[i-1].prumer > pole[i].prumer){
        pom=pole[i-1];
        pole[i-1]=pole[i];
        pole[i]=pom;
      }
    }
  }
}



int main()
{
    char nazev[14];
    printf("S jakym souborem pracujes?");
    scanf("%13s", nazev);

    FILE *f = fopen(nazev, "r");

    if(f == NULL){
      return -1;
    }

    int pocet;
    if(fscanf(f, "%d", &pocet) !=1){
      return -2;
    }

    TZAK pole[pocet];

    pocet = nacti(pole, f, pocet);
    printf("Pocet: %d\n", pocet);

    vypis(pole, pocet, stdout);
    serad(pole, pocet);
    printf("\n\n");
    vypis(pole, pocet, stdout);
    printf("\n\n");

    int pozice=najdiZaka(pole, pocet, 5);/*POSLAT KLIC...*/
    if(pozice == -1){
      printf("Zak ktery ma ze vseho petku se zde nevyskytuje....");
    }
    else{
      printf("Zak, ktery ma ze vseho petku je %s", pole[pozice].jmeno);
    }

    fclose(f);
    return 0;
}
