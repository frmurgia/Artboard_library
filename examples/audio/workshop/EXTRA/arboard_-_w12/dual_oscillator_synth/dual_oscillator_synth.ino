/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Dual Oscillator Synth - 12 voci polifoniche
Descrizione:   Sintetizzatore polifonico avanzato con:
               - 2 Oscillatori indipendenti (12 voci ciascuno)
               - Controllo indipendente di forma d'onda e ottava
               - Mixer per bilanciare i due oscillatori
               - Filtro con LFO modulabile
               - Inviluppo comune per tutte le voci

Hardware:
- Touch (0-11):  Suonano le 12 note
- Pot 0:         Attack
- Pot 1:         Release
- Pot 2:         Mix Oscillator 1/2 (0% osc1 ← → 100% osc2)
- Pot 3:         Filtro Cutoff
- Pot 4:         LFO Rate (velocità)
- Pot 5:         LFO Depth (quantità di modulazione)
- Button 0:      Forma d'onda Oscillatore 1 (cicla 4 forme)
- Button 1:      Ottava Oscillatore 1 (cicla 5 ottave)
- Button 2:      Forma d'onda Oscillatore 2 (cicla 4 forme)
- Button 3:      Ottava Oscillatore 2 (cicla 5 ottave)
- Button 4:      Forma d'onda LFO (cicla 4 forme)
- LED (Pin 29):  Segue l'inviluppo audio

--------------------------------------
ARCHITETTURA:
12 Oscillatori A → 12 Inviluppi → Mixer A ┐
                                            ├→ Mixer Mix → Filtro (LFO) → DAC
12 Oscillatori B → 12 Inviluppi → Mixer B ┘
                                            ↑
                                          LFO
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
// --- OSCILLATORE 1 (A) - 12 voci ---
AudioSynthWaveform osc1_1, osc1_2, osc1_3, osc1_4;
AudioSynthWaveform osc1_5, osc1_6, osc1_7, osc1_8;
AudioSynthWaveform osc1_9, osc1_10, osc1_11, osc1_12;

// --- OSCILLATORE 2 (B) - 12 voci ---
AudioSynthWaveform osc2_1, osc2_2, osc2_3, osc2_4;
AudioSynthWaveform osc2_5, osc2_6, osc2_7, osc2_8;
AudioSynthWaveform osc2_9, osc2_10, osc2_11, osc2_12;

// --- INVILUPPI (condivisi tra i due oscillatori) ---
AudioSynthWaveformDc env1, env2, env3, env4, env5, env6;
AudioSynthWaveformDc env7, env8, env9, env10, env11, env12;

// --- VCA (moltiplicatori per gli inviluppi) ---
AudioEffectMultiply vca1_1, vca1_2, vca1_3, vca1_4;
AudioEffectMultiply vca1_5, vca1_6, vca1_7, vca1_8;
AudioEffectMultiply vca1_9, vca1_10, vca1_11, vca1_12;

AudioEffectMultiply vca2_1, vca2_2, vca2_3, vca2_4;
AudioEffectMultiply vca2_5, vca2_6, vca2_7, vca2_8;
AudioEffectMultiply vca2_9, vca2_10, vca2_11, vca2_12;

// --- MIXER per Oscillatore 1 ---
AudioMixer4 mixer1_a, mixer1_b, mixer1_c;
AudioMixer4 mixer1_final;

// --- MIXER per Oscillatore 2 ---
AudioMixer4 mixer2_a, mixer2_b, mixer2_c;
AudioMixer4 mixer2_final;

// --- MIXER per bilanciare Osc1 e Osc2 ---
AudioMixer4 mixerAB;

// --- FILTRO e LFO ---
AudioSynthWaveform lfo1;
AudioFilterStateVariable filter1;

// --- OUTPUT ---
AudioAnalyzePeak peak1;
AudioOutputAnalog dac0;

