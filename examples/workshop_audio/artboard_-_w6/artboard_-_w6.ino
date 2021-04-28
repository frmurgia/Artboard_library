/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: waveform + ottava completa + inviluppo (Attack and Release)+filtro+delay

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
AudioSynthWaveform       waveform4; //xy=289.75,562.25
AudioSynthWaveformDc     voice1env4;     //xy=291,594.0000228881836
AudioSynthWaveform       waveform9; //xy=295.75,1051.25
AudioSynthWaveformDc     voice1env9;     //xy=296,1087.0000214576721
AudioSynthWaveform       waveform8; //xy=297.75,936.25
AudioSynthWaveformDc     voice1env5;     //xy=299,722.0000467300415
AudioSynthWaveformDc     voice1env6;     //xy=299,806.0000467300415
AudioSynthWaveformDc     voice1env8;     //xy=299,970.0000162124634
AudioSynthWaveform       waveform5; //xy=300.75,689.25
AudioSynthWaveformDc     voice1env7;     //xy=300,882.9999856948853
AudioSynthWaveform       waveform6; //xy=300.75,774.25
AudioSynthWaveformDc     voice1env3;     //xy=302.00000762939453,502.0000009536743
AudioSynthWaveform       waveform7; //xy=301.75,850.25
AudioSynthWaveform       waveform3; //xy=303.75,471.25
AudioSynthWaveformDc     voice1env2;     //xy=306.00000762939453,426.0000162124634
AudioSynthWaveform       waveform1;      //xy=308.75,295.7499990463257
AudioSynthWaveform       waveform12; //xy=304.75,1310.25
AudioSynthWaveform       waveform2; //xy=309.75,390.75
AudioSynthWaveformDc     voice1env;      //xy=310,333.00000762939453
AudioSynthWaveform       waveform10;  //xy=306.75,1148.25
AudioSynthWaveformDc     voice1env12;    //xy=305.99999237060547,1344.0000524520874
AudioSynthWaveform       waveform11; //xy=307.75000762939453,1226.2500171661377
AudioSynthWaveformDc     voice1env10;    //xy=308,1180.9999904632568
AudioSynthWaveformDc     voice1env11;    //xy=309,1258.000051498413
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
AudioMixer4              mixer2;         //xy=844.0000419616699,732.9999847412109
AudioMixer4              mixer3;         //xy=853.0000114440918,829
AudioMixer4              mixer1;         //xy=862,354
AudioFilterStateVariable filter2; //xy=984.7500267028809,734.0000152587891
AudioFilterStateVariable filter1; //xy=989.7500114440918,357.00001525878906
AudioFilterStateVariable filter3; //xy=1008.7500305175781,836.0000152587891
AudioMixer4              mixer5;         //xy=1187.00004196167,532.9999942779541
AudioEffectDelay         delay1;         //xy=1194.75004196167,692.2500457763672
AudioOutputAnalogStereo  dacs0;          //xy=1651.000087738037,553.0000095367432
AudioConnection          patchCord1(waveform4, 0, multiply4, 0);
AudioConnection          patchCord2(voice1env4, 0, multiply4, 1);
AudioConnection          patchCord3(waveform9, 0, multiply9, 0);
AudioConnection          patchCord4(voice1env9, 0, multiply9, 1);
AudioConnection          patchCord5(waveform8, 0, multiply8, 0);
AudioConnection          patchCord6(voice1env5, 0, multiply5, 1);
AudioConnection          patchCord7(voice1env6, 0, multiply6, 1);
AudioConnection          patchCord8(voice1env8, 0, multiply8, 1);
AudioConnection          patchCord9(waveform5, 0, multiply5, 0);
AudioConnection          patchCord10(voice1env7, 0, multiply7, 1);
AudioConnection          patchCord11(waveform6, 0, multiply6, 0);
AudioConnection          patchCord12(voice1env3, 0, multiply3, 1);
AudioConnection          patchCord13(waveform7, 0, multiply7, 0);
AudioConnection          patchCord14(waveform3, 0, multiply3, 0);
AudioConnection          patchCord15(voice1env2, 0, multiply2, 1);
AudioConnection          patchCord16(waveform1, 0, multiply1, 0);
AudioConnection          patchCord17(waveform12, 0, multiply12, 0);
AudioConnection          patchCord18(waveform2, 0, multiply2, 0);
AudioConnection          patchCord19(voice1env, 0, multiply1, 1);
AudioConnection          patchCord20(waveform10, 0, multiply10, 0);
AudioConnection          patchCord21(voice1env12, 0, multiply12, 1);
AudioConnection          patchCord22(waveform11, 0, multiply11, 0);
AudioConnection          patchCord23(voice1env10, 0, multiply10, 1);
AudioConnection          patchCord24(voice1env11, 0, multiply11, 1);
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
AudioConnection          patchCord37(mixer2, 0, filter2, 0);
AudioConnection          patchCord38(mixer3, 0, filter3, 0);
AudioConnection          patchCord39(mixer1, 0, filter1, 0);
AudioConnection          patchCord40(filter2, 0, mixer5, 1);
AudioConnection          patchCord41(filter1, 0, mixer5, 0);
AudioConnection          patchCord42(filter3, 0, mixer5, 2);
AudioConnection          patchCord43(mixer5, delay1);
AudioConnection          patchCord44(mixer5, 0, dacs0, 0);
AudioConnection          patchCord45(mixer5, 0, dacs0, 1);
AudioConnection          patchCord46(delay1, 0, mixer5, 3);
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
float SI    = 493.9 ;

