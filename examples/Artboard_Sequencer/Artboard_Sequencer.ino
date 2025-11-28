/*
 * Artboard Sequencer
 *
 * Un sequencer a 8 step con sintetizzatore polifonico a 12 note
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
 * - Pot 8:  Velocità del sequencer (BPM) - NOTA: Pot 8 non esiste su Artboard standard!
 *           Usa Pot 7 per BPM se hai solo 8 pot, o aggiungi controllo esterno
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

// --- AUDIO SETUP (Teensy Audio Design Tool) ---

// Oscillatori (2 per ogni nota = 12 note x 2 = 24 oscillatori)
AudioSynthWaveform osc1[12];
AudioSynthWaveform osc2[12];

// Envelopes per ogni nota
AudioEffectEnvelope env[12];

// Mixer per combinare osc1 e osc2 di ogni nota
AudioMixer4 noteMixer[12];

// Mixer principali (raggruppano le 12 note)
AudioMixer4 mainMixer1;
AudioMixer4 mainMixer2;
AudioMixer4 mainMixer3;

// LFO per modulazione filtro
AudioSynthWaveformSine lfo;
AudioSynthWaveformDc lfoDepth;
AudioEffectMultiply lfoMult;

// Filtro
AudioFilterStateVariable filter;

// Output
AudioOutputI2S i2s1;

// Connections
AudioConnection* patchCords[200]; // Array per tenere traccia delle connessioni
int patchCordIndex = 0;

void setup() {
  Serial.begin(115200);

  // Audio memory
  AudioMemory(120);

  // Setup oscillatori e envelopes
  setupAudioConnections();

  // Setup iniziale forme d'onda e parametri
  for (int i = 0; i < 12; i++) {
    osc1[i].begin(WAVEFORM_SAWTOOTH);
    osc2[i].begin(WAVEFORM_SQUARE);
    osc1[i].amplitude(0.3);
    osc2[i].amplitude(0.3);

    // Imposta le frequenze delle note (scala cromatica da C3)
    float freq = noteFrequency(i);
    osc1[i].frequency(freq);
    osc2[i].frequency(freq);

    // Envelope settings
    env[i].attack(10);
    env[i].decay(0);
    env[i].sustain(1.0);
    env[i].release(200);

    // Mixer delle note (combina osc1 e osc2)
    noteMixer[i].gain(0, 0.5); // osc1
    noteMixer[i].gain(1, 0.5); // osc2
  }

  // Mixer principali
  mainMixer1.gain(0, 0.25);
  mainMixer1.gain(1, 0.25);
  mainMixer1.gain(2, 0.25);
  mainMixer1.gain(3, 0.25);

  mainMixer2.gain(0, 0.25);
  mainMixer2.gain(1, 0.25);
  mainMixer2.gain(2, 0.25);
  mainMixer2.gain(3, 0.25);

  mainMixer3.gain(0, 0.25);
  mainMixer3.gain(1, 0.25);
  mainMixer3.gain(2, 0.25);
  mainMixer3.gain(3, 0.25);

  // LFO
  lfo.frequency(2.0);
  lfo.amplitude(1.0);
  lfoDepth.amplitude(0.5);

  // Filtro
  filter.frequency(2000);
  filter.resonance(1.4);

  // Setup pin on/off switch
  pinMode(28, INPUT_PULLUP);

  // Inizializza LED
  artboard.clearAllLEDs();

  Serial.println("=== ARTBOARD SEQUENCER ===");
  Serial.println("Ready!");
}

// --- SEQUENCER DATA ---
#define NUM_STEPS 8
#define NUM_NOTES 12

// Struttura per memorizzare lo stato di ogni step
struct Step {
  bool notes[NUM_NOTES];  // Quali note sono attive
  bool hasData;           // Se lo step contiene dati
};

Step sequence[NUM_STEPS];

// Variabili sequencer
int currentStep = 0;
unsigned long lastStepTime = 0;
int bpm = 120;
bool isPlaying = false;
int recordingStep = -1; // -1 = nessuna registrazione in corso

// Stato precedente dei controlli (per edge detection)
bool prevTouchState[NUM_NOTES] = {false};
bool prevButtonState[8] = {false};
bool prevPlayState = false;

void loop() {
  // --- LEGGI CONTROLLI ---

  // Attack e Release
  int attackTime = map(artboard.pot(0), 0, 1023, 1, 500);
  int releaseTime = map(artboard.pot(1), 0, 1023, 10, 1000);

  // Mix oscillatori
  float osc1Mix = map(artboard.pot(2), 0, 1023, 0, 100) / 100.0;
  float osc2Mix = 1.0 - osc1Mix;

  // Forme d'onda
  int waveform1Type = map(artboard.pot(3), 0, 1023, 0, 3);
  int waveform2Type = map(artboard.pot(4), 0, 1023, 0, 3);

  // Filtro
  int filterFreq = map(artboard.pot(5), 0, 1023, 100, 10000);

  // LFO
  float lfoRate = map(artboard.pot(6), 0, 1023, 1, 200) / 10.0;
  float lfoDepthValue = map(artboard.pot(7), 0, 1023, 0, 100) / 100.0;

  // BPM (usa pot 7 o aggiungi controllo esterno)
  // Per ora usa un valore fisso o pot 7 in alternativa
  // bpm = map(artboard.pot(7), 0, 1023, 40, 240);

  // Play/Stop
  bool playSwitch = (digitalRead(28) == LOW); // Assumendo switch pull-up

  // --- AGGIORNA PARAMETRI AUDIO ---

  // Aggiorna forme d'onda per tutti gli oscillatori
  static int prevWaveform1Type = -1;
  static int prevWaveform2Type = -1;

  if (waveform1Type != prevWaveform1Type) {
    short wf1 = getWaveformType(waveform1Type);
    for (int i = 0; i < 12; i++) {
      osc1[i].begin(wf1);
      osc1[i].frequency(noteFrequency(i));
      osc1[i].amplitude(0.3);
    }
    prevWaveform1Type = waveform1Type;
  }

  if (waveform2Type != prevWaveform2Type) {
    short wf2 = getWaveformType(waveform2Type);
    for (int i = 0; i < 12; i++) {
      osc2[i].begin(wf2);
      osc2[i].frequency(noteFrequency(i));
      osc2[i].amplitude(0.3);
    }
    prevWaveform2Type = waveform2Type;
  }

  // Aggiorna mix oscillatori
  for (int i = 0; i < 12; i++) {
    noteMixer[i].gain(0, osc1Mix);
    noteMixer[i].gain(1, osc2Mix);
  }

  // Aggiorna filtro
  filter.frequency(filterFreq);

  // Aggiorna LFO
  lfo.frequency(lfoRate);
  lfoDepth.amplitude(lfoDepthValue);

  // Aggiorna envelope
  for (int i = 0; i < 12; i++) {
    env[i].attack(attackTime);
    env[i].release(releaseTime);
  }

  // --- GESTIONE PULSANTI PER REGISTRAZIONE ---

  recordingStep = -1;
  for (int i = 0; i < 8; i++) {
    bool btnState = (artboard.button(i) == HIGH);

    // Rileva pressione pulsante (edge detection)
    if (btnState && !prevButtonState[i]) {
      // Nuovo step selezionato - pulisci i dati precedenti
      sequence[i].hasData = false;
      for (int n = 0; n < NUM_NOTES; n++) {
        sequence[i].notes[n] = false;
      }
      Serial.print("Recording on step: ");
      Serial.println(i);
    }

    if (btnState) {
      recordingStep = i;
      // Accendi LED per indicare registrazione
      artboard.setLED(i, 255, 0, 0); // Rosso per registrazione
    } else if (!btnState && prevButtonState[i]) {
      // Pulsante rilasciato
      artboard.clearLED(i);
    }

    prevButtonState[i] = btnState;
  }

  // --- GESTIONE TOUCH (SUONARE NOTE + REGISTRAZIONE) ---

  for (int i = 0; i < NUM_NOTES; i++) {
    int touchValue = artboard.touch(i);
    bool touched = (touchValue > 2000); // Soglia touch

    // Edge detection: nota appena toccata
    if (touched && !prevTouchState[i]) {
      // Trigger nota
      env[i].noteOn();

      // Se stiamo registrando, aggiungi la nota allo step
      if (recordingStep >= 0) {
        sequence[recordingStep].notes[i] = true;
        sequence[recordingStep].hasData = true;
        Serial.print("Recorded note ");
        Serial.print(i);
        Serial.print(" on step ");
        Serial.println(recordingStep);
      }
    }

    // Nota rilasciata
    if (!touched && prevTouchState[i]) {
      env[i].noteOff();
    }

    prevTouchState[i] = touched;
  }

  // --- SEQUENCER PLAYBACK ---

  // Gestisci play/stop
  if (playSwitch && !prevPlayState) {
    // Play premuto
    isPlaying = !isPlaying;
    if (isPlaying) {
      currentStep = 0;
      lastStepTime = millis();
      Serial.println("PLAY");
    } else {
      Serial.println("STOP");
      artboard.clearAllLEDs();
      // Spegni tutte le note
      for (int i = 0; i < NUM_NOTES; i++) {
        env[i].noteOff();
      }
    }
  }
  prevPlayState = playSwitch;

  // Avanza sequencer
  if (isPlaying) {
    unsigned long stepDuration = (60000 / bpm) / 2; // Durata step in ms (2 step per beat)

    if (millis() - lastStepTime >= stepDuration) {
      // Avanza allo step successivo
      lastStepTime = millis();

      // Spegni note dello step precedente
      for (int i = 0; i < NUM_NOTES; i++) {
        env[i].noteOff();
      }

      // Avanza step
      currentStep = (currentStep + 1) % NUM_STEPS;

      // Aggiorna LED
      artboard.clearAllLEDs();
      artboard.setLED(currentStep, 0, 255, 0); // Verde per playback

      // Suona le note dello step corrente
      if (sequence[currentStep].hasData) {
        for (int i = 0; i < NUM_NOTES; i++) {
          if (sequence[currentStep].notes[i]) {
            env[i].noteOn();
          }
        }
      }
    }
  }

  delay(1); // Piccolo delay per stabilità
}

// --- FUNZIONI HELPER ---

// Calcola frequenza nota (scala cromatica da C3)
float noteFrequency(int note) {
  // Note: C, C#, D, D#, E, F, F#, G, G#, A, A#, B
  float baseFreq = 130.81; // C3
  return baseFreq * pow(2.0, note / 12.0);
}

// Converte indice in tipo di forma d'onda
short getWaveformType(int index) {
  switch(index) {
    case 0: return WAVEFORM_SINE;
    case 1: return WAVEFORM_SAWTOOTH;
    case 2: return WAVEFORM_SQUARE;
    case 3: return WAVEFORM_TRIANGLE;
    default: return WAVEFORM_SINE;
  }
}

// Setup delle connessioni audio
void setupAudioConnections() {
  // Questa è una versione semplificata
  // In un progetto reale useresti il Teensy Audio Design Tool

  // Per ogni nota: osc1 e osc2 -> noteMixer -> envelope -> mainMixer

  // Esempio di connessioni per le prime note:
  // NOTA: Teensy ha un limite di oggetti AudioConnection (circa 100-120)
  // Per un progetto completo, potresti dover usare AudioMixer con meno canali
  // o un approccio diverso

  // Connetti oscillatori ai mixer delle note
  for (int i = 0; i < 12; i++) {
    patchCords[patchCordIndex++] = new AudioConnection(osc1[i], 0, noteMixer[i], 0);
    patchCords[patchCordIndex++] = new AudioConnection(osc2[i], 0, noteMixer[i], 1);
  }

  // Connetti note mixer agli envelope e poi ai mixer principali
  // Note 0-3 -> mainMixer1
  for (int i = 0; i < 4; i++) {
    patchCords[patchCordIndex++] = new AudioConnection(noteMixer[i], 0, env[i], 0);
    patchCords[patchCordIndex++] = new AudioConnection(env[i], 0, mainMixer1, i);
  }

  // Note 4-7 -> mainMixer2
  for (int i = 4; i < 8; i++) {
    patchCords[patchCordIndex++] = new AudioConnection(noteMixer[i], 0, env[i], 0);
    patchCords[patchCordIndex++] = new AudioConnection(env[i], 0, mainMixer2, i-4);
  }

  // Note 8-11 -> mainMixer3
  for (int i = 8; i < 12; i++) {
    patchCords[patchCordIndex++] = new AudioConnection(noteMixer[i], 0, env[i], 0);
    patchCords[patchCordIndex++] = new AudioConnection(env[i], 0, mainMixer3, i-8);
  }

  // Setup LFO
  patchCords[patchCordIndex++] = new AudioConnection(lfo, 0, lfoMult, 0);
  patchCords[patchCordIndex++] = new AudioConnection(lfoDepth, 0, lfoMult, 1);

  // Connetti mixer principali al filtro
  patchCords[patchCordIndex++] = new AudioConnection(mainMixer1, 0, filter, 0);
  patchCords[patchCordIndex++] = new AudioConnection(mainMixer2, 0, filter, 0);
  patchCords[patchCordIndex++] = new AudioConnection(mainMixer3, 0, filter, 0);

  // LFO modula il filtro
  patchCords[patchCordIndex++] = new AudioConnection(lfoMult, 0, filter, 1);

  // Filtro all'output
  patchCords[patchCordIndex++] = new AudioConnection(filter, 0, i2s1, 0);
  patchCords[patchCordIndex++] = new AudioConnection(filter, 0, i2s1, 1);

  Serial.print("Total patch cords: ");
  Serial.println(patchCordIndex);
}
