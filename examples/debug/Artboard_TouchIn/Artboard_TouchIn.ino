/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: touchin 
Descrizione: Legge lo stato di 12 sensori touch (0-11)
             e stampa i loro valori sul Serial Monitor.

Chiamare artboard.touch(i) per leggere l'ingresso capacitivo.
i equivale alla posizione di T
0=do
1=do#
2=re#
ecc.

La funzione artboard.touch(i) restituisce un valore "grezzo".
Più alto è il numero, più "vicino" è il tocco.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>
*/

#include <Artboard.h> // includiamo la libreria

Artboard artboard;    // Creiamo un oggetto "artboard"

// Imposta una soglia per decidere cosa è un "tocco"
// (Dovrai regolarla in base ai tuoi sensori, ma 7000 è un buon inizio)
const int SOGLIA_TOUCH = 7000; 

void setup(){
  Serial.begin(9600); // Avvia la comunicazione seriale
  Serial.println("--- Test Sensori Touch Artboard ---");
  Serial.println("Tocca i pad da 0 a 11...");
}


void loop(){
  
  // Usiamo un ciclo "for" per controllare tutti i 12 sensori touch
  for (int i = 0; i < 12; i++) {
    
    // 1. Leggiamo il valore del sensore "i"
    int valoreTouch = artboard.touch(i);
    
    // 2. Stampiamo il nome del sensore
    Serial.print("Touch ");
    Serial.print(i);
    Serial.print(": "); // Stampa: "Touch 5: "
    
    // 3. Stampiamo il suo valore grezzo
    Serial.print(valoreTouch);
    
    // 4. Stampiamo un messaggio se è considerato "toccato"
    if (valoreTouch > SOGLIA_TOUCH) {
      Serial.print("  <--- TOCCATO!");
    }
    
    // Vai a capo per il prossimo sensore
    Serial.println();
  }
  
  // Aggiungiamo un separatore per leggibilità
  Serial.println("--------------------");
  
  // Aspettiamo un po' prima di ripetere
  delay(250);
}