void setup() {
  pinMode(led, OUTPUT);
  AudioMemory(512);
  Serial.begin(9600);
  //volume del mixer


  //creiamo la nostra forma d'onda (ampiezza,frequenza,tipo di oscillatore
waveform1.begin(.3,DO,WAVEFORM_SAWTOOTH);
waveform2.begin(.3,DOd,WAVEFORM_SAWTOOTH);
waveform3.begin(.3,RE,WAVEFORM_SAWTOOTH);
waveform4.begin(.3,REd,WAVEFORM_SAWTOOTH);
waveform5.begin(.3,MI,WAVEFORM_SAWTOOTH);
waveform6.begin(.3,FA,WAVEFORM_SAWTOOTH);
waveform7.begin(.3,FAd,WAVEFORM_SAWTOOTH);
waveform8.begin(.3,SOL,WAVEFORM_SAWTOOTH);
waveform9.begin(.3,SOLd,WAVEFORM_SAWTOOTH);
waveform10.begin(.3,LA,WAVEFORM_SAWTOOTH);
waveform11.begin(.3,LAd,WAVEFORM_SAWTOOTH);
waveform12.begin(.3,SI,WAVEFORM_SAWTOOTH);
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

  mixer5.gain(0, .25);
  mixer5.gain(1, .25);
  mixer5.gain(2, .25);
  mixer5.gain(3, .25); //CANALE FEEDBACK DELAY



}

void loop() {

  int attackTime =  artboard.pot(0);
  int releaseTime = artboard.pot(1);
  filter1.frequency(artboard.pot(2)*2); //controlliamo la frequenza del filtro con il potenziometro 3
  filter2.frequency(artboard.pot(2)*2); //controlliamo la frequenza del filtro con il potenziometro 3
  filter3.frequency(artboard.pot(2)*2); //controlliamo la frequenza del filtro con il potenziometro 3
  //risonanza filtro
  filter1.resonance(artboard.pot(3)/202);
  filter2.resonance(artboard.pot(3)/202);
  filter3.resonance(artboard.pot(3)/202);
  //tempo di delay
  delay1.delay(0, artboard.pot(4));
  //feedback del delay
  float Delay=artboard.pot(5)/1200.0; // 0.0 - 0.84
  mixer5.gain(3,Delay); //il feedback è controllato dal volume del 4 canale del 5 mixer



  for (int i = 0; i < 12; i++) {

    if (artboard.touch(0) > 8000) {


      voice1env.amplitude(1, attackTime);

      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env.amplitude(0, releaseTime);

    }

    if (artboard.touch(1) > 8000) {
      voice1env2.amplitude(1, attackTime);

      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env2.amplitude(0, releaseTime);


    }



    if (artboard.touch(2) > 8000) {

      voice1env3.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env3.amplitude(0, releaseTime);


    }


    if (artboard.touch(3) > 8000) {

      voice1env4.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env4.amplitude(0, releaseTime);


    }


    if (artboard.touch(4) > 8000) {

      voice1env5.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env5.amplitude(0, releaseTime);


    }

    if (artboard.touch(5) > 8000) {

      voice1env6.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env6.amplitude(0, releaseTime);


    }

    if (artboard.touch(6) > 8000) {
      voice1env7.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env7.amplitude(0, releaseTime);


    }

    if (artboard.touch(7) > 8000) {
      voice1env8.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env8.amplitude(0, releaseTime);


    }
    if (artboard.touch(8) > 8000) {

      voice1env9.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env9.amplitude(0, releaseTime);


    }

    if (artboard.touch(9) > 8000) {


      voice1env10.amplitude(1, attackTime);
      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env10.amplitude(0, releaseTime);


    }

    if (artboard.touch(10) > 8000) {

      voice1env11.amplitude(1, attackTime);

      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env11.amplitude(0, releaseTime);


    }
    if (artboard.touch(11) > 8000) {

      voice1env12.amplitude(1, attackTime);

      noteTrigFlag[i] = true;

    }

    //altrimenti la nota non è piu suonata e parte il relase
    else {
      noteTrigFlag[i] = false;
      voice1env12.amplitude(0, releaseTime);


    }
  }//fine for

}//fine loop
