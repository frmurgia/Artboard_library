
/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: bottoni 
Descrizione: funzionamento libreria: bottoni


chiamarela artboard.button(i) per leggere lo stato dei bottoni 

la funzione artboard.button(i) restituisce un valore digitale.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/
#include <Artboard.h>  // includiamo la libreria

Artboard artboard;  // 

void setup() {
  Serial.begin(9600);
}


void loop() {
  // leggiamo e stampiamo sul monitor seriale tutti i valori dei bottoni
    int bottone1 = artboard.button(0); // variabile
    Serial.println(bottone1); //stampa su monitor serial

  delay(100);
  
}
