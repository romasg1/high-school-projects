/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package projektgrmelaroman;

/**
 * Vyjimka ktera vznika pri inicializaci otazky
 * @author Roman Grmela <romasg1@seznam.cz>
 */
public class BadQuestionException extends Exception {

    public BadQuestionException(){
      super("otazka chybne zadana...");
    }

    public BadQuestionException(String zprava){
       super(zprava);
    }  
}
