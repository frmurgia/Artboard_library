/*
 * Artboard Sequencer
 *
 * Un sequencer a 8 step con sintetizzatore polifonico a 12 note
 * Basato sull'architettura provata del workshop audio
 *
 * HARDWARE:
 * - Touch (0-11): Suonano le 12 note (scala cromatica)
 * - Pot 0:  Attack envelope
 * - Pot 1:  Release envelope
 * - Pot 2:  Mix tra oscillatore 1 e 2
 * - Pot 3:  Forma d'onda oscillatore 1 (Sine, Saw, Square, Triangle)
 * - Pot 4:  Forma d'onda oscillatore 2 (Sine, Saw, Square, Triangle)
 * - Pot 5:  Filtro Cutoff
 * - Pot 6:  LFO Rate (velocità modulazione)
 * - Pot 7:  LFO Depth (intensità modulazione)
 *
 * - Button (0-7): Seleziona step per registrazione
 * - On/Off Switch (pin 28): Play/Stop sequencer
 * - LED (0-7): Indicatore step corrente durante playback
 *
 * FUNZIONAMENTO:
 * 1. Tenere premuto un pulsante (0-7) per selezionare uno step
 * 2. Mentre tieni premuto il pulsante, suona le note con i touch
 * 3. Le note suonate vengono registrate in quello step
 * 4. Attiva lo switch (pin 28) per avviare il playback
 * 5. Il sequencer suonerà le note registrate in sequenza
 *
 * by Daniele Murgia © 2025 MIT License
 */

#include <Artboard.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

Artboard artboard;

// --- AUDIO SETUP (Architettura provata) ---

// Oscillatore 1 (12 voci)
AudioSynthWaveform waveform1_1, waveform1_2, waveform1_3, waveform1_4;
AudioSynthWaveform waveform1_5, waveform1_6, waveform1_7, waveform1_8;
AudioSynthWaveform waveform1_9, waveform1_10, waveform1_11, waveform1_12;

// Oscillatore 2 (12 voci)
AudioSynthWaveform waveform2_1, waveform2_2, waveform2_3, waveform2_4;
AudioSynthWaveform waveform2_5, waveform2_6, waveform2_7, waveform2_8;
AudioSynthWaveform waveform2_9, waveform2_10, waveform2_11, waveform2_12;

// Envelope (usando DC waveforms)
AudioSynthWaveformDc env1, env2, env3, env4, env5, env6;
AudioSynthWaveformDc env7, env8, env9, env10, env11, env12;

// Multiply per applicare envelope all'osc1
AudioEffectMultiply mult1_1, mult1_2, mult1_3, mult1_4;
AudioEffectMultiply mult1_5, mult1_6, mult1_7, mult1_8;
AudioEffectMultiply mult1_9, mult1_10, mult1_11, mult1_12;

// Multiply per applicare envelope all'osc2
AudioEffectMultiply mult2_1, mult2_2, mult2_3, mult2_4;
AudioEffectMultiply mult2_5, mult2_6, mult2_7, mult2_8;
AudioEffectMultiply mult2_9, mult2_10, mult2_11, mult2_12;

// Mixer per note (combina osc1 e osc2)
AudioMixer4 noteMix1, noteMix2, noteMix3, noteMix4;
AudioMixer4 noteMix5, noteMix6, noteMix7, noteMix8;
AudioMixer4 noteMix9, noteMix10, noteMix11, noteMix12;

// Mixer principali (raggruppano le note)
AudioMixer4 mainMixer1, mainMixer2, mainMixer3;

// Mixer finale
AudioMixer4 finalMixer;

// LFO e Filtro
AudioSynthWaveformSine lfo;
AudioFilterStateVariable filter;

// Output
AudioOutputAnalog dac0;
AudioAnalyzePeak peak1;

// --- CONNESSIONI AUDIO ---

// Note 1: waveform -> envelope -> mixer
AudioConnection pc1(waveform1_1, 0, mult1_1, 0);
AudioConnection pc2(env1, 0, mult1_1, 1);
AudioConnection pc3(waveform2_1, 0, mult2_1, 0);
AudioConnection pc4(env1, 0, mult2_1, 1);
AudioConnection pc5(mult1_1, 0, noteMix1, 0);
AudioConnection pc6(mult2_1, 0, noteMix1, 1);

