
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: audio workshop
Descrizione: sinusoide + potenziometro 1 freq

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/

/*  importiamo il setup da
 *   https://www.pjrc.com/teensy/gui

*/
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h> // includiamo la libreria

Artboard artboard; // Istanza

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=262,177
AudioOutputAnalogStereo  dacs1;          //xy=419,187
AudioConnection          patchCord1(sine1, 0, dacs1, 0);
AudioConnection          patchCord2(sine1, 0, dacs1, 1);
// GUItool: end automatically generated code

void setup() {
AudioMemory(512);
Serial.begin(9600);
sine1.amplitude(0.6);

}

void loop() {

int freq=map(artboard.pot(0),0,1023,100,17000);
sine1.frequency(freq);

}
