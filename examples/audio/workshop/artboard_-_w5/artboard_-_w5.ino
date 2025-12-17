/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 5 - Polifonia + Cambio Ottave
Descrizione:   Partiamo dal nostro synth polifonico (sketch 4)
               e aggiungiamo il controllo dell'OTTAVA.
               Usiamo il potenziometro 2 per cambiare l'altezza
               di tutte le 12 note contemporaneamente.

Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Controlla l'Attack
- Pot 1:       Controlla il Release
- Pot 2:       Controlla l'Ottava (5 livelli)
- LED (Pin 29): Segue l'inviluppo audio

--------------------------------------
DIVISIONE DELLA CORSA DEL POTENZIOMETRO
--------------------------------------
Il potenziometro legge valori da 0 a 1023.
Invece di usare tutta la corsa per un valore continuo,
la DIVIDIAMO in 5 ZONE uguali, ognuna rappresenta un'ottava:

Zone:           0-204  |  205-409  |  410-614  |  615-819  |  820-1023
Ottava:            1   |     2     |     4     |     8     |     16
Suono:       Grave ++  |  Grave +  |  Normale  |  Acuto +  |  Acuto ++

Questo ci permette di avere 5 scelte discrete (separate)
invece di un valore continuo che cambierebbe troppo rapidamente.

COME FUNZIONA NEL CODICE?
Usiamo una serie di "if" per controllare in quale zona
si trova il valore del potenziometro:
  if (potValue < 205) → ottava = 1
  else if (potValue < 410) → ottava = 2
  ...e così via

Questo è più semplice degli array e non serve l'edge detection!
--------------------------------------

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
<><><><><><><><><><><><><><><><><><><>
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h>
Artboard artboard;


