#include "WiFiEsp.h"
#include <SSLClient.h>
#include "trust_anchors.h" // Il file che abbiamo appena creato

// --- DATI WIFI ---
char ssid[] = "BRAMBRI";            
char pass[] = "CASAGALLO2872018";
int status = WL_IDLE_STATUS;     

// 1. Client WiFi base (insicuro)
WiFiEspClient wifiClient;

// 2. Client SSL (Sicuro) che avvolge quello base
// A5 = Pin analogico per generare numeri casuali (deve essere un pin libero!)
// Sketch: Teensy USB to Serial Bridge
// Carica questo sul TEENSY per poter programmare l'ESP
void setup() {
  // Pin di Reset dell'ESP (se collegato al Teensy, altrimenti ignoralo)
  // pinMode(X, OUTPUT); digitalWrite(X, LOW); delay(100); digitalWrite(X, HIGH);
}

void loop() {
  // Copia brutale di tutto ciò che passa
  // Serial = USB PC
  // Serial1 = ESP8266
  
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}SSLClient client(wifiClient, T_TRs, 1, A5);

char server[] = "stream.wikimedia.org";

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  
  // Inizializza modulo WiFi
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Connessione a SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  
  Serial.println("WiFi Connesso!");
  printWifiStatus();

  Serial.println("\n--- AVVIO CONNESSIONE HTTPS (TEENSY-POWERED) ---");
  Serial.println("Nota: La prima connessione SSL richiede qualche secondo...");

  // Qui usiamo il client SSL, non quello base
  if (client.connect(server, 443)) {
    Serial.println("Connesso al server Wikipedia (HTTPS)!");
    
    // Richiesta HTTP
    client.println("GET /v2/stream/recentchange HTTP/1.1");
    client.println("Host: stream.wikimedia.org");
    client.println("Accept: text/event-stream");
    client.println("User-Agent: TeensySSL/1.0");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connessione SSL Fallita.");
    Serial.print("Codice Errore SSL: ");
    Serial.println(client.getWriteError());
  }
}

void loop() {
  // Leggi i dati decriptati
  while (client.available()) {
    String line = client.readStringUntil('\n');
    
    // Filtro per vedere solo i dati JSON
    if (line.startsWith("data: ")) {
      Serial.println("--- WIKIPEDIA EDIT ---");
      Serial.println(line); 
      // Qui aggiungeremo il suono!
    }
  }

  if (!client.connected()) {
    Serial.println("Disconnesso.");
    client.stop();
    while(true);
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}