/*
 * real time change on wikipedia
*  https://stream.wikimedia.org/v2/stream/recentchange
*  https://wikitech.wikimedia.org/wiki/Event_Platform/EventStreams
*  
*  * selezionare dati in formato json portale opendata genova 
*  http://dati.comune.genova.it/
*  http://dati.comune.genova.it/dataset/rete-di-monitoraggio-pioggia
*  http://dati.comune.genova.it/Web_Service_meteo/handle_soap_request.php?mode=no_wsdl&action=read_json
*  
*  ArduinoJson library 
*  https://arduinojson.org/v6/assistant/
*  selezionare la board
*  deserialize
*  copiare il contenuto del file json
*  
 
*/

#include "libraries.h"
char ssid[] = "P10";            // your network SSID (name)
char pass[] = "$Murgia1";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiEspClient client;
#include <OSCMessage.h>
//WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP

char server[] = "dati.comune.genova.it";


void setup() {
  
 #include "settings.h"

}

void loop() {
chiamata();
delay(2000);


}


void chiamata(){
  
 //chiamata al sito 
  if (client.connect(server, 80)) {
  // Send HTTP request to https://dati.comune.genova.it/WebServiceMeteo/monitoraggio_meteo.json
  client.println(F("GET /WebServiceMeteo/monitoraggio_meteo.json HTTP/1.0"));
  client.println(F("Host: dati.comune.genova.it"));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    return;
  }
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  // It should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    //Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  DynamicJsonDocument doc(12288);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

 

//Variabili da  arduinojson.org/v6/assistant
/*
 configuration:
 processor:ep32
 Mode: deserialize
 Input type: stream

 input:
copia e incolla il contenuto della pagina 
http://dati.comune.genova.it/Web_Service_meteo/handle_soap_request.php?mode=no_wsdl&action=read_json


copia il valore: Total (recommended)  12288 su DynamicJsonDocument doc(valore);
*/
 

JsonObject root_11 = doc[11];
const char* root_11_id = root_11["id"]; // "16"
const char* root_11_name = root_11["name"]; // "Genova Centro"
const char* root_11_latitude = root_11["latitude"]; // "44.4121"
const char* root_11_longitude = root_11["longitude"]; // "8.9335"
const char* root_11_height = root_11["height"]; // "67"
const char* root_11_temperature = root_11["temperature"]; // "16.6"
const char* root_11_wind_chill = root_11["wind_chill"]; // "16.6"
const char* root_11_humidity = root_11["humidity"]; // "77"
const char* root_11_wind_speed = root_11["wind_speed"]; // "0.0"
const char* root_11_wind = root_11["wind"]; // "161.0"
const char* root_11_wind_dir = root_11["wind_dir"]; // "SSE"
const char* root_11_atmospheric_pressure = root_11["atmospheric_pressure"]; // "1005.8"
const char* root_11_rain = root_11["rain"]; // "0.0"
const char* root_11_dew_point = root_11["dew_point"]; // "12.8"
const char* root_11_rain_uh = root_11["rain_uh"]; // "0.0"
const char* root_11_last_update = root_11["last_update"]; // "2021-05-13 13:18:00"

  Serial.print(root_11_last_update);
  Serial.print(" wind: ");
  Serial.print(root_11_wind);
  Serial.print(" wind speed: ");
  Serial.print(root_11_wind_speed);
    Serial.print(" wind dir: ");
    Serial.println(root_11_wind_dir);
    
  // Disconnect
  client.stop();
  }
