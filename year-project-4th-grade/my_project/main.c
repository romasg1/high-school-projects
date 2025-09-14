#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
/*
soubor plavci1/2.txt:
Roman Grmela 2006 KomBr 23.82
Daniel Gracik 2004 SCPAP 22.47
Krystof Smehlik 2006 PKKBr 24.78
.........
*/


/*VYTVORENI NOVEHO DATOVEHO TYPU*/
/*PREDPOKLADAME, ZE V SOUBORU NENI ZADNY PLAVEC 2X !!!*/
typedef struct {
  char jmeno[21];
  char prijmeni[21];
  int rocnik;
  char klub[21];
  float osobak;   /*osobni rekord na 50 kraul za rok 2022*/
  bool obsazeno; /*je misto v poli obsazene?...true=ANO */
} TPLAVEC;


/*FCE - INICIALIZACE POLE*/
void init(TPLAVEC p[], int n)
{
   for (int i=0; i<n; i++)
  p[i].obsazeno = false; /*v kazde bunce pole o velikosti MAX se nastaví obsazeno na false*/
}


/*FCE PRO NACITANI ZE SOUBORU DO POLE STRUKTUR*/
int nactiDoPole(FILE *vstup, TPLAVEC pole[]){
  int i=0;
  while(i<MAX && fscanf(vstup, "%20s%20s%d%20s%f", pole[i].jmeno,
    pole[i].prijmeni, &pole[i].rocnik, pole[i].klub, &pole[i].osobak) == 5){
    pole[i].obsazeno=true;/*kdyz se povede nacteni, obsadime bunku pole*/
    i++;
  }

  if(i>MAX){
    printf("Presahl jsi maximalni velikost pole!!!");
    return -1;
  }

  return i;/*vraci pocet nactenych struktur - aktualni velikost pole*/
}


/*FCE PRO VYPIS OBSAZENYCH BUNEK POLE DO SOUBORU*/
void vypisDoSouboru(TPLAVEC pole[], FILE *out, int n){
  fprintf(out, "Jmeno          Prijmeni          Rocnik           Klub            Osobak\n");
  fprintf(out, "--------------------------------------------------------------------------\n");

  for(int i=0; i<n; i++){
    if(pole[i].obsazeno){
      fprintf(out, "%-16s%-18s%-16d%-16s%.2f\n", pole[i].jmeno,
      pole[i].prijmeni, pole[i].rocnik, pole[i].klub, pole[i].osobak);
    }
  }
}


/*FCE PRO OTESTOVANI, ZDA JE POLE SERAZENO PODLE RYCHLOSTI*/
bool serazenoPodleRychlosti(TPLAVEC pole[], int n){
  bool ok;
for(int i=1; i<n; i++){

    if(pole[i-1].osobak < pole[i].osobak){
    ok = true;
       }
  else{
    ok = false;
  }
}
return ok;
}


/*FCE PRO OTESTOVANI, ZDA JE POLE SERAZENO PODLE PRIJMENI*/
bool serazenoPodlePrijmeni(TPLAVEC pole[], int n){
   bool ok;
   for(int i=1; i<n; i++){
    if(strcmp(pole[i-1].prijmeni, pole[i].prijmeni) < 0){
      ok = true;
    }
    else{
      ok = false;
    }
   }
   return ok;
}


/*FCE NAJDE NEJRYCHLEJSIHO PLAVCE V POLI*/
int nejrychlejsiPlavec(TPLAVEC pole[], int n){
  int i=0;
  int kde;/*na jakem indexu lezi nejrychlejsi plavec?*/
  TPLAVEC nej;/*pomocna promenna*/

  for(i=0; i<n; i++){
    if(pole[i].obsazeno){
      kde=i;/*zatim je nejlepsi prvni nacteny plavec...*/
      nej=pole[i];
      break; /*jakmile najdu prvni obsazenou bunku v poli, opoustim cyklus...*/
    }
  }


   for(i=kde+1; i<n; i++){
    if(pole[i].osobak < nej.osobak && pole[i].obsazeno){
      nej=pole[i];
      kde=i;
    }
   }

   return kde;
}


