/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: simple drum_machine
  pot 0     = tempo
  button 0  = kick
  button 1  = snare
  button 2  = hihat
  button 3  = clap
  button 4  = resetAll
  button 5 + button 0-4  = reset singola posizione del sequencer selezionato


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

int tempo;
int kick;
int snare;
int hihat;
int clap;

int reset1;
int undo;
int sequencer_kick [8];
int sequencer_snare[8];
int sequencer_hihat[8];
int sequencer_clap[8];

int counter = 0;

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
  reset1 =  artboard.button(4);
  undo   =  artboard.button(5);

  counter++;
  //Serial.println(counter);
  if (counter == 8) {
    counter = 0;
  }

  ///////////////////contatore per la cassa////////////////////////
  if (kick > 0) {
    sequencer_kick[counter] = 1;
  }


  if (sequencer_kick[counter] == 1) {
    playSdWav1.play("kick.wav");
  }


  ///////////////////contatore per SNARE////////////////////////
  if (snare > 0) {
    sequencer_snare[counter] = 1;
  }

  if (sequencer_snare[counter] == 1) {
    playSdWav1.play("snare.wav");
  }

  ///////////////////contatore per hihat////////////////////////
  if (hihat > 0) {
    sequencer_hihat[counter] = 1;
  }

  if (sequencer_hihat[counter] == 1) {
    playSdWav1.play("hihat.wav");
  }

  ///////////////////contatore per clap////////////////////////
  if (clap > 0) {
    sequencer_clap[counter] = 1;
  }

  if (sequencer_clap[counter] == 1) {
    playSdWav1.play("clap.wav");
  }


  if (reset1 > 0) {
    for (int a = 0; a < 8; a++) {
      sequencer_kick[a] = 0;
      sequencer_snare[a] = 0;
      sequencer_hihat[a] = 0;
      sequencer_clap[a] = 0;
    }

  }
  if (undo == 1 && clap == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_clap[a] = 0;
    }
  }
  if (undo == 1 && kick == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_kick[a] = 0;
    }
  }
  if (undo == 1 && snare == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_snare[a] = 0;
    }
  }
  if (undo == 1 && hihat == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_hihat[a] = 0;
    }
  }


  delayMicroseconds(map(artboard.pot(0), 0, 1023, 180000, 120000));

}
