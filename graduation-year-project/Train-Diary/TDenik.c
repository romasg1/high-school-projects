#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "TDenik.h"


/**
 * \brief Inicializuje strukturu tréninkového deníku.
 *
 * Tato funkce alokuje paměť pro novou instanci tréninkového deníku,
 * nastavuje ukazatele na první a poslední jednotku na NULL a
 * počáteční počet jednotek na 0.
 *
 * \param void
 * \return TDenik* Ukazatel na inicializovaný deník nebo NULL v případě chyby.
 */
TDenik* denikInicializuj(void) {
    TDenik* denik = malloc(sizeof(TDenik));
    if (denik != NULL) {
        denik->prvni = NULL;       // Inicializace prvního ukazatele na NULL
        denik->posledni = NULL;    // Inicializace posledního ukazatele na NULL
        denik->pocetJednotek = 0;  // Počet jednotek nastaven na 0
    }
    return denik; // Vrátí ukazatel na inicializovaný deník
}


/**
 * @brief Kontroluje, zda je tréninkový deník prázdný.
 *
 * Tato funkce ověřuje, zda deník obsahuje nějaké tréninkové jednotky. Pokud je ukazatel na deník nebo
 * ukazatel na první jednotku v deníku `NULL`, funkce vrátí `true`, což znamená, že deník je prázdný.
 * Pokud deník obsahuje alespoň jednu jednotku, vrátí `false`.
 *
 * @param d Ukazatel na tréninkový deník, který má být zkontrolován.
 *
 * @return `true`, pokud je deník prázdný, jinak `false`.
 */

bool denikJePrazdny(TDenik* d) {
    if (d == NULL || d->prvni == NULL) {
        return true; // Deník je prázdný
    }
    return false; // Deník není prázdný
}



// Seznam povolených aktivit
const char* povoleneAktivity[] = {"plavani", "posilovna", "strecink", "sauna", "masaz"};
const int pocetAktivit = 5;


/**
 * @brief Kontroluje, zda je zadané datum ve správném formátu.
 *
 * Tato funkce ověřuje, zda zadané datum má formát "YYYY-MM-DD", kde:
 * - "YYYY" je rok ve čtyřech číslicích,
 * - "MM" je měsíc ve dvou číslicích (od 01 do 12),
 * - "DD" je den ve dvou číslicích (od 01 do 31).
 * Funkce nejprve kontroluje, že délka řetězce je 10 znaků a že znaky na pozicích 4 a 7 jsou pomlčky.
 * Poté zkontroluje, že všechny ostatní znaky jsou číslice.
 *
 * @param datum Řetězec obsahující datum ve formátu "YYYY-MM-DD".
 *
 * @return `true`, pokud je datum ve správném formátu, jinak `false`.
 */

bool _jePlatneDatum(const char* datum) {
    if (strlen(datum) != 10 || datum[4] != '-' || datum[7] != '-') {
        return false; // Neplatný formát data
    }

    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && datum[i] != '-') {
            return false; // Špatný formát
        }
        if ((i != 4 && i != 7) && !isdigit(datum[i])) {
            return false; // Pokud není číslice, datum je neplatné
        }
    }

    // Doplnit kontrolu pro měsíc a den podle jejich rozsahu
    return true;
}

/**
 * @brief Kontroluje, zda je zadaná aktivita platná.
 *
 * Tato funkce porovnává zadanou aktivitu s předdefinovaným seznamem povolených aktivit.
 * Pokud zadaná aktivita odpovídá některé z povolených aktivit, funkce vrací hodnotu `true`.
 * Pokud aktivita není v seznamu povolených aktivit, vrací `false`.
 *
 * @param aktivita Název aktivity, kterou chceme ověřit.
 *
 * @return `true`, pokud je aktivita platná (nachází se v seznamu povolených aktivit), jinak `false`.
 */

bool _jePlatnaAktivita(const char* aktivita) {
    for (int i = 0; i < pocetAktivit; i++) {
        if (strcmp(aktivita, povoleneAktivity[i]) == 0) {
            return true; // Aktivita je povolená
        }
    }
    return false; // Aktivita není povolená
}