/*FCE VYPISE PLAVCE Z KLUBU KOMETA BRNO*/
void vypisKometaky(TPLAVEC pole[], int n, FILE *out){
  int i;
  int pom=0;
  char ret[] = "KomBr";

  for(i=0; i<n; i++){
    if(strcmp(pole[i].klub, ret) == 0 && pole[i].obsazeno){
      fprintf(out, "%s %s %d %s %.2f\n", pole[i].jmeno,
    pole[i].prijmeni, pole[i].rocnik, pole[i].klub, pole[i].osobak);
    pom++;
    }
  }
  if(pom == 0){
    printf("V tomto souboru neni zadny plavec z komety...\n");
  }
}


/*POMOCNA FCE NAJDE POZICI PLAVCE V POLI PODLE JMENA A PRIJMENI*/
int najdiPlavce(TPLAVEC pole[], int n, char jmeno[], char prijmeni[]){

  for(int i=0; i<n; i++){
    if((strcmp(pole[i].jmeno, jmeno) == 0) && (strcmp(pole[i].prijmeni, prijmeni) == 0) && pole[i].obsazeno){
      return i;
    }
    }
    return -1;/*nenasel jsem...*/
  }


  /*FCE VYPISE RYCHLEJSI PLAVCE NEZ PLAVEC NA NÁM ZNÁMÉ POZICI*/
  void VypisRychlejsi(TPLAVEC pole[], int n, FILE *out, int index){
  int i;/*prvne jsem to chtel srovnat se mnou...srovnaval jsem s polem s indexem 4, kde jsem byl ja...
  ovsem kdyz by napr uzivatel prvne seradil pole a az pak me chtel srovnat..uz bych nejspis nebyl na indexu 4...tak jsem to vyresil takhle...*/

  for(i=0; i<n; i++){
    if(pole[i].osobak < pole[index].osobak && pole[i].obsazeno){
      fprintf(out, "%s %s %d %s %.2f\n", pole[i].jmeno,
    pole[i].prijmeni, pole[i].rocnik, pole[i].klub, pole[i].osobak);
    }
  }
  }


  /*FCE VYPISE POMALEJSI PLAVCE NEZ PLAVEC NA NÁM ZNÁMÉ POZICI*/
  void VypisPomalejsi(TPLAVEC pole[], int n, FILE *out, int index){
  int i;

  for(i=0; i<n; i++){
    if(pole[i].osobak > pole[index].osobak && pole[i].obsazeno){
      fprintf(out, "%s %s %d %s %.2f\n", pole[i].jmeno,
    pole[i].prijmeni, pole[i].rocnik, pole[i].klub, pole[i].osobak);
    }
  }
  }


  /*INSERT SORT - SERADI POLE PODLE OSOBAKU OD NEJRYCHLEJSIHO PO NEJPOMALEJSI*/
  void SeradPodleRychlosti(TPLAVEC pole[], int n) {
  int d, i;
  TPLAVEC vkladany;
  for (d = 1; d < n; d++) {
    vkladany = pole[d]; /*odlozeni vkladaneho (struktura)*/
    i = d;
    while ((i > 0) && (pole[i - 1].osobak > vkladany.osobak)) {
      pole[i] = pole[i - 1];
      i = i - 1;
    }
    pole[i] = vkladany; /*vlozeni vkladaneho*/
  }
}


/*SELECTION SORT - SERADI POLE ABECEDNE PODLE PRIJMENI*/
void SeradPodlePrijmeni(TPLAVEC pole[], int n) {
  int d, minIndex, i;
  TPLAVEC pom;/*pomocna promenna*/
  for (d = 0; d < n - 1; d++) {
    minIndex = d;

    for (i = d + 1; i < n; i++) {
      if (strcmp(pole[i].prijmeni, pole[minIndex].prijmeni) < 0) {
        minIndex = i; /*pozice nejmensiho prvku*/
      }
      /*pro pripad stejneho prijmeni porovname jmeno*/
      if(strcmp(pole[i].prijmeni, pole[minIndex].prijmeni) == 0){
        if(strcmp(pole[i].jmeno, pole[minIndex].jmeno) < 0)
          minIndex=i;
      }
    }
    pom = pole[minIndex];
    pole[minIndex] = pole[d];
    pole[d] = pom;
  }
}


