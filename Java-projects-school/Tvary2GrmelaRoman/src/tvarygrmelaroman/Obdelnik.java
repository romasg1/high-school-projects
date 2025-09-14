/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tvarygrmelaroman;

/**
 *
 * @author grmel19102
 */
public class Obdelnik extends Tvar{
    Bod stred;
    float sirka, delka;

    
    //vygenerovany konstruktor
    public Obdelnik(Bod stred, float sirka, float delka) {
        this.stred = stred;
        this.sirka = sirka;
        this.delka = delka;
    }
    
    
    @Override
    public double getObsah() {
        return sirka*delka;
    }

    @Override
    public double getObvod() {
        return 2*(sirka+delka);
    }
    
}