// Note 2
AudioConnection pc7(waveform1_2, 0, mult1_2, 0);
AudioConnection pc8(env2, 0, mult1_2, 1);
AudioConnection pc9(waveform2_2, 0, mult2_2, 0);
AudioConnection pc10(env2, 0, mult2_2, 1);
AudioConnection pc11(mult1_2, 0, noteMix2, 0);
AudioConnection pc12(mult2_2, 0, noteMix2, 1);

// Note 3
AudioConnection pc13(waveform1_3, 0, mult1_3, 0);
AudioConnection pc14(env3, 0, mult1_3, 1);
AudioConnection pc15(waveform2_3, 0, mult2_3, 0);
AudioConnection pc16(env3, 0, mult2_3, 1);
AudioConnection pc17(mult1_3, 0, noteMix3, 0);
AudioConnection pc18(mult2_3, 0, noteMix3, 1);

// Note 4
AudioConnection pc19(waveform1_4, 0, mult1_4, 0);
AudioConnection pc20(env4, 0, mult1_4, 1);
AudioConnection pc21(waveform2_4, 0, mult2_4, 0);
AudioConnection pc22(env4, 0, mult2_4, 1);
AudioConnection pc23(mult1_4, 0, noteMix4, 0);
AudioConnection pc24(mult2_4, 0, noteMix4, 1);

// Note 5
AudioConnection pc25(waveform1_5, 0, mult1_5, 0);
AudioConnection pc26(env5, 0, mult1_5, 1);
AudioConnection pc27(waveform2_5, 0, mult2_5, 0);
AudioConnection pc28(env5, 0, mult2_5, 1);
AudioConnection pc29(mult1_5, 0, noteMix5, 0);
AudioConnection pc30(mult2_5, 0, noteMix5, 1);

// Note 6
AudioConnection pc31(waveform1_6, 0, mult1_6, 0);
AudioConnection pc32(env6, 0, mult1_6, 1);
AudioConnection pc33(waveform2_6, 0, mult2_6, 0);
AudioConnection pc34(env6, 0, mult2_6, 1);
AudioConnection pc35(mult1_6, 0, noteMix6, 0);
AudioConnection pc36(mult2_6, 0, noteMix6, 1);

// Note 7
AudioConnection pc37(waveform1_7, 0, mult1_7, 0);
AudioConnection pc38(env7, 0, mult1_7, 1);
AudioConnection pc39(waveform2_7, 0, mult2_7, 0);
AudioConnection pc40(env7, 0, mult2_7, 1);
AudioConnection pc41(mult1_7, 0, noteMix7, 0);
AudioConnection pc42(mult2_7, 0, noteMix7, 1);

// Note 8
AudioConnection pc43(waveform1_8, 0, mult1_8, 0);
AudioConnection pc44(env8, 0, mult1_8, 1);
AudioConnection pc45(waveform2_8, 0, mult2_8, 0);
AudioConnection pc46(env8, 0, mult2_8, 1);
AudioConnection pc47(mult1_8, 0, noteMix8, 0);
AudioConnection pc48(mult2_8, 0, noteMix8, 1);

// Note 9
AudioConnection pc49(waveform1_9, 0, mult1_9, 0);
AudioConnection pc50(env9, 0, mult1_9, 1);
AudioConnection pc51(waveform2_9, 0, mult2_9, 0);
AudioConnection pc52(env9, 0, mult2_9, 1);
AudioConnection pc53(mult1_9, 0, noteMix9, 0);
AudioConnection pc54(mult2_9, 0, noteMix9, 1);

// Note 10
AudioConnection pc55(waveform1_10, 0, mult1_10, 0);
AudioConnection pc56(env10, 0, mult1_10, 1);
AudioConnection pc57(waveform2_10, 0, mult2_10, 0);
AudioConnection pc58(env10, 0, mult2_10, 1);
AudioConnection pc59(mult1_10, 0, noteMix10, 0);
AudioConnection pc60(mult2_10, 0, noteMix10, 1);

// Note 11
AudioConnection pc61(waveform1_11, 0, mult1_11, 0);
AudioConnection pc62(env11, 0, mult1_11, 1);
AudioConnection pc63(waveform2_11, 0, mult2_11, 0);
AudioConnection pc64(env11, 0, mult2_11, 1);
AudioConnection pc65(mult1_11, 0, noteMix11, 0);
AudioConnection pc66(mult2_11, 0, noteMix11, 1);

