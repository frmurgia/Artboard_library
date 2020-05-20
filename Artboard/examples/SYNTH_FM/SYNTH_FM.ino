 
 
 
 /* 
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
             ART-BOARD
     Prototyping board for atist
     
             POLY SYNTH 

            
by frmurgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>


 
AudioSynthWaveformDc     lfoenvelope;    //xy=765,1179
AudioSynthWaveform       lfo;            //xy=853,1385
AudioMixer4              mixer1;         //xy=896,1240
AudioAnalyzePeak         peak1;          //xy=1125,1103
AudioSynthWaveform       voice12b; //xy=1307,3266
AudioSynthNoiseWhite     voice12n; //xy=1307,3301
AudioSynthWaveform       voice12a; //xy=1309,3228
AudioSynthWaveform       voice11b; //xy=1322,2998
AudioSynthNoiseWhite     voice11n; //xy=1322,3033
AudioSynthWaveform       voice11a; //xy=1324,2960
AudioSynthWaveform       voice10b; //xy=1332,2716
AudioSynthNoiseWhite     voice10n; //xy=1332,2753
AudioSynthWaveform       voice10a; //xy=1334,2678
AudioSynthWaveform       voice9b; //xy=1336,2415
AudioSynthNoiseWhite     voice9n; //xy=1336,2450
AudioSynthWaveform       voice9a; //xy=1338,2377
AudioSynthWaveform       voice8b;        //xy=1361,2154
AudioSynthWaveform       voice8a;        //xy=1363,2116
AudioSynthNoiseWhite     voice8n;        //xy=1371,2181
AudioSynthWaveform       voice4a;        //xy=1382,1138
AudioSynthWaveform       voice4b;        //xy=1383,1176
AudioSynthNoiseWhite     voice4n;        //xy=1383,1211
AudioSynthWaveform       voice5b;        //xy=1384,1432
AudioSynthNoiseWhite     voice5n;        //xy=1384,1467
AudioSynthWaveform       voice5a;        //xy=1389,1389
AudioSynthWaveform       voice7b;        //xy=1393,1923
AudioSynthNoiseWhite     voice7n;        //xy=1393,1958
AudioSynthWaveform       voice6b;        //xy=1396,1686
AudioSynthNoiseWhite     voice6n;        //xy=1396,1721
AudioSynthWaveform       voice6a;        //xy=1398,1648
AudioSynthWaveform       voice7a;        //xy=1398,1880
AudioSynthWaveform       voice3b;        //xy=1404,928
AudioSynthNoiseWhite     voice3n;        //xy=1404,963
AudioSynthWaveform       voice3a;        //xy=1409,885
AudioSynthWaveform       voice1b;        //xy=1434,462
AudioSynthNoiseWhite     voice1n;        //xy=1437,506
AudioSynthWaveform       voice2b;        //xy=1437,696
AudioSynthNoiseWhite     voice2n;        //xy=1437,731
AudioSynthWaveform       voice1a;        //xy=1439,419
AudioSynthWaveform       voice2a;        //xy=1439,658
AudioSynthWaveformDc     voice12filterenv; //xy=1432,3403
AudioSynthWaveformDc     voice11filterenv; //xy=1447,3135
AudioSynthWaveformDc     voice10filterenv; //xy=1457,2853
AudioSynthWaveformDc     voice9filterenv; //xy=1461,2552
AudioSynthWaveformDc     voice8filterenv; //xy=1489,2300
AudioMixer4              voice12mix; //xy=1488,3271
AudioSynthWaveformDc     voice12env; //xy=1494,3333
AudioMixer4              voice8mix; //xy=1502,2169
AudioSynthWaveformDc     voice8env;      //xy=1503,2239
AudioMixer4              voice11mix; //xy=1502,3003
AudioSynthWaveformDc     voice4filterenv; //xy=1511,1322
AudioSynthWaveformDc     voice5filterenv; //xy=1512,1578
AudioSynthWaveformDc     voice11env; //xy=1509,3065
AudioMixer4              voice10mix;  //xy=1512,2721
AudioMixer4              voice9mix; //xy=1516,2420
AudioSynthWaveformDc     voice7filterenv; //xy=1521,2069
AudioSynthWaveformDc     voice4env;      //xy=1525,1261
AudioSynthWaveformDc     voice10env; //xy=1519,2783
AudioSynthWaveformDc     voice6filterenv; //xy=1524,1832
AudioSynthWaveformDc     voice5env;      //xy=1526,1517
AudioMixer4              voice4mix;      //xy=1528,1196
AudioSynthWaveformDc     voice9env; //xy=1523,2482
AudioMixer4              voice5mix;      //xy=1529,1452
AudioSynthWaveformDc     voice3filterenv; //xy=1532,1074
AudioSynthWaveformDc     voice7env;      //xy=1535,2008
AudioSynthWaveformDc     voice6env;      //xy=1538,1771
AudioMixer4              voice7mix;      //xy=1538,1943
AudioMixer4              voice6mix;      //xy=1541,1706
AudioSynthWaveformDc     voice3env;      //xy=1546,1013
AudioMixer4              voice3mix;      //xy=1549,948
AudioSynthWaveformDc     voice1filterenv; //xy=1563,598
AudioSynthWaveformDc     voice2filterenv; //xy=1565,842
AudioMixer4              voice1mix;      //xy=1579,482
AudioSynthWaveformDc     voice2env;      //xy=1579,781
AudioSynthWaveformDc     voice1env;      //xy=1580,547
AudioMixer4              voice2mix;      //xy=1582,716
AudioMixer4              voice12filtermodmixer; //xy=1662,3425
AudioEffectMultiply      voice8multiply; //xy=1670,2212
AudioEffectMultiply      voice12multiply; //xy=1674,3316
AudioMixer4              voice8filtermodmixer; //xy=1680,2328
AudioMixer4              voice11filtermodmixer; //xy=1677,3157
AudioEffectMultiply      voice4multiply; //xy=1692,1234
AudioMixer4              voice10filtermodmixer; //xy=1687,2875
AudioEffectMultiply      voice5multiply; //xy=1693,1490
AudioEffectMultiply      voice11multiply; //xy=1689,3048
AudioMixer4              voice9filtermodmixer; //xy=1691,2574
AudioMixer4              voice4filtermodmixer; //xy=1702,1350
AudioEffectMultiply      voice7multiply; //xy=1702,1981
AudioEffectMultiply      voice10multiply;  //xy=1699,2766
AudioEffectMultiply      voice6multiply; //xy=1705,1744
AudioEffectMultiply      voice9multiply; //xy=1703,2465
AudioMixer4              voice5filtermodmixer; //xy=1710,1600
AudioEffectMultiply      voice3multiply; //xy=1713,986
AudioMixer4              voice6filtermodmixer; //xy=1715,1860
AudioMixer4              voice7filtermodmixer; //xy=1719,2091
AudioMixer4              voice3filtermodmixer; //xy=1730,1096
AudioEffectMultiply      voice1multiply; //xy=1743,520
AudioEffectMultiply      voice2multiply; //xy=1746,754
AudioMixer4              voice2filtermodmixer; //xy=1756,870
AudioMixer4              voice1filtermodmixer; //xy=1760,630
AudioFilterStateVariable voice8filter;   //xy=1853,2235
AudioFilterStateVariable voice5filter;   //xy=1873,1534
AudioFilterStateVariable voice4filter;   //xy=1875,1257
AudioFilterStateVariable voice12filter; //xy=1873,3332
AudioFilterStateVariable voice7filter;   //xy=1882,2025
AudioFilterStateVariable voice6filter;   //xy=1888,1767
AudioFilterStateVariable voice3filter;   //xy=1893,1030
AudioFilterStateVariable voice11filter;  //xy=1888,3064
AudioFilterStateVariable voice10filter; //xy=1898,2782
AudioFilterStateVariable voice9filter;  //xy=1902,2481
AudioFilterStateVariable voice2filter;   //xy=1929,777
AudioFilterStateVariable voice1filter;   //xy=1946,572
AudioMixer4              new4premix; //xy=2195,2452
AudioMixer4              last4premix;    //xy=2353,1507
AudioMixer4              first4premix;   //xy=2354,1423
AudioFilterStateVariable delayFilter;    //xy=2539,1609
AudioEffectDelay         delay1;         //xy=2745,1816
AudioMixer4              mainOutMixer;   //xy=2874,1500
AudioEffectFreeverbStereo freeverbs1;     //xy=3214,1475
AudioOutputAnalogStereo  dacs1;          //xy=3311,1255
AudioConnection          patchCord1(lfoenvelope, 0, mixer1, 0);
AudioConnection          patchCord2(lfo, 0, voice1filtermodmixer, 1);
AudioConnection          patchCord3(lfo, 0, voice2filtermodmixer, 1);
AudioConnection          patchCord4(lfo, 0, voice3filtermodmixer, 1);
AudioConnection          patchCord5(lfo, 0, voice4filtermodmixer, 1);
AudioConnection          patchCord6(lfo, 0, voice5filtermodmixer, 1);
AudioConnection          patchCord7(lfo, 0, voice6filtermodmixer, 1);
AudioConnection          patchCord8(lfo, 0, voice7filtermodmixer, 1);
AudioConnection          patchCord9(lfo, 0, voice8filtermodmixer, 1);
AudioConnection          patchCord10(lfo, 0, mixer1, 1);
AudioConnection          patchCord11(lfo, 0, voice9filtermodmixer, 1);
AudioConnection          patchCord12(lfo, 0, voice10filtermodmixer, 1);
AudioConnection          patchCord13(lfo, 0, voice11filtermodmixer, 1);
AudioConnection          patchCord14(lfo, 0, voice12filtermodmixer, 1);
AudioConnection          patchCord15(mixer1, peak1);
AudioConnection          patchCord16(voice12b, 0, voice12mix, 1);
AudioConnection          patchCord17(voice12n, 0, voice12mix, 2);
AudioConnection          patchCord18(voice12a, 0, voice12mix, 0);
AudioConnection          patchCord19(voice11b, 0, voice11mix, 1);
AudioConnection          patchCord20(voice11n, 0, voice11mix, 2);
AudioConnection          patchCord21(voice11a, 0, voice11mix, 0);
AudioConnection          patchCord22(voice10b, 0, voice10mix, 1);
AudioConnection          patchCord23(voice10n, 0, voice10mix, 2);
AudioConnection          patchCord24(voice10a, 0, voice10mix, 0);
AudioConnection          patchCord25(voice9b, 0, voice9mix, 1);
AudioConnection          patchCord26(voice9n, 0, voice9mix, 2);
AudioConnection          patchCord27(voice9a, 0, voice9mix, 0);
AudioConnection          patchCord28(voice8b, 0, voice8mix, 1);
AudioConnection          patchCord29(voice8a, 0, voice8mix, 0);
AudioConnection          patchCord30(voice8n, 0, voice8mix, 2);
AudioConnection          patchCord31(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord32(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord33(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord34(voice5b, 0, voice5mix, 1);
AudioConnection          patchCord35(voice5n, 0, voice5mix, 2);
AudioConnection          patchCord36(voice5a, 0, voice5mix, 0);
AudioConnection          patchCord37(voice7b, 0, voice7mix, 1);
AudioConnection          patchCord38(voice7n, 0, voice7mix, 2);
AudioConnection          patchCord39(voice6b, 0, voice6mix, 1);
AudioConnection          patchCord40(voice6n, 0, voice6mix, 2);
AudioConnection          patchCord41(voice6a, 0, voice6mix, 0);
AudioConnection          patchCord42(voice7a, 0, voice7mix, 0);
AudioConnection          patchCord43(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord44(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord45(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord46(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord47(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord48(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord49(voice2n, 0, voice2mix, 3);
AudioConnection          patchCord50(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord51(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord52(voice12filterenv, 0, voice12filtermodmixer, 0);
AudioConnection          patchCord53(voice11filterenv, 0, voice11filtermodmixer, 0);
AudioConnection          patchCord54(voice10filterenv, 0, voice10filtermodmixer, 0);
AudioConnection          patchCord55(voice9filterenv, 0, voice9filtermodmixer, 0);
AudioConnection          patchCord56(voice8filterenv, 0, voice8filtermodmixer, 0);
AudioConnection          patchCord57(voice12mix, 0, voice12multiply, 0);
AudioConnection          patchCord58(voice12env, 0, voice12multiply, 1);
AudioConnection          patchCord59(voice8mix, 0, voice8multiply, 0);
AudioConnection          patchCord60(voice8env, 0, voice8multiply, 1);
AudioConnection          patchCord61(voice11mix, 0, voice11multiply, 0);
AudioConnection          patchCord62(voice4filterenv, 0, voice4filtermodmixer, 0);
AudioConnection          patchCord63(voice5filterenv, 0, voice5filtermodmixer, 0);
AudioConnection          patchCord64(voice11env, 0, voice11multiply, 1);
AudioConnection          patchCord65(voice10mix, 0, voice10multiply, 0);
AudioConnection          patchCord66(voice9mix, 0, voice9multiply, 0);
AudioConnection          patchCord67(voice7filterenv, 0, voice7filtermodmixer, 0);
AudioConnection          patchCord68(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord69(voice10env, 0, voice10multiply, 1);
AudioConnection          patchCord70(voice6filterenv, 0, voice6filtermodmixer, 0);
AudioConnection          patchCord71(voice5env, 0, voice5multiply, 1);
AudioConnection          patchCord72(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord73(voice9env, 0, voice9multiply, 1);
AudioConnection          patchCord74(voice5mix, 0, voice5multiply, 0);
AudioConnection          patchCord75(voice3filterenv, 0, voice3filtermodmixer, 0);
AudioConnection          patchCord76(voice7env, 0, voice7multiply, 1);
AudioConnection          patchCord77(voice6env, 0, voice6multiply, 1);
AudioConnection          patchCord78(voice7mix, 0, voice7multiply, 0);
AudioConnection          patchCord79(voice6mix, 0, voice6multiply, 0);
AudioConnection          patchCord80(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord81(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord82(voice1filterenv, 0, voice1filtermodmixer, 0);
AudioConnection          patchCord83(voice2filterenv, 0, voice2filtermodmixer, 0);
AudioConnection          patchCord84(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord85(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord86(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord87(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord88(voice12filtermodmixer, 0, voice12filter, 1);
AudioConnection          patchCord89(voice8multiply, 0, voice8filter, 0);
AudioConnection          patchCord90(voice12multiply, 0, voice12filter, 0);
AudioConnection          patchCord91(voice8filtermodmixer, 0, voice8filter, 1);
AudioConnection          patchCord92(voice11filtermodmixer, 0, voice11filter, 1);
AudioConnection          patchCord93(voice4multiply, 0, voice4filter, 0);
AudioConnection          patchCord94(voice10filtermodmixer, 0, voice10filter, 1);
AudioConnection          patchCord95(voice5multiply, 0, voice5filter, 0);
AudioConnection          patchCord96(voice11multiply, 0, voice11filter, 0);
AudioConnection          patchCord97(voice9filtermodmixer, 0, voice9filter, 1);
AudioConnection          patchCord98(voice4filtermodmixer, 0, voice4filter, 1);
AudioConnection          patchCord99(voice7multiply, 0, voice7filter, 0);
AudioConnection          patchCord100(voice10multiply, 0, voice10filter, 0);
AudioConnection          patchCord101(voice6multiply, 0, voice6filter, 0);
AudioConnection          patchCord102(voice9multiply, 0, voice9filter, 0);
AudioConnection          patchCord103(voice5filtermodmixer, 0, voice5filter, 1);
AudioConnection          patchCord104(voice3multiply, 0, voice3filter, 0);
AudioConnection          patchCord105(voice6filtermodmixer, 0, voice6filter, 1);
AudioConnection          patchCord106(voice7filtermodmixer, 0, voice7filter, 1);
AudioConnection          patchCord107(voice3filtermodmixer, 0, voice3filter, 1);
AudioConnection          patchCord108(voice1multiply, 0, voice1filter, 0);
AudioConnection          patchCord109(voice2multiply, 0, voice2filter, 0);
AudioConnection          patchCord110(voice2filtermodmixer, 0, voice2filter, 1);
AudioConnection          patchCord111(voice1filtermodmixer, 0, voice1filter, 1);
AudioConnection          patchCord112(voice8filter, 0, last4premix, 3);
AudioConnection          patchCord113(voice5filter, 0, last4premix, 0);
AudioConnection          patchCord114(voice4filter, 0, first4premix, 3);
AudioConnection          patchCord115(voice12filter, 0, new4premix, 3);
AudioConnection          patchCord116(voice7filter, 0, last4premix, 2);
AudioConnection          patchCord117(voice6filter, 0, last4premix, 1);
AudioConnection          patchCord118(voice3filter, 0, first4premix, 2);
AudioConnection          patchCord119(voice11filter, 0, new4premix, 2);
AudioConnection          patchCord120(voice10filter, 0, new4premix, 1);
AudioConnection          patchCord121(voice9filter, 0, new4premix, 0);
AudioConnection          patchCord122(voice2filter, 0, first4premix, 1);
AudioConnection          patchCord123(voice1filter, 0, first4premix, 0);
AudioConnection          patchCord124(new4premix, 0, mainOutMixer, 2);
AudioConnection          patchCord125(last4premix, 0, mainOutMixer, 1);
AudioConnection          patchCord126(first4premix, 0, mainOutMixer, 0);
AudioConnection          patchCord127(delayFilter, 0, mainOutMixer, 3);
AudioConnection          patchCord128(delay1, 0, delayFilter, 0);
AudioConnection          patchCord129(mainOutMixer, delay1);
AudioConnection          patchCord130(mainOutMixer, freeverbs1);
AudioConnection          patchCord131(freeverbs1, 0, dacs1, 0);
AudioConnection          patchCord132(freeverbs1, 1, dacs1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2837,1267
// GUItool: end automatically generated code


// Mux touch
int s4 = 12;
int s5 = 24;
int s6 = 33;
int s7 = 34;
int T_pin = 29;


//LEd 13
int led=13;
 //pots
  int pot1= analogRead(A0);
  int pot2= analogRead(A1);
  int pot3= analogRead(A2);
  int pot4= analogRead(A3);
  int pot5= analogRead(A12);
  int pot6= analogRead(A13);
            
 //Note 
 float DO = 261.6/4;
 float DOd = 277.2/4;
 float RE = 293.7/4;
 float REd = 311.1/4;
 float MI = 329.6/4;
 float FA = 349.2/4;
 float FAd = 370/4;
 float SOL = 392/4;
 float SOLd = 415.3/4;
 float LA = 440/4;
 float LAd = 466.2/4; 
 float SI = (246.95)/4;

int btnState[12];
int prevBtnState[12];

//synth
float mainVolume;
float vcoOneLevel;
float vcoTwoLevel;
int vcoOneOct;
int vcoTwoOct;
int octArray[6] = {1,1,2,4,8,16};
float deTune;
int waveShapeOneIndex;
int waveShapeTwoIndex;
int lfoWaveShapeIndex;
int octOneIndex;
int octTwoIndex;
//WaveShapes
short waveShapes[4] = {
  WAVEFORM_SINE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SQUARE,
  WAVEFORM_PULSE,
};
bool voiceBPulse;
float tempDetuneMod;
float deTuneLfo;
//LFO WaveShapes
short lfoWaveShapes[5] = {
  WAVEFORM_SINE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_SQUARE,
  WAVEFORM_SAMPLE_HOLD,
};
//ADSR
int attackTime;
int decayTime;
float sustainLevel;
int releaseTime;
//Filter ADSR
int attackTimeFilter;
int decayTimeFilter;
float sustainLevelFilter;
int releaseTimeFilter;
 //Note Timing
bool noteTrigFlag[12];
unsigned long attackWait[12];
bool firstRunRead;




void setup() {
  AudioMemory(512);
  Serial.begin(9600);

//Mux 
  pinMode(s4, OUTPUT); 
  pinMode(s5, OUTPUT); 
  pinMode(s6, OUTPUT); 
  pinMode(s7, OUTPUT); 
  pinMode(T_pin, INPUT);

  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
 pinMode(led, OUTPUT);
  //mix 0-4
  first4premix.gain(0, .3);
  first4premix.gain(1, .3);
  first4premix.gain(2, .3);
  first4premix.gain(3, .3);
  //mix 5-8
  last4premix.gain(0, .3);
  last4premix.gain(1, .3);
  last4premix.gain(2, .3);
  last4premix.gain(3, .3);
  //mix 9-12
  new4premix.gain(0, .3);
  new4premix.gain(1, .3);
  new4premix.gain(2, .3);
  new4premix.gain(3, .3);
  
  //Voice 1
  voice1a.begin(.3,DO,WAVEFORM_SINE);
  voice1b.begin(.3,DO,WAVEFORM_SAWTOOTH);
  //Voice 2
  voice2a.begin(.3,DOd,WAVEFORM_SINE);
  voice2b.begin(.3,DOd,WAVEFORM_SAWTOOTH);
  //Voice 3
  voice3a.begin(.3,RE,WAVEFORM_SINE);
  voice3b.begin(.3,RE,WAVEFORM_SAWTOOTH);
  //Voice 4
  voice4a.begin(.3,REd,WAVEFORM_SINE);
  voice4b.begin(.3,REd,WAVEFORM_SAWTOOTH);
  //Voice 5
  voice5a.begin(.3,MI,WAVEFORM_SINE);
  voice5b.begin(.3,MI,WAVEFORM_SAWTOOTH);
  //Voice 6
  voice6a.begin(.3,FA,WAVEFORM_SINE);
  voice6b.begin(.3,FA,WAVEFORM_SAWTOOTH);
  //Voice 7
  voice7a.begin(.3,FAd,WAVEFORM_SINE);
  voice7b.begin(.3,FAd,WAVEFORM_SAWTOOTH);
  //Voice 8
    voice8a.begin(.3,SOL,WAVEFORM_SINE);
  voice8b.begin(.3,SOL,WAVEFORM_SAWTOOTH);
  //Voice 9
  voice9a.begin(.3,SOLd,WAVEFORM_SINE);
  voice9b.begin(.3,SOLd,WAVEFORM_SAWTOOTH);
  //Voice 10
  voice10a.begin(.3,LA,WAVEFORM_SINE);
  voice10b.begin(.3,LA,WAVEFORM_SAWTOOTH);
  //Voice 11
  voice11a.begin(.3,LAd,WAVEFORM_SINE);
  voice11b.begin(.3,LAd,WAVEFORM_SAWTOOTH);
  //Voice 12
  voice12a.begin(.3,SI,WAVEFORM_SINE);
  voice12b.begin(.3,SI,WAVEFORM_SINE);
 
 //delay 
  delayFilter.frequency(3000);
  delayFilter.resonance(1);
  delay1.delay(0,0);
  mainOutMixer.gain(3,0);

  //LFO
  lfo.begin(1,3,WAVEFORM_SINE);

  vcoOneOct = 1;
  vcoTwoOct = 1;
  deTune = 1;
  mainOutMixer.gain(0,1);
  lfoenvelope.amplitude(1);

  firstRunRead = true;

 
  for(int i=0; i<8; i++){
    //audio startup
    if(i < 4){
      voice1env.amplitude(.1,1);
      voice1a.frequency(DO*i);
      voice1b.frequency(DO*2+5);
      delay(200);
      voice1env.amplitude(0,0);
    }
   }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int getSmooth(int pin){
  int vals[5]; //array che stora 5 letture analog.
  for(int i = 0; i < 5; i++){
    vals[i] = analogRead(pin); 
  }
  float smooth = (vals[0] + vals[1] + vals[2] + vals[3] + vals[4]) / 5;
  return smooth;
}


//Ciclo Mux 2
int readMux_2(int channel){
  int controlPin_2[] = {s4, s5, s6, s7};
  int muxChannel_2[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };
  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin_2[i], muxChannel_2[channel][i]);
  }
  //read the value at the SIG pin
  int val_2 = (touchRead(T_pin));
   //return the value
  return val_2;
   
  }

void loop() {
 
   int pot1= map(analogRead(A0),0,1023,1023,-2);
   int pot2= map(analogRead(A1),0,1023,1023,5); // filtro valore minimo della freq del filtro
   int pot3= map(analogRead(A2),0,1023,1023,-2); //ottava
   int pot4= map(analogRead(A3),0,1023,1023,-2);
   int pot5= map(analogRead(A12),0,1023,1023,-2); //attacco
   int pot6= map(analogRead(A13),0,1023,1023,-2);//relase


 
  //notes

  for(int i=0; i<11; i++){
    if(i == 0){
  voice1a.frequency((DO)*vcoOneOct);
      voice1b.frequency(((DO*vcoTwoOct) * deTune) * deTuneLfo);
   
    }
    if(i == 1){
      voice2a.frequency((DOd)*vcoOneOct);
      voice2b.frequency(((DOd*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 2){
      voice3a.frequency((RE)*vcoOneOct);
      voice3b.frequency(((RE*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 3){
      voice4a.frequency((REd)*vcoOneOct);
      voice4b.frequency(((REd*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 4){
      voice5a.frequency((MI)*vcoOneOct);
      voice5b.frequency(((MI*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 5){
      voice6a.frequency((FA)*vcoOneOct);
      voice6b.frequency(((FA*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 6){
      voice7a.frequency((FAd)*vcoOneOct);
      voice7b.frequency(((FAd*vcoTwoOct) * deTune) * deTuneLfo);
    }
    if(i == 7){
      voice8a.frequency((SOL)*vcoOneOct);
      voice8b.frequency(((SOL*vcoTwoOct) * deTune) * deTuneLfo);
    }
        if(i == 8){
      voice9a.frequency((SOLd)*vcoOneOct);
      voice9b.frequency(((SOLd*vcoTwoOct) * deTune) * deTuneLfo);
      //voice9b.frequency(((noteFreq[keyIndex][i]/4*vcoTwoOct) * deTune) * deTuneLfo);
    }
    
 if(i == 9){
      voice10a.frequency((LA)*vcoOneOct);
      voice10b.frequency(((LA*vcoTwoOct) * deTune) * deTuneLfo);
    }
     if(i ==10){
      voice11a.frequency((LAd)*vcoOneOct);
      voice11b.frequency(((LAd*vcoTwoOct) * deTune) * deTuneLfo);
    }
     if(i == 11){
      voice12a.frequency((SI)*vcoOneOct);
      voice12b.frequency(((SI *vcoTwoOct) * deTune) * deTuneLfo);
    }

// voice 1
  if (readMux_2(0)>=7000){
    
 digitalWrite(led,HIGH);
          voice1env.amplitude(1,attackTime);
          voice1filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice1env.amplitude(sustainLevel,decayTime);
        }
        }
         else{
          noteTrigFlag[i] = false;
          voice1env.amplitude(0,releaseTime);
          voice1filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice1env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice1filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

// voice 2
  if (readMux_2(1)>=7000){
    digitalWrite(led,HIGH);
          voice2env.amplitude(1,attackTime);
          voice2filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice1env.amplitude(sustainLevel,decayTime);
        }
        }
         else{
          noteTrigFlag[i] = false;
          voice2env.amplitude(0,releaseTime);
          voice2filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice2env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice2filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

// voice 3
 
  if (readMux_2(2)>=7000){
    digitalWrite(led,HIGH);
          voice3env.amplitude(1,attackTime);
          voice3filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice3env.amplitude(sustainLevel,decayTime);
        }
        }
         else{
              digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice3env.amplitude(0,releaseTime);
          voice3filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice3env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice3filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

// voice 4            
  if (readMux_2(3)>=7000){
    digitalWrite(led,HIGH);
          voice4env.amplitude(1,attackTime);
          voice4filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice4env.amplitude(sustainLevel,decayTime);
        }
        }
 
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice4env.amplitude(0,releaseTime);
          voice4filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice4env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice4filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
  
  // voice 5
  if (readMux_2(4)>=5100){
    digitalWrite(led,HIGH);
          voice5env.amplitude(1,attackTime);
          voice5filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice5env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice5env.amplitude(0,releaseTime);
          voice5filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice5env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice5filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

    // voice 6
  if (readMux_2(5)>=7000){
    digitalWrite(led,HIGH);
          voice6env.amplitude(1,attackTime);
          voice6filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice6env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice6env.amplitude(0,releaseTime);
          voice6filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice6env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice6filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

    
 // voice 7
  if (readMux_2(6)>=7000){
    digitalWrite(led,HIGH);
          voice7env.amplitude(1,attackTime);
          voice7filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice7env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice7env.amplitude(0,releaseTime);
          voice7filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice7env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice7filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

    // voice 8
  if (readMux_2(7)>=7000){
    digitalWrite(led,HIGH);
          voice8env.amplitude(1,attackTime);
          voice8filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice7env.amplitude(sustainLevel,decayTime);
        }
        }
         else{
          noteTrigFlag[i] = false;
          voice8env.amplitude(0,releaseTime);
          voice8filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice8env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice8filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

       // voice 9
  if (readMux_2(8)>=7000){
    
    digitalWrite(led,HIGH);
          voice9env.amplitude(1,attackTime);
          voice9filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice9env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice9env.amplitude(0,releaseTime);
          voice9filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice9env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice9filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
        
           // voice 10
  if (readMux_2(9)>=7000){
    digitalWrite(led,HIGH);
          voice10env.amplitude(1,attackTime);
          voice10filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice10env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice10env.amplitude(0,releaseTime);
          voice10filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice10env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice10filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }

           // voice 11
  if (readMux_2(10)>=7000){
    digitalWrite(led,HIGH);
          voice11env.amplitude(1,attackTime);
          voice11filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice11env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice11env.amplitude(0,releaseTime);
          voice11filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice11env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice11filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
        
           // voice 12
  if (readMux_2(11)>=7000){
    digitalWrite(led,HIGH);
          voice12env.amplitude(1,attackTime);
          voice12filterenv.amplitude(1,attackTimeFilter);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
            if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice12env.amplitude(sustainLevel,decayTime);
        }
        }
         else{ digitalWrite(led,LOW);
          noteTrigFlag[i] = false;
          voice12env.amplitude(0,releaseTime);
          voice12filterenv.amplitude(-1, releaseTimeFilter);
        }
          if(millis() - attackWait[i] > attackTime && noteTrigFlag[i]){
          voice12env.amplitude(sustainLevel,decayTime);
        }
        if(millis() - attackWait[i] > attackTimeFilter && noteTrigFlag[i]){
          voice12filterenv.amplitude(sustainLevelFilter,decayTimeFilter);
        }
  }


  //knobs


      //vcoOne
      
  
        //oct
        octOneIndex = (pot1/204)+1;
        if(octOneIndex < 6){
          vcoOneOct = octArray[octOneIndex];
        }
      

      
        //shape
//        waveShapeOneIndex = 100/255;
//        if(waveShapeOneIndex < 4){
//          voice1a.begin(waveShapes[waveShapeOneIndex]);
//          voice2a.begin(waveShapes[waveShapeOneIndex]);
//          voice3a.begin(waveShapes[waveShapeOneIndex]);
//          voice4a.begin(waveShapes[waveShapeOneIndex]);
//          voice5a.begin(waveShapes[waveShapeOneIndex]);
//          voice6a.begin(waveShapes[waveShapeOneIndex]);
//          voice7a.begin(waveShapes[waveShapeOneIndex]);
//          voice8a.begin(waveShapes[waveShapeOneIndex]);
//        }

 
        vcoOneLevel = (511.5)/1023;
        vcoTwoLevel = 1 - (511.5)/1023;
        voice1mix.gain(1,vcoOneLevel);
        voice1mix.gain(0,vcoTwoLevel);
        voice2mix.gain(1,vcoOneLevel);
        voice2mix.gain(0,vcoTwoLevel);
        voice3mix.gain(1,vcoOneLevel);
        voice3mix.gain(0,vcoTwoLevel);  
        voice4mix.gain(1,vcoOneLevel); 
        voice4mix.gain(0,vcoTwoLevel); 
        voice5mix.gain(1,vcoOneLevel); 
        voice5mix.gain(0,vcoTwoLevel); 
        voice6mix.gain(1,vcoOneLevel); 
        voice6mix.gain(0,vcoTwoLevel); 
        voice7mix.gain(1,vcoOneLevel); 
        voice7mix.gain(0,vcoTwoLevel); 
        voice8mix.gain(1,vcoOneLevel); 
        voice8mix.gain(0,vcoTwoLevel); 
        voice9mix.gain(1,vcoOneLevel); 
        voice9mix.gain(0,vcoTwoLevel); 
        voice10mix.gain(1,vcoOneLevel); 
        voice10mix.gain(0,vcoTwoLevel); 
        voice11mix.gain(1,vcoOneLevel); 
        voice11mix.gain(0,vcoTwoLevel); 
        voice12mix.gain(1,vcoOneLevel); 
        voice12mix.gain(0,vcoTwoLevel); 
      //vcoTwo
      
  
        //oct
        octTwoIndex = (pot1/204)+1;
 
        if(octTwoIndex < 6){ 
          vcoTwoOct = octArray[octTwoIndex];
        }
     
     
  
//        //shape
//        waveShapeTwoIndex = 511.5/255;
//        if(waveShapeTwoIndex < 4){
//          if(waveShapeTwoIndex == 3){
//            voiceBPulse = true;
//          }else{
//            voiceBPulse = false;
//          }          
//          voice1b.begin(waveShapes[waveShapeTwoIndex]);
//          voice2b.begin(waveShapes[waveShapeTwoIndex]);
//          voice3b.begin(waveShapes[waveShapeTwoIndex]);
//          voice4b.begin(waveShapes[waveShapeTwoIndex]);
//          voice5b.begin(waveShapes[waveShapeTwoIndex]);
//          voice6b.begin(waveShapes[waveShapeTwoIndex]);
//          voice7b.begin(waveShapes[waveShapeTwoIndex]);
//          voice8b.begin(waveShapes[waveShapeTwoIndex]);
//        }
    
      
      
      //LFO
 
        //freq
        lfo.frequency(pot4/50);
 
 
        lfoWaveShapeIndex = 511.5/204.6;
        if(lfoWaveShapeIndex < 5){
          lfo.begin(lfoWaveShapes[lfoWaveShapeIndex]);
       
        } 
      
      
      //noise

        voice1n.amplitude(0.0013);
        voice2n.amplitude(0.0013);
        voice3n.amplitude(0.0013);
        voice4n.amplitude(0.0013);
        voice5n.amplitude(0.0013);
        voice6n.amplitude(0.0013);
        voice7n.amplitude(0.0013);
        voice8n.amplitude(0.0013);
        voice9n.amplitude(0.0013);
        voice10n.amplitude(0.0013);
        voice11n.amplitude(0.0013);
        voice12n.amplitude(0.0013);

      //Filter
 
        //frequency
        voice1filter.frequency(pot2*5);
        voice2filter.frequency(pot2*5);
        voice3filter.frequency(pot2*5);
        voice4filter.frequency(pot2*5);
        voice5filter.frequency(pot2*5);
        voice6filter.frequency(pot2*5);
        voice7filter.frequency(pot2*5);
        voice8filter.frequency(pot2*5);
        voice9filter.frequency(pot2*5);
        voice10filter.frequency(pot2*5);
        voice11filter.frequency(pot2*5);
        voice12filter.frequency(pot2*5);
 
        //resonance
        voice1filter.resonance((analogRead(A2)/204)+.9);
        voice2filter.resonance((analogRead(A2)/204)+.9);
        voice3filter.resonance((analogRead(A2)/204)+.9);
        voice4filter.resonance((analogRead(A2)/204)+.9);
        voice5filter.resonance((analogRead(A2)/204)+.9);
        voice6filter.resonance((analogRead(A2)/204)+.9);
        voice7filter.resonance((analogRead(A2)/204)+.9);
        voice8filter.resonance((analogRead(A2)/204)+.9);
        voice9filter.resonance((analogRead(A2)/204)+.9);
        voice10filter.resonance((analogRead(A2)/204)+.9);
        voice11filter.resonance((analogRead(A2)/204)+.9);
        voice12filter.resonance((analogRead(A2)/204)+.9);
/*

        //lfo Mod
        voice1filtermodmixer.gain(1,200/1023);
        voice2filtermodmixer.gain(1,200/1023);
        voice3filtermodmixer.gain(1,200/1023);
        voice4filtermodmixer.gain(1,200/1023);
        voice5filtermodmixer.gain(1,200/1023);
        voice6filtermodmixer.gain(1,200/1023);
        voice7filtermodmixer.gain(1,200/1023);
        voice8filtermodmixer.gain(1,200/1023);


 
        //env Mod
        voice1filtermodmixer.gain(0, 200/1023);
        voice2filtermodmixer.gain(0, 200/1023);
        voice3filtermodmixer.gain(0, 200/1023);
        voice4filtermodmixer.gain(0, 200/1023);
        voice5filtermodmixer.gain(0, 200/1023);
        voice6filtermodmixer.gain(0, 200/1023);
        voice7filtermodmixer.gain(0, 200/1023);
        voice8filtermodmixer.gain(0, 200/1023);
 
 */
 
    // Delay
      //time
      delay1.delay(0, pot3/4.4);

      //feedback
      mainOutMixer.gain(3,0.3);
  
      //reverb
      freeverbs1.roomsize(0.7); //roomsize
      freeverbs1.damping(0.3); //amount
       
  
  //ExtraAnalogIn
 
        //attack 
          attackTimeFilter = pot5*2;
          attackTime = pot5*4.4; 
          Serial.println(attackTime);
        //decay
          decayTime = 260;
          sustainLevel = 260/1023;
        //sustain
        //release
         releaseTime = pot6*4;

         
         
}
