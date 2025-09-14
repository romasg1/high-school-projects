/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

import java.util.ArrayList;

/**
 *
 * @author Roman Grmela <romasg1@seznam.cz>
 */
public class OtazkaText extends Otazka{
   
    //seznam se spravnymi odpovedmi
    protected ArrayList<Odpoved> odpovedi=new ArrayList<>();//seznam pro uchovani odpovedi
    
    public OtazkaText(String textOtazky, int hodnota) throws BadQuestionException {
        super(textOtazky, hodnota);
    }
    
    /**
     * 
     * @param textOtazky uchovava text otazky
     * @param odpovedi ma v sobe moznosti spravnych textovych odpovedi
     * @param hodnota reprezentuje hodnotu - bodovou
     * @throws BadQuestionException kdyz je prazdny text otazky...
     */
    public OtazkaText(String textOtazky, ArrayList<Odpoved> odpovedi, int hodnota) throws BadQuestionException {
        super(textOtazky, hodnota);
        this.odpovedi=odpovedi;
    }
    
    /**
     *
     * @param odpoved je odpoved uzivatele ktera se porovnava se spravnymi odpovedmi
     * @return
     */
    @Override
public boolean checkAnswer(String odpoved) {
    // Procházíme seznam správných odpovědí a porovnáváme s uživatelovou odpovědí
    for (Odpoved spravnaOdpoved : odpovedi) {
        if (spravnaOdpoved.getText().equalsIgnoreCase(odpoved)) {
            return true; // Nalezena shodná správná odpověď
        }
    }
    return false; // Uživatelova odpověď se neshoduje s žádnou ze správných odpovědí
}

    @Override
    public ArrayList<Odpoved> getOdpovedi() {
        return odpovedi;
    }




  /**
     * Vrací textovou reprezentaci otázky s odpověďmi.
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
    
}
