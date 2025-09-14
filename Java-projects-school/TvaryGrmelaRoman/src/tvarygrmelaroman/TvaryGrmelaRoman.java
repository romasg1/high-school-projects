/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package tvarygrmelaroman;

import java.util.Random;

/**
 *
 * @author grmel19102
 */
public class TvaryGrmelaRoman {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Tvar[] pole = new Tvar[10];//pres new pak musim vytvorit kazde to policko
        //ted mam jakoby pole ukazatelu...
        Random r = new Random();
        int polomer, vyska, sirka;
        Bod b=new Bod();//nezapomenout na new!!!!
        float sumaObvod=0;
        float sumaObsah=0;
        
        for(int i=0; i<10; i++){
        polomer=r.nextInt(20)+1;//protoze generuje 0->19 a ja chci 1 az 20
        vyska=r.nextInt(20)+1;
        sirka=r.nextInt(20)+1;
        b.x=(float) r.nextDouble(r.nextDouble()*60+20);//aby to bylo v pozadovanem rozmezi
        b.y=(float) r.nextDouble(r.nextDouble()*60+20);
        
        switch(r.nextInt(3)/*varianty 0, 1, 2*/){
            case 0: pole[i]=new Obdelnik(b, sirka, vyska);
            break;
            
            case 1: pole[i]=new Trojuhelnik(b, sirka);//opravdu??
            break;
            
            case 2: pole[i]=new Kruh(b, polomer);
            break;
            
        }//switch
        }//for 1
        
        /*pocitani*/
        for(Tvar pom: pole){
           sumaObsah=(float) (sumaObsah+pom.getObsah());
           sumaObvod=(float) (sumaObvod+pom.getObvod());
        }//for 2
        
        System.out.println("Soucet obsahu je: "+sumaObsah);
        System.out.println("Soucet obvodu je: "+sumaObvod);
        
    }//main
    
}//class