// Note 12
AudioConnection pc67(waveform1_12, 0, mult1_12, 0);
AudioConnection pc68(env12, 0, mult1_12, 1);
AudioConnection pc69(waveform2_12, 0, mult2_12, 0);
AudioConnection pc70(env12, 0, mult2_12, 1);
AudioConnection pc71(mult1_12, 0, noteMix12, 0);
AudioConnection pc72(mult2_12, 0, noteMix12, 1);

// Note mixer -> main mixers
AudioConnection pc73(noteMix1, 0, mainMixer1, 0);
AudioConnection pc74(noteMix2, 0, mainMixer1, 1);
AudioConnection pc75(noteMix3, 0, mainMixer1, 2);
AudioConnection pc76(noteMix4, 0, mainMixer1, 3);

AudioConnection pc77(noteMix5, 0, mainMixer2, 0);
AudioConnection pc78(noteMix6, 0, mainMixer2, 1);
AudioConnection pc79(noteMix7, 0, mainMixer2, 2);
AudioConnection pc80(noteMix8, 0, mainMixer2, 3);

AudioConnection pc81(noteMix9, 0, mainMixer3, 0);
AudioConnection pc82(noteMix10, 0, mainMixer3, 1);
AudioConnection pc83(noteMix11, 0, mainMixer3, 2);
AudioConnection pc84(noteMix12, 0, mainMixer3, 3);

// Main mixers -> final mixer
AudioConnection pc85(mainMixer1, 0, finalMixer, 0);
AudioConnection pc86(mainMixer2, 0, finalMixer, 1);
AudioConnection pc87(mainMixer3, 0, finalMixer, 2);

// Final mixer -> filter
AudioConnection pc88(finalMixer, 0, filter, 0);
AudioConnection pc89(lfo, 0, filter, 1);

// Filter -> output
AudioConnection pc90(filter, 0, dac0, 0);
AudioConnection pc91(filter, 0, peak1, 0);

// --- NOTE FREQUENCY ---
float notes[12] = {
  261.6 / 4,  // C (DO)
  277.2 / 4,  // C# (DO#)
  293.7 / 4,  // D (RE)
  311.1 / 4,  // D# (RE#)
  329.6 / 4,  // E (MI)
  349.2 / 4,  // F (FA)
  370.0 / 4,  // F# (FA#)
  392.0 / 4,  // G (SOL)
  415.3 / 4,  // G# (SOL#)
  440.0 / 4,  // A (LA)
  466.2 / 4,  // A# (LA#)
  493.9 / 4   // B (SI)
};

// --- SEQUENCER DATA ---
#define NUM_STEPS 8
#define NUM_NOTES 12

struct Step {
  bool notes[NUM_NOTES];
  bool hasData;
};

Step sequence[NUM_STEPS];

// Variabili sequencer
int currentStep = 0;
unsigned long lastStepTime = 0;
int bpm = 120;
bool isPlaying = false;
int recordingStep = -1;

// Stato precedente controlli
bool prevTouchState[NUM_NOTES] = {false};
bool prevButtonState[8] = {false};
bool prevPlayState = false;

// Forme d'onda
int waveforms[4] = {WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE};
int currentWaveform1 = 1; // Sawtooth
int currentWaveform2 = 2; // Square

