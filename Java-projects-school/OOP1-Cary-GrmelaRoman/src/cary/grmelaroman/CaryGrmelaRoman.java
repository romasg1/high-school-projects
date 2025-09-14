/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package cary.grmelaroman;

import java.util.Locale;
import java.util.Scanner;

/**
 *
 * @author roman
 */
public class CaryGrmelaRoman {
    
    //jedina fce krome fce main...
    public static void najdiObdelnik(Bod[] body) {
    float minX = body[0].getX();
    float maxX = body[0].getX();//vhodnejsi pomoci getteru
    float minY = body[0].getY();
    float maxY = body[0].getY();

    // Najdi minimální a maximální souřadnice
    for (int i = 1; i < body.length; i++) {//cyklus od indexu 1...
        float x = body[i].getX();
        float y = body[i].getY();

        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    // Vypiš levý horní a pravý dolní bod obdélníku
    System.out.println("Levy horni roh obdelniku: (" + minX + ", " + maxY + ")");
    System.out.println("Pravy dolni bod obdelniku: (" + maxX + ", " + minY + ")");
}

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner sc = new Scanner(System.in);
        sc.useLocale(Locale.US);
        System.out.print("Zadej pocet bodu: ");
        int pocet = sc.nextInt();
        
        Bod[] body = new Bod[pocet];
        
        for(int i=0; i<pocet; i++){
            System.out.print("Zadej 2 souradnice "+(i+1)+'.'+ " bodu oddelenych mezerou: ");
            
            float x, y;
            while (!sc.hasNextFloat()) {
                System.out.print("Nespravny format, zadej prosim dve cisla oddelena mezerou:");
                sc.next(); // Vyprázdnění bufferu
            }
            x = sc.nextFloat();
            while (!sc.hasNextFloat()) {
                System.out.println("Nespravny format, zadej prosim dve cisla oddelena mezerou:");
                sc.next(); // Vyprázdnění bufferu
            }
            y = sc.nextFloat();

            body[i] = new Bod(x, y);
        }//for
        
        //vypocet delky lomene cary...
        float delkaLomeneCary = 0;
        for (int i = 0; i < pocet - 1; i++) {
            delkaLomeneCary += body[i].vzdalenost(body[i + 1]);
        }

        // Vypsání délky lomené čáry
        System.out.println("Delka lomene cary: " + delkaLomeneCary);
        
        najdiObdelnik(body);
    }//main
    
}//class
