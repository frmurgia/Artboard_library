/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 1 - La Prima Sinusoide
Descrizione: "Hello, World!" dell'audio.
             Questo sketch genera un'onda sinusoidale pura (un fischio)
             alla frequenza di 440Hz (la nota "La").
             Non c'è ancora interazione.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------

 importiamo il setup da
 https://www.pjrc.com/teensy/gui
<><><><><><><><><><><><><><><><><><><>
*/

#include <Artboard.h>  // Includiamo la libreria (non la usiamo ancora)
Artboard artboard;     // Istanza (non usata ancora)

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine sine1;                   // Oggetto che genera il suono
AudioOutputAnalog dac0;                         // Uscita audio (cuffie/casse) DAC 0
AudioConnection patchCord1(sine1, 0, dac0, 0);  // Suono -> Canale Sinistro
AudioConnection patchCord2(sine1, 0, dac0, 1);  // Suono -> Canale Destro
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);

  // Alloca la memoria per il sistema audio.
  // 12 è un numero standard che funziona per quasi tutti i progetti.
  AudioMemory(12);

  // Impostiamo un volume (ampiezza) fisso.
  // 0.6 è un buon volume (circa 60%)
  sine1.amplitude(0.6);

  //Applica la frequenza 
  sine1.frequency(440);
}

void loop() {
  // Il loop() è VUOTO!
}