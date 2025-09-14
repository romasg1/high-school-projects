/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 * OBSTARAVA SOUBOR - respektive zpracovava, zatim bez GUI
 * @author Roman Grmela <romasg1@seznam.cz>
 */
public class Kviz {
    ArrayList<Otazka> seznam;//sem budu nacitat otazky
    String nazevKvizu;//pro pozdejsi zobrazeni v gui

    public Kviz(){
      seznam=new ArrayList<>();
    }
    
      
     /**
      * METODA KTERA ZAMICHA OTAZKY V SEZNAMU...
      * @param seznamOtazek uchovava vsechny otazky ze souboru 
      */
    public void zamichatOtazky(ArrayList<Otazka> seznamOtazek) {
        Collections.shuffle(seznamOtazek);
    }

    /**
     * 
     * @return nazev kvizu pro zobrazeni v zahlavi GUI
     */
    public String getNazevKvizu() {
        return nazevKvizu;
    }

    /**
     * 
     * @return seznam otazek...
     */
    public ArrayList<Otazka> getSeznam() {
        return seznam;
    }
    
   
    
    /**
     * 
     * @param o je otazka, ktera je testovana a zjistujeme zda je kompletní
     * @return true pokud je v poradku, jinak false
     */
    public boolean testOtazky(Otazka o){
       if (o == null) return false;
        if (o.getTextOtazky()== null || o.getTextOtazky().trim().isEmpty()) return false;
        if (o.getHodnota() <= 0) return false;
        if (o instanceof Otazka1zN || o instanceof OtazkaText) {
            ArrayList<Odpoved> odpovedi = o.getOdpovedi();
            if (odpovedi == null || odpovedi.isEmpty()) return false;
            
            boolean maSpravnouOdpoved = false;
            for (Odpoved odp : odpovedi) {
                if (odp.isSpravne()) {
                    maSpravnouOdpoved = true;
                    break;
                }
            }
              if (!maSpravnouOdpoved) return false;
               }
        return true;
    }
    
    
    
 
    
