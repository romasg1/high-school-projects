/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package farma01.grmelaroman;

/**
 *
 * @author grmel19102
 */
public class Zvire {
    protected String jmeno;
    protected int pocetNohou;
    
   
public Zvire()
{ /* nastavení jména */ 
  jmeno="NoName";//proc bez this - protoze se to pouzivs jenom kdyz je nejasne jake jmeno to je..zde je to jasny
  pocetNohou = 0;
  
}

public Zvire(String jmeno)
{ /* nastavení jména */ 
    this.jmeno=jmeno;
}



@Override
public String toString()
{/* vrať textovou podobu objektu */
return "Obecne zvire";
}

    public String getJmeno() {
        return jmeno;
    }

    public int getPocetNohou() {
        return pocetNohou;
    }

    public void setJmeno(String jmeno) {
        this.jmeno = jmeno;
    }

    public void setPocetNohou(int pocetNohou) {
        //protoze muzu pocet nohou jen ubirat..
        if(pocetNohou < this.pocetNohou && pocetNohou > 0)
        this.pocetNohou = pocetNohou;
    }


    
}


