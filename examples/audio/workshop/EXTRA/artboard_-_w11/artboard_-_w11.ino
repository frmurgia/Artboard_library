/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: audio workshop
  Descrizione: simple drum_machine con effetti
  pot 0     = tempo
  pot 1     = bitcrusher (bits)
  pot 2     = frequenza filtro
  pot 3     = risonanza filtro
  pot 4     = wet/dry mix
  pot 5     = reverb (room size)
  
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
#include <Artboard.h>
Artboard artboard;

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;
AudioEffectBitcrusher    bitcrusher1;
AudioEffectFreeverbStereo freeverbs1;
AudioFilterLadder        ladder1;
AudioMixer4              mixer1;
AudioOutputAnalogStereo  dacs1;

AudioConnection          patchCord1(playSdWav1, 0, bitcrusher1, 0);
AudioConnection          patchCord2(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord5(bitcrusher1, freeverbs1);
AudioConnection          patchCord6(freeverbs1, 0, ladder1, 0);
AudioConnection          patchCord7(ladder1, 0, mixer1, 1);
AudioConnection          patchCord8(mixer1, 0, dacs1, 0);
AudioConnection          patchCord9(mixer1, 0, dacs1, 1);
// GUItool: end automatically generated code


#define SDCARD_CS_PIN BUILTIN_SDCARD
#define SDCARD_MOSI_PIN 11
#define SDCARD_SCK_PIN 13

int tempo;
int kick;
int snare;
int hihat;
int clap;

int reset1;
int undo;
int sequencer_kick[8];
int sequencer_snare[8];
int sequencer_hihat[8];
int sequencer_clap[8];

int counter = 0;

// Debug
unsigned long lastDebugTime = 0;
const char* sampleFiles[] = {"kick.wav", "snare.wav", "hihat.wav", "clap.wav"};
int numSamples = 4;


// --- FUNZIONI DEBUG SD ---

void printSDInfo() {
  Serial.println("\n╔══════════════════════════════════════╗");
  Serial.println("║         SD CARD INFO                 ║");
  Serial.println("╚══════════════════════════════════════╝");
  
  uint8_t cardType = SD.sdfs.card()->type();
  Serial.print("Tipo SD: ");
  switch(cardType) {
    case 0: Serial.println("SD1"); break;
    case 1: Serial.println("SD2"); break;
    case 3: Serial.println("SDHC"); break;
    default: Serial.println("Sconosciuto");
  }
  
  uint64_t cardSize = SD.sdfs.card()->sectorCount();
  Serial.print("Dimensione: ");
  Serial.print((float)cardSize * 512 / 1000000);
  Serial.println(" MB");
  Serial.println();
}

void listFiles(File dir, int indent) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    
    for (int i = 0; i < indent; i++) Serial.print("  ");
    
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      listFiles(entry, indent + 1);
    } else {
      Serial.print("\t");
      Serial.print(entry.size());
      Serial.println(" bytes");
    }
    entry.close();
  }
}

void printSDContents() {
  Serial.println("---------- CONTENUTO SD ----------");
  File root = SD.open("/");
  if (root) {
    listFiles(root, 0);
    root.close();
  } else {
    Serial.println("ERRORE: impossibile aprire root");
  }
  Serial.println("----------------------------------\n");
}

bool checkFileExists(const char* filename) {
  bool exists = SD.exists(filename);
  Serial.print("[CHECK] ");
  Serial.print(filename);
  Serial.print(" -> ");
  
  if (exists) {
    File f = SD.open(filename);
    Serial.print("OK (");
    Serial.print(f.size());
    Serial.println(" bytes)");
    f.close();
    return true;
  } else {
    Serial.println("NON TROVATO!");
    return false;
  }
}

void checkAllSamples() {
  Serial.println("---------- VERIFICA SAMPLES ----------");
  int found = 0;
  for (int i = 0; i < numSamples; i++) {
    if (checkFileExists(sampleFiles[i])) {
      found++;
    }
  }
  Serial.print("\nTrovati: ");
  Serial.print(found);
  Serial.print("/");
  Serial.println(numSamples);
  
  if (found < numSamples) {
    Serial.println("ATTENZIONE: mancano dei file!");
  } else {
    Serial.println("Tutti i samples presenti!");
  }
  Serial.println("--------------------------------------\n");
}

void printSequencerStatus() {
  Serial.println("\n---------- SEQUENCER STATUS ----------");
  Serial.print("Step corrente: ");
  Serial.println(counter);
  
  Serial.print("KICK:  [");
  for (int i = 0; i < 8; i++) {
    Serial.print(sequencer_kick[i] ? "X" : ".");
    if (i < 7) Serial.print(" ");
  }
  Serial.println("]");
  
  Serial.print("SNARE: [");
  for (int i = 0; i < 8; i++) {
    Serial.print(sequencer_snare[i] ? "X" : ".");
    if (i < 7) Serial.print(" ");
  }
  Serial.println("]");
  
  Serial.print("HIHAT: [");
  for (int i = 0; i < 8; i++) {
    Serial.print(sequencer_hihat[i] ? "X" : ".");
    if (i < 7) Serial.print(" ");
  }
  Serial.println("]");
  
  Serial.print("CLAP:  [");
  for (int i = 0; i < 8; i++) {
    Serial.print(sequencer_clap[i] ? "X" : ".");
    if (i < 7) Serial.print(" ");
  }
  Serial.println("]");
  
  Serial.print("Tempo: ");
  Serial.println(artboard.pot(0));
  Serial.println("--------------------------------------\n");
}

