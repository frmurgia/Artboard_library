/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 6 - Polifonia + Ottave + Forme d'Onda
Descrizione:   Partiamo dallo Sketch 5 e aggiungiamo il controllo
               della FORMA D'ONDA (timbro).
               Usiamo il potenziometro 2 per l'ottava e il
               potenziometro 3 per la forma d'onda.

Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Controlla l'Attack
- Pot 1:       Controlla il Release
- Pot 2:       Controlla l'Ottava (5 livelli)
- Pot 3:       Controlla la Forma d'Onda (4 tipi)
- LED (Pin 29): Segue l'inviluppo audio

--------------------------------------
FORME D'ONDA E ZONE DEI POTENZIOMETRI
--------------------------------------
FORME D'ONDA:
Nello sketch precedente usavamo solo AudioSynthWaveformSine,
che genera solo onde sinusoidali (suono puro, tipo flauto).

Ora passiamo a AudioSynthWaveform, che può generare 4 tipi diversi:
- WAVEFORM_SINE:     Suono morbido, puro (flauto)
- WAVEFORM_SAWTOOTH: Suono brillante, ricco (archi, synth)
- WAVEFORM_SQUARE:   Suono vuoto, elettronico (clarinetto, chip music)
- WAVEFORM_TRIANGLE: Suono intermedio tra sine e square

ZONE DEI POTENZIOMETRI:
Pot 2 (Ottava) - diviso in 5 zone:
  0-204    → ottava 1
  205-409  → ottava 2
  410-614  → ottava 4
  615-819  → ottava 8
  820-1023 → ottava 16

