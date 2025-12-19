/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: premi bottone suona campione

  button 0  = kick
  button 1  = snare
  button 2  = hihat
  button 3  = clap

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
Artboard artboard; // Istanza


AudioOutputAnalogStereo  dac0;
AudioPlaySdWav           playSdWav1;
AudioMixer4              mixer1;
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0,   dac0, 0);
AudioConnection          patchCord4(mixer1, 0,   dac0, 1);

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
///////////////////////////////////


int kick;
int snare;
int hihat;
int clap;


void setup() {

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);

  Serial.begin(9600);
  AudioMemory(8);


  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }




}

void loop() {
  kick   =  artboard.button(0);
  snare  =  artboard.button(1);
  hihat  =  artboard.button(2);
  clap   =  artboard.button(3);

  ///////////////////kick///////////////////////
  if (kick > 0 && playSdWav1.isPlaying()==0) {
    playSdWav1.play("kick.wav");
  }

  ///////////////////SNARE////////////////////////
  if (snare > 0 && playSdWav1.isPlaying()==0) {
    playSdWav1.play("snare.wav");
  }

  ///////////////////hihat////////////////////////
  if (hihat > 0 && playSdWav1.isPlaying()==0) {
    playSdWav1.play("hihat.wav");
  }

  ///////////////////clap////////////////////////
  if (clap > 0 && playSdWav1.isPlaying()==0) {
    playSdWav1.play("clap.wav");
  }


 delay(100);
}
