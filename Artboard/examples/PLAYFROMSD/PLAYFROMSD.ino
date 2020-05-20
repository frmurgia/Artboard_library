
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: touchin play wav file from sd
Descrizione: riprodurre un file wave da SD


artboard.touch(i) per leggere l'ingresso capacitivo è sufficente
chiamarela funzione touch all'interno della libreria artboard
dove i equivale alla posizione dell'ingresso.
0=do
1=do#
2=re#
ecc.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Artboard.h> // includiamo la libreria

AudioPlaySdWav           playSdWav1;
AudioOutputAnalog        dac0; 
AudioConnection          patchCord1(playSdWav1, 0, dac0, 0);
AudioConnection          patchCord2(playSdWav1, 1, dac0, 1);
AudioControlSGTL5000     sgtl5000_1;

Artboard artboard; // Istanza



// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
 #define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used


void setup(){

  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}




void loop(){
  
  for( int i=0; i<=15; i++){ // leggiamo e stampiamo sulla seriale tutti i valori
      int val = artboard.touch(i);
      Serial.print("pos: ");
      Serial.print(i);
      Serial.print(": ");
     Serial.print(val);
       Serial.print(" ");
if(val>7400){
  
     if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing");
    playSdWav1.play("1.WAV");
    delay(10); // wait for library to parse WAV info
  }
  
  else{
     playSdWav1.stop();
    }
    }
   Serial.println();

 
  }

}
