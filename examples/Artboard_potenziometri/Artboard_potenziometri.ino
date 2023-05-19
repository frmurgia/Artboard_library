
/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: potenziometri
Descrizione: funzionamento libreria potenziometri


artboard.button(i) per leggere lo stato dei potenziometri è sufficente
chiamarela funzione pot all'interno della libreria artboard
dove i equivale alla posizione del potenziometro.

la funzione potenziomentro restituisce un valore analogico.


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
  for (int i = 0; i < 8; i++) {  // leggiamo e stampiamo sulla seriale tutti i valori
    int val = artboard.pot(i);
    Serial.print("pos: ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(val);
    Serial.print(" ");
  }
  Serial.println();
}
