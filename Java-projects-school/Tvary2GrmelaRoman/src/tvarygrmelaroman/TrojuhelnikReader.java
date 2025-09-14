/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tvarygrmelaroman;

import java.util.Scanner;

/**
 *
 * @author grmel19102
 */

public class TrojuhelnikReader extends TvarReader{

    //konstruktor insert code
    public TrojuhelnikReader(Scanner sc) {
        super(sc);
    }
    
    
//je potreba implementovat abstraktni metody
    @Override
    public boolean hasNext() {
        return sc.hasNext("Trojuhelnik:");//sc je porad ten stejny scanner
    }

    //prikazem next vytvorim kruh ktery vratim
    @Override
    public Tvar next() {
        Bod stred = new Bod();
        float delka;
        stred.x=sc.nextFloat();
        stred.y=sc.nextFloat();
        delka=sc.nextFloat();
        
        
        return new Trojuhelnik(stred, delka);
    }

 
    
}