// GUItool: begin automatically generated code
AudioSynthWaveformDc     voice1env4;
AudioSynthWaveformDc     voice1env2;
AudioSynthWaveformDc     voice1env3;
AudioSynthWaveformDc     voice1env1;
AudioSynthWaveformSine   sine4;
AudioSynthWaveformDc     voice1env5;
AudioSynthWaveformSine   sine1;
AudioSynthWaveformDc     voice1env7;
AudioSynthWaveformDc     voice1env9;
AudioSynthWaveformSine   sine2;
AudioSynthWaveformDc     voice1env10;
AudioSynthWaveformDc     voice1env8;
AudioSynthWaveformSine   sine3;
AudioSynthWaveformDc     voice1env6;
AudioSynthWaveformDc     voice1env12;
AudioSynthWaveformSine   sine5;
AudioSynthWaveformSine   sine7;
AudioSynthWaveformSine   sine9;
AudioSynthWaveformDc     voice1env11;
AudioSynthWaveformSine   sine6;
AudioSynthWaveformSine   sine8;
AudioSynthWaveformSine   sine10;
AudioSynthWaveformSine   sine12;
AudioSynthWaveformSine   sine11;
AudioEffectMultiply      multiply12;
AudioEffectMultiply      multiply11;
AudioEffectMultiply      multiply2;
AudioEffectMultiply      multiply1;
AudioEffectMultiply      multiply10;
AudioEffectMultiply      multiply3;
AudioEffectMultiply      multiply9;
AudioEffectMultiply      multiply7;
AudioEffectMultiply      multiply6;
AudioEffectMultiply      multiply4;
AudioEffectMultiply      multiply8;
AudioEffectMultiply      multiply5;
AudioMixer4              mixer2;
AudioMixer4              mixer1;
AudioMixer4              mixer3;
AudioMixer4              mixer4;
AudioAnalyzePeak         peak1;
AudioOutputAnalog        dac0;
AudioConnection          patchCord1(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord2(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord3(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord4(voice1env1, 0, multiply1, 1);
AudioConnection          patchCord5(sine4, 0, multiply4, 0);
AudioConnection          patchCord6(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord7(sine1, 0, multiply1, 0);
AudioConnection          patchCord8(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord9(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord10(sine2, 0, multiply2, 0);
AudioConnection          patchCord11(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord12(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord13(sine3, 0, multiply3, 0);
AudioConnection          patchCord14(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord15(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord16(sine5, 0, multiply5, 0);
AudioConnection          patchCord17(sine7, 0, multiply7, 0);
AudioConnection          patchCord18(sine9, 0, multiply9, 0);
AudioConnection          patchCord19(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord20(sine6, 0, multiply6, 0);
AudioConnection          patchCord21(sine8, 0, multiply8, 0);
AudioConnection          patchCord22(sine10, 0, multiply10, 0);
AudioConnection          patchCord23(sine12, 0, multiply12, 0);
AudioConnection          patchCord24(sine11, 0, multiply11, 0);
AudioConnection          patchCord25(multiply12, 0, mixer3, 3);
AudioConnection          patchCord26(multiply11, 0, mixer3, 2);
AudioConnection          patchCord27(multiply2, 0, mixer1, 1);
AudioConnection          patchCord28(multiply1, 0, mixer1, 0);
AudioConnection          patchCord29(multiply10, 0, mixer3, 1);
AudioConnection          patchCord30(multiply3, 0, mixer1, 2);
AudioConnection          patchCord31(multiply9, 0, mixer3, 0);
AudioConnection          patchCord32(multiply7, 0, mixer2, 2);
AudioConnection          patchCord33(multiply6, 0, mixer2, 1);
AudioConnection          patchCord34(multiply4, 0, mixer1, 3);
AudioConnection          patchCord35(multiply8, 0, mixer2, 3);
AudioConnection          patchCord36(multiply5, 0, mixer2, 0);
AudioConnection          patchCord37(mixer2, 0, mixer4, 1);
AudioConnection          patchCord38(mixer1, 0, mixer4, 0);
AudioConnection          patchCord39(mixer3, 0, mixer4, 2);
AudioConnection          patchCord40(mixer4, 0, dac0, 0);
AudioConnection          patchCord41(mixer4, 0, peak1, 0);
// GUItool: end automatically generated code


int led = 29; // Pin del LED

// Variabile per tenere traccia dell'ottava precedente
int lastOctave = -1;

// Note (Frequenze di base, divise per 4 per avere margine verso l'alto)
float DO    = 261.6 / 4;
float DOd   = 277.2 / 4;
float RE    = 293.7 / 4;
float REd   = 311.1 / 4;
float MI    = 329.6 / 4;
float FA    = 349.2 / 4;
float FAd   = 370 / 4  ;
float SOL   = 392 / 4  ;
float SOLd  = 415.3 / 4;
float LA    = 440 / 4  ;
float LAd   = 466.2 / 4;
float SI    = 493.9 / 4;


// ----- SETUP -----

void setup() {
  pinMode(led, OUTPUT); 
  AudioMemory(24);
  Serial.begin(9600);
  
  // Inizializza tutti gli inviluppi a 0 (silenzio)
  voice1env1.amplitude(0.0);
  voice1env2.amplitude(0.0);
  voice1env3.amplitude(0.0);
  voice1env4.amplitude(0.0);
  voice1env5.amplitude(0.0);
  voice1env6.amplitude(0.0);
  voice1env7.amplitude(0.0);
  voice1env8.amplitude(0.0);
  voice1env9.amplitude(0.0);
  voice1env10.amplitude(0.0);
  voice1env11.amplitude(0.0);
  voice1env12.amplitude(0.0);
  
  // Imposta il volume fisso delle sinusoidi
  sine1.amplitude(0.8);  sine2.amplitude(0.8);
  sine3.amplitude(0.8);  sine4.amplitude(0.8);
  sine5.amplitude(0.8);  sine6.amplitude(0.8);
  sine7.amplitude(0.8);  sine8.amplitude(0.8);
  sine9.amplitude(0.8);  sine10.amplitude(0.8);
  sine11.amplitude(0.8); sine12.amplitude(0.8);
  
  // Imposta i gain dei mixer
  mixer1.gain(0, .25); mixer1.gain(1, .25); mixer1.gain(2, .25); mixer1.gain(3, .25);
  mixer2.gain(0, .25); mixer2.gain(1, .25); mixer2.gain(2, .25); mixer2.gain(3, .25);
  mixer3.gain(0, .25); mixer3.gain(1, .25); mixer3.gain(2, .25); mixer3.gain(3, .25);
  mixer4.gain(0, .33); mixer4.gain(1, .33); mixer4.gain(2, .33);
  
  Serial.println("Sketch 5: Cambio Ottave con Potenziometro");
  Serial.println("Pot 2: Controlla l'ottava (5 livelli)");
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);
  
  // Leggi il potenziometro 2 per l'ottava
  int potOctave = artboard.pot(2);


  // --- 2. DETERMINA L'OTTAVA IN BASE ALLA POSIZIONE DEL POT ---

  // Zone del potenziometro:
  // 0-204    → ottava 1  (molto grave)
  // 205-409  → ottava 2  (grave)
  // 410-614  → ottava 4  (normale)
  // 615-819  → ottava 8  (acuto)
  // 820-1023 → ottava 16 (molto acuto)
  
  int currentOctave;
  
  if (potOctave < 205) {
    currentOctave = 1;
  } 
  else if (potOctave < 410) {
    currentOctave = 2;
  }
  else if (potOctave < 615) {
    currentOctave = 4;
  }
  else if (potOctave < 820) {
    currentOctave = 8;
  }
  else {
    currentOctave = 16;
  }
  
  // --- 3. APPLICA LA NUOVA OTTAVA (solo se è cambiata) ---
  //
  // Per evitare di cambiare le frequenze continuamente,
  // aggiorniamo solo quando l'ottava effettivamente cambia zona
  
  if (currentOctave != lastOctave) {
    Serial.print("Ottava: "); Serial.println(currentOctave);
    
    // Applica la nuova ottava a tutte le 12 voci
    sine1.frequency(DO * currentOctave);
    sine2.frequency(DOd * currentOctave);
    sine3.frequency(RE * currentOctave);
    sine4.frequency(REd * currentOctave);
    sine5.frequency(MI * currentOctave);
    sine6.frequency(FA * currentOctave);
    sine7.frequency(FAd * currentOctave);
    sine8.frequency(SOL * currentOctave);
    sine9.frequency(SOLd * currentOctave);
    sine10.frequency(LA * currentOctave);
    sine11.frequency(LAd * currentOctave);
    sine12.frequency(SI * currentOctave);
    
    lastOctave = currentOctave;
  }

  // --- 4. LOGICA NOTE (Touch) ---

  if (artboard.touch(0) > 6000) { voice1env1.amplitude(1.0, attackTime); }
  else { voice1env1.amplitude(0.0, releaseTime); }

  if (artboard.touch(1) > 6000) { voice1env2.amplitude(1.0, attackTime); }
  else { voice1env2.amplitude(0.0, releaseTime); }

  if (artboard.touch(2) > 6000) { voice1env3.amplitude(1.0, attackTime); }
  else { voice1env3.amplitude(0.0, releaseTime); }

  if (artboard.touch(3) > 6000) { voice1env4.amplitude(1.0, attackTime); }
  else { voice1env4.amplitude(0.0, releaseTime); }

  if (artboard.touch(4) > 6000) { voice1env5.amplitude(1.0, attackTime); }
  else { voice1env5.amplitude(0.0, releaseTime); }

  if (artboard.touch(5) > 6000) { voice1env6.amplitude(1.0, attackTime); }
  else { voice1env6.amplitude(0.0, releaseTime); }

  if (artboard.touch(6) > 6000) { voice1env7.amplitude(1.0, attackTime); }
  else { voice1env7.amplitude(0.0, releaseTime); }

  if (artboard.touch(7) > 6000) { voice1env8.amplitude(1.0, attackTime); }
  else { voice1env8.amplitude(0.0, releaseTime); }

  if (artboard.touch(8) > 6000) { voice1env9.amplitude(1.0, attackTime); }
  else { voice1env9.amplitude(0.0, releaseTime); }

  if (artboard.touch(9) > 6000) { voice1env10.amplitude(1.0, attackTime); }
  else { voice1env10.amplitude(0.0, releaseTime); }

  if (artboard.touch(10) > 6000) { voice1env11.amplitude(1.0, attackTime); }
  else { voice1env11.amplitude(0.0, releaseTime); }

  if (artboard.touch(11) > 6000) { voice1env12.amplitude(1.0, attackTime); }
  else { voice1env12.amplitude(0.0, releaseTime); }
  

  delay(5);
}
