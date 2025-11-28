/*
 * Artboard Wikipedia Sonification (Simulata)
 *
 * Questo esempio sonorizza eventi simulati in stile Wikipedia
 * ispirato al progetto "Listen to Wikipedia" (http://listen.hatnote.com/)
 *
 * NOTA: Questa versione genera eventi SIMULATI invece di connettersi
 * al vero stream Wikipedia, perché l'ESP8266 ha difficoltà con HTTPS.
 *
 * Utilizza:
 * - Teensy Audio Library per generare suoni
 * - LED RGB per feedback visivo
 * - Eventi random che simulano modifiche Wikipedia
 *
 * Ogni tipo di evento ha un suono e colore diverso:
 * - Nuove pagine: suono cristallino (1000-1500 Hz), LED verde
 * - Modifiche piccole: suono morbido (500-800 Hz), LED blu
 * - Modifiche grandi: suono profondo (200-300 Hz), LED rosso
 * - Bot edits: suono meccanico (300 Hz), LED giallo
 *
 * Controlli:
 * - Pot 0: Volume
 * - Pot 1: Frequenza eventi (lento/veloce)
 * - Pot 2: Probabilità tipo evento (più bot o più umani)
 */

#include <Arduino.h>
#include <Audio.h>
#include <Artboard.h>

Artboard artboard;

// Audio setup (architettura semplice e provata)
AudioSynthWaveformDc     env1;
AudioSynthWaveform       waveform1;
AudioEffectMultiply      multiply1;
AudioFilterStateVariable filter1;
AudioOutputAnalog        dac0;

AudioConnection patchCord1(waveform1, 0, multiply1, 0);
AudioConnection patchCord2(env1, 0, multiply1, 1);
AudioConnection patchCord3(multiply1, 0, filter1, 0);
AudioConnection patchCord4(filter1, 0, dac0, 0);

// Variabili per simulazione
unsigned long lastEventTime = 0;
int eventInterval = 500; // ms tra eventi

// Statistiche (per debug)
unsigned long totalEvents = 0;
unsigned long newPages = 0;
unsigned long botEdits = 0;
unsigned long smallEdits = 0;
unsigned long largeEdits = 0;

void setup() {
  Serial.begin(115200);

  // Audio setup
  AudioMemory(20);

  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.8);

  env1.amplitude(0.0);

  filter1.frequency(5000);
  filter1.resonance(1.2);

  Serial.println("=== WIKIPEDIA SONIFICATION (SIMULATED) ===");
  Serial.println("Generating random Wikipedia-style events...");
  Serial.println("Pot 0: Volume");
  Serial.println("Pot 1: Event frequency");
  Serial.println("Pot 2: Bot/Human ratio");
}

void loop() {
  // Leggi controlli
  float volume = artboard.pot(0) / 1023.0;
  int eventFreq = map(artboard.pot(1), 0, 1023, 100, 3000); // 100ms a 3s
  float botProbability = artboard.pot(2) / 1023.0; // 0-100% bot

  eventInterval = eventFreq;

  // Genera eventi random
  if (millis() - lastEventTime >= eventInterval) {
    lastEventTime = millis();
    generateRandomEvent(botProbability, volume);
  }

  // Decay envelope
  float currentEnv = env1.read();
  if (currentEnv > 0.01) {
    env1.amplitude(currentEnv * 0.95, 20); // Decay graduale
  }

  delay(10);
}

void generateRandomEvent(float botProb, float volume) {
  totalEvents++;

  // Decide tipo di evento
  float eventType = random(1000) / 1000.0;
  bool isBot = (random(1000) / 1000.0) < botProb;
  bool isNew = (eventType < 0.1); // 10% nuove pagine
  int changeSize = random(1, 1000);

  float frequency;
  int r, g, b;
  String eventName;

  if (isNew) {
    // Nuova pagina: suono cristallino alto
    frequency = 1000 + random(500);
    r = 0; g = 255; b = 0;
    eventName = "NEW PAGE";
    newPages++;

  } else if (isBot) {
    // Bot edit: suono meccanico
    frequency = 300;
    r = 255; g = 255; b = 0;
    eventName = "BOT EDIT";
    botEdits++;

  } else if (changeSize > 500) {
    // Modifica grande: suono profondo
    frequency = 200 + random(100);
    r = 255; g = 0; b = 0;
    eventName = "LARGE EDIT";
    largeEdits++;

  } else {
    // Modifica piccola: suono morbido
    frequency = 500 + random(300);
    r = 0; g = 100; b = 255;
    eventName = "SMALL EDIT";
    smallEdits++;
  }

  // Trigger suono
  waveform1.frequency(frequency);
  env1.amplitude(volume, 10); // Attack veloce
  filter1.frequency(frequency * 2);

  // LED
  artboard.setAllLEDs(r, g, b);

  // Debug
  Serial.print("#");
  Serial.print(totalEvents);
  Serial.print(" ");
  Serial.print(eventName);
  Serial.print(" ");
  Serial.print(frequency);
  Serial.print("Hz size:");
  Serial.println(changeSize);

  // Statistiche ogni 50 eventi
  if (totalEvents % 50 == 0) {
    Serial.println("--- STATS ---");
    Serial.print("New: "); Serial.print(newPages);
    Serial.print(" | Bot: "); Serial.print(botEdits);
    Serial.print(" | Small: "); Serial.print(smallEdits);
    Serial.print(" | Large: "); Serial.println(largeEdits);
  }
}
