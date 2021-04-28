/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: sinusoide + nota + inviluppo (Attack and Release)

  by Daniele Murgia © 2019-20 MIT License
    sgtmurgia@gmail.com
  --------------------------------------
  <><><><><><><><><><><><><><><><><><><>

*/

/*  importiamo il setup da
     https://www.pjrc.com/teensy/gui
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h> // includiamo la libreria

Artboard artboard; // Istanza

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=387,395
AudioSynthWaveformDc     voice1env;            //xy=565.8730583190918,579.3650741577148
AudioEffectMultiply      multiply1;      //xy=602.2222442626953,449.99998664855957
AudioMixer4              mixer1;         //xy=797,417
AudioOutputAnalogStereo  dacs0;          //xy=1009,437
AudioConnection          patchCord1(sine1, 0, multiply1, 0);
AudioConnection          patchCord2(voice1env, 0, multiply1, 1);
AudioConnection          patchCord3(multiply1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, 0, dacs0, 0);
AudioConnection          patchCord5(mixer1, 0, dacs0, 1);
// GUItool: end automatically generated code

bool noteTrigFlag[12];// un array che contiene dodici valoro vuoti


//Note
float DO    = 261.6 ;
float DOd   = 277.2 ;
float RE    = 293.7 ;
float REd   = 311.1 ;
float MI    = 329.6 ;
float FA    = 349.2 ;
float FAd   = 370   ;
float SOL   = 392   ;
float SOLd  = 415.3 ;
float LA    = 440   ;
float LAd   = 466.2 ;
float SI    = 246.95;

void setup() {
  AudioMemory(512);
  Serial.begin(9600);
  //volume del mixer
  mixer1.gain(0, 0.7);
  //ampiezza sinusoide
  sine1.amplitude(1);

}

void loop() {

  // dichiariamo 2 nuove variabili dell'inviluppo: una per l'attacco e una per il release
  int attackTime = artboard.pot(0);
  int releaseTime = artboard.pot(1);

  if (artboard.touch(0) > 8000) {
    sine1.frequency(DO * 2);      //frequenza della nostra sinusoide
    voice1env.amplitude(1, attackTime);// (livello, millisecondi) voice1env è un segnale continuo utile per controllare dei
    //parametri di modulazione del segnale
  }

  //altrimenti la nota non è piu suonata e parte il relase
  else {
    voice1env.amplitude(0, releaseTime); // (livello, millisecondi)
  }

}
