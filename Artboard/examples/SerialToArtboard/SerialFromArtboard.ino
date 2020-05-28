
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: touchin exemple
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
    int pot1 = map(analogRead(A0), 1023, 0, 0, 1023);
  int pot2 = map(analogRead(A1), 1023, 0, 0, 1023);
  int pot3 = map(analogRead(A2), 1023, 0, 0, 1023);
  int pot4 = map(analogRead(A3), 1023, 0, 0, 1023);
  int pot5 = map(analogRead(A12), 1023, 0, 0, 1023);
  int pot6 = map(analogRead(A13), 1023, 0, 0, 1023);
  

  
    for( int i=0; i<=11; i++){ // leggiamo e stampiamo sulla seriale tutti i valori
    
   Serial.print(artboard.touch(i)); Serial.print(" "); 

    }

    Serial.print(" ");
  Serial.print(pot1);
 Serial.print(" ");
  Serial.print(pot2);
 Serial.print(" ");
  Serial.print(pot3);
Serial.print(" ");
  Serial.print(pot4);
Serial.print(" ");
  Serial.print(pot5);
Serial.print(" ");
  Serial.println(pot6);

}