void setup() {
  Serial.begin(115200);
  AudioMemory(120);

  pinMode(28, INPUT_PULLUP);

  // Setup oscillatori
  setupOscillators();

  // Setup envelope (tutti a 0)
  env1.amplitude(0.0); env2.amplitude(0.0); env3.amplitude(0.0); env4.amplitude(0.0);
  env5.amplitude(0.0); env6.amplitude(0.0); env7.amplitude(0.0); env8.amplitude(0.0);
  env9.amplitude(0.0); env10.amplitude(0.0); env11.amplitude(0.0); env12.amplitude(0.0);

  // Setup mixer gain
  // Note mixers (mix osc1 e osc2)
  noteMix1.gain(0, 0.5); noteMix1.gain(1, 0.5);
  noteMix2.gain(0, 0.5); noteMix2.gain(1, 0.5);
  noteMix3.gain(0, 0.5); noteMix3.gain(1, 0.5);
  noteMix4.gain(0, 0.5); noteMix4.gain(1, 0.5);
  noteMix5.gain(0, 0.5); noteMix5.gain(1, 0.5);
  noteMix6.gain(0, 0.5); noteMix6.gain(1, 0.5);
  noteMix7.gain(0, 0.5); noteMix7.gain(1, 0.5);
  noteMix8.gain(0, 0.5); noteMix8.gain(1, 0.5);
  noteMix9.gain(0, 0.5); noteMix9.gain(1, 0.5);
  noteMix10.gain(0, 0.5); noteMix10.gain(1, 0.5);
  noteMix11.gain(0, 0.5); noteMix11.gain(1, 0.5);
  noteMix12.gain(0, 0.5); noteMix12.gain(1, 0.5);

  // Main mixers
  mainMixer1.gain(0, 0.25); mainMixer1.gain(1, 0.25); mainMixer1.gain(2, 0.25); mainMixer1.gain(3, 0.25);
  mainMixer2.gain(0, 0.25); mainMixer2.gain(1, 0.25); mainMixer2.gain(2, 0.25); mainMixer2.gain(3, 0.25);
  mainMixer3.gain(0, 0.25); mainMixer3.gain(1, 0.25); mainMixer3.gain(2, 0.25); mainMixer3.gain(3, 0.25);

  // Final mixer
  finalMixer.gain(0, 0.33); finalMixer.gain(1, 0.33); finalMixer.gain(2, 0.33);

  // LFO
  lfo.frequency(1.0);
  lfo.amplitude(1.0);

  // Filtro
  filter.frequency(2000);
  filter.resonance(1.4);
  filter.octaveControl(0.0);

  // Inizializza sequenza
  for (int i = 0; i < NUM_STEPS; i++) {
    sequence[i].hasData = false;
    for (int n = 0; n < NUM_NOTES; n++) {
      sequence[i].notes[n] = false;
    }
  }

  artboard.clearAllLEDs();

  Serial.println("=== ARTBOARD SEQUENCER ===");
  Serial.println("Ready!");
}

