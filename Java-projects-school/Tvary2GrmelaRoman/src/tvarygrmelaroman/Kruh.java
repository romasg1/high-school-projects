/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tvarygrmelaroman;

/**
 *
 * @author grmel19102
 */
public class Kruh extends Tvar{
    Bod stred;
    float polomer;

    
    //vygenerovany konstruktor

    public Kruh(Bod stred, float polomer) {
        this.stred = stred;
        this.polomer = polomer;
    }
   
    @Override
    public double getObsah() {
       return Math.PI*Math.pow(polomer, 2);
    }

    @Override
    public double getObvod() {
         float vysledek;
        vysledek = (float) (2*Math.PI*polomer);
        
        return vysledek;
    }
    
}