Pot 3 (Forma d'onda) - diviso in 4 zone:
  0-255    → SINE
  256-511  → SAWTOOTH
  512-767  → SQUARE
  768-1023 → TRIANGLE
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
// --- MODIFICA: Sostituiamo Sine con Waveform ---
AudioSynthWaveformDc     voice1env4;
AudioSynthWaveformDc     voice1env2;
AudioSynthWaveformDc     voice1env3;
AudioSynthWaveformDc     voice1env1;
AudioSynthWaveform       waveform4;      // Era AudioSynthWaveformSine
AudioSynthWaveformDc     voice1env5;
AudioSynthWaveform       waveform1;      // Era AudioSynthWaveformSine
AudioSynthWaveformDc     voice1env7;
AudioSynthWaveformDc     voice1env9;
AudioSynthWaveform       waveform2;      // Era AudioSynthWaveformSine
AudioSynthWaveformDc     voice1env10;
AudioSynthWaveformDc     voice1env8;
AudioSynthWaveform       waveform3;      // Era AudioSynthWaveformSine
AudioSynthWaveformDc     voice1env6;
AudioSynthWaveformDc     voice1env12;
AudioSynthWaveform       waveform5;      // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform7;      // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform9;      // Era AudioSynthWaveformSine
AudioSynthWaveformDc     voice1env11;
AudioSynthWaveform       waveform6;      // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform8;      // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform10;     // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform12;     // Era AudioSynthWaveformSine
AudioSynthWaveform       waveform11;     // Era AudioSynthWaveformSine
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
AudioConnection          patchCord5(waveform4, 0, multiply4, 0);
AudioConnection          patchCord6(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord7(waveform1, 0, multiply1, 0);
AudioConnection          patchCord8(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord9(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord10(waveform2, 0, multiply2, 0);
AudioConnection          patchCord11(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord12(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord13(waveform3, 0, multiply3, 0);
AudioConnection          patchCord14(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord15(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord16(waveform5, 0, multiply5, 0);
AudioConnection          patchCord17(waveform7, 0, multiply7, 0);
AudioConnection          patchCord18(waveform9, 0, multiply9, 0);
AudioConnection          patchCord19(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord20(waveform6, 0, multiply6, 0);
AudioConnection          patchCord21(waveform8, 0, multiply8, 0);
AudioConnection          patchCord22(waveform10, 0, multiply10, 0);
AudioConnection          patchCord23(waveform12, 0, multiply12, 0);
AudioConnection          patchCord24(waveform11, 0, multiply11, 0);
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

// Variabili per tenere traccia degli stati precedenti
int lastOctave = -1;
int lastWaveform = -1;

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
  
  // Inizializza tutte le voci con forma d'onda e ottava base
  // Partiremo con SINE (zona centrale del pot 3) e ottava 4 (zona centrale del pot 2)
  waveform1.begin(1.0, DO * 4, WAVEFORM_SINE);
  waveform2.begin(1.0, DOd * 4, WAVEFORM_SINE);
  waveform3.begin(1.0, RE * 4, WAVEFORM_SINE);
  waveform4.begin(1.0, REd * 4, WAVEFORM_SINE);
  waveform5.begin(1.0, MI * 4, WAVEFORM_SINE);
  waveform6.begin(1.0, FA * 4, WAVEFORM_SINE);
  waveform7.begin(1.0, FAd * 4, WAVEFORM_SINE);
  waveform8.begin(1.0, SOL * 4, WAVEFORM_SINE);
  waveform9.begin(1.0, SOLd * 4, WAVEFORM_SINE);
  waveform10.begin(1.0, LA * 4, WAVEFORM_SINE);
  waveform11.begin(1.0, LAd * 4, WAVEFORM_SINE);
  waveform12.begin(1.0, SI * 4, WAVEFORM_SINE);
  
  // Imposta i gain dei mixer
  mixer1.gain(0, .25); mixer1.gain(1, .25); mixer1.gain(2, .25); mixer1.gain(3, .25);
  mixer2.gain(0, .25); mixer2.gain(1, .25); mixer2.gain(2, .25); mixer2.gain(3, .25);
  mixer3.gain(0, .25); mixer3.gain(1, .25); mixer3.gain(2, .25); mixer3.gain(3, .25);
  mixer4.gain(0, .33); mixer4.gain(1, .33); mixer4.gain(2, .33);
  
  Serial.println("Sketch 6: Ottave + Forme d'Onda con Potenziometri");
  Serial.println("Pot 2: Controlla l'ottava (5 livelli)");
  Serial.println("Pot 3: Controlla la forma d'onda (4 tipi)");
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);
  
  // Leggi i potenziometri per ottava e forma d'onda
  int potOctave = artboard.pot(2);
  int potWaveform = artboard.pot(3);


  // --- 2. DETERMINA L'OTTAVA IN BASE ALLA POSIZIONE DEL POT 2 ---
  //
  // Zone del potenziometro 2:
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
  
  
  // --- 3. DETERMINA LA FORMA D'ONDA IN BASE ALLA POSIZIONE DEL POT 3 ---
  //
  // Zone del potenziometro 3:
  // 0-255    → SINE (morbido)
  // 256-511  → SAWTOOTH (brillante)
  // 512-767  → SQUARE (elettronico)
  // 768-1023 → TRIANGLE (intermedio)
  
  int currentWaveform;
  
  if (potWaveform < 256) {
    currentWaveform = WAVEFORM_SINE;
  }
  else if (potWaveform < 512) {
    currentWaveform = WAVEFORM_SAWTOOTH;
  }
  else if (potWaveform < 768) {
    currentWaveform = WAVEFORM_SQUARE;
  }
  else {
    currentWaveform = WAVEFORM_TRIANGLE;
  }
  
  
  // --- 4. APPLICA LA NUOVA OTTAVA (solo se è cambiata) ---
  
  if (currentOctave != lastOctave) {
    Serial.print("Ottava: "); Serial.println(currentOctave);
    
    // Applica la nuova ottava a tutte le 12 voci
    waveform1.frequency(DO * currentOctave);
    waveform2.frequency(DOd * currentOctave);
    waveform3.frequency(RE * currentOctave);
    waveform4.frequency(REd * currentOctave);
    waveform5.frequency(MI * currentOctave);
    waveform6.frequency(FA * currentOctave);
    waveform7.frequency(FAd * currentOctave);
    waveform8.frequency(SOL * currentOctave);
    waveform9.frequency(SOLd * currentOctave);
    waveform10.frequency(LA * currentOctave);
    waveform11.frequency(LAd * currentOctave);
    waveform12.frequency(SI * currentOctave);
    
    lastOctave = currentOctave;
  }
  
  
  // --- 5. APPLICA LA NUOVA FORMA D'ONDA (solo se è cambiata) ---
  
  if (currentWaveform != lastWaveform) {
    // Stampa il nome della forma d'onda
    Serial.print("Forma d'onda: ");
    
    if (currentWaveform == WAVEFORM_SINE) {
      Serial.println("SINE");
    }
    else if (currentWaveform == WAVEFORM_SAWTOOTH) {
      Serial.println("SAWTOOTH");
    }
    else if (currentWaveform == WAVEFORM_SQUARE) {
      Serial.println("SQUARE");
    }
    else if (currentWaveform == WAVEFORM_TRIANGLE) {
      Serial.println("TRIANGLE");
    }
    
    // Applica la nuova forma d'onda a tutte le 12 voci
    // Usiamo begin() per reimpostare forma d'onda, volume e frequenza
    waveform1.begin(1.0, DO * currentOctave, currentWaveform);
    waveform2.begin(1.0, DOd * currentOctave, currentWaveform);
    waveform3.begin(1.0, RE * currentOctave, currentWaveform);
    waveform4.begin(1.0, REd * currentOctave, currentWaveform);
    waveform5.begin(1.0, MI * currentOctave, currentWaveform);
    waveform6.begin(1.0, FA * currentOctave, currentWaveform);
    waveform7.begin(1.0, FAd * currentOctave, currentWaveform);
    waveform8.begin(1.0, SOL * currentOctave, currentWaveform);
    waveform9.begin(1.0, SOLd * currentOctave, currentWaveform);
    waveform10.begin(1.0, LA * currentOctave, currentWaveform);
    waveform11.begin(1.0, LAd * currentOctave, currentWaveform);
    waveform12.begin(1.0, SI * currentOctave, currentWaveform);
    
    lastWaveform = currentWaveform;
  }


  // --- 6. LOGICA NOTE (Touch) ---

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