/*FCE NAJDE POZICI PLAVCE PODLE JMENA A PRIJMENI A CELOU STRUKTURU UZIVATEL UPRAVI*/
void upravPlavce(TPLAVEC pole[], int n, char jmeno[], char prijmeni[]){

     int index=najdiPlavce(pole, n, jmeno, prijmeni);
      if(index == -1){
        printf("Tento plavec se v seznamu nenachazi!!!\n");
      }
      else{
        printf("\nUpravujeme plavce: %s %s %d %s %.2f \n\n", pole[index].jmeno,
    pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);

      printf("Zadej jmeno plavce: ");
      scanf("%14s", pole[index].jmeno);
      printf("zadej prijmeni plavce: ");
      scanf("%14s", pole[index].prijmeni);
      printf("Zadej rocnik plavce: ");
      scanf("%d", &pole[index].rocnik);
      printf("Zadej klub plavce: ");
      scanf("%14s", pole[index].klub);
      printf("Zadej osobak na 50 kraul plavce: ");
      scanf("%f", &pole[index].osobak);

      printf("\nZmena probehla uspesne...\n");
      printf("Nova data o plavci: %s %s %d %s %.2f \n", pole[index].jmeno,
    pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);
      }
}


/*FCE URCI POCET PLAVCCU S OSOBAKEM POD 23 SEKUND A VYPISE JE NA OBRAZOVKU*/
int kolikPlavcu(TPLAVEC pole[], int n){
  int kolik=0;
  TPLAVEC pomPole[n];/*pomocne pole..abych potom ty plavce mohl vypsat i na obrazovku...*/
  int j=0;/*ridici promenna cyklu v pomocnem poli a na konci velikost noveho pole...*/
  for(int i=0; i<n; i++){
    if(pole[i].osobak < 23 && pole[i].obsazeno){
      kolik++;
      pomPole[j]=pole[i];
      j++;
    }
  }
  vypisDoSouboru(pomPole, stdout, j);
  return kolik;
}


/*FCE VYHLEDA NEJLEPSIHO PLAVCE Z KLUBU KOMETA BRNO...PRVNE SE POLE SERADI PODLE RYCHLOSTI A HLEDAME PRVNIHO PLAVCE PODLE KLICE = KomBr*/
int najdiNejKometaka(TPLAVEC p[], int n, char klic[]){
int i;

for(i=0; i<n; i++){
  if(p[i].obsazeno && (strcmp(p[i].klub, klic) == 0)){
    return i;
  }
}
return -1;
}


 /*FCE SPOCITA PRUMERNY OSOBAK A URCI, ZDA JE PLAVEC NA JISTÉ POZICI NADPRUMERNY NEBO NE*/
 bool jeNadprumerny(TPLAVEC pole[], int n, int index){
  int aktualniPocet=n;/*na konci to bude ten pocet bez smazanych lidi*/

  float prumernyOsobak;
  float sum=0;
  for(int i=0; i<n; i++){
      if(pole[i].obsazeno){
        sum=sum+pole[i].osobak;
      }
      else{
        aktualniPocet=aktualniPocet-1;
      }
  }
  prumernyOsobak=sum/aktualniPocet;
  printf("\nPrumerny osobak je: %.2f\n", prumernyOsobak);

bool odpoved;
if(pole[index].osobak < prumernyOsobak){
  odpoved=true;
  return odpoved;
}
else{
  odpoved=false;
  return odpoved;
}
}


/*FCE POUZE NASTAVI OBSAZENO NA FALSE*/
void vymazPlavce(TPLAVEC pole[], int n, int index){

if(pole[index].obsazeno){
  pole[index].obsazeno=false;
}

}



/*FCE ULOZI NOVOU STRUKTURU DO POLE, JEHOZ AKTUALNI VELIKOST SE PREDEM ZMENILA*/
int ulozPlavceDoPole(TPLAVEC pole[], int n, TPLAVEC novy){/*n uz je o jedno vetsi...*/
if(n < MAX){
    pole[n-1]=novy;/*na posledni INDEX v poli dam noveho plavce*/
    pole[n-1].obsazeno=true;
    return 0;/*SPRAVNE...*/
}
else{
    printf("Pole nema dostatecnou kapacitu!!!");
    return -1;/*SPATNE...*/
}
}

/*FCE NAJDE PRVNIHO PLAVCE ZE ZADANEHO KLUBU*/
int najdiPodleKlubu(TPLAVEC pole[], int n, char klub[], int index/*index od ktereho hledame klub*/){
int i;
for(i=index; i<n; i++){
    if(pole[i].obsazeno && strcmp(pole[i].klub, klub) == 0){
        return i;
    }
}
return -1;
}


