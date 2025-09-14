/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package farma01.grmelaroman;

/**
 *
 * @author grmel19102
 */
public class Farma01GrmelaRoman {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Pes p = new Pes("vlcak", 2, "Alik");//ve spravnem poradi
        Ptak a = new Ptak("andulka", 1, "Julca");
        
        /*fce na vypis automaticky vola metodu toString..
        kdyz bych ji zakomentoval ve tride pes.java tak se vypise ToString
        predka, tuzid by se vypsalo obecne zvire - jak jde videt ve tride Zvire..
        kdyz bych smazal i metodu toString v predkovi, tak se nevypisou hezke veci..
        */
        System.out.println("Pes: "+p);//automaticke volani tostring
        p.VydejZvuk();
        System.out.println("Ptak: "+a);
        a.VydejZvuk();
        
    }
    
}
