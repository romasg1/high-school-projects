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

public class KruhReader extends TvarReader{

    //konstruktor insert code
    public KruhReader(Scanner sc) {
        super(sc);
    }
    
    

    @Override
    public boolean hasNext() {
        return sc.hasNext("Kruh:");//sc je porad ten stejny scanner
    }

    //prikazem next vytvorim kruh ktery vratim
    @Override
    public Tvar next() {
        Bod stred = new Bod();
        float polomer;
        stred.x=sc.nextFloat();
        stred.y=sc.nextFloat();
        polomer=sc.nextFloat();
        
        return new Kruh(stred, polomer);
    }

 
    
}
