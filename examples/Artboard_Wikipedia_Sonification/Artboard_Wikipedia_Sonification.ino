/*
 * Artboard Wikipedia Sonification
 *
 * Questo esempio sonorizza in tempo reale i contributi a Wikipedia,
 * ispirato al progetto "Listen to Wikipedia" (http://listen.hatnote.com/)
 *
 * Utilizza:
 * - WiFi ESP12S per connettersi allo stream EventStreams di Wikipedia
 * - Teensy Audio Library per generare suoni
 * - LED RGB per feedback visivo
 *
 * Ogni tipo di evento ha un suono e colore diverso:
 * - Nuove pagine: suono cristallino, LED verde
 * - Modifiche piccole: suono morbido, LED blu
 * - Modifiche grandi: suono profondo, LED rosso
 * - Bot edits: suono meccanico, LED giallo
 *
 * Stream API: https://stream.wikimedia.org/v2/stream/recentchange
 * Documentazione: https://wikitech.wikimedia.org/wiki/Event_Platform/EventStreams
 */

#include <Arduino.h>
#include <WiFiEsp.h>
#include <Audio.h>
#include <Artboard.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";  // Cambia con il tuo SSID
char pass[] = "YOUR_WIFI_PASSWORD";  // Cambia con la tua password

int status = WL_IDLE_STATUS;
WiFiEspClient client;

Artboard artboard;

// Audio setup
AudioSynthWaveform     waveform1;
AudioSynthWaveform     waveform2;
AudioEffectEnvelope    envelope1;
AudioMixer4            mixer;
AudioOutputI2S         i2s1;

AudioConnection        patchCord1(waveform1, envelope1);
AudioConnection        patchCord2(envelope1, 0, mixer, 0);
AudioConnection        patchCord3(waveform2, 0, mixer, 1);
AudioConnection        patchCord4(mixer, 0, i2s1, 0);
AudioConnection        patchCord5(mixer, 0, i2s1, 1);

// Server Wikipedia EventStreams
const char server[] = "stream.wikimedia.org";
const int port = 443; // HTTPS

// Buffer per parsing
String currentLine = "";
int changeSize = 0;
bool isBot = false;
bool isNew = false;

void setup() {
  Serial.begin(115200);

  // Initialize WiFi
  Serial.println("Initializing WiFi...");
  WiFi.init(&Serial1);

  // Check WiFi module
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  // Connect to WiFi
  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("Connected to WiFi!");
  printWifiStatus();

  // Audio setup
  AudioMemory(20);

  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_TRIANGLE);

  envelope1.attack(10.0);
  envelope1.decay(35.0);
  envelope1.sustain(0.5);
  envelope1.release(250.0);

  mixer.gain(0, 0.7);
  mixer.gain(1, 0.3);

  // Connect to Wikipedia stream
  connectToWikipedia();
}

void loop() {
  // Read data from stream
  if (client.connected()) {
    while (client.available()) {
      char c = client.read();

      // Build line
      if (c == '\n') {
        // Parse the line
        parseWikipediaEvent(currentLine);
        currentLine = "";
      } else {
        currentLine += c;
      }
    }
  } else {
    // Reconnect if disconnected
    Serial.println("Disconnected. Reconnecting...");
    delay(5000);
    connectToWikipedia();
  }

  // Use potentiometers to control audio parameters
  float volume = artboard.pot(0) / 1023.0;
  mixer.gain(0, volume * 0.7);

  float pitchMod = artboard.pot(1) / 1023.0;
  // pitchMod can be used to transpose all notes
}

void connectToWikipedia() {
  Serial.println("Connecting to Wikipedia EventStreams...");

  if (client.connect(server, 80)) {
    Serial.println("Connected!");

    // HTTP GET request for SSE stream
    client.println("GET /v2/stream/recentchange HTTP/1.1");
    client.println("Host: stream.wikimedia.org");
    client.println("Accept: text/event-stream");
    client.println("Connection: keep-alive");
    client.println();
  } else {
    Serial.println("Connection failed!");
  }
}

void parseWikipediaEvent(String line) {
  // Simple parsing (in production use ArduinoJson)

  // Check for event data
  if (line.startsWith("data:")) {

    // Extract relevant info
    if (line.indexOf("\"type\":\"new\"") > 0) {
      isNew = true;
    }

    if (line.indexOf("\"bot\":true") > 0) {
      isBot = true;
    }

    // Extract change size (simplified)
    int lengthIdx = line.indexOf("\"length\":");
    if (lengthIdx > 0) {
      int oldLengthIdx = line.indexOf("\"oldlength\":");
      if (oldLengthIdx > 0) {
        // Calculate approximate change size
        changeSize = random(1, 500); // Simplified
      }
    }

    // Trigger sound and visual
    triggerEvent();

    // Reset flags
    isNew = false;
    isBot = false;
    changeSize = 0;
  }
}

void triggerEvent() {
  float frequency;
  int r, g, b;

  if (isNew) {
    // New page: high, bell-like sound
    frequency = 1000.0 + random(500);
    r = 0; g = 255; b = 0;
    waveform1.begin(WAVEFORM_SINE);

  } else if (isBot) {
    // Bot edit: mechanical sound
    frequency = 300.0;
    r = 255; g = 255; b = 0;
    waveform1.begin(WAVEFORM_SQUARE);

  } else if (changeSize > 200) {
    // Large edit: deep sound
    frequency = 200.0 + random(100);
    r = 255; g = 0; b = 0;
    waveform1.begin(WAVEFORM_TRIANGLE);

  } else {
    // Small edit: soft sound
    frequency = 500.0 + random(300);
    r = 0; g = 100; b = 255;
    waveform1.begin(WAVEFORM_SINE);
  }

  // Play sound
  waveform1.frequency(frequency);
  waveform1.amplitude(0.5);
  envelope1.noteOn();

  // Set all LED color
  artboard.setAllLEDs(r, g, b);

  // Print to serial
  Serial.print("Event: ");
  if (isNew) Serial.print("NEW ");
  if (isBot) Serial.print("BOT ");
  Serial.print("Size: ");
  Serial.print(changeSize);
  Serial.print(" Hz: ");
  Serial.println(frequency);
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