/**
 * @brief Kontroluje, zda je zadaná délka trvání v platném rozsahu.
 *
 * Tato funkce ověřuje, zda je hodnota délky trvání tréninkové jednotky kladná.
 * Pokud je délka trvání nulová nebo záporná, funkce vrací hodnotu `false`, jinak `true`.
 *
 * @param delkaTrvani Délka trvání tréninkové jednotky v minutách.
 *
 * @return `true`, pokud je délka trvání kladná, jinak `false`.
 */

bool _jePlatnaDelkaTrvani(int delkaTrvani) {
    if (delkaTrvani <= 0) {
        return false; // Záporná nebo nulová délka trvání
    }
    return true; // Platná délka trvání
}


/**
 * @brief Kontroluje, zda je zadaná náročnost v platném rozsahu.
 *
 * Tato funkce ověřuje, zda je hodnota náročnosti v platném rozsahu mezi 1 a 10.
 * Pokud je náročnost mimo tento rozsah, funkce vrací hodnotu `false`, jinak `true`.
 *
 * @param narocnost Hodnota náročnosti tréninkové jednotky.
 *
 * @return `true`, pokud je náročnost v platném rozsahu (1 až 10), jinak `false`.
 */

bool _jePlatnaNarocnost(int narocnost) {
    if (narocnost < 1 || narocnost > 10) {
        return false; // Neplatná náročnost
    }
    return true; // Platná náročnost
}

/**
 * @brief INTERNI FUNKCE ---> Otestuje platnost treningove jednotky.
 * @param datum Datum treningove jednotky.
 * @param aktivita Typ aktivity.
 * @param delkaTrvani Delka trvani treningove jednotky.
 * @param narocnost Narocnost treningove jednotky.
 * @return true Pokud je jednotka platna.
 * @return false Pokud je jednotka neplatna.
 */
bool _otestujJednotku(const char* datum, const char* aktivita, int delkaTrvani, int narocnost) {

    // Kontrola platnosti data
    if (!_jePlatneDatum(datum)) {
        printf("Chybny format data: %s\n", datum);
        return false;
    }

    // Kontrola platnosti aktivity
    if (!_jePlatnaAktivita(aktivita)) {
        printf("Neplatna aktivita: %s\n", aktivita);
        return false;
    }

    // Kontrola platnosti delky trvani
    if (!_jePlatnaDelkaTrvani(delkaTrvani)) {
        printf("Chybna delka trvani: %d minut\n", delkaTrvani);
        return false;
    }

    // Kontrola platnosti narocnosti
    if (!_jePlatnaNarocnost(narocnost)) {
        printf("Chybna narocnost: %d/10\n", narocnost);
        return false;
    }

    return true; // Pokud prosla vsechny kontroly, jednotka je platna
}





/**
 * @brief INTERNÍ FUNKCE: Vytvoří novou tréninkovou jednotku.
 *
 * Tato funkce alokuje paměť pro novou instanci tréninkové jednotky,
 * nastavuje její atributy na základě předaných parametrů.
 *
 * @param datum Datum tréninkové jednotky ve formátu YYYY-MM-DD.
 * @param aktivita Typ aktivity (např. plavání, posilovna).
 * @param delkaTrvani Délka trvání tréninkové jednotky v minutách.
 * @param narocnost Náročnost tréninkové jednotky (1-10).
 * @return Ukazatel na novou tréninkovou jednotku nebo NULL v případě chyby.
 */
TJednotka* _vytvorJednotku(const char* datum, const char* aktivita, int delkaTrvani, int narocnost) {
    TJednotka* jednotka = malloc(sizeof(TJednotka));
    if (jednotka == NULL) {
        return NULL;
    }

    // Nastavení atributů tréninkové jednotky
    strcpy(jednotka->datum, datum);  // Použití strcpy pro kopírování řetězce
    strcpy(jednotka->aktivita, aktivita);  // Použití strcpy pro kopírování aktivity
    jednotka->delkaTrvani = delkaTrvani;
    jednotka->narocnost = narocnost;
    jednotka->dalsi = NULL;

    return jednotka;
}



/**
 * @brief Přidá novou tréninkovou jednotku do deníku.
 *
 * Tato funkce přidá novou tréninkovou jednotku na konec seznamu v tréninkovém deníku.
 * Pokud je deník prázdný, jednotka se stane první a poslední jednotkou v seznamu.
 * Pokud deník již obsahuje nějaké jednotky, nová jednotka je přidána na konec a
 * aktualizuje se ukazatel na poslední jednotku.
 *
 * @param d Ukazatel na tréninkový deník, do kterého bude jednotka přidána.
 * @param jednotka Ukazatel na tréninkovou jednotku, kterou chceme přidat.
 *
 * @note Po přidání jednotky je aktualizován počet jednotek v deníku.
 */

