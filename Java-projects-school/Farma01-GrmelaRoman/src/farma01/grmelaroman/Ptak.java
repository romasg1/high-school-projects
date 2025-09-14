/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package farma01.grmelaroman;

/**
 *
 * @author grmel19102
 */
public class Ptak extends Zvire{
    protected String rasa;
    protected int vek;
    
    
    //ve vsech konstruktorech se musi nastavit vsechno
    public Ptak(String rasa)
    { 
        super();
        this.rasa=rasa;
        vek=0;
        pocetNohou=2;
    }

    public Ptak(String rasa, int vek) {
        super();//nasatvi na noname
        this.rasa = rasa;
        this.vek = vek;
        pocetNohou=2;
    }

    public Ptak(String rasa, int vek, String jmeno) {
        super(jmeno);
        this.rasa = rasa;
        this.vek = vek;
        pocetNohou=2;
    }

    public Ptak(String rasa, String jmeno) {
        super(jmeno);
        this.rasa = rasa;
        vek=0; //dodelat..
        pocetNohou=2;
    }

    //gettery pro VSECHNO
    public String getRasa() {
        return rasa;
    }

    public int getVek() {
        return vek;
    }

    //tohle zbytecne..predek tuto metodu ma
    public String getJmeno() {
        return jmeno;
    }

    public int getPocetNohou() {
        return pocetNohou;
    }

    //pro vsechno settery
    public void setRasa(String rasa) {
        this.rasa = rasa;
    }

    public void setVek(int vek) {
        if(vek > this.vek)//jde jenom zvysovat..to co zadal musi byt vetsi nez to co tam mam
        this.vek = vek;
    }

    public void setJmeno(String jmeno) {
        this.jmeno = jmeno;
    }

    
    public void VydejZvuk(){
        System.out.println("Pip pip!");
    }

    @Override
   public String toString(){
   return jmeno+", "+rasa+", "+vek+", "+pocetNohou;
   }
   
   
    
    
    
    
    
    
    
    
    
}
