 /*
*
*  ArduinoJson library 
*  https://arduinojson.org/v6/assistant/
*  selezionare la board
*  deserialize
*  copiare il contenuto del file json

*  NEXT project
 * real time change on wikipedia
*  https://stream.wikimedia.org/v2/stream/recentchange
*  https://wikitech.wikimedia.org/wiki/Event_Platform/EventStreams
 
*/

#include "libraries.h"
char ssid[] = "BRAMBRI";  // your network SSID (name)
char pass[] = "CASAGALLO2872018";
int status = WL_IDLE_STATUS;  // the Wifi radio's status
WiFiEspClient client;

//WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP

char server[] = "api.open-notify.org";


void setup() {

#include "settings.h"

  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
    client.println("GET /iss-now.json HTTP/1.1");
    client.println("Host: api.open-notify.org");
    client.println("Connection: close");
    client.println();
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    // do nothing forevermore
    while (true);
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}