    /**
     * ROZSAHLA METODA PRO NACTENI FORMATOVANEHO SOUBORU...
     * @param nazevSouboru uchovava nazev vstupniho souboru
     * @throws BadQuestionException kzdyz je prazdny text otazky
     */
   public void nactiSoubor(String nazevSouboru) throws BadQuestionException{
        try(Scanner sc = new Scanner(new FileInputStream(new File(nazevSouboru)))){
         System.out.println("Soubor se otevrel");
            System.out.println("--------------------");
         //pozn.: scanner muzu pouzivat pouze v bloku try catch kdyz jsem to udelal se zdrojem..
         // jinak bych to musel deklarovat mimo a bez zdroje
            String radek; //pro ulozeni radku souboru
            String otazkaText="";//inicializace potrebnych datovych polozek
            int hodnota=-1;
            String spravnaOdpoved;
            String spatnaOdpoved;
            ArrayList<Odpoved> odpovedi=new ArrayList<>();
            boolean prvniOtazkaNactena=false;
            String posledniTypOtazky=""; // Atribut pro uchování posledního typu otázky...bude potreba pro rozhodovani jaky typ otazky bude vytvoren
            
            //cteni po radcich
            while(sc.hasNextLine()){
                
                radek = sc.nextLine();//prectu radek a pak s nim jdu pracovat...
                 if (radek.isEmpty()) {continue;} // Přeskočit prázdný řádek
                // Kontrola formátu řádku pomoci REGEXU
                if (!radek.matches("^(Nazev:|Otazka 1zN:|Otazka text:|Hodnota:|#|Spravne:|Spatne:).*")) {
                    //vyskoci dialogove okno s errorem
                    JOptionPane.showMessageDialog(null, "Chybný formát řádku: " + radek, "Chyba formátu", JOptionPane.ERROR_MESSAGE);
                    System.exit(0); // Ukončí aplikaci...0 - sucessfull...1 - spatne
                }
                if(radek.startsWith("#")){continue;}//zajisti ze se # nebudou zobrazovat uzivateli
                
                else if(radek.startsWith("Nazev:")){
                         nazevKvizu=radek.substring(6);
                     }
       
                else if(radek.startsWith("Otazka 1zN:") || radek.startsWith("Otazka text:")){
                    // Uložení posledního typu otázky
                    posledniTypOtazky = radek.startsWith("Otazka 1zN:") ? "Otazka 1zN" : "Otazka text";
                    
                    //bud se cte prvni otazka a nebo je to dalsi otazka a je tudiz cas vytvorit objekt predchozi otazky
                    if(prvniOtazkaNactena && radek.startsWith("Otazka 1zN:")) {
                      //pred tvorbou otazky se zamichaji odpovedi
                      Collections.shuffle(odpovedi);
                      //nemuzu vytvorit konkretni otazku..
                      //MUSIM ZJISTIT JAKEHO TYPU JE TAA PREDCHOZI...
                      
                        Otazka pridejOtazkuDoSeznamu = new Otazka1zN(otazkaText, new ArrayList<>(odpovedi), hodnota);
                      
                      
                      //POZOR: Kazda otazka ma svuj novy seznam odpovedi...
                      //Otazka pridejOtazkuDoSeznamu = new Otazka(otazkaText, odpovedi, hodnota);...NEFUNGOVALO
                      //pozor, otazkaText je trida i atribut tady :(
                      if(testOtazky(pridejOtazkuDoSeznamu)){
                        seznam.add(pridejOtazkuDoSeznamu); //po pridani do seznamu nastaveni potrebnych hodnot...
                        hodnota=-1;
                      }
                      else {
                        JOptionPane.showMessageDialog(null, "Neplatná otázka: " + otazkaText, "Chyba validace", JOptionPane.WARNING_MESSAGE);
                        System.exit(0); // Ukončí aplikaci
                    }
                      odpovedi.clear();
                      otazkaText=radek.substring(11);//nebo 12 pro otazka text
                    }//prvni otazka je nactena a narazim na otazka 1zN 
                    
                    
                    //2. moznost...
                    if(prvniOtazkaNactena && radek.startsWith("Otazka text:")) {
                       Collections.shuffle(odpovedi); //pred tvorbou otazky se zamichaji odpovedi
                      //nemuzu vytvorit konkretni otazku..
                      //MUSIM ZJISTIT JAKEHO TYPU JE TAA PREDCHOZI...
                      Otazka pridejOtazkuDoSeznamu = new OtazkaText(otazkaText, new ArrayList<>(odpovedi), hodnota);
                    
                      //Otazka pridejOtazkuDoSeznamu = new Otazka(otazkaText, odpovedi, hodnota);
                      //pozor, otazkaText je trida i atribut tady :(
                      //Otazka pridejOtazkuDoSeznamu = new Otazka(otazkaText, odpovedi, hodnota); nefungovalo
                       if(testOtazky(pridejOtazkuDoSeznamu)){
                        seznam.add(pridejOtazkuDoSeznamu); 
                        hodnota=-1;
                      }
                      else {
                        JOptionPane.showMessageDialog(null, "Neplatná otázka: " + otazkaText, "Chyba validace", JOptionPane.WARNING_MESSAGE);
                        System.exit(0); // Ukončí aplikaci
                       }
                      
                      odpovedi.clear();
                      otazkaText=radek.substring(12);//nebo 12 pro otazka text

                  }
                    
                    //jinak ctu prvni otazku...
                    else{
                        if(posledniTypOtazky.equals("Otazka 1zN")){
                           otazkaText=radek.substring(11);//nebo 12
                           prvniOtazkaNactena = true;
                          //System.out.println(otazkaText); 
                        }
                        
                        if(posledniTypOtazky.equals("Otazka text")){
                           otazkaText=radek.substring(12);//nebo 12
                           prvniOtazkaNactena = true;
                          //System.out.println(otazkaText); 
                        }
                  
                    }//konec vetve else, ktera cte prvni otazku...
                }
                
                
                
                
                
                
   
                
                else if(radek.startsWith("Hodnota:")){
                  hodnota=Integer.parseInt(radek.substring(8).trim());//trim zajisti ze okolo cisla nebudou mezery a v pohode se to prevede na cislo
                    //System.out.println(hodnota);
                }
                else if(radek.startsWith("Spravne:")){
                   spravnaOdpoved=radek.substring(8);
                    //System.out.println(spravnaOdpoved);//vypise jen spravne odpovedi
                   //tvorba objektu odpoved a pridani do seznamu odpovedi
                    Odpoved odpoved = new Odpoved(true, spravnaOdpoved);
                    odpovedi.add(odpoved);
                }
                else if(radek.startsWith("Spatne:")){
                  spatnaOdpoved=radek.substring(7);
                    //System.out.println(spatnaOdpoved);
                  Odpoved odpoved = new Odpoved(false, spatnaOdpoved);
                  odpovedi.add(odpoved);
                }
                
                else{
                    System.out.println("Neocekavany format souboru!!");
                    JOptionPane.showMessageDialog(null, "Nastala obecná chyba při zpracování souboru.", "Chyba", JOptionPane.ERROR_MESSAGE);
                    System.exit(1); // Ukončí aplikaci s chybou
   
                }
                
            }//while
            
            // Po ukonceni while cyklu se jeste nepridala posledni nactena otazka..
            if (prvniOtazkaNactena) {
                if(posledniTypOtazky.equals("Otazka 1zN")){
                 Otazka pridejOtazkuDoSeznamu = new Otazka1zN(otazkaText, odpovedi, hodnota);
                 if(testOtazky(pridejOtazkuDoSeznamu)){
                   seznam.add(pridejOtazkuDoSeznamu);
                 }
                 else{
                  JOptionPane.showMessageDialog(null, "Neplatná otázka: " + otazkaText, "Chyba validace", JOptionPane.WARNING_MESSAGE);
                  System.exit(0); // Ukončí aplikaci
                 }
                 
                 //System.out.println(pridejOtazkuDoSeznamu);
                }//if OTAZKA 1zN
                
                else if(posledniTypOtazky.equals("Otazka text")){
                  Otazka pridejOtazkuDoSeznamu = new OtazkaText(otazkaText, odpovedi, hodnota);
                 if(testOtazky(pridejOtazkuDoSeznamu)){
                   seznam.add(pridejOtazkuDoSeznamu);
                 }
                 else{
                  JOptionPane.showMessageDialog(null, "Neplatná otázka: " + otazkaText, "Chyba validace", JOptionPane.WARNING_MESSAGE);
                  System.exit(0); // Ukončí aplikaci
                 }
                }//jinak OTAZKA TEXT

             }
         
         
         
      }//try
        //spatna cesta k souboru
      catch(FileNotFoundException e){//odchytavani vyjimek
          System.out.println("Soubor se nepodarilo otevrit...");
          JOptionPane.showMessageDialog(null, "Soubor se nepodařilo otevřít.", "Chyba", JOptionPane.WARNING_MESSAGE);
          System.exit(0);
          e.getMessage();
      }//catch1
        
        catch(NumberFormatException e){
            System.out.println("Spatna prace s formatem cisla v souboru...");
            JOptionPane.showMessageDialog(null, "Chybný formát čísla v souboru.", "Chyba formátu", JOptionPane.WARNING_MESSAGE);
            System.exit(0); // Ukončí aplikaci
        }//catch2
        
        
        //vola metodu, ktera zamicha otazky v seznamu
        zamichatOtazky(seznam);
        //pro implementacni ucely vypis na konzoli
        for(Otazka o: seznam){
            System.out.println(o);
            System.out.print("\n");
        }
     
}//nactiSoubor
}//class
