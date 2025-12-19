/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 7 - Synth Completo con Filtro e LFO
Descrizione:   Questo è lo sketch completo! Combiniamo tutto:
               1. Polysynth a 12 voci
               2. Selettori di Ottava e Forma d'Onda (Pot 2, 3)
               3. Inviluppo (Pot 0, 1)
               4. Un Filtro per il "tono" (Pot 4)
               5. Un LFO per modulare il filtro (Pot 5, 6)

Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Attack
- Pot 1:       Release
- Pot 2:       Ottava (5 livelli)
- Pot 3:       Forma d'Onda oscillatori (4 tipi)
- Pot 4:       Filtro Cutoff (frequenza/tono)
- Pot 5:       Velocità dell'LFO (da 0.1 Hz a 10 Hz)
- Pot 6:       Forma d'Onda dell'LFO (4 tipi)
- LED (Pin 29): Segue l'inviluppo audio

--------------------------------------
LEZIONE: COS'È UN LFO?
--------------------------------------
LFO significa "Low Frequency Oscillator" (Oscillatore a Bassa Frequenza).
È un oscillatore come quelli che generano le note, ma molto più LENTO.
Invece di generare un suono udibile (20-20000 Hz), l'LFO oscilla
tra 0.1 e 10 Hz (da 1 volta ogni 10 secondi a 10 volte al secondo).

COME FUNZIONA NEL NOSTRO SYNTH:
L'LFO MODULA (cambia automaticamente) la frequenza del filtro,
creando un effetto di "wobble" o "movimento" nel suono.

Pot 5 - VELOCITÀ (Rate):
- Sinistra (0.1 Hz): wobble molto lento
- Destra (10 Hz): wobble veloce/vibrante

Pot 6 - FORMA D'ONDA dell'LFO (diviso in 4 zone):
- SINE: movimento morbido, arrotondato
- SAWTOOTH: movimento ascendente lineare, ritorno brusco
- SQUARE: salto improvviso tra due valori (on/off)
- TRIANGLE: movimento su e giù lineare

