/*
 * Projekt: Tréninkový deník - jako DDS
 * Autor: Roman Grmela 6.G - GVID
 * Datum: 3.11. 2024
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false
#include <ctype.h>   // isalpha, isspace, islower, isupper, ...
#include <math.h>    // funkce z matematicke knihovny
#include <float.h>   // konstanty pro racionalni typy DBL_MAX, DBL_DIG, ...
#include <limits.h>  // konstanty pro celociselne typy INT_MAX, INT_MIN, ...
#include <time.h>    // funkce time a dalsi pro praci s casem

#include "TDenik.h"

void tiskniNapovedu() {
    system("cls");//vycisti obrazovku a uvidim jenom toto..


    printf("===============================================================================\n");
    printf("                      NAPOVEDA K POUZIVANI APLIKACE      \n");
    printf("===============================================================================\n");
    printf("Na kazdem radku se nachazi data k treninkove jednotce v nasledujicim poradi:\n");
    printf("\n");
    printf("1. DATUM:         zadavej ve tvaru: YYYY-MM-DD\n");
    printf("2. AKTIVITA:      klicova slova: plavani, posilovna, strecink, masaz, sauna\n");
    printf("3. DELKA TRVANI:  delka treninku uvedena v minutach (cela cisla)\n");
    printf("4. NAROCNOST:     RPE = Rate of Perceived Exertion; ciselna hodnota v rozsahu 1-10\n");
    printf("\n");
    printf("Priklad platneho radku: 2024-10-12 plavani 100 7\n");
    printf("\n");
    printf("Pokud je format souboru spatny, vypise se chybove hlaseni.\n");
    printf("Doporucujeme pravidelne zaznamenavat sve treninky pro lepsi prehled.\n");
    printf("Pro pridani nove jednotky muzete vyuzit funkci denikPridatJednotku.\n");
    printf("Caste chyby: zkontrolujte format datumu a typ aktivity.\n");
    printf("===============================================================================\n");
}


void tiskniMenu() {

   // Vyčistí obrazovku
    system("cls");  // nebo system("clear"); pro Linux/Mac

    printf("\n");
    printf("*********************************************\n");
    printf("*         APLIKACE - TRENINKOVY DENIK       *\n");
    printf("*********************************************\n");
    printf("*  [0] - KONEC                              *\n");
    printf("*  [1] - NAPOVEDA                           *\n");
    printf("*  [2] - VYPIS DENIKU                       *\n");
    printf("*  [3] - PRIDAT JEDNOTKU                    *\n");
    printf("*  [4] - ODSTRANIT JEDNOTKU                 *\n");
    printf("*  [5] - STATISTIKY                         *\n");
    printf("*  [6] - ULOZ STAV DENIKU                   *\n");
    printf("*********************************************\n");
}



void denikVypisStatistiky(TDenik* d) {
    if (denikJePrazdny(d)) {
        printf("Denik je prazdny, nejsou dostupne zadne statistiky.\n");
        return;
    }

    int celkovyPocet = 0;
    int soucetDelky = 0;
    int soucetNarocnosti = 0;
    int nejdelsiDelka = 0;
    int nejtezsiNarocnost = 0;
    char nejtezsiDatum[20] = "";
    char nejtezsiAktivita[50] = "";
    char nejdelsiDatum[20] = "";
    char nejdelsiAktivita[50] = "";

    // Tabulka aktivit (max 10 ruznych aktivit, muze se rozsirit)
    typedef struct {
        char aktivita[50];
        int pocet;
        int soucetDelkyAktivity;
        int maxDelka;
    } TAktivitaStat;
    TAktivitaStat aktivity[10];
    int pocetAktivit = 0;

    // Pruchod seznamem treninku
    TJednotka* aktualni = d->prvni;
    while (aktualni != NULL) {
        celkovyPocet++;
        soucetDelky += aktualni->delkaTrvani;
        soucetNarocnosti += aktualni->narocnost;

        // Kontrola nejtezsiho treninku
        if (aktualni->narocnost > nejtezsiNarocnost) {
            nejtezsiNarocnost = aktualni->narocnost;
            strcpy(nejtezsiDatum, aktualni->datum);
            strcpy(nejtezsiAktivita, aktualni->aktivita);
        }

        // Kontrola nejdelsiho treninku
        if (aktualni->delkaTrvani > nejdelsiDelka) {
            nejdelsiDelka = aktualni->delkaTrvani;
            strcpy(nejdelsiDatum, aktualni->datum);
            strcpy(nejdelsiAktivita, aktualni->aktivita);
        }

        // Ulozeni poctu treninku pro kazdou aktivitu
        int nalezeno = 0;
        for (int i = 0; i < pocetAktivit; i++) {
            if (strcmp(aktivity[i].aktivita, aktualni->aktivita) == 0) {
                aktivity[i].pocet++;
                aktivity[i].soucetDelkyAktivity += aktualni->delkaTrvani;
                if (aktualni->delkaTrvani > aktivity[i].maxDelka) {
                    aktivity[i].maxDelka = aktualni->delkaTrvani;
                }
                nalezeno = 1;
                break;
            }
        }
        if (!nalezeno && pocetAktivit < 10) {
            strcpy(aktivity[pocetAktivit].aktivita, aktualni->aktivita);
            aktivity[pocetAktivit].pocet = 1;
            aktivity[pocetAktivit].soucetDelkyAktivity = aktualni->delkaTrvani;
            aktivity[pocetAktivit].maxDelka = aktualni->delkaTrvani;
            pocetAktivit++;
        }

        aktualni = aktualni->dalsi;
    }

    // Vypocet prumeru
    float prumernaDelka = soucetDelky / celkovyPocet;
    float prumernaNarocnost = soucetNarocnosti / celkovyPocet;

    // Vypis statistik
    printf("\n--- STATISTIKY DENIKU ---\n");
    printf("Celkovy pocet treninku: %d\n", celkovyPocet);
    printf("Celkovy cas vsech treninku: %d minut\n", soucetDelky);
    printf("Prumerna delka treninku: %.2f minut\n", prumernaDelka);
    printf("Prumerna narocnost: %.2f / 10\n", prumernaNarocnost);

    printf("Nejtezsi trenink: %s - %s (Narocnost: %d/10)\n", nejtezsiDatum, nejtezsiAktivita, nejtezsiNarocnost);
    printf("Nejdelsi trenink: %s - %s (Delka: %d minut)\n", nejdelsiDatum, nejdelsiAktivita, nejdelsiDelka);

    // Vypis poctu treninku podle aktivit
    printf("\n--- Pocet treninku podle aktivit ---\n");
    for (int i = 0; i < pocetAktivit; i++) {
        float prumerDelkyAktivity = aktivity[i].soucetDelkyAktivity / aktivity[i].pocet;
        printf("%s: %d treninku\n", aktivity[i].aktivita, aktivity[i].pocet);
        printf("  - Prumerna delka treninku: %.2f minut\n", prumerDelkyAktivity);
        printf("  - Nejvetsi delka treninku: %d minut\n", aktivity[i].maxDelka);
    }
}






//int main(int argc, char *argv[])  // pro parametry prikazoveho radku
int main(void)
{
    TDenik* denik = denikInicializuj(); // Inicializace treninkoveho deniku

    if (denik == NULL) {
        printf("Nepodarilo se alokovat pamet pro denik.\n");
        return -1; // Chyba pri alokaci
    }

    char volba[20]; // Políčko pro uložení celé volby jako řetězce
    bool spravnaVolba = false;

    // Cyklus pro overeni spravne volby
    while (!spravnaVolba) {
        printf("Chces pokracovat s prazdnym denikem? [Y/N]: ");
        scanf("%19s", volba); // Čteme volbu jako řetězec s maximálně 19 znaky

        // Vyčistíme buffer, pokud zadal uživatel něco většího než 1 slovo
        if (getchar() != '\n') {
            while (getchar() != '\n'); // Vyčištění bufferu
        }

        // Porovnáme řetězce pro Y nebo N
        if (strcmp(volba, "Y") == 0 || strcmp(volba, "y") == 0) {
            printf("Prazdny denik je k dispozici.\n");
            spravnaVolba = true; // Spravna volba, ukoncime cyklus
        } else if (strcmp(volba, "N") == 0 || strcmp(volba, "n") == 0) {
            char nazev[20 + 1]; // Nazev souboru
            printf("Zadej nazev souboru s daty: ");
            scanf("%20s", nazev);
            nazev[20] = '\0'; // Ruční ukončení řetězce

            // Zavolani funkce denikNactiZeSouboru
            printf("Nacitam soubor: %s\n", nazev);
            denikNactiZeSouboru(denik, nazev);

            if (denik->pocetJednotek > 0) { // Kontrola, zda denik obsahuje nejake jednotky
                printf("Soubor byl nacten.\n");
                //denikTiskni(denik); // Vypis nactenych dat
            } else {
                printf("Soubor neobsahuje platna data nebo se nacteni nezadarilo.\n");
                printf("Konec programu.\n");
                denikUvolni(denik);
                return -1;

            }

            spravnaVolba = true; // Spravna volba, ukoncime cyklus
        } else {
            printf("Neplatna volba - zadej Y/N\n");
        }
    }//konec cyklu while pro volbu

    char datum[11];
    char aktivita[15];
    int delkaTrvani, narocnost;

    while (1) {
        tiskniMenu(); // Zobrazit menu
        printf("Zadej volbu: ");
        scanf("%19s", volba);  // Čteme volbu uživatele jako řetězec

        // Ošetření neplatných voleb pomocí switch
        switch (volba[0]) { // Pro switch použijeme první znak řetězce
            case '0':
                printf("Konec programu.\n");
                denikUvolni(denik); // Uvolnit alokovanou paměť před ukončením
                return 0; // Ukončí program
            case '1':
                tiskniNapovedu();
                break;
            case '2':
                denikTiskni(denik);
                break;
            case '3':
                // Akce pro volbu 3
                printf("Zadej datum v platnem tvaru (YYYY-MM-DD): ");
                scanf("%10s", datum);
                printf("Zadejte aktivitu: ");
                scanf("%14s", aktivita);
                printf("Zadejte delku trvani (v minutach): ");
                scanf("%d", &delkaTrvani);
                printf("Zadejte narocnost (1-10): ");
                scanf("%d", &narocnost);

                 // Otestujeme jednotku
                if (!_otestujJednotku(datum, aktivita, delkaTrvani, narocnost)) {
                   printf("Neplatna treninkova jednotka! Zkuste to znovu.\n");
                   break;
                    }

                   // Vytvoření nové jednotky
                   TJednotka* novaJednotka = _vytvorJednotku(datum, aktivita, delkaTrvani, narocnost);
                   if (novaJednotka == NULL) {
                   printf("Chyba při alokaci paměti!\n");
                   break;
                    }

                  denikPridatJednotku(denik, novaJednotka);
                  printf("Jednotka byla uspesne pridana do deniku");
                break;

            case '4':
                // Akce pro volbu 4

                 printf("Zadej datum v platnem tvaru (YYYY-MM-DD): ");
                 scanf("%10s", datum);
                 denikOdstranitJednotku(denik, datum);
                break;
            case '5':
                // Akce pro volbu 5
                denikVypisStatistiky(denik);

                break;

            case '6':
                // Akce pro volbu 6
                if(denikJePrazdny(denik)){
                  printf("Nemuzu ulozit stav deniku, je prazdny!");
                  break;
                }
                char nazevSouboru[50];
                printf("Zadej nazev souboru pro ulozeni: ");
                scanf("%49s", nazevSouboru);

                denikTiskniDoSouboru(denik, nazevSouboru);
                printf("Denik byl uspesne ulozen do souboru %s.", nazevSouboru);
                break;

            default:
                printf("Neplatna volba, prosim zadejte cislo mezi 0 a 6.\n");
                break; // Pokud uživatel zadá něco jiného, neplatnou volbu
        }

        // Pauza pro zobrazení před dalším zobrazením menu
        printf("\nStiskni Enter pro dalsi akci...");
        getchar();  // Po stisknutí libovolné klávesy pokračuje
        getchar();  // Druhý getchar() pro odstranění Enter po scanf
    }

    denikUvolni(denik);
    return 0;
}
