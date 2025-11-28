/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 4 - synth polifonico
Descrizione:   La versione più semplice di un synth.

               
Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Controlla l'Attack
- Pot 1:       Controlla il Release
- LED (Pin 29): Segue l'inviluppo audio (luminosità)

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h>
Artboard artboard;


// GUItool: begin automatically generated code
AudioSynthWaveformDc     voice1env4;     //xy=241,428
AudioSynthWaveformDc     voice1env2;     //xy=248,241
AudioSynthWaveformDc     voice1env3;     //xy=249,331
AudioSynthWaveformDc     voice1env1; //xy=251,147
AudioSynthWaveformSine   sine4;          //xy=252,395
AudioSynthWaveformDc     voice1env5;     //xy=257.25000381469727,533.2500085830688
AudioSynthWaveformSine   sine1;          //xy=259,116
AudioSynthWaveformDc     voice1env7;     //xy=257,700.7500123977661
AudioSynthWaveformDc     voice1env9;     //xy=256.75,918.2500143051147
AudioSynthWaveformSine   sine2;          //xy=260,209
AudioSynthWaveformDc     voice1env10;    //xy=257.50000762939453,1006.2500162124634
AudioSynthWaveformDc     voice1env8;     //xy=259.75000762939453,785.0000123977661
AudioSynthWaveformSine   sine3;          //xy=262,299
AudioSynthWaveformDc     voice1env6;     //xy=264.75,622.2500104904175
AudioSynthWaveformDc     voice1env12;    //xy=263.25000381469727,1167.750020980835
AudioSynthWaveformSine   sine5;          //xy=266.00000381469727,500.50000858306885
AudioSynthWaveformSine   sine7;          //xy=267.50000762939453,668.7500104904175
AudioSynthWaveformSine   sine9;          //xy=267.50000381469727,886.7500143051147
AudioSynthWaveformDc     voice1env11;    //xy=267.25000762939453,1085.5000168085098
AudioSynthWaveformSine   sine6;          //xy=272.00000381469727,590.2500104904175
AudioSynthWaveformSine   sine8;          //xy=271.50000762939453,752.5000123977661
AudioSynthWaveformSine   sine10;         //xy=271.00000762939453,972.2500162124634
AudioSynthWaveformSine   sine12;         //xy=275.50000381469727,1133.5000200271606
AudioSynthWaveformSine   sine11;         //xy=279.50000762939453,1052.0000162124634
AudioEffectMultiply      multiply12;     //xy=449.75000381469727,1151.7500200271606
AudioEffectMultiply      multiply11;     //xy=458.25000762939453,1066.7500171661377
AudioEffectMultiply      multiply2;      //xy=463,229
AudioEffectMultiply      multiply1;      //xy=465,130
AudioEffectMultiply      multiply10;     //xy=462.75000762939453,990.0000162124634
AudioEffectMultiply      multiply3;      //xy=469,314
AudioEffectMultiply      multiply9;      //xy=470.25000762939453,906.0000133514404
AudioEffectMultiply      multiply7;      //xy=472.25,685.2500009536743
AudioEffectMultiply      multiply6;      //xy=473.25,603.2500009536743
AudioEffectMultiply      multiply4;      //xy=475,385
AudioEffectMultiply      multiply8;      //xy=473.75000762939453,771.0000123977661
AudioEffectMultiply      multiply5;      //xy=476.25,519.2500009536743
AudioMixer4              mixer2;         //xy=774.7500114440918,650.7500076293945
AudioMixer4              mixer1; //xy=787.0000152587891,277.75000381469727
AudioMixer4              mixer3;         //xy=786.7500152587891,1032.7500076293945
AudioMixer4              mixer4;         //xy=1026.250015258789,509.2500057220459
AudioOutputAnalog        dac0;           //xy=1199.7500228881836,506.0000047683716
AudioAnalyzePeak         peak1;          //xy=1203.7500190734863,561.2500095367432
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
AudioConnection          patchCord40(mixer4, dac0);
AudioConnection          patchCord41(mixer4, peak1);
// GUItool: end automatically generated code


int led = 29; // Pin del LED

//Note
float DO    = 261.6 ;
float DOd   = 277.2 ;
float RE    = 293.7 ;
float REd   = 311.1 ;
float MI    = 329.6 ;
float FA    = 349.2 ;
float FAd   = 370   ;
float SOL   = 392   ;
float SOLd  = 415.3 ;
float LA    = 440   ;
float LAd   = 466.2 ;
float SI    = 493.9;

void setup() {
  pinMode(led, OUTPUT); 
  AudioMemory(24);
  Serial.begin(9600);
  
  // Inizializza tutte le voci (volume e inviluppo a 0)
  sine1.amplitude(0.8);  voice1env1.amplitude(0.0);
  sine2.amplitude(0.8);  voice1env2.amplitude(0.0);
  sine3.amplitude(0.8);  voice1env3.amplitude(0.0);
  sine4.amplitude(0.8);  voice1env4.amplitude(0.0);
  sine5.amplitude(0.8);  voice1env5.amplitude(0.0);
  sine6.amplitude(0.8);  voice1env6.amplitude(0.0);
  sine7.amplitude(0.8);  voice1env7.amplitude(0.0);
  sine8.amplitude(0.8);  voice1env8.amplitude(0.0);
  sine9.amplitude(0.8);  voice1env9.amplitude(0.0);
  sine10.amplitude(0.8); voice1env10.amplitude(0.0);
  sine11.amplitude(0.8); voice1env11.amplitude(0.0);
  sine12.amplitude(0.8); voice1env12.amplitude(0.0);
  
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
}


