/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 7 - Filtro e LFO
Descrizione:   Questo è lo sketch completo! Combiniamo tutto:
               1. Polysynth a 12 voci
               2. Selettori di Ottava e Forma d'Onda (Bottoni 0, 1)
               3. Inviluppo (Pot 0, 1)
               4. Un Filtro per il "tono" (Pot 2, 3)
               5. Un LFO per modulare il filtro (Pot 4, 5)

Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Attack
- Pot 1:       Release
- Pot 2:       Filtro Cutoff (frequenza base del "tono")
- Pot 3:       Filtro Resonance (enfasi del "tono")
- Pot 4:       LFO Rate (velocità del "wobble")
- Pot 5:       LFO Depth (quantità/forza del "wobble")
- LED (Pin 29): Segue l'inviluppo audio

- Button 0:    Cambia Forma d'Onda (avanti)
- Button 1:    Cambia Ottava (su)

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
// --- ARCHITETTURA FINALE CON FILTRO E LFO ---
AudioSynthWaveformDc     voice1env4;
AudioSynthWaveformDc     voice1env2;
AudioSynthWaveformDc     voice1env3;
AudioSynthWaveformDc     voice1env1;
AudioSynthWaveform       waveform4;
AudioSynthWaveformDc     voice1env5;
AudioSynthWaveform       waveform1;
AudioSynthWaveformDc     voice1env7;
AudioSynthWaveformDc     voice1env9;
AudioSynthWaveform       waveform2;
AudioSynthWaveformDc     voice1env10;
AudioSynthWaveformDc     voice1env8;
AudioSynthWaveform       waveform3;
AudioSynthWaveformDc     voice1env6;
AudioSynthWaveformDc     voice1env12;
AudioSynthWaveform       waveform5;
AudioSynthWaveform       waveform7;
AudioSynthWaveform       waveform9;
AudioSynthWaveformDc     voice1env11;
AudioSynthWaveform       waveform6;
AudioSynthWaveform       waveform8;
AudioSynthWaveform       waveform10;
AudioSynthWaveform       waveform12;
AudioSynthWaveform       waveform11;
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
AudioMixer4              mixer4;         // Mixer finale
AudioSynthWaveformSine   lfo1;           // <-- NOVITÀ: L'LFO
AudioFilterStateVariable filter1;        // <-- NOVITÀ: Filtro Unico
AudioOutputAnalog        dac0;
AudioAnalyzePeak         peak1;
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
// --- NUOVA CATENA DEL SEGNALE ---
AudioConnection          patchCord40(mixer4, 0, filter1, 0); // Audio -> Filtro (Input 0)
AudioConnection          patchCord41(lfo1, 0, filter1, 1);   // LFO -> Filtro (Input 1, Modulazione Freq)
AudioConnection          patchCord42(filter1, 0, dac0, 0);   // Filtro -> DAC (Audio)
AudioConnection          patchCord43(filter1, 0, peak1, 0); // Filtro -> Peak (LED)
// GUItool: end automatically generated code


int led = 29; // Pin del LED

// --- Variabili per i selettori ---

// 1. ARRAY PER LE OTTAVE
int octaves[] = {1, 2, 4, 8, 16}; 
int numOctaves = 5;
int currentOctave = 2; // Indice 2 = "4"

// 2. ARRAY PER LE FORME D'ONDA
int waveforms[] = {
  WAVEFORM_SINE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE
};
int numWaveforms = 4;
int currentWaveform = 0; // Indice 0 = SINE

// 3. Stato dei bottoni
bool btn0_last = false;
bool btn1_last = false;

