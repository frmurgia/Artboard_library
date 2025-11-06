/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Audio Workshop 3 - Inviluppo
Descrizione: Usiamo un inviluppo per controllare il volume nel tempo.
             Creiamo un "VCA" (Voltage Controlled Amplifier)
             moltiplicando la sinusoide per un segnale di controllo (l'inviluppo).

Hardware:
- Touch 0:   Avvia la nota ("Note On") e la ferma ("Note Off")
- Pot 0:     Controlla il tempo di ATTACCO (quanto ci mette a raggiungere il max volume)
- Pot 1:     Controlla il tempo di RILASCIO (quanto ci mette a tornare a zero)

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Artboard.h> // includiamo la libreria
Artboard artboard;    // Istanza

// GUItool: begin automatically generated code
// (Modificato per uscita MONO e per chiarezza)

AudioSynthWaveformSine   sine1;       // Il nostro oscillatore (genera il suono)
AudioSynthWaveformDc     envelope;    // Un segnale DC che useremo come inviluppo
AudioEffectMultiply      vca;         // Il "VCA": moltiplica Suono * Inviluppo
AudioOutputAnalog        dac;         // Uscita audio MONO

AudioConnection          patchCord1(sine1, 0, vca, 0);     // Sinusoide -> Ingresso A del VCA
AudioConnection          patchCord2(envelope, 0, vca, 1);  // Inviluppo -> Ingresso B del VCA
AudioConnection          patchCord3(vca, 0, dac, 0);       // Uscita VCA -> DAC (casse)
// GUItool: end automatically generated code


// Variabile per sapere se la nota è attualmente "accesa" o "spenta"
bool notaAttiva = false;

// Definiamo la frequenza della nota
float DO = 261.6;
 
void setup() {
  AudioMemory(12);
  Serial.begin(9600);
  
  // Impostiamo il volume della sinusoide al massimo (1.0).
  // Sarà l'inviluppo a controllarne il volume finale.
  sine1.amplitude(1.0);
  
  // Impostiamo la frequenza della nota (una sola volta)
  sine1.frequency(DO * 2); // Un'ottava sopra
  
  // IMPORTANTE: Inizializza l'inviluppo a 0 (silenzio)
  envelope.amplitude(0.0);
  
  Serial.println("Sketch 3: Inviluppo Attack/Release");
  Serial.println("Tocca il pad 0 per suonare.");
  Serial.println("Usa i pot 0 (Attack) e 1 (Release).");
}

void loop() {

  // 1. Leggi i potenziometri e mappali in un range utile (in millisecondi)
  // Usiamo map() per evitare tempi di 0ms (che fanno "click")
  // Range: da 5ms (molto veloce) a 1000ms (1 secondo)
  int attackTime = map(artboard.pot(0), 0, 1023, 5, 1000);
  int releaseTime = map(artboard.pot(1), 0, 1023, 5, 1000);

  // 2. Controlla se il pad touch è premuto
  bool touchPremuto = (artboard.touch(0) > 8000);


  // 3. Logica di "Edge Detection" (Rilevamento del cambiamento)

  // --- Evento NOTE ON ---
  // Se il tasto è PREMUTO (touchPremuto == true)
  // E la nota era SPENTA (notaAttiva == false)
  if (touchPremuto && !notaAttiva) {
    notaAttiva = true; // Imposta lo stato su "accesa"
    
    // Avvia l'inviluppo: vai a volume 1.0 in 'attackTime' millisecondi
    envelope.amplitude(1.0, attackTime);
    
    Serial.print("NOTA ON (Attacco: ");
    Serial.print(attackTime);
    Serial.println("ms)");
  }
  
  // --- Evento NOTE OFF ---
  // Se il tasto è RILASCIATO (touchPremuto == false)
  // E la nota era ACCESA (notaAttiva == true)
  else if (!touchPremuto && notaAttiva) {
    notaAttiva = false; // Imposta lo stato su "spenta"
    
    // Avvia l'inviluppo: vai a volume 0.0 in 'releaseTime' millisecondi
    envelope.amplitude(0.0, releaseTime);
    
    Serial.print("NOTA OFF (Rilascio: ");
    Serial.print(releaseTime);
    Serial.println("ms)");
  }
  
  delay(10); // Piccolo delay per stabilizzare le letture
}