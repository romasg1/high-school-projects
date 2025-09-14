/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tvarygrmelaroman;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Pattern;

/**
 *
 * @author grmel19102
 */
public abstract class TvarReader {
    Scanner sc;
    static ArrayList<TvarReader> seznam = new ArrayList<TvarReader>();
    public abstract boolean hasNext();
    public abstract Tvar next();//potomek je nucen doprogramovat

    //konstruktor vygenerovany
    public TvarReader(Scanner sc) {
        this.sc = sc;
    }
    
    //pridani citace do pole seznam
    public static void pridej(TvarReader x){
        seznam.add(x);
        
    }
   
    //static abych mohl volat z mainu
//kompozice a delegovani
public static boolean hasNexTvar(){
  /* Pattern nazev = Pattern.compile("(Kruh:|Obdelnik:|Trojuhelnik:)");
   return sc.hasNext(nazev);*/
  for(TvarReader pom: seznam){
      if(pom.hasNext()/*volam hasnext potomka*/){
        return true;//ano, jsem schopen cist
      }
     
  }
         return false;  
}

//static aby slo volat z mainu
public static Tvar nextTvar(){

 for(TvarReader pom: seznam){
      if(pom.hasNext()/*volam hasnext potomka*/){
        return pom.next();
      }
  }
 return null;
}


/*public Tvar nextTvar(){
   String nazev;
   Bod b=new Bod();
   float strana;
   Tvar T=null;
   if(hasNextTvar()){
      nazev=sc.next();
   }
   /*switch(nazev){
       case "Trojuhelnik:": b.x=sc.nextFloat();//??????
                            b.y=sc.nextFloat();
                            strana=sc.nextFloat();
       T=new ();
       break;
   }*/
  /* 
   return T;

}*/

    

    
    
    
}
