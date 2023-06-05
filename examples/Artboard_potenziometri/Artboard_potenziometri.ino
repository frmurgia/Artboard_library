
/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: potenziometri
Descrizione: funzionamento libreria potenziometri

chiamare artboard.pot(i) per leggere lo stato dei potenziometri

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
    int pot1 = artboard.pot(0);
    Serial.println(pot1);
}
