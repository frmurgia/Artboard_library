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
AudioSynthWaveform       waveform3;      //xy=195.25403594970703,207.00023555755615
AudioSynthWaveformDc     voice1env3;     //xy=198.25402450561523,238.00020599365234
AudioSynthWaveform       waveform12;     //xy=203.25403594970703,1010.0002861022949
AudioSynthWaveform       waveform4;      //xy=208.25402069091797,284.00020599365234
AudioSynthWaveformDc     voice1env4;     //xy=209.25402069091797,320.00020694732666
AudioSynthWaveformDc     voice1env1;     //xy=213.25402069091797,73.00020599365234
AudioSynthWaveformDc     voice1env12;    //xy=212.25402069091797,1043.0002098083496
AudioSynthWaveformDc     voice1env2;     //xy=217.25402450561523,168.00020694732666
AudioSynthWaveform       waveform1;      //xy=218.25402450561523,41.000205993652344
AudioSynthWaveform       waveform2;      //xy=218.25403594970703,132.00022315979004
AudioSynthWaveformDc     voice1env5;     //xy=219.2540283203125,439.00020694732666
AudioSynthWaveform       waveform6;      //xy=220.2540168762207,475.00013732910156
AudioSynthWaveformDc     voice1env11;    //xy=220.2540397644043,974.0002861022949
AudioSynthWaveform       waveform5;      //xy=223.25402069091797,404.0001344680786
AudioSynthWaveformDc     voice1env6;     //xy=224.2540168762207,506.00013732910156
AudioSynthWaveform       waveform11;     //xy=224.2540397644043,945.0002861022949
AudioSynthWaveform       waveform9;      //xy=227.25402069091797,775.0002098083496
AudioSynthWaveform       waveform10;     //xy=227.2540397644043,854.0002222061157
AudioSynthWaveformDc     voice1env10;    //xy=229.25402450561523,901.0002784729004
AudioSynthWaveformDc     voice1env9;     //xy=230.2540283203125,806.0002841949463
AudioSynthWaveformDc     voice1env8;     //xy=232.25402450561523,706.0002069473267
AudioSynthWaveformDc     voice1env7;     //xy=239.25402450561523,626.0002062320709
AudioSynthWaveform       waveform8;      //xy=241.25401306152344,666.0001373291016
AudioSynthWaveform       waveform7;      //xy=246.25401496887207,593.0001373291016
AudioEffectMultiply      multiply11;     //xy=524.2540245056152,945.0002098083496
AudioEffectMultiply      multiply12;     //xy=527.254020690918,1000.0002098083496
AudioEffectMultiply      multiply10;     //xy=531.2540245056152,888.0002098083496
AudioEffectMultiply      multiply8;      //xy=533.2540740966797,710.0000810623169
AudioEffectMultiply      multiply9;      //xy=533.254020690918,832.0002098083496
AudioEffectMultiply      multiply7;      //xy=558.2540130615234,631.000078201294
AudioEffectMultiply      multiply2;      //xy=563.2540130615234,140.00013732910156
AudioEffectMultiply      multiply5;      //xy=569.2540435791016,447.00013542175293
AudioEffectMultiply      multiply4;      //xy=570.2540130615234,298.00007820129395
AudioEffectMultiply      multiply6;      //xy=572.2540130615234,522.000078201294
AudioEffectMultiply      multiply1;      //xy=574.2540168762207,57.00013732910156
AudioEffectMultiply      multiply3;      //xy=577.2540168762207,230.00013732910156
AudioMixer4              mixer2;         //xy=802.2540512084961,572.0001029968262
AudioMixer4              mixer3;         //xy=801.2540550231934,901.000280380249
AudioMixer4              mixer1;         //xy=810.2540512084961,173.00010299682617
AudioMixer4              mixer4;         //xy=967.2540588378906,600.0000171661377
AudioAnalyzePeak         peak1;          //xy=1106.2540645599365,575.0000162124634
AudioOutputAnalog        dac0;           //xy=1114.2540645599365,613.0000162124634
AudioConnection          patchCord1(waveform3, 0, multiply3, 0);
AudioConnection          patchCord2(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord3(waveform12, 0, multiply12, 0);
AudioConnection          patchCord4(waveform4, 0, multiply4, 0);
AudioConnection          patchCord5(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord6(voice1env1, 0, multiply1, 1);
AudioConnection          patchCord7(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord8(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord9(waveform1, 0, multiply1, 0);
AudioConnection          patchCord10(waveform2, 0, multiply2, 0);
AudioConnection          patchCord11(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord12(waveform6, 0, multiply6, 0);
AudioConnection          patchCord13(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord14(waveform5, 0, multiply5, 0);
AudioConnection          patchCord15(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord16(waveform11, 0, multiply11, 0);
AudioConnection          patchCord17(waveform9, 0, multiply9, 0);
AudioConnection          patchCord18(waveform10, 0, multiply10, 0);
AudioConnection          patchCord19(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord20(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord21(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord22(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord23(waveform8, 0, multiply8, 0);
AudioConnection          patchCord24(waveform7, 0, multiply7, 0);
AudioConnection          patchCord25(multiply11, 0, mixer3, 2);
AudioConnection          patchCord26(multiply12, 0, mixer3, 3);
AudioConnection          patchCord27(multiply10, 0, mixer3, 1);
AudioConnection          patchCord28(multiply8, 0, mixer2, 3);
AudioConnection          patchCord29(multiply9, 0, mixer3, 0);
AudioConnection          patchCord30(multiply7, 0, mixer2, 2);
AudioConnection          patchCord31(multiply2, 0, mixer1, 1);
AudioConnection          patchCord32(multiply5, 0, mixer2, 0);
AudioConnection          patchCord33(multiply4, 0, mixer1, 3);
AudioConnection          patchCord34(multiply6, 0, mixer2, 1);
AudioConnection          patchCord35(multiply1, 0, mixer1, 0);
AudioConnection          patchCord36(multiply3, 0, mixer1, 2);
AudioConnection          patchCord37(mixer2, 0, mixer4, 1);
AudioConnection          patchCord38(mixer3, 0, mixer4, 2);
AudioConnection          patchCord39(mixer1, 0, mixer4, 0);
AudioConnection          patchCord40(mixer4, dac0);
AudioConnection          patchCord41(mixer4, peak1);
// GUItool: end automatically generated code

// Variabili per tenere traccia degli stati precedenti
int lastOctave = -1;
int lastWaveform = -1;

// Note (Frequenze di base, divise per 4 per avere margine verso l'alto)
float DO = 261.6 / 4;
float DOd = 277.2 / 4;
float RE = 293.7 / 4;
float REd = 311.1 / 4;
float MI = 329.6 / 4;
float FA = 349.2 / 4;
float FAd = 370 / 4;
float SOL = 392 / 4;
float SOLd = 415.3 / 4;
float LA = 440 / 4;
float LAd = 466.2 / 4;
float SI = 493.9 / 4;


// ----- SETUP -----

void setup() {
  
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
  mixer1.gain(0, .25);
  mixer1.gain(1, .25);
  mixer1.gain(2, .25);
  mixer1.gain(3, .25);
  mixer2.gain(0, .25);
  mixer2.gain(1, .25);
  mixer2.gain(2, .25);
  mixer2.gain(3, .25);
  mixer3.gain(0, .25);
  mixer3.gain(1, .25);
  mixer3.gain(2, .25);
  mixer3.gain(3, .25);
  mixer4.gain(0, .33);
  mixer4.gain(1, .33);
  mixer4.gain(2, .33);

  Serial.println("Sketch 6: Ottave + Forme d'Onda con Potenziometri");
  Serial.println("Pot 2: Controlla l'ottava (5 livelli)");
  Serial.println("Pot 3: Controlla la forma d'onda (4 tipi)");
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime = map(artboard.pot(0), 0, 1023, 5, 1000);
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
  } else if (potOctave < 410) {
    currentOctave = 2;
  } else if (potOctave < 615) {
    currentOctave = 4;
  } else if (potOctave < 820) {
    currentOctave = 8;
  } else {
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
  } else if (potWaveform < 512) {
    currentWaveform = WAVEFORM_SAWTOOTH;
  } else if (potWaveform < 768) {
    currentWaveform = WAVEFORM_SQUARE;
  } else {
    currentWaveform = WAVEFORM_TRIANGLE;
  }


  // --- 4. APPLICA LA NUOVA OTTAVA (solo se è cambiata) ---

  if (currentOctave != lastOctave) {
    Serial.print("Ottava: ");
    Serial.println(currentOctave);

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
    } else if (currentWaveform == WAVEFORM_SAWTOOTH) {
      Serial.println("SAWTOOTH");
    } else if (currentWaveform == WAVEFORM_SQUARE) {
      Serial.println("SQUARE");
    } else if (currentWaveform == WAVEFORM_TRIANGLE) {
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

  if (artboard.touch(0) > 6000) {
    voice1env1.amplitude(1.0, attackTime);
  } else {
    voice1env1.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(1) > 6000) {
    voice1env2.amplitude(1.0, attackTime);
  } else {
    voice1env2.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(2) > 6000) {
    voice1env3.amplitude(1.0, attackTime);
  } else {
    voice1env3.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(3) > 6000) {
    voice1env4.amplitude(1.0, attackTime);
  } else {
    voice1env4.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(4) > 6000) {
    voice1env5.amplitude(1.0, attackTime);
  } else {
    voice1env5.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(5) > 6000) {
    voice1env6.amplitude(1.0, attackTime);
  } else {
    voice1env6.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(6) > 6000) {
    voice1env7.amplitude(1.0, attackTime);
  } else {
    voice1env7.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(7) > 6000) {
    voice1env8.amplitude(1.0, attackTime);
  } else {
    voice1env8.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(8) > 6000) {
    voice1env9.amplitude(1.0, attackTime);
  } else {
    voice1env9.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(9) > 6000) {
    voice1env10.amplitude(1.0, attackTime);
  } else {
    voice1env10.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(10) > 6000) {
    voice1env11.amplitude(1.0, attackTime);
  } else {
    voice1env11.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(11) > 6000) {
    voice1env12.amplitude(1.0, attackTime);
  } else {
    voice1env12.amplitude(0.0, releaseTime);
  }


  delay(5);
}