void loop() {
  // --- LEGGI CONTROLLI ---
  int attackTime = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);

  // Mix oscillatori
  float osc1Mix = map(artboard.pot(2), 0, 1023, 0, 100) / 100.0;
  float osc2Mix = 1.0 - osc1Mix;

  // Update note mixers
  noteMix1.gain(0, osc1Mix); noteMix1.gain(1, osc2Mix);
  noteMix2.gain(0, osc1Mix); noteMix2.gain(1, osc2Mix);
  noteMix3.gain(0, osc1Mix); noteMix3.gain(1, osc2Mix);
  noteMix4.gain(0, osc1Mix); noteMix4.gain(1, osc2Mix);
  noteMix5.gain(0, osc1Mix); noteMix5.gain(1, osc2Mix);
  noteMix6.gain(0, osc1Mix); noteMix6.gain(1, osc2Mix);
  noteMix7.gain(0, osc1Mix); noteMix7.gain(1, osc2Mix);
  noteMix8.gain(0, osc1Mix); noteMix8.gain(1, osc2Mix);
  noteMix9.gain(0, osc1Mix); noteMix9.gain(1, osc2Mix);
  noteMix10.gain(0, osc1Mix); noteMix10.gain(1, osc2Mix);
  noteMix11.gain(0, osc1Mix); noteMix11.gain(1, osc2Mix);
  noteMix12.gain(0, osc1Mix); noteMix12.gain(1, osc2Mix);

  // Forme d'onda
  int wf1Index = map(artboard.pot(3), 0, 1023, 0, 3);
  int wf2Index = map(artboard.pot(4), 0, 1023, 0, 3);

  if (wf1Index != currentWaveform1) {
    currentWaveform1 = wf1Index;
    updateWaveform1(waveforms[wf1Index]);
  }

  if (wf2Index != currentWaveform2) {
    currentWaveform2 = wf2Index;
    updateWaveform2(waveforms[wf2Index]);
  }

  // Filtro
  float filterFreq = map(artboard.pot(5), 0, 1023, 100, 12000);
  filter.frequency(filterFreq);

  // LFO
  float lfoRate = map(artboard.pot(6), 0, 1023, 1, 100) / 10.0;
  float lfoDepth = map(artboard.pot(7), 0, 1023, 0, 50) / 10.0;
  lfo.frequency(lfoRate);
  filter.octaveControl(lfoDepth);

  // --- GESTIONE PULSANTI PER REGISTRAZIONE ---
  recordingStep = -1;
  for (int i = 0; i < 8; i++) {
    bool btnState = (artboard.button(i) == HIGH);

    if (btnState && !prevButtonState[i]) {
      // Pulisci step
      sequence[i].hasData = false;
      for (int n = 0; n < NUM_NOTES; n++) {
        sequence[i].notes[n] = false;
      }
      Serial.print("Recording step: ");
      Serial.println(i);
    }

    if (btnState) {
      recordingStep = i;
      artboard.setLED(i, 255, 0, 0); // Rosso
    } else if (!btnState && prevButtonState[i]) {
      artboard.clearLED(i);
    }

    prevButtonState[i] = btnState;
  }

  // --- GESTIONE TOUCH (NOTE + REGISTRAZIONE) ---
  for (int i = 0; i < NUM_NOTES; i++) {
    int touchValue = artboard.touch(i);
    bool touched = (touchValue > 2000);

    if (touched && !prevTouchState[i]) {
      // Trigger nota
      triggerNote(i, attackTime);

      // Registra se necessario
      if (recordingStep >= 0) {
        sequence[recordingStep].notes[i] = true;
        sequence[recordingStep].hasData = true;
        Serial.print("Recorded note ");
        Serial.print(i);
        Serial.print(" on step ");
        Serial.println(recordingStep);
      }
    }

    if (!touched && prevTouchState[i]) {
      releaseNote(i, releaseTime);
    }

    prevTouchState[i] = touched;
  }

  // --- SEQUENCER PLAYBACK ---
  bool playSwitch = (digitalRead(28) == LOW);

  if (playSwitch && !prevPlayState) {
    isPlaying = !isPlaying;
    if (isPlaying) {
      currentStep = 0;
      lastStepTime = millis();
      Serial.println("PLAY");
    } else {
      Serial.println("STOP");
      artboard.clearAllLEDs();
      // Release tutte le note
      for (int i = 0; i < NUM_NOTES; i++) {
        releaseNote(i, 50);
      }
    }
  }
  prevPlayState = playSwitch;

  if (isPlaying) {
    unsigned long stepDuration = (60000 / bpm) / 2;

    if (millis() - lastStepTime >= stepDuration) {
      lastStepTime = millis();

      // Release note step precedente
      for (int i = 0; i < NUM_NOTES; i++) {
        releaseNote(i, 50);
      }

      // Avanza step
      currentStep = (currentStep + 1) % NUM_STEPS;

      // Update LED
      artboard.clearAllLEDs();
      artboard.setLED(currentStep, 0, 255, 0); // Verde

      // Trigger note step corrente
      if (sequence[currentStep].hasData) {
        for (int i = 0; i < NUM_NOTES; i++) {
          if (sequence[currentStep].notes[i]) {
            triggerNote(i, attackTime);
          }
        }
      }
    }
  }

  delay(5);
}

// --- HELPER FUNCTIONS ---