void printEffectsStatus(int bits, float filterFreq, float filterRes, float dryLevel, float wetLevel, float reverbRoom) {
  Serial.println("---------- EFFECTS STATUS ----------");
  Serial.print("Bitcrusher: ");
  Serial.print(bits);
  Serial.println(" bits");
  Serial.print("Filter Freq: ");
  Serial.print((int)filterFreq);
  Serial.println(" Hz");
  Serial.print("Filter Res: ");
  Serial.println(filterRes, 2);
  Serial.print("Mix: DRY=");
  Serial.print((int)(dryLevel * 100));
  Serial.print("% WET=");
  Serial.print((int)(wetLevel * 100));
  Serial.println("%");
  Serial.print("Reverb Room: ");
  Serial.print((int)(reverbRoom * 100));
  Serial.println("%");
  Serial.println("------------------------------------\n");
}


void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("\n");
  Serial.println("╔══════════════════════════════════════╗");
  Serial.println("║     ARTBOARD DRUM MACHINE v2.0       ║");
  Serial.println("║     Bitcrusher + Reverb + Filter     ║");
  Serial.println("║     by Daniele Murgia                ║");
  Serial.println("╚══════════════════════════════════════╝");
  
  AudioMemory(160);

  // --- SETUP EFFETTI ---
  
  // Bitcrusher
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  
  // Reverb
  freeverbs1.roomsize(0.5);
  freeverbs1.damping(0.5);
  
  // Filtro Ladder
  ladder1.frequency(10000);
  ladder1.resonance(0.7);
  ladder1.octaveControl(0);
  
  // Mixer wet/dry
  mixer1.gain(0, 0.5);  // DRY
  mixer1.gain(1, 0.5);  // WET
  mixer1.gain(2, 0.0);
  mixer1.gain(3, 0.0);

  // --- INIZIALIZZAZIONE SD ---
  Serial.println("\n[INIT] Inizializzazione SD card...");
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  if (!(SD.begin(SDCARD_CS_PIN))) {
    Serial.println("\n╔══════════════════════════════════════╗");
    Serial.println("║  ERRORE: SD CARD NON ACCESSIBILE!    ║");
    Serial.println("╠══════════════════════════════════════╣");
    Serial.println("║  Verifica:                           ║");
    Serial.println("║  - SD inserita correttamente?        ║");
    Serial.println("║  - SD formattata FAT32?              ║");
    Serial.println("║  - Contatti puliti?                  ║");
    Serial.println("╚══════════════════════════════════════╝");
    while (1) {
      Serial.println("[ERRORE] SD non trovata - riprovo...");
      delay(2000);
      if (SD.begin(SDCARD_CS_PIN)) {
        Serial.println("[OK] SD trovata!");
        break;
      }
    }
  }
  
  Serial.println("[OK] SD card inizializzata!");
  
  printSDInfo();
  printSDContents();
  checkAllSamples();
  
  Serial.println("╔══════════════════════════════════════╗");
  Serial.println("║  CONTROLLI:                          ║");
  Serial.println("║  Pot 0 = Tempo                       ║");
  Serial.println("║  Pot 1 = Bitcrusher (1-16 bits)      ║");
  Serial.println("║  Pot 2 = Filtro Frequenza            ║");
  Serial.println("║  Pot 3 = Filtro Risonanza            ║");
  Serial.println("║  Pot 4 = Wet/Dry Mix                 ║");
  Serial.println("║  Pot 5 = Reverb Room Size            ║");
  Serial.println("╠══════════════════════════════════════╣");
  Serial.println("║  Button 0 = Kick                     ║");
  Serial.println("║  Button 1 = Snare                    ║");
  Serial.println("║  Button 2 = HiHat                    ║");
  Serial.println("║  Button 3 = Clap                     ║");
  Serial.println("║  Button 4 = Reset All                ║");
  Serial.println("║  Button 5 + 0-3 = Reset singolo      ║");
  Serial.println("╚══════════════════════════════════════╝");
  Serial.println("\n>>> PRONTO! <<<\n");
}