//Note (Frequenze di base, divise per 4)
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
  AudioMemory(64);
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
  
  // Applica la forma d'onda e l'ottava iniziale a tutte le voci
  int ottavaIniziale = octaves[currentOctave];
  int waveIniziale = waveforms[currentWaveform];
  
  waveform1.begin(1.0, DO * ottavaIniziale, waveIniziale);
  waveform2.begin(1.0, DOd * ottavaIniziale, waveIniziale);
  waveform3.begin(1.0, RE * ottavaIniziale, waveIniziale);
  waveform4.begin(1.0, REd * ottavaIniziale, waveIniziale);
  waveform5.begin(1.0, MI * ottavaIniziale, waveIniziale);
  waveform6.begin(1.0, FA * ottavaIniziale, waveIniziale);
  waveform7.begin(1.0, FAd * ottavaIniziale, waveIniziale);
  waveform8.begin(1.0, SOL * ottavaIniziale, waveIniziale);
  waveform9.begin(1.0, SOLd * ottavaIniziale, waveIniziale);
  waveform10.begin(1.0, LA * ottavaIniziale, waveIniziale);
  waveform11.begin(1.0, LAd * ottavaIniziale, waveIniziale);
  waveform12.begin(1.0, SI * ottavaIniziale, waveIniziale);
  
  // --- IMPOSTAZIONI INIZIALI FILTRO E LFO ---
  lfo1.frequency(1.0);     // LFO inizia a 1 Hz
  lfo1.amplitude(1.0);     // LFO sempre a piena ampiezza (da -1.0 a 1.0)
  filter1.octaveControl(0.0); // Il LFO inizia non avendo effetto
  
  // Imposta i gain dei mixer
  mixer1.gain(0, .25); mixer1.gain(1, .25); mixer1.gain(2, .25); mixer1.gain(3, .25);
  mixer2.gain(0, .25); mixer2.gain(1, .25); mixer2.gain(2, .25); mixer2.gain(3, .25);
  mixer3.gain(0, .25); mixer3.gain(1, .25); mixer3.gain(2, .25); mixer3.gain(3, .25);
  mixer4.gain(0, .33); mixer4.gain(1, .33); mixer4.gain(2, .33);
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);

  // --- CONTROLLO FILTRO ---
  float filterFreqBase = map(artboard.pot(2), 0, 1023, 100, 12000);
  float filterRes = map(artboard.pot(3), 0, 1023, 7, 50) / 10.0; // da 0.7 a 5.0

  // --- CONTROLLO LFO ---
  // Pot 4 controlla la VELOCITÀ del wobble (da 0.1 Hz a 10 Hz)
  float lfoRate = map(artboard.pot(4), 0, 1023, 1, 100) / 10.0;
  // Pot 5 controlla la QUANTITÀ di wobble (da 0 a 5 ottave)
  float lfoDepth = map(artboard.pot(5), 0, 1023, 0, 50) / 10.0;

  // Applica i valori letti
  filter1.frequency(filterFreqBase);      // Frequenza centrale del filtro
  filter1.resonance(filterRes);
  filter1.octaveControl(lfoDepth);    // Quantità di "wobble"
  lfo1.frequency(lfoRate);            // Velocità del "wobble"


  // --- 2. LOGICA BOTTONI ---
  bool btn0_now = (artboard.button(0) == LOW);
  bool btn1_now = (artboard.button(1) == LOW);

  // Bottone 0: Forma d'onda (avanti)
  if (btn0_now && !btn0_last) {
    currentWaveform = (currentWaveform + 1) % numWaveforms; 
    int newWave = waveforms[currentWaveform];
    int ottava = octaves[currentOctave];
    Serial.print("Forma d'onda: "); Serial.println(currentWaveform);
    
    // Applica a mano a tutte le 12 voci
    waveform1.begin(1.0, DO * ottava, newWave);
    waveform2.begin(1.0, DOd * ottava, newWave);
    waveform3.begin(1.0, RE * ottava, newWave);
    waveform4.begin(1.0, REd * ottava, newWave);
    waveform5.begin(1.0, MI * ottava, newWave);
    waveform6.begin(1.0, FA * ottava, newWave);
    waveform7.begin(1.0, FAd * ottava, newWave);
    waveform8.begin(1.0, SOL * ottava, newWave);
    waveform9.begin(1.0, SOLd * ottava, newWave);
    waveform10.begin(1.0, LA * ottava, newWave);
    waveform11.begin(1.0, LAd * ottava, newWave);
    waveform12.begin(1.0, SI * ottava, newWave);
  }

  // Bottone 1: Ottava (su)
  if (btn1_now && !btn1_last) {
    currentOctave = (currentOctave + 1) % numOctaves;
    int newOctave = octaves[currentOctave];
    Serial.print("Ottava: "); Serial.println(newOctave);

    // Applica a mano a tutte le 12 voci
    waveform1.frequency(DO * newOctave);
    waveform2.frequency(DOd * newOctave);
    waveform3.frequency(RE * newOctave);
    waveform4.frequency(REd * newOctave);
    waveform5.frequency(MI * newOctave);
    waveform6.frequency(FA * newOctave);
    waveform7.frequency(FAd * newOctave);
    waveform8.frequency(SOL * newOctave);
    waveform9.frequency(SOLd * newOctave);
    waveform10.frequency(LA * newOctave);
    waveform11.frequency(LAd * newOctave);
    waveform12.frequency(SI * newOctave);
  }

  // Aggiorna lo stato "precedente" dei bottoni
  btn0_last = btn0_now;
  btn1_last = btn1_now;


  // --- 3. LOGICA NOTE (Touch) ---
  if (artboard.touch(0) > 8000) { voice1env1.amplitude(1.0, attackTime); }
  else { voice1env1.amplitude(0.0, releaseTime); }

  if (artboard.touch(1) > 8000) { voice1env2.amplitude(1.0, attackTime); }
  else { voice1env2.amplitude(0.0, releaseTime); }

  if (artboard.touch(2) > 8000) { voice1env3.amplitude(1.0, attackTime); }
  else { voice1env3.amplitude(0.0, releaseTime); }

  if (artboard.touch(3) > 8000) { voice1env4.amplitude(1.0, attackTime); }
  else { voice1env4.amplitude(0.0, releaseTime); }

  if (artboard.touch(4) > 8000) { voice1env5.amplitude(1.0, attackTime); }
  else { voice1env5.amplitude(0.0, releaseTime); }

  if (artboard.touch(5) > 8000) { voice1env6.amplitude(1.0, attackTime); }
  else { voice1env6.amplitude(0.0, releaseTime); }

  if (artboard.touch(6) > 8000) { voice1env7.amplitude(1.0, attackTime); }
  else { voice1env7.amplitude(0.0, releaseTime); }

  if (artboard.touch(7) > 8000) { voice1env8.amplitude(1.0, attackTime); }
  else { voice1env8.amplitude(0.0, releaseTime); }

  if (artboard.touch(8) > 8000) { voice1env9.amplitude(1.0, attackTime); }
  else { voice1env9.amplitude(0.0, releaseTime); }

  if (artboard.touch(9) > 8000) { voice1env10.amplitude(1.0, attackTime); }
  else { voice1env10.amplitude(0.0, releaseTime); }

  if (artboard.touch(10) > 8000) { voice1env11.amplitude(1.0, attackTime); }
  else { voice1env11.amplitude(0.0, releaseTime); }

  if (artboard.touch(11) > 8000) { voice1env12.amplitude(1.0, attackTime); }
  else { voice1env12.amplitude(0.0, releaseTime); }
  
  
  // --- 4. CONTROLLO LED ---
  if (peak1.available()) {
    float level = peak1.read();
    int brightness = (int)(level * 255.0);
    analogWrite(led, brightness);
  }

  delay(5); // Piccolo delay per stabilità
}