// --- CONNESSIONI OSCILLATORE 1 ---
AudioConnection pc1(osc1_1, 0, vca1_1, 0);
AudioConnection pc2(env1, 0, vca1_1, 1);
AudioConnection pc3(osc1_2, 0, vca1_2, 0);
AudioConnection pc4(env2, 0, vca1_2, 1);
AudioConnection pc5(osc1_3, 0, vca1_3, 0);
AudioConnection pc6(env3, 0, vca1_3, 1);
AudioConnection pc7(osc1_4, 0, vca1_4, 0);
AudioConnection pc8(env4, 0, vca1_4, 1);
AudioConnection pc9(osc1_5, 0, vca1_5, 0);
AudioConnection pc10(env5, 0, vca1_5, 1);
AudioConnection pc11(osc1_6, 0, vca1_6, 0);
AudioConnection pc12(env6, 0, vca1_6, 1);
AudioConnection pc13(osc1_7, 0, vca1_7, 0);
AudioConnection pc14(env7, 0, vca1_7, 1);
AudioConnection pc15(osc1_8, 0, vca1_8, 0);
AudioConnection pc16(env8, 0, vca1_8, 1);
AudioConnection pc17(osc1_9, 0, vca1_9, 0);
AudioConnection pc18(env9, 0, vca1_9, 1);
AudioConnection pc19(osc1_10, 0, vca1_10, 0);
AudioConnection pc20(env10, 0, vca1_10, 1);
AudioConnection pc21(osc1_11, 0, vca1_11, 0);
AudioConnection pc22(env11, 0, vca1_11, 1);
AudioConnection pc23(osc1_12, 0, vca1_12, 0);
AudioConnection pc24(env12, 0, vca1_12, 1);

// --- CONNESSIONI OSCILLATORE 2 ---
AudioConnection pc25(osc2_1, 0, vca2_1, 0);
AudioConnection pc26(env1, 0, vca2_1, 1);
AudioConnection pc27(osc2_2, 0, vca2_2, 0);
AudioConnection pc28(env2, 0, vca2_2, 1);
AudioConnection pc29(osc2_3, 0, vca2_3, 0);
AudioConnection pc30(env3, 0, vca2_3, 1);
AudioConnection pc31(osc2_4, 0, vca2_4, 0);
AudioConnection pc32(env4, 0, vca2_4, 1);
AudioConnection pc33(osc2_5, 0, vca2_5, 0);
AudioConnection pc34(env5, 0, vca2_5, 1);
AudioConnection pc35(osc2_6, 0, vca2_6, 0);
AudioConnection pc36(env6, 0, vca2_6, 1);
AudioConnection pc37(osc2_7, 0, vca2_7, 0);
AudioConnection pc38(env7, 0, vca2_7, 1);
AudioConnection pc39(osc2_8, 0, vca2_8, 0);
AudioConnection pc40(env8, 0, vca2_8, 1);
AudioConnection pc41(osc2_9, 0, vca2_9, 0);
AudioConnection pc42(env9, 0, vca2_9, 1);
AudioConnection pc43(osc2_10, 0, vca2_10, 0);
AudioConnection pc44(env10, 0, vca2_10, 1);
AudioConnection pc45(osc2_11, 0, vca2_11, 0);
AudioConnection pc46(env11, 0, vca2_11, 1);
AudioConnection pc47(osc2_12, 0, vca2_12, 0);
AudioConnection pc48(env12, 0, vca2_12, 1);

// --- MIXER OSCILLATORE 1 ---
AudioConnection pc49(vca1_1, 0, mixer1_a, 0);
AudioConnection pc50(vca1_2, 0, mixer1_a, 1);
AudioConnection pc51(vca1_3, 0, mixer1_a, 2);
AudioConnection pc52(vca1_4, 0, mixer1_a, 3);
AudioConnection pc53(vca1_5, 0, mixer1_b, 0);
AudioConnection pc54(vca1_6, 0, mixer1_b, 1);
AudioConnection pc55(vca1_7, 0, mixer1_b, 2);
AudioConnection pc56(vca1_8, 0, mixer1_b, 3);
AudioConnection pc57(vca1_9, 0, mixer1_c, 0);
AudioConnection pc58(vca1_10, 0, mixer1_c, 1);
AudioConnection pc59(vca1_11, 0, mixer1_c, 2);
AudioConnection pc60(vca1_12, 0, mixer1_c, 3);
AudioConnection pc61(mixer1_a, 0, mixer1_final, 0);
AudioConnection pc62(mixer1_b, 0, mixer1_final, 1);
AudioConnection pc63(mixer1_c, 0, mixer1_final, 2);

