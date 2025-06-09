#include <stdio.h>
#include <stdlib.h>

/*VYHLEDEJ NEJMLADSI ZVIRE Z PAVILONU 5...

soubor:
pocet(nemusi sedet)
jmeno, rod, vek, pohlavi, pavilon...

14
Adam papousek 4 0 11
Borka zebra 6 1 3
Jeliman Lemur 2 0 5
*/

typedef struct{
char jmeno[15];
char rod[15];
int vek, pohlavi, pavilon;
}TZVIRE;

int nacti(FILE *f, TZVIRE p[], int n){
int i=0;
while(i<n && fscanf(f, "%14s%14s%d%d%d",
  p[i].jmeno, p[i].rod, &p[i].vek, &p[i].pohlavi, &p[i].pavilon) == 5){
  i++;
}
return i;
}

void vypis(TZVIRE p[], int n){
printf("Jmeno          Rod          Vek        pohlavi       pavilon\n------------------------------------------------------------------------\n");

  for(int i=0; i<n; i++){
    printf("%-15s%-14s%-13d%-13d%d\n", p[i].jmeno, p[i].rod, p[i].vek, p[i].pohlavi, p[i].pavilon);
  }

  }

void serad(TZVIRE p[], int n){
  int i, d;
  TZVIRE pom;
  for(int d=0; d<n-1; d++){
    for(int i=n-1; i>d; i--){
      if(p[i].vek < p[i-1].vek){
        pom=p[i-1];
        p[i-1]=p[i];
        p[i]=pom;
      }
    }
  }
  }

  int najdi(TZVIRE p[], int n, int klic){
  int i=0;
  while(i<n && p[i].pavilon != klic){
    i++;
  }
  if(i<n){
    return i;
  }
  return -1;
  }




    int main()
{
    FILE *f = fopen("OPRAVNYTEST.txt", "r");

    if(f == NULL){
      printf("neotevrel");
      return -1;
    }

    int n;
    if(fscanf(f, "%d", &n) != 1){
      printf("Nenacteno");
      return -2;
    }


    TZVIRE p[n];
    n=nacti(f, p, n);
    printf("pocet: %d\n\n", n);

    vypis(p, n);
    printf("\n\n");
    serad(p, n);
    printf("\n\n");
    vypis(p, n);
    printf("\n\n");

    int pozice=najdi(p, n, 5);
    if(pozice != -1){
      printf("Nejmladsi zvire z pavilonu 5 je %s a jeho vek: %d", p[pozice].jmeno, p[pozice].vek);
    }

    else{
      printf("Zvire z pavilonu 5 tu neni,.....");
    }



    fclose(f);
    return 0;
}
