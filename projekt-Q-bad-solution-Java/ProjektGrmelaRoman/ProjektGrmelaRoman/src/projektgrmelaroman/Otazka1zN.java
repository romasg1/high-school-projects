/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

import java.util.ArrayList;

/**
 * tato TRIDA reprezentuje typ otazky, ktera ma 1 spravnou odpoved
 * @author Roman Grmela <romasg1@seznam.cz>
 */
public class Otazka1zN extends Otazka{
    protected ArrayList<Odpoved> odpovedi=new ArrayList<>();//seznam pro uchovani odpovedi

    /**
     * 
     * @param textOtazky uchovava text otazky
     * @param hodnota uchovava pocet bodu za spravnou odpoved
     * @throws BadQuestionException pokud je text otazky prazdny..vyjimku kdyztak vyhodi predek
     */
    public Otazka1zN(String textOtazky, int hodnota) throws BadQuestionException {
        super(textOtazky, hodnota);
    }

    /**
     * konstruktor
     */
    public Otazka1zN() {
    }

    /**
     * 
     * @param textOtazky uchovava text otazky
     * @param odpovedi uchovava seznam odpovedi - tedy moznosti
     * @param hodnota uchovava pocet bodu za spravnou odpoved
     * @throws BadQuestionException pokud je text otazky prazdny
     */
    public Otazka1zN(String textOtazky, ArrayList<Odpoved> odpovedi, int hodnota) throws BadQuestionException {
        super(textOtazky, hodnota);
        this.odpovedi=odpovedi;
    }
    
    
    /**
     * 
     * @param odpovedi uchovava seznam odpovedi - tedy moznosti
     */
    public void setOdpovedi(ArrayList<Odpoved> odpovedi) {
        this.odpovedi = odpovedi;
    }
    
     /**
     *
     * @return - tato funkce vrací seznam odpovedi na otazku...
     */
    @Override
    public ArrayList<Odpoved> getOdpovedi() {
        return odpovedi;
    }
    
    
     
    /**
     * Přepsaná metoda toString pro vrácení textu otázky a jejích odpovědí
     * @return Textový popis otázky a odpovědí
     * je potreba i metodu toString prepsat aby fungoval polymorfismus...
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append("\nOdpovedi:");
        for (Odpoved odpoved : odpovedi) {
            sb.append("\n - ").append(odpoved);
        }
        return sb.toString();
    }

   
    /**
     * Implementace abstraktní metody checkAnswer
     * @param textOdpovedi text odpovědi, který má být zkontrolován
     * @return true pokud je odpověď správná, jinak false
     */
    @Override
    public boolean checkAnswer(String textOdpovedi) {
        for (Odpoved o : odpovedi) {
            if (o.isSpravne() && o.getText().equals(textOdpovedi)) {
                return true;
            }
        }
        return false;
    }
    
   
}