void loop() {
  kick = artboard.button(0);
  snare = artboard.button(1);
  hihat = artboard.button(2);
  clap = artboard.button(3);
  reset1 = artboard.button(4);
  undo = artboard.button(5);

  // --- LETTURA POTENZIOMETRI EFFETTI ---
  
  // Pot 1: Bitcrusher (16 bits = pulito, 1 bit = lo-fi)
  int bits = map(artboard.pot(1), 0, 1023, 16, 1);
  bitcrusher1.bits(bits);
  
  // Pot 2: Frequenza filtro (100Hz - 15000Hz)
  float filterFreq = map(artboard.pot(2), 0, 1023, 100, 15000);
  ladder1.frequency(filterFreq);
  
  // Pot 3: Risonanza filtro (0.0 - 1.0)
  float filterRes = artboard.pot(3) / 1023.0;
  ladder1.resonance(filterRes);
  
  // Pot 4: Wet/Dry mix
  float wetDry = artboard.pot(4) / 1023.0;
  float dryLevel = 1.0 - wetDry;
  float wetLevel = wetDry;
  mixer1.gain(0, dryLevel);
  mixer1.gain(1, wetLevel);
  
  // Pot 5: Reverb Room Size (0.0 - 1.0)
  float reverbRoom = artboard.pot(5) / 1023.0;
  freeverbs1.roomsize(reverbRoom);
  // Damping proporzionale alla room size (più grande = più damping)
  freeverbs1.damping(0.3 + (reverbRoom * 0.5));


  counter++;
  if (counter == 8) {
    counter = 0;
  }

  // Debug step
  static int lastCounter = -1;
  if (counter != lastCounter) {
    Serial.print("[STEP] ");
    Serial.print(counter);
    Serial.print(" [");
    for (int s = 0; s < 8; s++) {
      if (s == counter) {
        Serial.print(">");
      } else {
        Serial.print(" ");
      }
    }
    Serial.print("] ");
    
    bool hasSound = false;
    if (sequencer_kick[counter]) { Serial.print("KICK "); hasSound = true; }
    if (sequencer_snare[counter]) { Serial.print("SNARE "); hasSound = true; }
    if (sequencer_hihat[counter]) { Serial.print("HIHAT "); hasSound = true; }
    if (sequencer_clap[counter]) { Serial.print("CLAP "); hasSound = true; }
    if (!hasSound) Serial.print("---");
    Serial.println();
    
    lastCounter = counter;
  }

  ///////////////////contatore per la cassa////////////////////////
  if (kick > 0) {
    sequencer_kick[counter] = 1;
    Serial.print("[REC] KICK registrato in step ");
    Serial.println(counter);
  }

  if (sequencer_kick[counter] == 1) {
    playSdWav1.play("kick.wav");
  }

  ///////////////////contatore per SNARE////////////////////////
  if (snare > 0) {
    sequencer_snare[counter] = 1;
    Serial.print("[REC] SNARE registrato in step ");
    Serial.println(counter);
  }

  if (sequencer_snare[counter] == 1) {
    playSdWav1.play("snare.wav");
  }

  ///////////////////contatore per hihat////////////////////////
  if (hihat > 0) {
    sequencer_hihat[counter] = 1;
    Serial.print("[REC] HIHAT registrato in step ");
    Serial.println(counter);
  }

  if (sequencer_hihat[counter] == 1) {
    playSdWav1.play("hihat.wav");
  }

  ///////////////////contatore per clap////////////////////////
  if (clap > 0) {
    sequencer_clap[counter] = 1;
    Serial.print("[REC] CLAP registrato in step ");
    Serial.println(counter);
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
    Serial.println("[RESET] Tutti i pattern cancellati!");
    printSequencerStatus();
  }
  
  if (undo == 1 && clap == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_clap[a] = 0;
    }
    Serial.println("[RESET] Pattern CLAP cancellato!");
  }
  if (undo == 1 && kick == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_kick[a] = 0;
    }
    Serial.println("[RESET] Pattern KICK cancellato!");
  }
  if (undo == 1 && snare == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_snare[a] = 0;
    }
    Serial.println("[RESET] Pattern SNARE cancellato!");
  }
  if (undo == 1 && hihat == 1) {
    for (int a = 0; a < 8; a++) {
      sequencer_hihat[a] = 0;
    }
    Serial.println("[RESET] Pattern HIHAT cancellato!");
  }

  // Debug periodico ogni 5 secondi
  unsigned long now = millis();
  if (now - lastDebugTime >= 5000) {
    lastDebugTime = now;
    printSequencerStatus();
    printEffectsStatus(bits, filterFreq, filterRes, dryLevel, wetLevel, reverbRoom);
  }

  delayMicroseconds(map(artboard.pot(0), 0, 1023, 100000, 120000));
}


/*

**Pot 5 - Reverb Room Size:**
- Controlla la dimensione della "stanza" del riverbero (0.0 - 1.0)
- Pot tutto a sinistra = stanza piccola, riverbero corto
- Pot tutto a destra = stanza grande, riverbero lungo
- Il damping aumenta automaticamente con la room size per un suono più naturale

**Catena audio:**
```
playSdWav1 ────────────────────────────────► mixer1[0] DRY ─┐
     │                                                       │
     └──► bitcrusher ──► freeverb ──► ladder filter ──► mixer1[1] WET ──► dacs1
```

**Debug ogni 5 secondi:**
```
---------- EFFECTS STATUS ----------
Bitcrusher: 12 bits
Filter Freq: 8000 Hz
Filter Res: 0.45
Mix: DRY=40% WET=60%
Reverb Room: 75%
------------------------------------*/