ARCHITETTURA DEL SEGNALE:
12 Oscillatori → 12 Inviluppi (VCA) → 3 Mixer → 1 Mixer Finale
→ FILTRO (modulato da LFO) → DAC (uscita audio)
         ↑
      LFO (modula il cutoff del filtro)

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
// --- ARCHITETTURA COMPLETA CON FILTRO E LFO ---
AudioSynthWaveform       waveform4;
AudioSynthWaveformDc     voice1env4;
AudioSynthWaveformDc     voice1env3;
AudioSynthWaveformDc     voice1env2;
AudioSynthWaveform       waveform2;
AudioSynthWaveformDc     voice1env12;
AudioSynthWaveform       waveform3;
AudioSynthWaveformDc     voice1env1;
AudioSynthWaveformDc     voice1env8;
AudioSynthWaveform       waveform12;
AudioSynthWaveform       waveform1;
AudioSynthWaveformDc     voice1env9;
AudioSynthWaveformDc     voice1env10;
AudioSynthWaveform       waveform10;
AudioSynthWaveformDc     voice1env11;
AudioSynthWaveform       waveform9;
AudioSynthWaveform       waveform11;
AudioSynthWaveformDc     voice1env7;
AudioSynthWaveform       waveform8;
AudioSynthWaveform       waveform7;
AudioSynthWaveformDc     voice1env6;
AudioSynthWaveformDc     voice1env5;
AudioSynthWaveform       waveform6;
AudioSynthWaveform       waveform5;
AudioEffectMultiply      multiply3;
AudioEffectMultiply      multiply2;
AudioEffectMultiply      multiply4;
AudioEffectMultiply      multiply1;
AudioEffectMultiply      multiply8;
AudioEffectMultiply      multiply6;
AudioEffectMultiply      multiply7;
AudioEffectMultiply      multiply5;
AudioEffectMultiply      multiply12;
AudioEffectMultiply      multiply10;
AudioEffectMultiply      multiply11;
AudioEffectMultiply      multiply9;
AudioMixer4              mixer3;
AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioMixer4              mixer4;           // Mixer finale
AudioSynthWaveform       lfo1;             // <-- NOVITÀ: L'LFO
AudioFilterStateVariable filter1;          // Filtro con modulazione LFO
AudioAnalyzePeak         peak1;
AudioOutputAnalog        dac0;
AudioConnection          patchCord1(waveform4, 0, multiply4, 0);
AudioConnection          patchCord2(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord3(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord4(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord5(waveform2, 0, multiply2, 0);
AudioConnection          patchCord6(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord7(waveform3, 0, multiply3, 0);
AudioConnection          patchCord8(voice1env1, 0, multiply1, 1);
AudioConnection          patchCord9(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord10(waveform12, 0, multiply12, 0);
AudioConnection          patchCord11(waveform1, 0, multiply1, 0);
AudioConnection          patchCord12(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord13(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord14(waveform10, 0, multiply10, 0);
AudioConnection          patchCord15(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord16(waveform9, 0, multiply9, 0);
AudioConnection          patchCord17(waveform11, 0, multiply11, 0);
AudioConnection          patchCord18(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord19(waveform8, 0, multiply8, 0);
AudioConnection          patchCord20(waveform7, 0, multiply7, 0);
AudioConnection          patchCord21(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord22(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord23(waveform6, 0, multiply6, 0);
AudioConnection          patchCord24(waveform5, 0, multiply5, 0);
AudioConnection          patchCord25(multiply3, 0, mixer1, 2);
AudioConnection          patchCord26(multiply2, 0, mixer1, 1);
AudioConnection          patchCord27(multiply4, 0, mixer1, 3);
AudioConnection          patchCord28(multiply1, 0, mixer1, 0);
AudioConnection          patchCord29(multiply8, 0, mixer2, 3);
AudioConnection          patchCord30(multiply6, 0, mixer2, 1);
AudioConnection          patchCord31(multiply7, 0, mixer2, 2);
AudioConnection          patchCord32(multiply5, 0, mixer2, 0);
AudioConnection          patchCord33(multiply12, 0, mixer3, 3);
AudioConnection          patchCord34(multiply10, 0, mixer3, 1);
AudioConnection          patchCord35(multiply11, 0, mixer3, 2);
AudioConnection          patchCord36(multiply9, 0, mixer3, 0);
AudioConnection          patchCord37(mixer3, 0, mixer4, 2);
AudioConnection          patchCord38(mixer1, 0, mixer4, 0);
AudioConnection          patchCord39(mixer2, 0, mixer4, 1);
// --- CATENA SEGNALE CON LFO ---
AudioConnection          patchCord40(mixer4, 0, filter1, 0);  // Audio → Filtro (Input 0)
AudioConnection          patchCord41(lfo1, 0, filter1, 1);    // LFO → Filtro (Input 1, Modulazione)
AudioConnection          patchCord42(filter1, 0, dac0, 0);    // Filtro → DAC
AudioConnection          patchCord43(filter1, 0, peak1, 0);   // Filtro → Peak (LED)
// GUItool: end automatically generated code


int led = 29; // Pin del LED

// Variabili per tenere traccia degli stati precedenti
int lastOctave = -1;
int lastWaveform = -1;
int lastLfoWaveform = -1;

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
  AudioMemory(64);  // Aumentato per filtro + LFO
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
  
  // --- IMPOSTAZIONI INIZIALI FILTRO ---
  filter1.resonance(2.0);           // Resonance fissa a 2.0
  filter1.octaveControl(2.0);       // Quantità di modulazione dell'LFO (2 ottave)
  
  // --- IMPOSTAZIONI INIZIALI LFO ---
  lfo1.begin(1.0, 1.0, WAVEFORM_SINE);  // Ampiezza 1.0, Frequenza 1 Hz, Forma SINE
  
  Serial.println("Sketch 7: Synth Completo con Filtro e LFO");
  Serial.println("Pot 2: Ottava (5 livelli)");
  Serial.println("Pot 3: Forma d'onda oscillatori (4 tipi)");
  Serial.println("Pot 4: Filtro cutoff");
  Serial.println("Pot 5: Velocità LFO (0.1-10 Hz)");
  Serial.println("Pot 6: Forma d'onda LFO (4 tipi)");
  Serial.println("Resonance: Fissa a 2.0");
  Serial.println("LFO Depth: Fissa a 2 ottave");
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);
  
  // Leggi i potenziometri per ottava, forma d'onda, filtro e LFO
  int potOctave = artboard.pot(2);
  int potWaveform = artboard.pot(3);
  int potFilter = artboard.pot(4);
  int potLfoRate = artboard.pot(5);
  int potLfoWaveform = artboard.pot(6);


  // --- 2. DETERMINA L'OTTAVA IN BASE ALLA POSIZIONE DEL POT 2 ---
  
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
  
  
  // --- 3. DETERMINA LA FORMA D'ONDA OSCILLATORI IN BASE AL POT 3 ---
  
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
  
  
  // --- 4. CONTROLLO FILTRO (POT 4) ---
  //
  // Il filtro viene aggiornato continuamente per permettere
  // un controllo espressivo in tempo reale
  
  float filterFreq = map(potFilter, 0, 1023, 100, 12000);
  filter1.frequency(filterFreq);
  
  
  // --- 5. CONTROLLO LFO RATE (POT 5) ---
  //
  // La velocità dell'LFO viene aggiornata continuamente
  // Range: da 0.1 Hz (molto lento) a 10 Hz (veloce)
  
  float lfoRate = map(potLfoRate, 0, 1023, 1, 100) / 10.0;  // Da 0.1 a 10.0 Hz
  lfo1.frequency(lfoRate);
  
  
  // --- 6. DETERMINA LA FORMA D'ONDA DELL'LFO (POT 6) ---
  
  int currentLfoWaveform;
  
  if (potLfoWaveform < 256) {
    currentLfoWaveform = WAVEFORM_SINE;
  }
  else if (potLfoWaveform < 512) {
    currentLfoWaveform = WAVEFORM_SAWTOOTH;
  }
  else if (potLfoWaveform < 768) {
    currentLfoWaveform = WAVEFORM_SQUARE;
  }
  else {
    currentLfoWaveform = WAVEFORM_TRIANGLE;
  }
  
  
  // --- 7. APPLICA LA NUOVA OTTAVA (solo se è cambiata) ---
  
  if (currentOctave != lastOctave) {
    Serial.print("Ottava: "); Serial.println(currentOctave);
    
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
  
  
  // --- 8. APPLICA LA NUOVA FORMA D'ONDA OSCILLATORI (solo se è cambiata) ---
  
  if (currentWaveform != lastWaveform) {
    Serial.print("Forma d'onda oscillatori: ");
    
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
  
  
  // --- 9. APPLICA LA NUOVA FORMA D'ONDA DELL'LFO (solo se è cambiata) ---
  
  if (currentLfoWaveform != lastLfoWaveform) {
    Serial.print("Forma d'onda LFO: ");
    
    if (currentLfoWaveform == WAVEFORM_SINE) {
      Serial.println("SINE");
    }
    else if (currentLfoWaveform == WAVEFORM_SAWTOOTH) {
      Serial.println("SAWTOOTH");
    }
    else if (currentLfoWaveform == WAVEFORM_SQUARE) {
      Serial.println("SQUARE");
    }
    else if (currentLfoWaveform == WAVEFORM_TRIANGLE) {
      Serial.println("TRIANGLE");
    }
    
    // Cambia la forma d'onda dell'LFO mantenendo ampiezza e frequenza
    lfo1.begin(1.0, lfoRate, currentLfoWaveform);
    
    lastLfoWaveform = currentLfoWaveform;
  }


  // --- 10. LOGICA NOTE (Touch) ---

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
  
  
  // --- 11. CONTROLLO LED ---
  if (peak1.available()) {
    float level = peak1.read();
    int brightness = (int)(level * 255.0);
    analogWrite(led, brightness);
  }

  delay(5);
}
