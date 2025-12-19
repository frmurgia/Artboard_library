/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio 7 - Polifonia + Ottave + Forme d'Onda + Filtro
Descrizione:   Partiamo dallo Sketch 6 e aggiungiamo un FILTRO
               per controllare il "tono" del suono.
               Il filtro viene applicato dopo che tutte le 12 voci
               sono state mixate insieme.

Hardware:
- Touch (0-11): Suonano le 12 note
- Pot 0:       Controlla l'Attack
- Pot 1:       Controlla il Release
- Pot 2:       Controlla l'Ottava (5 livelli)
- Pot 3:       Controlla la Forma d'Onda (4 tipi)
- Pot 4:       Controlla il Filtro Cutoff (frequenza/tono)
- LED (Pin 29): Segue l'inviluppo audio

--------------------------------------
LEZIONE: COS'È UN FILTRO?
--------------------------------------
Un FILTRO è come un equalizzatore che lascia passare alcune
frequenze e ne blocca altre. Il filtro che usiamo si chiama
"Low-Pass Filter" (passa-basso) perché lascia passare le
frequenze BASSE e attenua quelle ALTE.

CUTOFF FREQUENCY (Frequenza di Taglio):
- È il punto dove il filtro inizia a tagliare le frequenze alte
- Pot 4 tutto a sinistra (100 Hz) = suono molto scuro, ovattato
- Pot 4 tutto a destra (12000 Hz) = suono brillante, completo

RESONANCE (Risonanza):
- Enfatizza le frequenze vicino al cutoff
- Nel nostro sketch è FISSA a 2.0 (valore medio)
- Valori più alti creano un suono più "nasale" o "resonante"

ARCHITETTURA DEL SEGNALE:
12 Oscillatori → 12 Inviluppi (VCA) → 3 Mixer → 1 Mixer Finale
→ FILTRO → DAC (uscita audio)

Il filtro è l'ULTIMO stadio prima dell'uscita, così modifica
il suono di tutte le voci contemporaneamente.
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
AudioSynthWaveform       waveform4;      //xy=406,479
AudioSynthWaveformDc     voice1env4;     //xy=409,511
AudioSynthWaveformDc     voice1env3;     //xy=411,438
AudioSynthWaveformDc     voice1env2;     //xy=412,375
AudioSynthWaveform       waveform2;      //xy=414,344
AudioSynthWaveformDc     voice1env12;    //xy=411,1147
AudioSynthWaveform       waveform3;      //xy=414,410
AudioSynthWaveformDc     voice1env1;     //xy=416,306
AudioSynthWaveformDc     voice1env8;     //xy=415,843
AudioSynthWaveform       waveform12;     //xy=414,1112
AudioSynthWaveform       waveform1;      //xy=418,272
AudioSynthWaveformDc     voice1env9;     //xy=416,935
AudioSynthWaveformDc     voice1env10;    //xy=416,1005
AudioSynthWaveform       waveform10;     //xy=417,970
AudioSynthWaveformDc     voice1env11;    //xy=418,1075
AudioSynthWaveform       waveform9;      //xy=420,901
AudioSynthWaveform       waveform11;     //xy=420,1041
AudioSynthWaveformDc     voice1env7;     //xy=422,764
AudioSynthWaveform       waveform8;      //xy=422,808
AudioSynthWaveform       waveform7;      //xy=423,729
AudioSynthWaveformDc     voice1env6;     //xy=426,688
AudioSynthWaveformDc     voice1env5;     //xy=428,619
AudioSynthWaveform       waveform6;      //xy=428,655
AudioSynthWaveform       waveform5;      //xy=431,585
AudioEffectMultiply      multiply3;      //xy=603,412
AudioEffectMultiply      multiply2;      //xy=604,381
AudioEffectMultiply      multiply4;      //xy=607,442
AudioEffectMultiply      multiply1;      //xy=609,348
AudioEffectMultiply      multiply8;      //xy=619,813
AudioEffectMultiply      multiply6;      //xy=622,657
AudioEffectMultiply      multiply7;      //xy=624,759
AudioEffectMultiply      multiply5;      //xy=626,593
AudioEffectMultiply      multiply12;     //xy=648,1103
AudioEffectMultiply      multiply10;     //xy=649,1043
AudioEffectMultiply      multiply11;     //xy=650,1075
AudioEffectMultiply      multiply9;      //xy=651,1013
AudioMixer4              mixer3;         //xy=813,1035
AudioMixer4              mixer1;         //xy=821,371
AudioMixer4              mixer2;         //xy=834,660
AudioMixer4              mixer4;         //xy=1063,664
AudioFilterStateVariable filter1;        //xy=1200,664
AudioAnalyzePeak         peak1;          //xy=1341,691
AudioOutputAnalog        dac0;           //xy=1342,631
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
AudioConnection          patchCord40(mixer4, 0, filter1, 0);
AudioConnection          patchCord41(filter1, 0, dac0, 0);
AudioConnection          patchCord42(filter1, 0, peak1, 0);
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
  AudioMemory(64);  // Aumentato per il filtro
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
  // Resonance fissa a 2.0 (valore medio)
  filter1.resonance(2.0);
  
  Serial.println("Sketch 7: Ottave + Forme d'Onda + Filtro");
  Serial.println("Pot 2: Controlla l'ottava (5 livelli)");
  Serial.println("Pot 3: Controlla la forma d'onda (4 tipi)");
  Serial.println("Pot 4: Controlla il filtro cutoff (tono)");
  Serial.println("Resonance: Fissa a 2.0");
}


// ----- LOOP -----

void loop() {

  // --- 1. LETTURA POTENZIOMETRI ---
  int attackTime  = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);
  
  // Leggi i potenziometri per ottava, forma d'onda e filtro
  int potOctave = artboard.pot(2);
  int potWaveform = artboard.pot(3);
  int potFilter = artboard.pot(4);


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
  
  
  // --- 3. DETERMINA LA FORMA D'ONDA IN BASE ALLA POSIZIONE DEL POT 3 ---
  
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

  
  // Mappa il pot 4 sulla frequenza di taglio (da 100 Hz a 12000 Hz)
  float filterFreq = map(potFilter, 0, 1023, 100, 12000);
  
  // Applica la frequenza al filtro
  filter1.frequency(filterFreq);
  // La resonance rimane fissa a 2.0 (impostata nel setup)
  
  
  // --- 5. APPLICA LA NUOVA OTTAVA (solo se è cambiata) ---
  
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
  
  
  // --- 6. APPLICA LA NUOVA FORMA D'ONDA (solo se è cambiata) ---
  
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


  // --- 7. LOGICA NOTE (Touch) ---

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
