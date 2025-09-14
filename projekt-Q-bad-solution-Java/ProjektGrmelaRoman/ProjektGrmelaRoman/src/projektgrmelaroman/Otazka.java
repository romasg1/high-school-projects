/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

import java.util.ArrayList;

/**
 * TRIDA OTAZKA REPREZENTUJICI 1 OTAZKU V SOUBORU
 * @author Roman Grmela <romasg1@seznam.cz>
 */

public abstract class Otazka {
    //ATRIBUTY
    protected String textOtazky;
    protected int hodnota;

    
    /**
     * KONSTRUKTORY
     * @param textOtazky uchovava text otazky
     * @param hodnota uchovava pocet bodu za spravnou odpoved
     * @throws projektgrmelaroman.BadQuestionException
     */
    public Otazka(String textOtazky, int hodnota) throws BadQuestionException {
        this.textOtazky = textOtazky;
        this.hodnota = hodnota;
        if(textOtazky == null || textOtazky.isBlank()){
          throw new BadQuestionException("Prazdny text otazky!!");
        }
    }
    
    public Otazka() {
    }

    
    /**
     * //pretezovani konstruktoru
     * Konstruktor obecné otázky
     * @param textOtazky je text otázky
     * @throws BadQuestionException vyhazuje výjimku, když je zadaný text prázdný
     */
    public Otazka(String textOtazky) throws BadQuestionException{
        this.textOtazky = textOtazky;
        if(textOtazky == null || textOtazky.isBlank()){
          throw new BadQuestionException("Prazdny text otazky!!");
        }
    }

    
    
    /**
     * //SETTERY
     * @param textOtazky uchovava text otazky
     * @throws projektgrmelaroman.BadQuestionException
     */
    public void setTextOtazky(String textOtazky) throws BadQuestionException {
        this.textOtazky = textOtazky;
        if(textOtazky == null || textOtazky.isBlank()){
          throw new BadQuestionException("Prazdny text otazky!!");
        }
    }

    

    /*public void setSpravnaOdpoved(String spravnaOdpoved) {
        this.spravnaOdpoved = spravnaOdpoved;
    }*/

    
    
    /**
     * //tento setter tetsuje zapornou hodnotu bodů...
     * @param hodnota uchovava pocet bodu za spravnou odpoved
     */
    public void setHodnota(int hodnota) {
        if(hodnota < 0){
           System.out.println("Zaporne body!!");
        }
        this.hodnota = hodnota;
    }

    
    /**
     * 
     * @return Hodnota atributu text.
     */
    public String getTextOtazky() {
        return textOtazky;
    }

   /* public String getSpravnaOdpoved() {
        return spravnaOdpoved;
    }*/

    public int getHodnota() {
        return hodnota;
    }
    
   

    
    /**
     * //TOSTRING - pro textovou reprezentaci objektu
     * @return String otazka - pro implementacni ucely...
     */
    @Override
    public String toString() {
        return "Otazka{" + "textOtazky=" + textOtazky + ", hodnota=" + hodnota + '}';
    }
    

    /**
     * ABSTRAKTNI METODA
     * @param textOdpovedi
     * @return true pokud je odpoved spravna...
     */
    public abstract boolean checkAnswer(String textOdpovedi);
    
    public abstract ArrayList<Odpoved> getOdpovedi();
    
      
}
