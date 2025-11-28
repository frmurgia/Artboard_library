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

#include <Artboard.h> // Includiamo la libreria (non la usiamo ancora)
Artboard artboard;    // Istanza (non usata ancora)

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          // Oggetto che genera il suono
AudioOutputAnalog          dac;           // Uscita audio (cuffie/casse)
AudioConnection          patchCord1(sine1, 0, dac, 0); // Suono -> Canale Sinistro
AudioConnection          patchCord2(sine1, 0, dac, 1); // Suono -> Canale Destro
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);
  
  // Alloca la memoria per il sistema audio.
  // 12 è un numero standard che funziona per quasi tutti i progetti.
  AudioMemory(12);
  
  // Imposta l'ampiezza (volume)
  // 1.0 è il massimo. Iniziamo con 0.5 (metà volume) 
  // per non danneggiare le orecchie!
  sine1.amplitude(0.5); 
  
  // Imposta la frequenza (pitch)
  // 440 Hz è la nota "La" standard (A4)
  sine1.frequency(440);
  
  Serial.println("Sketch 1: Sinusoide avviata.");
  Serial.println("Dovresti sentire un tono fisso (440 Hz).");
}

void loop() {
  // Il loop() è VUOTO!
  // L'oggetto Audio non ha bisogno del loop() per funzionare.
  // Genera il suono "in background" usando gli interrupt del Teensy.
}