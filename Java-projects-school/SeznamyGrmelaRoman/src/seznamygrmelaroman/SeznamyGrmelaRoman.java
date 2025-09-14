/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package seznamygrmelaroman;

import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author roman
 */
public class SeznamyGrmelaRoman {
    
     //Vytvoření seznamu
    //v tomto pripade zde musi byt static..jinak by neslo pridat prvek
  static ArrayList<Double> seznam = new ArrayList<Double>(); // mohl by být i LinkedList<Double>
  //- var - nové klíčové slovo - Vezme si typ pro deklaraci proměnné z konstruktoru na pravé straně.
  //- <Typ> - použití generického typu - Typ se dosazuje až při výrobě proměnné, ne při programování
  //samotné třídy (zde ArrayList). To   dovoluje vytvářet zobecněné kolekce (seznamy, stromy apod.)
  //namísto nutnosti programovat vše znovu (bez toho by byly potřeba extra   seznamy nad
  //typy Integer, Double, Zvire, ...).
  //- () - Kulaté závorky jsou tu proto, že se zde volá konstruktor bez parametrů.


    
    public static void seznamy01() { 
 
  //Přidání prvku
  seznam.add(2.5);
  seznam.add(3.5);
  seznam.add(4.5);
  seznam.add(5.5);
  seznam.add(6.5);
  seznam.add(7.5);

  //Indexování prvku
  double prvek = seznam.get(0); // parametrem je index -- pořadové číslo
  //System.out.println(prvek);

  //Výpis seznamu
  for (Double cislo : seznam) // Projde všechny prvky seznamu. Double je třída zastřešující double.
  {
    System.out.println(cislo);
  }
}
    
    
    
    public static void seznamy02() {
  //Odstranění prvku ze seznamu
  //seznam.remove() -- je několik variant

  //Odstranění prvků při průchodu iterátorem
 // - Nejde v obyčejném cyklu for ani while, protože by se takový cyklus pokazil a skončil chybou.
 // - Musí se použít průchod přes iterátor. Iterátory jsou speciální objekty, které slouží k procházení kolekcí.
  //- Metoda remove se volá nad iterátorem, ne nad seznamem!

  for (Iterator<Double> iterator = seznam.iterator(); iterator.hasNext();)
  {
    Double next = iterator.next();
    if (/*chcismazat(next)*/next>4)
      iterator.remove(); // odstranění prvku next, ale pomocí iterátoru!
  }
  
   //Výpis seznamu
  for (Double cislo : seznam) // Projde všechny prvky seznamu. Double je třída zastřešující double.
  {
    System.out.println(cislo);
  }
}
    
    public static void seznamy03() {
  //Funkcionální programování (s anonymními funkcemi)
  //- Dají se použít i metody s tzv lambda funkcí
  //(anonymní funkcí, která se zapíše přímo do argumentu funkce).

  //Odstranění všech prvků splňujících zadanou podmínku
  seznam.removeIf(n -> (n > 2.5));

  //BTW PRACUJE SE PORAD SE STEJNYM SEZNAMEM...
  //- n -> (n > 5.5) je anonymní lambda funkce s tímto významem:
    //boolean funkce(double n) { return n > 5.5; }
  //- Metoda removeIf ze seznamu odstraní všechny prvky, nad kterými
  //zadaná lambda funkce vrátí true.
  //- viz https://www.geeksforgeeks.org/arraylist-removeif-method-in-java/

  //Vykonání akce nad všemi prvky seznamu
  seznam.forEach((n) -> System.out.println(n));
  //- viz https://www.geeksforgeeks.org/arraylist-foreach-method-in-java/
}
    
        public static void main(String[] args) {
        // TODO code application logic here
        
        seznamy01();
        System.out.println(".......");
        seznamy02();
         System.out.println(".......");
         seznamy03();
    }
    
}
   

    