// --- MIXER OSCILLATORE 2 ---
AudioConnection pc64(vca2_1, 0, mixer2_a, 0);
AudioConnection pc65(vca2_2, 0, mixer2_a, 1);
AudioConnection pc66(vca2_3, 0, mixer2_a, 2);
AudioConnection pc67(vca2_4, 0, mixer2_a, 3);
AudioConnection pc68(vca2_5, 0, mixer2_b, 0);
AudioConnection pc69(vca2_6, 0, mixer2_b, 1);
AudioConnection pc70(vca2_7, 0, mixer2_b, 2);
AudioConnection pc71(vca2_8, 0, mixer2_b, 3);
AudioConnection pc72(vca2_9, 0, mixer2_c, 0);
AudioConnection pc73(vca2_10, 0, mixer2_c, 1);
AudioConnection pc74(vca2_11, 0, mixer2_c, 2);
AudioConnection pc75(vca2_12, 0, mixer2_c, 3);
AudioConnection pc76(mixer2_a, 0, mixer2_final, 0);
AudioConnection pc77(mixer2_b, 0, mixer2_final, 1);
AudioConnection pc78(mixer2_c, 0, mixer2_final, 2);

// --- MIXER A/B + FILTRO + OUTPUT ---
AudioConnection pc79(mixer1_final, 0, mixerAB, 0);  // Osc1 → MixAB
AudioConnection pc80(mixer2_final, 0, mixerAB, 1);  // Osc2 → MixAB
AudioConnection pc81(mixerAB, 0, filter1, 0);       // MixAB → Filtro
AudioConnection pc82(lfo1, 0, filter1, 1);          // LFO → Filtro (modulazione)
AudioConnection pc83(filter1, 0, dac0, 0);          // Filtro → DAC
AudioConnection pc84(filter1, 0, peak1, 0);         // Filtro → Peak (LED)
// GUItool: end automatically generated code


int led = 29;

// Array ottave e forme d'onda
int octaves[] = { 1, 2, 4, 8, 16 };
int waveforms[] = { WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE };

// Indici correnti
int osc1_octave_idx = 2;  // Ottava 4 (default)
int osc1_wave_idx = 0;    // SINE (default)
int osc2_octave_idx = 2;  // Ottava 4 (default)
int osc2_wave_idx = 1;    // SAWTOOTH (default)
int lfo_wave_idx = 0;     // SINE (default)

// Stati bottoni
bool btn0_last = false;
bool btn1_last = false;
bool btn2_last = false;
bool btn3_last = false;
bool btn4_last = false;

// Note (divise per 4 per margine)
float DO = 261.6 / 4, DOd = 277.2 / 4, RE = 293.7 / 4, REd = 311.1 / 4;
float MI = 329.6 / 4, FA = 349.2 / 4, FAd = 370 / 4, SOL = 392 / 4;
float SOLd = 415.3 / 4, LA = 440 / 4, LAd = 466.2 / 4, SI = 493.9 / 4;


