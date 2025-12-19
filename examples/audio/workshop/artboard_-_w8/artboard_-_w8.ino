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
AudioSynthWaveformDc     voice1env4;     //xy=346.2540092468262,364.0000581741333
AudioSynthWaveform       waveform3;      //xy=349.25401306152344,259.00007152557373
AudioSynthWaveformDc     voice1env3;     //xy=349.2539863586426,295.00004863739014
AudioSynthWaveform       waveform4;      //xy=353.2540092468262,328.00007247924805
AudioSynthWaveform       waveform2;      //xy=362.25399017333984,186.00004863739014
AudioSynthWaveformDc     voice1env2;     //xy=368.25399017333984,221.00004863739014
AudioSynthWaveformDc     voice1env1;     //xy=370.25401306152344,144.00004959106445
AudioSynthWaveform       waveform6;      //xy=371.25406646728516,493.000039100647
AudioSynthWaveform       waveform1;      //xy=373.25401306152344,115.0000057220459
AudioSynthWaveformDc     voice1env5;     //xy=372.25401306152344,459.00004291534424
AudioSynthWaveformDc     voice1env6;     //xy=373.2540092468262,527.0000429153442
AudioSynthWaveform       waveform5;      //xy=374.25401306152344,429.00004291534424
AudioSynthWaveform       waveform7;      //xy=382.2540969848633,562.0001344680786
AudioSynthWaveformDc     voice1env8;     //xy=387.2540092468262,670.0000429153442
AudioSynthWaveform       waveform8;      //xy=389.25406646728516,635.000075340271
AudioSynthWaveformDc     voice1env7;     //xy=393.2540969848633,597.0001363754272
AudioSynthWaveform       waveform9;      //xy=433.25407791137695,754.0000848770142
AudioSynthWaveformDc     voice1env9;     //xy=435.2539978027344,790.000054359436
AudioSynthWaveform       waveform10;     //xy=437.25401306152344,828.0001440048218
AudioSynthWaveformDc     voice1env10;    //xy=446.25404357910156,858.0001788139343
AudioSynthWaveformDc     voice1env11;    //xy=446.25407791137695,921.0001792907715
AudioSynthWaveform       waveform11;     //xy=447.25407791137695,886.0001783370972
AudioSynthWaveform       waveform12;     //xy=447.2539825439453,952.0000486373901
AudioSynthWaveformDc     voice1env12;    //xy=448.25397872924805,990.0000486373901
AudioEffectMultiply      multiply5;      //xy=601.2540092468262,433.00004291534424
AudioEffectMultiply      multiply7;      //xy=603.2540435791016,557.0000715255737
AudioEffectMultiply      multiply6;      //xy=606.2540092468262,478.00004291534424
AudioEffectMultiply      multiply8;      //xy=609.2540092468262,594.0000410079956
AudioEffectMultiply      multiply4;      //xy=619.2539863586426,310.00004863739014
AudioEffectMultiply      multiply1;      //xy=621.2539863586426,149.00004816055298
AudioEffectMultiply      multiply3;      //xy=625.2539863586426,252.00004863739014
AudioEffectMultiply      multiply2;      //xy=626.2539901733398,189.00004863739014
AudioEffectMultiply      multiply10;     //xy=703.2540168762207,834.0001440048218
AudioEffectMultiply      multiply12;     //xy=703.2540168762207,952.0001440048218
AudioEffectMultiply      multiply11;     //xy=706.2540245056152,889.0001440048218
AudioEffectMultiply      multiply9;      //xy=718.254020690918,779.0001440048218
AudioMixer4              mixer2;         //xy=792.2540016174316,519.000018119812
AudioMixer4              mixer1;         //xy=871.253978729248,246.0000238418579
AudioMixer4              mixer3;         //xy=911.2540130615234,845.0001192092896
AudioMixer4              mixer4;         //xy=1087.2542114257812,541.0001573562622
AudioSynthWaveform       lfo1;           //xy=1157.2539825439453,726.0000295639038
AudioFilterStateVariable filter1;        //xy=1350.253978729248,651.0000257492065
AudioOutputAnalog        dac0;           //xy=1490.253978729248,761.0000257492065
AudioAnalyzePeak         peak1;          //xy=1503.253978729248,723.0000257492065
AudioConnection          patchCord1(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord2(waveform3, 0, multiply3, 0);
AudioConnection          patchCord3(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord4(waveform4, 0, multiply4, 0);
AudioConnection          patchCord5(waveform2, 0, multiply2, 0);
AudioConnection          patchCord6(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord7(voice1env1, 0, multiply1, 1);
AudioConnection          patchCord8(waveform6, 0, multiply6, 0);
AudioConnection          patchCord9(waveform1, 0, multiply1, 0);
AudioConnection          patchCord10(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord11(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord12(waveform5, 0, multiply5, 0);
AudioConnection          patchCord13(waveform7, 0, multiply7, 0);
AudioConnection          patchCord14(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord15(waveform8, 0, multiply8, 0);
AudioConnection          patchCord16(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord17(waveform9, 0, multiply9, 0);
AudioConnection          patchCord18(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord19(waveform10, 0, multiply10, 0);
AudioConnection          patchCord20(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord21(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord22(waveform11, 0, multiply11, 0);
AudioConnection          patchCord23(waveform12, 0, multiply12, 0);
AudioConnection          patchCord24(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord25(multiply5, 0, mixer2, 0);
AudioConnection          patchCord26(multiply7, 0, mixer2, 2);
AudioConnection          patchCord27(multiply6, 0, mixer2, 1);
AudioConnection          patchCord28(multiply8, 0, mixer2, 3);
AudioConnection          patchCord29(multiply4, 0, mixer1, 3);
AudioConnection          patchCord30(multiply1, 0, mixer1, 0);
AudioConnection          patchCord31(multiply3, 0, mixer1, 2);
AudioConnection          patchCord32(multiply2, 0, mixer1, 1);
AudioConnection          patchCord33(multiply10, 0, mixer3, 1);
AudioConnection          patchCord34(multiply12, 0, mixer3, 3);
AudioConnection          patchCord35(multiply11, 0, mixer3, 2);
AudioConnection          patchCord36(multiply9, 0, mixer3, 0);
AudioConnection          patchCord37(mixer2, 0, mixer4, 1);
AudioConnection          patchCord38(mixer1, 0, mixer4, 0);
AudioConnection          patchCord39(mixer3, 0, mixer4, 2);
AudioConnection          patchCord40(mixer4, 0, filter1, 0);
AudioConnection          patchCord41(lfo1, 0, filter1, 1);
AudioConnection          patchCord42(filter1, 0, dac0, 0);
AudioConnection          patchCord43(filter1, 0, peak1, 0);
// GUItool: end automatically generated code

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
  
 
  delay(5);
}