/*FCE VYPISE MOZNOSTI*/
void menu(){
  printf("Vypis data o nejrychlejsim plavci v seznamu................................................1\n");
  printf("Vypis plavce z klubu Kometa Brno...........................................................2\n");
  printf("Je zadany plavec nadprumerny nebo ne?......................................................3\n");
  printf("Srovnej zadaneho plavce s ostatnimi........................................................4\n");
  printf("Serad plavce od nejrychlejsiho po nejpomalejsi.............................................5\n");
  printf("Serad plavce podle abecedy - podle prijmeni................................................6\n");
  printf("Chci data upravit..........................................................................7\n");
  printf("Vypis aktualni pole struktur na obrazovku..................................................8\n");
  printf("Kolik plavcu ma osobak pod 23 vterin?......................................................9\n");
  printf("Kdo je nejrychlejsi plavec z Komety Brno?.................................................10\n");
  printf("Chci plavce odstranit.....................................................................11\n");
  printf("Chci pridat noveho plavce.................................................................12\n");
  printf("Vymaz plavce podle klubu..................................................................13\n");
  printf("Konec programu.............................................................................0\n");
}


/*HLAVNI FCE - PODLE VOLBY UZIVATELE PROVEDE CO JE POZADOVANO....*/
void proved(TPLAVEC pole[], int n, int volba){
  TPLAVEC pom;/*pomocna promenna kam si poslu co vraci funkce...*/
  int index;/*index, kde lezi hledany klic...*/
  char jmeno[15];/*pro hledani jmena...*/
  char prijmeni[15];/*pro hledani prijmeni*/
  int rocnik;/*pro vytvoreni nove polozky*/
  char klub[15];/*pro vytvoreni nove polozky*/
  float osobak;/*pro vytvoreni nove polozky*/
  bool serazeno;/*je to serazene?*/
  int pocet=0;/*kolik pod 23 sekund...*/
  TPLAVEC novy;/*nova struktura*/
  int vysledek;/*pro vetev cislo 12*/
  int volba2;/*pro posledni vetev*/

  switch(volba){

     case 1:
     index=nejrychlejsiPlavec(pole, n);
     printf("Data o nejrychlejsim plavci v seznamu: %s %s %d %s %.2f\n", pole[index].jmeno,
     pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);
     break;


     case 2:
       printf("Plavci z klubu Kometa Brno: \n\n");
       vypisKometaky(pole, n, stdout);
       break;


     case 3:/*je zadany plavec nadprumerny???*/
      printf("Zadej jmeno plavce: ");
      scanf("%14s", jmeno);
      printf("Zadej prijmeni plavce: ");
      scanf("%14s", prijmeni);
      index=najdiPlavce(pole, n, jmeno, prijmeni);
      if(index == -1){
        printf("Tento plavec se v seznamu nenachazi!!!\n");
      }
      else{
        bool ok=jeNadprumerny(pole, n, index);
        if(ok){
          printf("Plavec %s %s je nadprumerny....\n", pole[index].jmeno, pole[index].prijmeni);
        }
        else{
          printf("Plavec %s %s neni nadprumerny....\n", pole[index].jmeno, pole[index].prijmeni);
        }
        printf("Data o plavci: %s %s %d %s %.2f\n",
        pole[index].jmeno, pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);
      }
      break;


     case 4:
        printf("Jakeho plavce chces srovnat?\n\n");
        printf("Zadej jmeno: ");
        scanf("%14s", jmeno);
        printf("Zadej prijmeni: ");
        scanf("%14s", prijmeni);

        index=najdiPlavce(pole, n, jmeno, prijmeni);
      if(index == -1){
        printf("Tento plavec se v seznamu nenachazi!!!\n");
      }
      else{
        printf("\nData o plavci, ktereho srovnavame:\n%s %s %d %s %.2f\n\n", pole[index].jmeno,
      pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);

        printf("--------------------------------------------------------------------------\n");
        printf("Tohle jsou rychlejsi plavci nez %s %s: \n\n", jmeno, prijmeni);
        VypisRychlejsi(pole, n, stdout, index);
        printf("--------------------------------------------------------------------------\n");
        printf("Tohle jsou pomalejsi plavci nez %s %s: \n\n", jmeno, prijmeni);
        VypisPomalejsi(pole, n, stdout, index);
      }
      break;



     case 5:
        SeradPodleRychlosti(pole, n);
        serazeno=serazenoPodleRychlosti(pole, n);

        if(serazeno){
          printf("Plavce se podarilo seradit od nejrychlejsiho po nejpomalejsi. \n");
          printf("--------------------------------------------------------------------------\n");
          vypisDoSouboru(pole, stdout, n);
        }
        else{
          printf("Plavce se nepodarilo seradit...\n");
        }
      break;




      case 6:
        SeradPodlePrijmeni(pole, n);
        serazeno=serazenoPodlePrijmeni(pole, n);

        if(serazeno){
          printf("Plavce se podarilo seradit abecedne podle prijmeni. \n");
          printf("--------------------------------------------------------------------------\n");
          vypisDoSouboru(pole, stdout, n);
        }

        else{
          printf("Plavce se nepodarilo seradit...\n");
        }
        break;




      case 7:
        printf("Zadej jmeno plavce, ketreho chces upravit: ");
        scanf("%14s", jmeno);
        printf("Zadej prijmeni plavce, ktereho chces upravit: ");
        scanf("%14s", prijmeni);
        upravPlavce(pole, n, jmeno, prijmeni);
        break;




      case 8:
        vypisDoSouboru(pole, stdout, n);
        break;



      case 9: pocet=kolikPlavcu(pole, n);
        printf("--------------------------------------------------------------------------\n");
        printf("Pocet plavcu s osobakem pod 23 sekund je: %d\n", pocet);
        break;


      case 10:
        SeradPodleRychlosti(pole, n);
        char klic[]="KomBr";
        index = najdiNejKometaka(pole, n, klic);
        if(index == -1){
          printf("Nenasel jsem...");
        }
        else{
          printf("Nejrychlejsi plavec z Komety Brno je %s %s\n\n", pole[index].jmeno, pole[index].prijmeni);
          printf("Data o plavci: %s %s %d %s %.2f\n",
          pole[index].jmeno, pole[index].prijmeni, pole[index].rocnik, pole[index].klub, pole[index].osobak);
        }
        break;


      case 11:
        printf("Zadej jmeno plavce, ktereho vymazeme: ");
        scanf("%14s", jmeno);
        printf("Zadej prijmeni plavce, ktereho vymazeme: ");
        scanf("%14s", prijmeni);
        index=najdiPlavce(pole, n, jmeno, prijmeni);
        if(index == -1){
          printf("\ntakovy plavec zde neni...\n");
        }
        else{
          vymazPlavce(pole, n, index);
          printf("\nByla odstranena osoba %s %s\n", pole[index].jmeno, pole[index].prijmeni);
        }
        break;


      case 12:
        printf("Zadej jmeno plavce, ktereho chces pridat: ");
        scanf("%14s", novy.jmeno);
        printf("Zadej prijmeni plavce, ktereho chces pridat: ");
        scanf("%14s", novy.prijmeni);
        index = najdiPlavce(pole, n, novy.jmeno, novy.prijmeni);
        if(index != -1){
            printf("Tenhle plavec uz se zde nachazi!!!\n");
            break;
        }
        printf("Zadej rocnik plavce, ktereho chces pridat: ");
        scanf("%d", &novy.rocnik);
        printf("Zadej klub plavce, ktereho chces pridat: ");
        scanf("%14s", novy.klub);
        printf("Zadej osobak plavce, ktereho chces pridat: ");
        scanf("%f", &novy.osobak);

        printf("\nData o novem plavci: %s %s %d %s %.2f\n\n", novy.jmeno,
      novy.prijmeni, novy.rocnik, novy.klub, novy.osobak);
      printf("--------------------------------------------------------------------------\n");

        vysledek=ulozPlavceDoPole(pole, n, novy);
        if(vysledek == 0){
          vypisDoSouboru(pole, stdout, n);
        }
        else{
          printf("Nemame kapacitu bro");
        }
        break;


      case 13:
          printf("Zadej klub plavce, ktereho chces odstranit: ");
          scanf("%14s", klub);
          printf("--------------------------------------------------------------------------\n");
          index=najdiPodleKlubu(pole, n, klub, 0);
        if(index == -1){
          printf("Zadny plavec z klubu %s zde neni...\n", klub);
          break;
        }

        printf("Prvni plavec z klubu %s je -----> %s %s ", pole[index].klub, pole[index].jmeno, pole[index].prijmeni);


          volba2=2;
          while(index<n && index != -1 && volba2 != 1 && (volba2 == 2 || volba2 == 3)/*kdyby nahodou nekdo zadal jinou volbu nez 1, 2 nebo 3...*/){
          printf("\n\nJsi si jisty, ze chces smazat plavce %s %s z klubu %s?\n\n", pole[index].jmeno, pole[index].prijmeni, pole[index].klub);
          printf("1......ANO, SMAZAT A KONEC\n2......ANO, SMAZAT A CHCI SMAZAT DALSIHO\n3......NE, NEMAZAT A PREJIT NA DALSIHO PLAVCE\n\nVolba: ");
          scanf("%d", &volba2);
          printf("--------------------------------------------------------------------------\n");

          switch(volba2){
          case 1:
          vymazPlavce(pole, n, index);
          printf("Byla odstranena osoba %s %s\n", pole[index].jmeno, pole[index].prijmeni);
          printf("--------------------------------------------------------------------------\n");
          printf("Koncim s mazanim...\n");
            break;

          case 2:
            vymazPlavce(pole, n, index);
          printf("Byla odstranena osoba %s %s\n", pole[index].jmeno, pole[index].prijmeni);
          printf("--------------------------------------------------------------------------\n");

          index=najdiPodleKlubu(pole, n, klub, index+1);
          if(index == -1){
          printf("Dalsi plavec z klubu %s zde neni...\n", klub);
            break;
            }

            printf("Dalsi plavec z klubu %s je -----> %s %s ", pole[index].klub, pole[index].jmeno, pole[index].prijmeni);
            break;


          case 3:
            index=najdiPodleKlubu(pole, n, klub, index+1);
          if(index == -1){
          printf("Dalsi plavec z klubu %s zde neni...\n", klub);
            break;
            }

            printf("Dalsi plavec z klubu %s je -----> %s %s ", pole[index].klub, pole[index].jmeno, pole[index].prijmeni);
            break;


          default:
            printf("Smula, netrefil ses!\n");
            break;

          }
                }
        break;


      case 0: printf("Stiskni libovolnou klavesu pro konec programu\n");
        break;


     default: printf("Netrefil ses, zkus to znovu\n");
     break;
  }
  printf("--------------------------------------------------------------------------\n");
  system("pause");/*at se to nevymaze hned..*/

}