void setupOscillators() {
  waveform1_1.begin(1.0, notes[0], waveforms[currentWaveform1]);
  waveform1_2.begin(1.0, notes[1], waveforms[currentWaveform1]);
  waveform1_3.begin(1.0, notes[2], waveforms[currentWaveform1]);
  waveform1_4.begin(1.0, notes[3], waveforms[currentWaveform1]);
  waveform1_5.begin(1.0, notes[4], waveforms[currentWaveform1]);
  waveform1_6.begin(1.0, notes[5], waveforms[currentWaveform1]);
  waveform1_7.begin(1.0, notes[6], waveforms[currentWaveform1]);
  waveform1_8.begin(1.0, notes[7], waveforms[currentWaveform1]);
  waveform1_9.begin(1.0, notes[8], waveforms[currentWaveform1]);
  waveform1_10.begin(1.0, notes[9], waveforms[currentWaveform1]);
  waveform1_11.begin(1.0, notes[10], waveforms[currentWaveform1]);
  waveform1_12.begin(1.0, notes[11], waveforms[currentWaveform1]);

  waveform2_1.begin(1.0, notes[0], waveforms[currentWaveform2]);
  waveform2_2.begin(1.0, notes[1], waveforms[currentWaveform2]);
  waveform2_3.begin(1.0, notes[2], waveforms[currentWaveform2]);
  waveform2_4.begin(1.0, notes[3], waveforms[currentWaveform2]);
  waveform2_5.begin(1.0, notes[4], waveforms[currentWaveform2]);
  waveform2_6.begin(1.0, notes[5], waveforms[currentWaveform2]);
  waveform2_7.begin(1.0, notes[6], waveforms[currentWaveform2]);
  waveform2_8.begin(1.0, notes[7], waveforms[currentWaveform2]);
  waveform2_9.begin(1.0, notes[8], waveforms[currentWaveform2]);
  waveform2_10.begin(1.0, notes[9], waveforms[currentWaveform2]);
  waveform2_11.begin(1.0, notes[10], waveforms[currentWaveform2]);
  waveform2_12.begin(1.0, notes[11], waveforms[currentWaveform2]);
}

void updateWaveform1(int waveType) {
  waveform1_1.begin(1.0, notes[0], waveType);
  waveform1_2.begin(1.0, notes[1], waveType);
  waveform1_3.begin(1.0, notes[2], waveType);
  waveform1_4.begin(1.0, notes[3], waveType);
  waveform1_5.begin(1.0, notes[4], waveType);
  waveform1_6.begin(1.0, notes[5], waveType);
  waveform1_7.begin(1.0, notes[6], waveType);
  waveform1_8.begin(1.0, notes[7], waveType);
  waveform1_9.begin(1.0, notes[8], waveType);
  waveform1_10.begin(1.0, notes[9], waveType);
  waveform1_11.begin(1.0, notes[10], waveType);
  waveform1_12.begin(1.0, notes[11], waveType);
}

void updateWaveform2(int waveType) {
  waveform2_1.begin(1.0, notes[0], waveType);
  waveform2_2.begin(1.0, notes[1], waveType);
  waveform2_3.begin(1.0, notes[2], waveType);
  waveform2_4.begin(1.0, notes[3], waveType);
  waveform2_5.begin(1.0, notes[4], waveType);
  waveform2_6.begin(1.0, notes[5], waveType);
  waveform2_7.begin(1.0, notes[6], waveType);
  waveform2_8.begin(1.0, notes[7], waveType);
  waveform2_9.begin(1.0, notes[8], waveType);
  waveform2_10.begin(1.0, notes[9], waveType);
  waveform2_11.begin(1.0, notes[10], waveType);
  waveform2_12.begin(1.0, notes[11], waveType);
}

void triggerNote(int note, int attack) {
  switch(note) {
    case 0:  env1.amplitude(1.0, attack); break;
    case 1:  env2.amplitude(1.0, attack); break;
    case 2:  env3.amplitude(1.0, attack); break;
    case 3:  env4.amplitude(1.0, attack); break;
    case 4:  env5.amplitude(1.0, attack); break;
    case 5:  env6.amplitude(1.0, attack); break;
    case 6:  env7.amplitude(1.0, attack); break;
    case 7:  env8.amplitude(1.0, attack); break;
    case 8:  env9.amplitude(1.0, attack); break;
    case 9:  env10.amplitude(1.0, attack); break;
    case 10: env11.amplitude(1.0, attack); break;
    case 11: env12.amplitude(1.0, attack); break;
  }
}

void releaseNote(int note, int release) {
  switch(note) {
    case 0:  env1.amplitude(0.0, release); break;
    case 1:  env2.amplitude(0.0, release); break;
    case 2:  env3.amplitude(0.0, release); break;
    case 3:  env4.amplitude(0.0, release); break;
    case 4:  env5.amplitude(0.0, release); break;
    case 5:  env6.amplitude(0.0, release); break;
    case 6:  env7.amplitude(0.0, release); break;
    case 7:  env8.amplitude(0.0, release); break;
    case 8:  env9.amplitude(0.0, release); break;
    case 9:  env10.amplitude(0.0, release); break;
    case 10: env11.amplitude(0.0, release); break;
    case 11: env12.amplitude(0.0, release); break;
  }
}
