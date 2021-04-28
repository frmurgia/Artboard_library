/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: sinusoide + ottava completa + inviluppo (Attack and Release)

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
AudioSynthWaveformDc     voice1env4;     //xy=291,594.0000228881836
AudioSynthWaveformDc     voice1env9;     //xy=296,1087.0000214576721
AudioSynthWaveformDc     voice1env5;     //xy=299,722.0000467300415
AudioSynthWaveformDc     voice1env6;     //xy=299,806.0000467300415
AudioSynthWaveformDc     voice1env8;     //xy=299,970.0000162124634
AudioSynthWaveformDc     voice1env7;     //xy=300,882.9999856948853
AudioSynthWaveformDc     voice1env3;     //xy=302.00000762939453,502.0000009536743
AudioSynthWaveformSine   sine4;          //xy=301.99999237060547,555.0000228881836
AudioSynthWaveformDc     voice1env2;     //xy=306.00000762939453,426.0000162124634
AudioSynthWaveformSine   sine8;          //xy=307.00000762939453,935.0000152587891
AudioSynthWaveformDc     voice1env;      //xy=310,333.00000762939453
AudioSynthWaveformDc     voice1env12;    //xy=305.99999237060547,1344.0000524520874
AudioSynthWaveformSine   sine7;          //xy=308.00000762939453,850
AudioSynthWaveformSine   sine9;          //xy=308.00000762939453,1053.000006198883
AudioSynthWaveformDc     voice1env10;    //xy=308,1180.9999904632568
AudioSynthWaveformSine   sine5;          //xy=309.99999237060547,683.9999856948853
AudioSynthWaveformSine   sine6;          //xy=310,769.0000457763672
AudioSynthWaveformDc     voice1env11;    //xy=309,1258.000051498413
AudioSynthWaveformSine   sine3;          //xy=313,467.0000238418579
AudioSynthWaveformSine   sine2;          //xy=314.00000762939453,393.0000009536743
AudioSynthWaveformSine   sine1; //xy=317.00000762939453,299.99999713897705
AudioSynthWaveformSine   sine10;         //xy=319.99999237060547,1146.000020980835
AudioSynthWaveformSine   sine11;         //xy=320.00000762939453,1227.0000066757202
AudioSynthWaveformSine   sine12;         //xy=321,1306.0000972747803
AudioEffectMultiply      multiply8;      //xy=513.9999961853027,941.0000314712524
AudioEffectMultiply      multiply4;      //xy=516.9999923706055,559.0000162124634
AudioEffectMultiply      multiply7;      //xy=519.000020980835,854.0000152587891
AudioEffectMultiply      multiply6;      //xy=520.0000057220459,772.9999856948853
AudioEffectMultiply      multiply3;      //xy=521.9999961853027,473.0000238418579
AudioEffectMultiply      multiply5;      //xy=523,688.0000314712524
AudioEffectMultiply      multiply2;      //xy=525.9999961853027,397.99999237060547
AudioEffectMultiply      multiply1;      //xy=528.0000228881836,305.0000352859497
AudioEffectMultiply      multiply10;     //xy=532.0000076293945,1150.0000219345093
AudioEffectMultiply      multiply12;     //xy=534.0000152587891,1313.000005722046
AudioEffectMultiply      multiply11;     //xy=535.0000228881836,1233.0000066757202
AudioEffectMultiply      multiply9;      //xy=537.0000190734863,1056.0000219345093
AudioMixer4              mixer3;         //xy=838.9999809265137,1100.000036239624
AudioMixer4              mixer2;         //xy=844.0000419616699,732.9999847412109
AudioMixer4              mixer1;         //xy=862,354
AudioMixer4              mixer5;         //xy=1173,533
AudioOutputAnalogStereo  dacs0;          //xy=1370,383
AudioConnection          patchCord1(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord2(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord3(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord4(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord5(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord6(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord7(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord8(sine4, 0, multiply4, 0);
AudioConnection          patchCord9(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord10(sine8, 0, multiply8, 0);
AudioConnection          patchCord11(voice1env, 0, multiply1, 1);
AudioConnection          patchCord12(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord13(sine7, 0, multiply7, 0);
AudioConnection          patchCord14(sine9, 0, multiply9, 0);
AudioConnection          patchCord15(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord16(sine5, 0, multiply5, 0);
AudioConnection          patchCord17(sine6, 0, multiply6, 0);
AudioConnection          patchCord18(voice1env11, 0, multiply11, 1);
AudioConnection          patchCord19(sine3, 0, multiply3, 0);
AudioConnection          patchCord20(sine2, 0, multiply2, 0);
AudioConnection          patchCord21(sine1, 0, multiply1, 0);
AudioConnection          patchCord22(sine10, 0, multiply10, 0);
AudioConnection          patchCord23(sine11, 0, multiply11, 0);
AudioConnection          patchCord24(sine12, 0, multiply12, 0);
AudioConnection          patchCord25(multiply8, 0, mixer2, 3);
AudioConnection          patchCord26(multiply4, 0, mixer1, 3);
AudioConnection          patchCord27(multiply7, 0, mixer2, 2);
AudioConnection          patchCord28(multiply6, 0, mixer2, 1);
AudioConnection          patchCord29(multiply3, 0, mixer1, 2);
AudioConnection          patchCord30(multiply5, 0, mixer2, 0);
AudioConnection          patchCord31(multiply2, 0, mixer1, 1);
AudioConnection          patchCord32(multiply1, 0, mixer1, 0);
AudioConnection          patchCord33(multiply10, 0, mixer3, 1);
AudioConnection          patchCord34(multiply12, 0, mixer3, 3);
AudioConnection          patchCord35(multiply11, 0, mixer3, 2);
AudioConnection          patchCord36(multiply9, 0, mixer3, 0);
AudioConnection          patchCord37(mixer3, 0, mixer5, 2);
AudioConnection          patchCord38(mixer2, 0, mixer5, 1);
AudioConnection          patchCord39(mixer1, 0, mixer5, 0);
AudioConnection          patchCord40(mixer5, 0, dacs0, 0);
AudioConnection          patchCord41(mixer5, 0, dacs0, 1);
// GUItool: end automatically generated code

bool noteTrigFlag[12];// un array che contiene dodici valoro vuoti
int led=28;

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
float SI    = 493.9;

void setup() {
  pinMode(led, OUTPUT);
  AudioMemory(512);
  Serial.begin(9600);
  //volume del mixer

  //ampiezza sinusoide
  sine1.amplitude(0.8);
  sine2.amplitude(0.8);
  sine3.amplitude(0.8);
  sine4.amplitude(0.8);
  sine5.amplitude(0.8);
  sine6.amplitude(0.8);
  sine7.amplitude(0.8);
  sine8.amplitude(0.8);
  sine9.amplitude(0.8);
  sine10.amplitude(0.8);
  sine11.amplitude(0.8);
  sine12.amplitude(0.8);

  //mix 0-4
  mixer1.gain(0, .25);
  mixer1.gain(1, .25);
  mixer1.gain(2, .25);
  mixer1.gain(3, .25);
  //mix 5-8
  mixer2.gain(0, .25);
  mixer2.gain(1, .25);
  mixer2.gain(2, .25);
  mixer2.gain(3, .25);
  //mix 9-12
  mixer3.gain(0, .25);
  mixer3.gain(1, .25);
  mixer3.gain(2, .25);
  mixer3.gain(3, .25);

  mixer5.gain(0, .33);
  mixer5.gain(1, .33);
  mixer5.gain(2, .33);

}

void loop() {

  int attackTime =  artboard.pot(0);
  int releaseTime = artboard.pot(1);

  for (int i = 0; i < 12; i++) {

    if (artboard.touch(0) > 8000) {

      sine1.frequency(DO * 2);      //frequenza della nostra sinusoide
      voice1env.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env.amplitude(0, releaseTime);
      digitalWrite(led, LOW);
    }

    if (artboard.touch(1) > 8000) {

      sine2.frequency(DOd * 2);      //frequenza della nostra sinusoide
      voice1env2.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env2.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }



    if (artboard.touch(2) > 8000) {

      sine3.frequency(RE * 2);      //frequenza della nostra sinusoide
      voice1env3.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env3.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }


    if (artboard.touch(3) > 8000) {

      sine4.frequency(REd * 2);      //frequenza della nostra sinusoide
      voice1env4.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env4.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }


    if (artboard.touch(4) > 8000) {

      sine5.frequency(MI * 2);      //frequenza della nostra sinusoide
      voice1env5.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env5.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }

    if (artboard.touch(5) > 8000) {

      sine6.frequency(FA * 2);      //frequenza della nostra sinusoide
      voice1env6.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env6.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }

    if (artboard.touch(6) > 8000) {

      sine7.frequency(FAd * 2);      //frequenza della nostra sinusoide
      voice1env7.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env7.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }

    if (artboard.touch(7) > 8000) {

      sine8.frequency(SOL * 2);      //frequenza della nostra sinusoide
      voice1env8.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env8.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }
    if (artboard.touch(8) > 8000) {

      sine9.frequency(SOLd * 2);      //frequenza della nostra sinusoide
      voice1env9.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env9.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }

    if (artboard.touch(9) > 8000) {

      sine10.frequency(LA * 2);      //frequenza della nostra sinusoide
      voice1env10.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env10.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }

    if (artboard.touch(10) > 8000) {

      sine11.frequency(LAd * 2);      //frequenza della nostra sinusoide
      voice1env11.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env11.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }
    if (artboard.touch(11) > 8000) {

      sine12.frequency(SI * 2);      //frequenza della nostra sinusoide
      voice1env12.amplitude(1, attackTime);
      digitalWrite(led, HIGH);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env12.amplitude(0, releaseTime);
      digitalWrite(led, LOW);

    }
  }//fine for

}//fine loop