void denikPridatJednotku(TDenik* d, TJednotka* jednotka) {
    if (denikJePrazdny(d)) {// Deník je prázdný
        d->prvni = jednotka;
        d->posledni = jednotka;
    }
    else {// Přidání na konec seznamu
        d->posledni->dalsi = jednotka;
        d->posledni = jednotka;
    }
    d->pocetJednotek++;
}


/**
 * @brief Odstraní tréninkovou jednotku z deníku na základě zadaného data a názvu aktivity.
 *
 * Tato funkce prochází seznam tréninkových jednotek v deníku, hledá jednotky odpovídající
 * zadanému datu a po zobrazení nalezených jednotek vyzve uživatele k zadání názvu aktivity,
 * kterou chce odstranit. Pokud nalezne odpovídající jednotku, odstraní ji ze seznamu.
 * V případě, že jednotka neexistuje pro zadané datum nebo aktivitu, funkce vypíše chybovou
 * hlášku a vrátí se do původního stavu.
 *
 * @param d Ukazatel na deník, ve kterém bude jednotka odstraněna.
 * @param datum Datum tréninkové jednotky, kterou je potřeba odstranit (formát: YYYY-MM-DD).
 *
 * @note Funkce kontroluje, zda je deník prázdný a zda existují tréninkové jednotky pro dané datum.
 *       Pokud nejsou nalezeny žádné jednotky pro zadané datum, nebo pokud uživatel zadá neplatnou
 *       aktivitu, funkce umožní opravit vstup nebo zrušit operaci.
 */

void denikOdstranitJednotku(TDenik* d, const char* datum) {
    if (denikJePrazdny(d)) {
        printf("Denik je prazdny, nelze nic odstranit.\n");
        return;
    }

    TJednotka* aktualni = d->prvni;
    TJednotka* predchozi = NULL;
    bool nalezeno = false;

    // Prochazeni seznamu a hledani jednotek se stejnym datem
    printf("Nasledujici treninkove jednotky odpovidaji zadanemu datu %s:\n", datum);
    while (aktualni != NULL) {
        if (strcmp(aktualni->datum, datum) == 0) {
            nalezeno = true;
            printf("Aktivita: %s, Delka: %d min, Narocnost: %d/10\n",
                   aktualni->aktivita, aktualni->delkaTrvani, aktualni->narocnost);
        }
        aktualni = aktualni->dalsi;
    }

    if (!nalezeno) {
        printf("Pro zadane datum nebyla nalezena zadna treninkova jednotka.\n");
        return;
    }

    // Po vypisu uzivatele vyzveme k zadani aktivity, kterou chce odstranit
    char aktivita[15];
    bool valid = false;
    while (!valid) {
        printf("Zadejte presny nazev aktivity k odstraneni: ");
        scanf("%14s", aktivita);

        // Kontrola, jestli aktivita odpovida nejaké nalezené jednotce
        aktualni = d->prvni;
        valid = false;
        while (aktualni != NULL) {
            if (strcmp(aktualni->datum, datum) == 0 && strcmp(aktualni->aktivita, aktivita) == 0) {
                valid = true;
                break;
            }
            aktualni = aktualni->dalsi;
        }

        if (!valid) {
            char odpoved;  // Používáme char místo stringu
            printf("Chyba: Aktivita '%s' pro zadane datum neexistuje. Chcete zadat jinou aktivitu? (Y/N): ", aktivita);
            scanf(" %c", &odpoved);  // Dáme před čtečkou mezeru, aby se vyčistil buffer

            if (odpoved == 'N' || odpoved == 'n') {
                return;  // Pokud uzivatel zadal 'N', ukonci funkci
            } else if (odpoved != 'Y' && odpoved != 'y') {
                printf("Neplatna odpoved, prosim zadejte Y pro opravu nebo N pro zruseni.\n");
            }
        }
    }

    // Hledani spravne jednotky k odstraneni
    aktualni = d->prvni;
    predchozi = NULL;

    while (aktualni != NULL) {
        if (strcmp(aktualni->datum, datum) == 0 && strcmp(aktualni->aktivita, aktivita) == 0) {
            // Odstraneni jednotky
            if (predchozi == NULL) { // Prvni prvek v seznamu
                d->prvni = aktualni->dalsi;
                if (d->prvni == NULL) { // Pokud jsme odstranili posledni jednotku
                    d->posledni = NULL;
                }
            } else {
                predchozi->dalsi = aktualni->dalsi;
                if (aktualni == d->posledni) { // Pokud odstranujeme posledni jednotku
                    d->posledni = predchozi;
                }
            }

            free(aktualni);
            d->pocetJednotek--;
            printf("Jednotka byla uspesne odstranena.\n");
            return;
        }
        predchozi = aktualni;
        aktualni = aktualni->dalsi;
    }

    printf("Jednotka s aktivitou '%s' pro dane datum nebyla nalezena.\n", aktivita);
}





