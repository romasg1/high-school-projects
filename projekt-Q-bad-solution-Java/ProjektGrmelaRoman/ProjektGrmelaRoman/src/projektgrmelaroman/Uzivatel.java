/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

/**
 * TRIDA UZIVATEL uchovavajici informace o uzivateli
 * @author Roman Grmela <romasg1@seznam.cz>
 */
public class Uzivatel {
    private String jmeno;
    private String prijmeni;
    private int body;

    /**
     * 
     * @param jmeno v sobe uchovava jmeno uzivatele
     * @param body uklada aktualni zisk bodu uzivatele
     */
    public Uzivatel(String jmeno, int body) {
        this.jmeno = jmeno;
        this.body = body;
    }

    /**
     * PREZEZOVANI KONSTRUKTORU
     * @param jmeno v sobe uchovava jmeno uzivatele
     * @param prijmeni v sobe uchovava prijmeni uzivatele
     * @param body uklada aktualni zisk bodu uzivatele
     */
    public Uzivatel(String jmeno, String prijmeni, int body) {
        this.jmeno = jmeno;
        this.prijmeni = prijmeni;
        this.body = body;
    }
   

     /**
     * PRETEZOVANI KONSTRUKTORU
     * @param jmeno v sobe uchovava jmeno uzivatele
     * BODY se automaticky nastavi na 0
     */
    public Uzivatel(String jmeno) {
        this.jmeno = jmeno;
        this.body = 0;
    }

     /**
     * PRETEZOVANI KONSTRUKTORU
     * @param body uklada aktualni zisk bodu uzivatele
     */
    public Uzivatel(int body) {
        this.body = body;
        this.jmeno="noName";
        this.prijmeni="";
    }
    
    /**
     * GETTER
     * @return jmeno - vraci jmeno uzivatele
     */
    public String getJmeno() {
        return jmeno;
    }

    /**
     * 
     * @return prijmeni uzivatele
     */
    public String getPrijmeni() {
        return prijmeni;
    }

     /**
     * GETTER
     * @return BODY - vraci body uzivatele
     */
    public int getBody() {
        return body;
    }
    
     /**
     * SETTER
     * @param jmeno v sobe uchovava a nastavuje jmeno uzivatele 
     */
    public void setJmeno(String jmeno) {
        this.jmeno = jmeno;
    }

     /**
     * SETTER
     * @param body NASTAVUJE body uzivatele
     */
    public void setBody(int body) {
        this.body = body;
    }
    
    
    /**
     * METODA ktera pridava uzivateli body
     * @param hodnota - body, ktere se maji pridat uzivateli v kvizu...
     */
    public void pridatBody(int hodnota){
      this.body += hodnota;
    }
    
    
    
    
    
}
