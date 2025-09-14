/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package cary.grmelaroman;

/**
 *
 * @author roman
 */
//trida bod reprezentujici bod v rovine
public class Bod {
    protected float x;//souradnice - atributy
    protected float y;//zvenku se k tomu nedostanu..nejde tam jit pres tecku

    //konstruktor...
    //ve strukture jsou metody - fce
    public Bod(float x, float y) {
        this.x = x;
        this.y = y;
    }
    
    //pretezovani konstruktoru
    public Bod(Bod b){
    this(b.x, b.y);//volani vedlejsiho konstruktoru ve tride
    }
   
    //metoda - vzdalenost 2 zadanych bodu..
	public float vzdalenost(Bod a, Bod b) {
           return (float) Math.sqrt(Math.pow(b.x - a.x, 2) + Math.pow(b.y - a.y, 2)); 
	}
    
        //pretezovani - hlavni metoda pro vzdalenost
        public float vzdalenost(float x, float y){
        return (float) Math.sqrt(Math.pow(x-this.x, 2) + Math.pow(y-this.y, 2));
        }
    
  
    //metoda - pretezovani - vzdalenost meho bodu od dalsiho
     //pretezovani: jmenuji se fce stejne a maji jine parametry
        
	public float vzdalenost(Bod jiny) {
       // return (float) Math.sqrt(Math.pow(jiny.x - this.x, 2) + Math.pow(jiny.y - this.y, 2));
        return vzdalenost(jiny.x, jiny.y);
    }
   

    //getter..//abych se k tomu dostal..je to private/protected
    public float getX() {
        return x;
    }

    //getter
    public float getY() {
        return y;
    }

    //setter
    public void setX(float x) {
        this.x = x;
    }

    //setter
    public void setY(float y) {
        this.y = y;
    }

    
    //prekryti metody toString ze tridy Object pro muj bod...
    @Override
    public String toString() {
        return "Bod{" + "x=" + x + ", y=" + y + '}';
    }
    
}
