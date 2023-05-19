
/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: bottoni 
Descrizione: funzionamento libreria: bottoni


artboard.button(i) per leggere lo stato dei bottoni è sufficente
chiamarela funzione button all'interno della libreria artboard
dove i equivale alla posizione del bottone.

la funzione button restituisce un valore digitale.


by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/
#include <Artboard.h>  // includiamo la libreria

Artboard artboard;  // Istanza

void setup() {
  Serial.begin(9600);
}


void loop() {
  for (int i = 0; i < 8; i++) {  // leggiamo e stampiamo sul monitor seriale tutti i valori dei bottoni
    int val = artboard.button(i);
    Serial.print("pos: ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(val);
    Serial.print(" ");
  }
  delay(100);
  Serial.println();
}
