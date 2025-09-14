/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tvarygrmelaroman;

/**
 *
 * @author grmel19102
 */
public class Trojuhelnik extends Tvar{
    Bod stred;
    float delka;

    
    //vygenerovany konstruktor
    public Trojuhelnik(Bod stred, float delka) {
        this.stred = stred;
        this.delka = delka;
    }
    
    
    @Override
    public double getObsah() {
        float vysledek;
        vysledek=(float) Math.sqrt(Math.pow(delka, 2)+Math.pow(delka/2, 2));
        return vysledek;
    }

    @Override
    public double getObvod() {
        return 3*delka;
    }
    
}
