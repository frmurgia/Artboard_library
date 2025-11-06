/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: potenziometri
Descrizione: Legge lo stato di 8 potenziometri (0-7)
             e stampa i loro valori sul Serial Monitor.

La funzione artboard.pot(i) restituisce un valore analogico:
- Un numero che va circa da 0 a 1023.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>
*/

#include <Artboard.h>  // includiamo la libreria

Artboard artboard;  // Creiamo un oggetto "artboard"

void setup() {
  Serial.begin(9600); // Avvia la comunicazione seriale
  Serial.println("--- Test Potenziometri Artboard ---");
  Serial.println("Muovi i potenziometri da 0 a 7...");
}


void loop() {    
  
  // Usiamo un ciclo "for" per controllare tutti i potenziometri da 0 a 7
  // NOTA: La condizione è i < 8 (non i > 8)
  for (int i = 0; i < 8; i++) {
    
    // 1. Leggiamo il valore del potenziometro "i"
    int valorePot = artboard.pot(i);
    
    // 2. Stampiamo il nome del potenziometro
    Serial.print("Pot ");
    Serial.print(i);
    Serial.print(": "); // Stampa: "Pot 2: "
    
    // 3. Stampiamo il suo valore (0-1023)
    Serial.println(valorePot);
  }
  
  // Aggiungiamo un separatore per leggibilità
  Serial.println("--------------------");
  
  // Aspettiamo un po' prima di ripetere
  delay(250); 
}