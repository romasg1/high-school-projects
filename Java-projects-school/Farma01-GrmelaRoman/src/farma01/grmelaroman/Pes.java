/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package farma01.grmelaroman;

/**
 *
 * @author grmel19102
 */
public class Pes extends Zvire{
    protected String rasa;
    protected int vek;
    
    
    //ve vsech konstruktorech se musi nastavit vsechno
    public Pes(String rasa)
    { 
        super();
        this.rasa=rasa;
        vek=0;
        pocetNohou=4;
    }

    public Pes(String rasa, int vek) {
        super();//nasatvi na noname
        this.rasa = rasa;
        this.vek = vek;
        pocetNohou=4;
    }

    public Pes(String rasa, int vek, String jmeno) {
        super(jmeno);
        this.rasa = rasa;
        this.vek = vek;
        pocetNohou=4;
    }

    public Pes(String rasa, String jmeno) {
        super(jmeno);
        this.rasa = rasa;
        vek=0; //dodelat..
        pocetNohou=4;
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

    //pro vsechno settery..setter na rasu by tady byt nemel..protoze ji menit nechci
    /*public void setRasa(String rasa) {
        this.rasa = rasa;
    }*/

    public void setVek(int vek) {
        if(vek > this.vek)//jde jeom zvysovat..to co zadal musi byt vetsi nez to co tam mam
        this.vek = vek;
    }

    public void setJmeno(String jmeno) {
        this.jmeno = jmeno;
    }

    
    public void VydejZvuk(){
        System.out.println("Haf haf!");
    }

    @Override
   public String toString(){
   return jmeno+", "+rasa+", "+vek+", "+pocetNohou;
   }
   
   
    
    
    
    
    
    
    
    
    
}
