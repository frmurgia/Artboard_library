/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo: Test Bottoni
Descrizione: Legge lo stato di 8 bottoni (0-7)
             e stampa un messaggio chiaro sul Serial Monitor.

La funzione artboard.button(i) restituisce un valore digitale:
- 0 (LOW) se il bottone è PREMUTO
- 1 (HIGH) se il bottone è RILASCIATO

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>
*/

#include <Artboard.h>  // Includiamo la libreria

Artboard artboard;     // Creiamo un oggetto "artboard"

void setup() {
  Serial.begin(9600); // Avvia la comunicazione seriale
  Serial.println("--- Test Bottoni Artboard ---");
  Serial.println("Premi i bottoni da 0 a 7...");
}


void loop() {
  
  // Usiamo un ciclo "for" per controllare tutti i bottoni da 0 a 7
  for (int i = 0; i < 8; i++) {
    
    // 1. Leggiamo lo stato del bottone "i"
    int statoBottone = artboard.button(i);
    
    // 2. Stampiamo il nome del bottone
    Serial.print("Bottone ");
    Serial.print(i);
    Serial.print(": "); // Stampa: "Bottone 3: "
    
    // 3. Controlliamo se è premuto o rilasciato
    if (statoBottone == LOW) {
      Serial.println("Rilasciato"); // Stampa "PREMUTO" se il valore è 0
    } else {
      Serial.println("Premuto"); // Stampa "Rilasciato" se il valore è 1
    }
  }
  
  // Aggiungiamo un separatore per leggibilità
  Serial.println("--------------------");
  
  // Aspettiamo mezzo secondo prima di ripetere
  delay(100); 
}