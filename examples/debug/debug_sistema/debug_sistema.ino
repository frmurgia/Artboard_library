/*
  DEBUG TOTALE ARTBOARD
  Combina test per: Potenziometri (0-7), Bottoni (0-7) e Touch (0-11).
*/

#include <Artboard.h> // [cite: 4, 14, 24]

Artboard artboard; // Creazione oggetto artboard [cite: 5, 16, 25]

// Soglia per il sensore capacitivo 
const int SOGLIA_TOUCH = 7000; 

void setup() {
  Serial.begin(9600); // [cite: 6, 16, 26]
  Serial.println("--- AVVIO DEBUG COMPLETO ARTBOARD ---");
  Serial.println("Leggo: 8 Potenziometri, 8 Bottoni, 12 Touch");
  delay(1000);
}

void loop() {
  Serial.println("\n\n=== 1. POTENZIOMETRI (0-7) ===");
  // Ciclo lettura 8 potenziometri [cite: 23]
  for (int i = 0; i < 8; i++) {
    int valPot = artboard.pot(i); // Lettura valore 0-1023 
    
    Serial.print("Pot ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(valPot);
    Serial.print("\t"); // Tabulazione per formattazione
    
    // A capo ogni 4 potenziometri per ordine visivo
    if ((i + 1) % 4 == 0) Serial.println(); 
  }

  Serial.println("\n=== 2. BOTTONI (0-7) ===");
  // Ciclo lettura 8 bottoni [cite: 14]
  for (int i = 0; i < 8; i++) {
    int statoBtn = artboard.button(i); // Legge 0 o 1 
    
    Serial.print("Btn ");
    Serial.print(i);
    Serial.print(": ");
    
    // NOTA: Basato sulla documentazione, 0 (LOW) è PREMUTO.
    if (statoBtn == 0) {
      Serial.print("PREMUTO (0)"); 
    } else {
      Serial.print("- (1)");
    }
    Serial.print("\t");
    
    if ((i + 1) % 4 == 0) Serial.println();
  }

  Serial.println("\n=== 3. TOUCH (0-11) ===");
  // Ciclo lettura 12 sensori touch [cite: 1]
  for (int i = 0; i < 12; i++) {
    int valTouch = artboard.touch(i); // Valore grezzo [cite: 2]
    
    Serial.print("T");
    Serial.print(i);
    Serial.print(":");
    Serial.print(valTouch);
    
    // Controllo soglia tocco 
    if (valTouch > SOGLIA_TOUCH) {
      Serial.print("*ON*");
    } else {
      Serial.print("    ");
    }
    Serial.print("\t");
    
    // A capo ogni 4 sensori
    if ((i + 1) % 4 == 0) Serial.println();
  }

  Serial.println("------------------------------------------------");
  delay(800); // Pausa per permettere la lettura dei dati [cite: 13, 22, 30]
}