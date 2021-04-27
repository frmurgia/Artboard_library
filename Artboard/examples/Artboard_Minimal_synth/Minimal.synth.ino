/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Minimal Synth
Descrizione: con la funzione touch della libreria artboard  e il tool
grafico per la libreria audio teensy si crea un semplice sintettizatore monofonico formato da :

 oscillatore ad onda sinosuidale --> generatore di inviluppo --> filtro passa basso --> amplificatore

come controlli vengono utilizzati i potenziometri in questo modo:

D31 frequenza
D32 risonanza

D33 attack
d34 decay
D35 release

D38 Volume

 come uscite audio si utilzzano i dac (digital to analog converter) integrati nell teensy al pin A22 e A21 ,
 che nel Artboard corisspondono al uscita minijack stereo DAC0

by Jackeightgoods © 2020-21 MIT License
      otto@insiberia.net
--------------------------------------
<><><><><><><><><><><><><><><><><><><>
*/
#include <Artboard.h> // includiamo la libreria

Artboard artboard; // Istanza
//definisco le frequenze delle 12 note
float note[12] = {220 ,233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99 ,392.00, 440};
// array che raccoglie lo stato dei tasti
boolean key[12];
//variabile di controllo in cui si vede se un tasto è schiacciato
int state;
//esendo monofonico può suonare una nota alla volta e con queste variabile si memorizza il tasto più alto premotuo e il precedente tasto premuto.
int mn,mnb;
//includo la parte generata dal tool grafico fornito da  pjrc.com
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=227.75,281.75
AudioEffectEnvelope      envelope1;      //xy=365.75,279.75
AudioFilterStateVariable filter1;        //xy=500.75,287.75
AudioAmplifier           amp1;           //xy=653.75,287.75
AudioOutputAnalogStereo  dacs1;          //xy=848.75,281.75
AudioConnection          patchCord1(sine1, envelope1);
AudioConnection          patchCord2(envelope1, 0, filter1, 0);
AudioConnection          patchCord3(filter1, 0, amp1, 0);
AudioConnection          patchCord4(amp1, 0, dacs1, 0);
AudioConnection          patchCord5(amp1, 0, dacs1, 1);
AudioControlSGTL5000     audioShield;    //xy=121,171
// GUItool: end automatically generated code


void setup(){

  Serial.begin(115200);



AudioMemory(13);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //setto il volume audioshield a 1
  audioShield.volume(1);
  //imposto il volume del oscilattore ad 1
sine1.amplitude(1);

//inizzializzo lo stato dei tasti per non avere problemi
mn=0;
  mnb =-1;
}


void loop(){

  // leggo i valori dei potenziometri
float cut = analogRead(31);
float res= analogRead(32);

float at = analogRead(33);
float dec= analogRead(34);
float rel= analogRead(35);

float vol= analogRead(38);

// mappo e imposto i valori dei potenziometri
filter1.frequency(map(cut,0.00,1023.00,0,440));
filter1.resonance(map(res,0,1023,0.7,5));

envelope1.attack(map(at,0.00,1023.00,0.00,11880));
envelope1.decay(map(dec,0,1023,0,11880));
envelope1.release(map(rel,0,1023,0,11880 ));

amp1.gain(map(vol,0,1023,0,4));

  // guardo i tasti premuti sulla tasitera
  for( int i=0; i<12; i++){
      if (artboard.touch(i)> 20000){
        key[i]=1;
        }else{key[i]=0;}

     }

    //verifico se qualche tasto è premuto
    for ( int i =0; i<12; i++){
    state += key[i];


    if (key[i] ==1){
      //salvo il tasto più alto schiacciato
      Serial.println(i);
      mn=i;
      }



    }

    Serial.print("stato");
    Serial.print(state);


    if (state == 0){
      //se nessun tasto è schiacciato faccio smettere il suono
      envelope1.noteOff();
      Serial.println("off");
      //imposto il precedente tast su un tasto impossible per non avere problemi
      mnb=-1;
      }else{

             if(mnb!=mn){
        envelope1.noteOn();
        sine1.frequency(note[mn]);
             mnb=mn;
             }


 }
    state=0;




}