void setup() {
  pinMode(led, OUTPUT);
  AudioMemory(120);  // Memoria aumentata per doppi oscillatori
  Serial.begin(9600);

  // Inizializza tutti gli inviluppi a 0
  env1.amplitude(0.0);
  env2.amplitude(0.0);
  env3.amplitude(0.0);
  env4.amplitude(0.0);
  env5.amplitude(0.0);
  env6.amplitude(0.0);
  env7.amplitude(0.0);
  env8.amplitude(0.0);
  env9.amplitude(0.0);
  env10.amplitude(0.0);
  env11.amplitude(0.0);
  env12.amplitude(0.0);

  // Inizializza Oscillatore 1 (SINE, ottava 4)
  int oct1 = octaves[osc1_octave_idx];
  int wave1 = waveforms[osc1_wave_idx];
  osc1_1.begin(1.0, DO * oct1, wave1);
  osc1_2.begin(1.0, DOd * oct1, wave1);
  osc1_3.begin(1.0, RE * oct1, wave1);
  osc1_4.begin(1.0, REd * oct1, wave1);
  osc1_5.begin(1.0, MI * oct1, wave1);
  osc1_6.begin(1.0, FA * oct1, wave1);
  osc1_7.begin(1.0, FAd * oct1, wave1);
  osc1_8.begin(1.0, SOL * oct1, wave1);
  osc1_9.begin(1.0, SOLd * oct1, wave1);
  osc1_10.begin(1.0, LA * oct1, wave1);
  osc1_11.begin(1.0, LAd * oct1, wave1);
  osc1_12.begin(1.0, SI * oct1, wave1);

  // Inizializza Oscillatore 2 (SAWTOOTH, ottava 4)
  int oct2 = octaves[osc2_octave_idx];
  int wave2 = waveforms[osc2_wave_idx];
  osc2_1.begin(1.0, DO * oct2, wave2);
  osc2_2.begin(1.0, DOd * oct2, wave2);
  osc2_3.begin(1.0, RE * oct2, wave2);
  osc2_4.begin(1.0, REd * oct2, wave2);
  osc2_5.begin(1.0, MI * oct2, wave2);
  osc2_6.begin(1.0, FA * oct2, wave2);
  osc2_7.begin(1.0, FAd * oct2, wave2);
  osc2_8.begin(1.0, SOL * oct2, wave2);
  osc2_9.begin(1.0, SOLd * oct2, wave2);
  osc2_10.begin(1.0, LA * oct2, wave2);
  osc2_11.begin(1.0, LAd * oct2, wave2);
  osc2_12.begin(1.0, SI * oct2, wave2);

  // Gain dei mixer interni
  mixer1_a.gain(0, .25);
  mixer1_a.gain(1, .25);
  mixer1_a.gain(2, .25);
  mixer1_a.gain(3, .25);
  mixer1_b.gain(0, .25);
  mixer1_b.gain(1, .25);
  mixer1_b.gain(2, .25);
  mixer1_b.gain(3, .25);
  mixer1_c.gain(0, .25);
  mixer1_c.gain(1, .25);
  mixer1_c.gain(2, .25);
  mixer1_c.gain(3, .25);
  mixer1_final.gain(0, .33);
  mixer1_final.gain(1, .33);
  mixer1_final.gain(2, .33);

  mixer2_a.gain(0, .25);
  mixer2_a.gain(1, .25);
  mixer2_a.gain(2, .25);
  mixer2_a.gain(3, .25);
  mixer2_b.gain(0, .25);
  mixer2_b.gain(1, .25);
  mixer2_b.gain(2, .25);
  mixer2_b.gain(3, .25);
  mixer2_c.gain(0, .25);
  mixer2_c.gain(1, .25);
  mixer2_c.gain(2, .25);
  mixer2_c.gain(3, .25);
  mixer2_final.gain(0, .33);
  mixer2_final.gain(1, .33);
  mixer2_final.gain(2, .33);

  // Mixer A/B: bilanciamento 50/50 di default
  mixerAB.gain(0, 0.5);  // Osc1
  mixerAB.gain(1, 0.5);  // Osc2

  // Filtro e LFO
  filter1.resonance(2.0);
  filter1.octaveControl(2.0);  // Depth LFO di default
  lfo1.begin(1.0, 1.0, WAVEFORM_SINE);

  Serial.println("Dual Oscillator Synth - 12 voci polifoniche");
  Serial.println("Btn0: Wave Osc1 | Btn1: Oct Osc1");
  Serial.println("Btn2: Wave Osc2 | Btn3: Oct Osc2");
  Serial.println("Btn4: Wave LFO");
  Serial.println("Pot0: Attack | Pot1: Release | Pot2: Mix A/B");
  Serial.println("Pot3: Filter | Pot4: LFO Rate | Pot5: LFO Depth");
}


