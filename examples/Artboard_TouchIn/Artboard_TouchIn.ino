
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: touchin 
Descrizione: funzionamento libreria touch


artboard.touch(i) per leggere l'ingresso capacitivo è sufficente
chiamarela funzione touch all'interno della libreria artboard
dove i equivale alla posizione dell'ingresso.
0=do
1=do#
2=re#
ecc.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/
#include <Artboard.h> // includiamo la libreria

Artboard artboard; // Istanza

void setup(){

  Serial.begin(9600);

}


void loop(){
  for( int i=0; i<12; i++){ // leggiamo e stampiamo sulla seriale tutti i valori
      int val = artboard.touch(i);
      Serial.print("pos: ");
      Serial.print(i+1);
      Serial.print(": ");
     Serial.print(val);
       Serial.print(" ");

    }
   Serial.println();
}
