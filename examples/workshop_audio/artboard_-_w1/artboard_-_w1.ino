
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: audio workshop
Descrizione: sinusoide

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/

/*https://www.pjrc.com/teensy/gui
 importiamo il setup da
*/

#include <Artboard.h> // includiamo la libreria

Artboard artboard; // Istanza

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=262,177
AudioOutputAnalogStereo  dacs1;          //xy=419,187
AudioConnection          patchCord1(sine1, 0, dacs1, 0);
AudioConnection          patchCord2(sine1, 0, dacs1, 1);
// GUItool: end automatically generated code

void setup() {
AudioMemory(512);
Serial.begin(9600);
sine1.amplitude(1);
sine1.frequency(440);
}

void loop() {


}