/*MAIN - otevreni souboru, test, inicializace pole, nacteni ze souboru do pole, zaloha souboru, prace s programem, zavreni souboru*/
int main(void) {
  printf("       STATISTIKY PLAVCU\n");
  printf("-------------------------------\n");

  char ret[15];
  printf("S jakym souborem chces pracovat?\n----> plavci1.txt / plavci2.txt <-----\n");
  scanf("%14s", ret);
  printf("\n");


  FILE *vstup = fopen(ret, "r");
  FILE *novy = fopen("plavci_zaloha.txt", "w");

  if(vstup == NULL || novy == NULL){
    printf("Soubor se nepodarilo otevrit!!");
    return -1;
  }

  TPLAVEC pole[MAX];
  init(pole, MAX); /*inicializace - obsazeno: false*/
  int n=nactiDoPole(vstup, pole);/*pocet spravne nactenych struktur v poli*/
  printf("Pocet nactenych struktur: %d\n\n", n);


    int volba=1;
    while(volba!=0){
    menu();
    printf("\n");
    printf("Zadej volbu: ");
    scanf("%d", &volba);
    if(volba == 12){
      n=n+1;/*kdyz pridavam plavce, potrebuji zvednout aktualni velikost pole...*/
      if(n>MAX){
        printf("Presahl jsi maximalni velikost pole!!!");
        return -1;
      }
    }
    printf("--------------------------------------------------------------------------\n");

      proved(pole, n, volba);
      system("cls");/*smaze obrazovku*/

  }


  vypisDoSouboru(pole, novy, n); /*Zaloha dat do noveho souboru po zmenach v programu zadane uzivatelem*/


  fclose(vstup);
  fclose(novy);
  return 0;
}
