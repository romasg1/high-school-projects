/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

/**
 * TRIDA odpoved reprezentujici 1 odpoved v souboru...
 * je obecna, takze se z ni bude dedit u specifictejsich typu otazek
 * @author Roman Grmela <romasg1@seznam.cz>
 */

public class Odpoved {
    protected boolean spravne;//je odpoved spravna?
    protected String text;//text odpovedi..

    /**
     *
     * @param spravne - jestli je odpoved na otazku spravna
     * @param textOdpovedi - text odpovedi ze souboru
     */
    public Odpoved(boolean spravne, String textOdpovedi) {
        this.spravne = spravne;
        this.text = textOdpovedi;
    }

    
    /**
     * pretezovani konstruktoru
     * @param spravne jestli je odpoved na otazku spravna
     */
    public Odpoved(boolean spravne) {
        this.spravne = spravne;
        this.text="";
    }

    //GETTERY
    public String getText() {
        return text;
    }
    
    /**
     * Getter pro správnost odpovědi
     * @return true pokud je odpověď správná, jinak false
     */
    public boolean isSpravne() {
        return spravne;
    }

    //SETTERY
    public void setSpravne(boolean spravne) {
        this.spravne = spravne;
    }

    public void setText(String text) {
        this.text = text;
    }
    
    

    /**
     * 
     * @return retezec - textova reprezentace otazky pro implementacni ucely
     */
    @Override
    public String toString() {
        return "Odpoved{" + "spravne=" + spravne + ", text="+text + '}';
    }
 
}