/**
 * @brief Načte tréninkové jednotky ze souboru a přidá je do deníku.
 *
 * Tato funkce otevře soubor se zadaným názvem a načte tréninkové jednotky ve formátu:
 * - datum (ve formátu YYYY-MM-DD),
 * - aktivita (max. 14 znaků),
 * - délka trvání v minutách (celé číslo),
 * - náročnost (hodnota mezi 1 a 10).
 * Po každém úspěšném načtení jednotky zkontroluje její platnost pomocí funkce `_otestujJednotku`.
 * Pokud je jednotka platná, vytvoří novou tréninkovou jednotku pomocí funkce `_vytvorJednotku` a přidá ji do deníku.
 * V případě, že se jednotku nepodaří vytvořit nebo je neplatná, vypíše chybovou hlášku.
 *
 * @param d Ukazatel na tréninkový deník, do kterého se jednotky načtou.
 * @param nazevSouboru Název souboru, ze kterého budou načteny tréninkové jednotky.
 *
 * @note Funkce volá interní funkce `_otestujJednotku`, `_vytvorJednotku` a `denikPridatJednotku`.
 * Po dokončení operace je soubor automaticky uzavřen.
 */

void denikNactiZeSouboru(TDenik* d, const char* nazevSouboru){
    FILE *f = fopen(nazevSouboru, "r");
    if(f == NULL){
      printf("Soubor se nepodarilo otevrit..\n");
      return;
    }
    //promenne pro ukladani dat
    char datum[11];
    char aktivita[15];
    int delkaTrvani;
    int narocnost;

    //printf("Chyby v souboru: \n");

    while(fscanf(f, "%10s %14s %d %d", datum, aktivita, &delkaTrvani, &narocnost) == 4){
        if (_otestujJednotku(datum, aktivita, delkaTrvani, narocnost)) {
            TJednotka* jednotka = _vytvorJednotku(datum, aktivita, delkaTrvani, narocnost);
            if (jednotka != NULL) {
                // Přidáme jednotku do deníku
                denikPridatJednotku(d, jednotka);
            }
            else {
                printf("Nepodarilo se vytvorit treninkovou\n", datum);
            }
        }//konec vetve if ktera pocita s platnou jednotkou
    }//konec cyklu while

    fclose(f);//uklidit po sobe
}

/**
 * @brief Vytiskne hlavičku pro výpis tréninkového deníku.
 *
 * Tato funkce vypisuje úvodní text a sloupce pro správné formátování tréninkového deníku.
 * Hlavička obsahuje informace o názvech sloupců: Datum, Aktivita, Délka (minuty), a Náročnost.
 * Používá se pro zajištění konzistentního formátování výpisu tréninkových jednotek v deníku.
 *
 * @param vystup Ukazatel na soubor, kam bude hlavička vytištěna (např. na standardní výstup).
 *
 * @note Funkce je interní (začíná podtržítkem), takže by měla být volána pouze z jiných
 * funkcí uvnitř tohoto souboru.
 */

void _vypisHlavicku(FILE* vystup) {
    fprintf(vystup, "==============================Treninkovy denik==================================\n");
    fprintf(vystup, "Datum                  Aktivita               Delka (min)              Narocnost\n");
    fprintf(vystup, "================================================================================\n");
}


