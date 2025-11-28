/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 2 - Controllo Frequenza
Descrizione: Generiamo un'onda sinusoidale e usiamo
             il potenziometro 0 per controllare la sua frequenza (pitch).
             
Hardware:
- Potenziometro 0: Controlla la frequenza (da bassa ad alta)

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------

 importiamo il setup da
 https://www.pjrc.com/teensy/gui
<><><><><><><><><><><><><><><><><><><>
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h> // Includiamo la libreria Artboard
Artboard artboard;    // Creiamo l'oggetto artboard

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;     // Oggetto che genera il suono
AudioOutputAnalog        dac;       // Uscita audio (MONO)
AudioConnection          patchCord1(sine1, 0, dac, 0); // Suono -> Uscita
// GUItool: end automatically generated code

void setup() {
  AudioMemory(12); // Alloca la memoria audio
  Serial.begin(9600);
  
  // Impostiamo un volume (ampiezza) fisso.
  // 0.6 è un buon volume (circa 60%)
  sine1.amplitude(0.6);
  
  Serial.println("Sketch 2: Controllo Frequenza.");
  Serial.println("Muovi il potenziometro 0 per cambiare il pitch.");
}

void loop() {
  
  // 1. Leggi il potenziometro 0 (valore da 0 a 1023)
  int valorePot = artboard.pot(0);
  
  // 2. Mappa (converti) il valore del potenziometro in un range di frequenze
  // Usiamo un range da 100Hz (basso) a 2000Hz (alto)
  int freq = map(valorePot, 0, 1023, 100, 2000);
  
  // 3. Applica la nuova frequenza al generatore di suono
  sine1.frequency(freq);
  
  // (Opzionale) Stampa il valore per debug
  // Serial.println(freq);
  
  // Piccolo ritardo per non sovraccaricare il sistema
  delay(10); 
}