void loop() {

  // --- LETTURA POTENZIOMETRI ---
  int attackTime = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);

  // Pot 2: Mix tra Osc1 e Osc2 (0% osc1 ← → 100% osc2)
  int mixPot = artboard.pot(2);
  float mix = mixPot / 1023.0;  // 0.0 a 1.0
  mixerAB.gain(0, 1.0 - mix);   // Osc1: 100% quando mix=0
  mixerAB.gain(1, mix);         // Osc2: 100% quando mix=1.0

  // Pot 3: Filtro Cutoff
  float filterFreq = map(artboard.pot(3), 0, 1023, 100, 12000);
  filter1.frequency(filterFreq);

  // Pot 4: LFO Rate
  float lfoRate = map(artboard.pot(4), 0, 1023, 1, 100) / 10.0;  // 0.1-10 Hz
  lfo1.frequency(lfoRate);

  // Pot 5: LFO Depth
  float lfoDepth = map(artboard.pot(5), 0, 1023, 0, 50) / 10.0;  // 0-5 ottave
  filter1.octaveControl(lfoDepth);


  // --- BOTTONI ---
  bool btn0_now = (artboard.button(0) == LOW);
  bool btn1_now = (artboard.button(1) == LOW);
  bool btn2_now = (artboard.button(2) == LOW);
  bool btn3_now = (artboard.button(3) == LOW);
  bool btn4_now = (artboard.button(4) == LOW);

  // Bottone 0: Forma d'onda Oscillatore 1
  if (btn0_now && !btn0_last) {
    osc1_wave_idx = (osc1_wave_idx + 1) % 4;
    int wave = waveforms[osc1_wave_idx];
    int oct = octaves[osc1_octave_idx];

    osc1_1.begin(1.0, DO * oct, wave);
    osc1_2.begin(1.0, DOd * oct, wave);
    osc1_3.begin(1.0, RE * oct, wave);
    osc1_4.begin(1.0, REd * oct, wave);
    osc1_5.begin(1.0, MI * oct, wave);
    osc1_6.begin(1.0, FA * oct, wave);
    osc1_7.begin(1.0, FAd * oct, wave);
    osc1_8.begin(1.0, SOL * oct, wave);
    osc1_9.begin(1.0, SOLd * oct, wave);
    osc1_10.begin(1.0, LA * oct, wave);
    osc1_11.begin(1.0, LAd * oct, wave);
    osc1_12.begin(1.0, SI * oct, wave);

    Serial.print("Osc1 Wave: ");
    Serial.println(wave == WAVEFORM_SINE ? "SINE" : wave == WAVEFORM_SAWTOOTH ? "SAW"
                                                  : wave == WAVEFORM_SQUARE   ? "SQR"
                                                                              : "TRI");
  }

  // Bottone 1: Ottava Oscillatore 1
  if (btn1_now && !btn1_last) {
    osc1_octave_idx = (osc1_octave_idx + 1) % 5;
    int oct = octaves[osc1_octave_idx];

    osc1_1.frequency(DO * oct);
    osc1_2.frequency(DOd * oct);
    osc1_3.frequency(RE * oct);
    osc1_4.frequency(REd * oct);
    osc1_5.frequency(MI * oct);
    osc1_6.frequency(FA * oct);
    osc1_7.frequency(FAd * oct);
    osc1_8.frequency(SOL * oct);
    osc1_9.frequency(SOLd * oct);
    osc1_10.frequency(LA * oct);
    osc1_11.frequency(LAd * oct);
    osc1_12.frequency(SI * oct);

    Serial.print("Osc1 Octave: ");
    Serial.println(oct);
  }

  // Bottone 2: Forma d'onda Oscillatore 2
  if (btn2_now && !btn2_last) {
    osc2_wave_idx = (osc2_wave_idx + 1) % 4;
    int wave = waveforms[osc2_wave_idx];
    int oct = octaves[osc2_octave_idx];

    osc2_1.begin(1.0, DO * oct, wave);
    osc2_2.begin(1.0, DOd * oct, wave);
    osc2_3.begin(1.0, RE * oct, wave);
    osc2_4.begin(1.0, REd * oct, wave);
    osc2_5.begin(1.0, MI * oct, wave);
    osc2_6.begin(1.0, FA * oct, wave);
    osc2_7.begin(1.0, FAd * oct, wave);
    osc2_8.begin(1.0, SOL * oct, wave);
    osc2_9.begin(1.0, SOLd * oct, wave);
    osc2_10.begin(1.0, LA * oct, wave);
    osc2_11.begin(1.0, LAd * oct, wave);
    osc2_12.begin(1.0, SI * oct, wave);

 

  // Bottone 3: Ottava Oscillatore 2
  if (btn3_now && !btn3_last) {
    osc2_octave_idx = (osc2_octave_idx + 1) % 5;
    int oct = octaves[osc2_octave_idx];

    osc2_1.frequency(DO * oct);
    osc2_2.frequency(DOd * oct);
    osc2_3.frequency(RE * oct);
    osc2_4.frequency(REd * oct);
    osc2_5.frequency(MI * oct);
    osc2_6.frequency(FA * oct);
    osc2_7.frequency(FAd * oct);
    osc2_8.frequency(SOL * oct);
    osc2_9.frequency(SOLd * oct);
    osc2_10.frequency(LA * oct);
    osc2_11.frequency(LAd * oct);
    osc2_12.frequency(SI * oct);

    Serial.print("Osc2 Octave: ");
    Serial.println(oct);
  }

  // Bottone 4: Forma d'onda LFO
  if (btn4_now && !btn4_last) {
    lfo_wave_idx = (lfo_wave_idx + 1) % 4;
    int wave = waveforms[lfo_wave_idx];
    lfo1.begin(1.0, lfoRate, wave);

  
  // Aggiorna stati bottoni
  btn0_last = btn0_now;
  btn1_last = btn1_now;
  btn2_last = btn2_now;
  btn3_last = btn3_now;
  btn4_last = btn4_now;


  // --- TOUCH PAD (12 NOTE) ---
  if (artboard.touch(0) > 6000) {
    env1.amplitude(1.0, attackTime);
  } else {
    env1.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(1) > 6000) {
    env2.amplitude(1.0, attackTime);
  } else {
    env2.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(2) > 6000) {
    env3.amplitude(1.0, attackTime);
  } else {
    env3.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(3) > 6000) {
    env4.amplitude(1.0, attackTime);
  } else {
    env4.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(4) > 6000) {
    env5.amplitude(1.0, attackTime);
  } else {
    env5.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(5) > 6000) {
    env6.amplitude(1.0, attackTime);
  } else {
    env6.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(6) > 6000) {
    env7.amplitude(1.0, attackTime);
  } else {
    env7.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(7) > 6000) {
    env8.amplitude(1.0, attackTime);
  } else {
    env8.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(8) > 6000) {
    env9.amplitude(1.0, attackTime);
  } else {
    env9.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(9) > 6000) {
    env10.amplitude(1.0, attackTime);
  } else {
    env10.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(10) > 6000) {
    env11.amplitude(1.0, attackTime);
  } else {
    env11.amplitude(0.0, releaseTime);
  }

  if (artboard.touch(11) > 6000) {
    env12.amplitude(1.0, attackTime);
  } else {
    env12.amplitude(0.0, releaseTime);
  }


  delay(5);
}
