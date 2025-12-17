/*seriale wifi collegato alla porta seriale del teensy 
  teesny TX->  RX MCU
  teesny RX->  TX MCU
*/

  // initialize serial for debugging
 

 Serial.begin(115200);   // Verso il PC
  Serial1.begin(115200);  // Verso l'ESP (Prova anche 9600 se non va)
  WiFi.init(&Serial1);
  // Attendi l'apertura del monitor seriale
  while (!Serial); 
  Serial.println("--- MODALITÀ PONTE ATTIVA ---");
  Serial.println("Scrivi 'AT' e premi Invio. Se ricevi 'OK', l'ESP funziona.");

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");

    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  