// ----- LOOP -----

void loop() {

  // 1. Leggi i potenziometri per Attack e Release
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);

  // ----- LOGICA SEMPLIFICATA -----
  //
  // Questo codice è semplice e funziona perfettamente.
  //
  // Quando tieni premuto un tasto, il loop() chiama
  // "voice1env.amplitude(1.0, attackTime)" migliaia di volte.
  //
  // La libreria Audio è "intelligente": capisce che le stai
  // dando lo stesso comando (vai a 1.0) e quindi ignora
  // i comandi duplicati, lasciando che il primo attacco
  // si completi senza interruzioni.
  //
  // Reagisce solo quando riceve un *nuovo* comando
  // (come "amplitude(0.0, releaseTime)" quando rilasci il tasto).

  // NOTA 0 (DO)
  if (artboard.touch(0) > 8000) {
    sine1.frequency(DO * 2);
    voice1env1.amplitude(1.0, attackTime); // Avvia l'Attacco
  } else {
    voice1env1.amplitude(0.0, releaseTime); // Avvia il Rilascio
  }

  // NOTA 1 (DO#)
  if (artboard.touch(1) > 8000) {
    sine2.frequency(DOd * 2);
    voice1env2.amplitude(1.0, attackTime);
  } else {
    voice1env2.amplitude(0.0, releaseTime);
  }

  // NOTA 2 (RE)
  if (artboard.touch(2) > 8000) {
    sine3.frequency(RE * 2);
    voice1env3.amplitude(1.0, attackTime);
  } else {
    voice1env3.amplitude(0.0, releaseTime);
  }

  // NOTA 3 (RE#)
  if (artboard.touch(3) > 8000) {
    sine4.frequency(REd * 2);
    voice1env4.amplitude(1.0, attackTime);
  } else {
    voice1env4.amplitude(0.0, releaseTime);
  }

  // NOTA 4 (MI)
  if (artboard.touch(4) > 8000) {
    sine5.frequency(MI * 2);
    voice1env5.amplitude(1.0, attackTime);
  } else {
    voice1env5.amplitude(0.0, releaseTime);
  }

  // NOTA 5 (FA)
  if (artboard.touch(5) > 8000) {
    sine6.frequency(FA * 2);
    voice1env6.amplitude(1.0, attackTime);
  } else {
    voice1env6.amplitude(0.0, releaseTime);
  }

  // NOTA 6 (FA#)
  if (artboard.touch(6) > 8000) {
    sine7.frequency(FAd * 2);
    voice1env7.amplitude(1.0, attackTime);
  } else {
    voice1env7.amplitude(0.0, releaseTime);
  }

  // NOTA 7 (SOL)
  if (artboard.touch(7) > 8000) {
    sine8.frequency(SOL * 2);
    voice1env8.amplitude(1.0, attackTime);
  } else {
    voice1env8.amplitude(0.0, releaseTime);
  }

  // NOTA 8 (SOL#)
  if (artboard.touch(8) > 8000) {
    sine9.frequency(SOLd * 2);
    voice1env9.amplitude(1.0, attackTime);
  } else {
    voice1env9.amplitude(0.0, releaseTime);
  }

  // NOTA 9 (LA)
  if (artboard.touch(9) > 8000) {
    sine10.frequency(LA * 2);
    voice1env10.amplitude(1.0, attackTime);
  } else {
    voice1env10.amplitude(0.0, releaseTime);
  }

  // NOTA 10 (LA#)
  if (artboard.touch(10) > 8000) {
    sine11.frequency(LAd * 2);
    voice1env11.amplitude(1.0, attackTime);
  } else {
    voice1env11.amplitude(0.0, releaseTime);
  }

  // NOTA 11 (SI)
  if (artboard.touch(11) > 8000) {
    sine12.frequency(SI * 2);
    voice1env12.amplitude(1.0, attackTime);
  } else {
    voice1env12.amplitude(0.0, releaseTime);
  }
  
  
  // === CONTROLLO LED ===
  
  // Controlliamo se l'analizzatore 'peak1' ha un nuovo valore
  if (peak1.available()) {
    // Leggi il livello del volume (un valore da 0.0 a 1.0)
    float level = peak1.read();
    
    // Converti il livello in un valore di luminosità (0-255)
    int brightness = (int)(level * 255.0);
    
    // Applica la luminosità al LED.
    // Il LED ora seguirà perfettamente l'inviluppo audio,
    // accendendosi con l'attacco e spegnendosi col rilascio.
    analogWrite(led, brightness);
  }

  delay(5); // Piccolo delay per stabilità
}