/**
 * @brief Vytiskne všechny tréninkové jednotky v deníku.
 *
 * Tato funkce prochází celý tréninkový deník a vypisuje informace o každé tréninkové jednotce
 * ve formátu: datum, aktivita, délka trvání a náročnost (RPE). Pokud je deník prázdný,
 * funkce informuje uživatele a nic nevytiskne. Před výpisem tréninkových jednotek je
 * vytištěna hlavička pro lepší čitelnost.
 *
 * @param d Ukazatel na deník, jehož tréninkové jednotky mají být vytištěny.
 *
 * @note Funkce využívá systémový příkaz `cls` pro vyčištění obrazovky, což je platformně
 * závislé a může fungovat pouze na některých systémech (např. Windows).
 */
void denikTiskni(TDenik* d) {
    system("cls");
    if (denikJePrazdny(d)) {
        printf("Denik je prazdny.\n");
        return;
    }

    // Výpis hlavičky
    _vypisHlavicku(stdout);

    TJednotka* aktualni = d->prvni;
    while (aktualni != NULL) {
        // Tisk informací o jednotce s pevným formátováním
        printf("%-23s %-25s %-18d %5d/10\n",
               aktualni->datum,
               aktualni->aktivita,
               aktualni->delkaTrvani,
               aktualni->narocnost);

        // Posun na další jednotku
        aktualni = aktualni->dalsi;
    }
}




/**
 * @brief Tiskne tréninkové jednotky z deníku do souboru bez hlavičky pro možné budoucí zpracování.
 *
 * Tato funkce prochází seznam tréninkových jednotek v deníku a zapisuje je do zadaného souboru.
 * Výstupní soubor bude obsahovat data o každé tréninkové jednotce, včetně data, názvu aktivity,
 * délky trvání v minutách a náročnosti (RPE). Funkce neukládá hlavičku, aby bylo možné soubor
 * snadno zpracovávat v budoucnu.
 *
 * @param d Ukazatel na deník, jehož tréninkové jednotky mají být vytištěny do souboru.
 * @param nazevSouboru Název souboru, do kterého budou tréninkové jednotky uloženy.
 *
 * @note Pokud je deník prázdný nebo dojde k chybě při otevírání souboru, funkce vypíše chybovou hlášku.
 */

void denikTiskniDoSouboru(TDenik* d, const char* nazevSouboru) {
    if (denikJePrazdny(d)) {
        printf("Denik je prazdny.\n");
        return;
    }

    FILE* soubor = fopen(nazevSouboru, "w");
    if (soubor == NULL) {
        printf("Chyba pri otevirani souboru.\n");
        return;
    }


    // Výpis jednotlivých jednotek do souboru
    TJednotka* aktualni = d->prvni;
    while (aktualni != NULL) {
        fprintf(soubor, "%-23s %-25s %-18d %5d\n",
                aktualni->datum,
                aktualni->aktivita,
                aktualni->delkaTrvani,
                aktualni->narocnost);

        // Posun na další jednotku
        aktualni = aktualni->dalsi;
    }

    // Zavření souboru
    fclose(soubor);

    //printf("Denik byl ulozen do souboru %s.\n", nazevSouboru);
}


/**
 * @brief Uvolní paměť alokovanou pro deník a všechny jeho tréninkové jednotky.
 *
 * Tato funkce prochází všechny tréninkové jednotky v deníku a postupně uvolňuje jejich paměť.
 * Na závěr uvolní paměť alokovanou pro samotný deník. Funkce je určena pro správu paměti
 * a prevenci úniku paměti při ukončení práce s deníkem.
 *
 * @param d Ukazatel na deník, jehož paměť má být uvolněna.
 *
 * @note Funkce neprovádí žádnou akci, pokud je ukazatel na deník NULL.
 */

void denikUvolni(TDenik* d) {
    if (d == NULL) {
        return; // Pokud je deník NULL, nic se nedělá
    }

    TJednotka* aktualni = d->prvni;

    // Projdeme všechny tréninkové jednotky v deníku
    while (aktualni != NULL) {
        TJednotka* dalsi = aktualni->dalsi; // Uložíme si ukazatel na další jednotku
        free(aktualni);                    // Uvolníme paměť pro aktuální jednotku
        aktualni = dalsi;                  // Posuneme se na další jednotku
    }

    // Na závěr uvolníme paměť pro deník samotný
    free(d);
}


