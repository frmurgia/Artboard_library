/*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: Artboard MIDI Controller
Descrizione:   Trasforma l'Artboard in un controller MIDI completo.
               Tutti i controlli vengono mappati su messaggi MIDI:
               - Potenziometri → MIDI CC (Control Change)
               - Bottoni → MIDI CC
               - Touch Pad → MIDI Note On/Off

Hardware:
- Touch (0-11):  Note MIDI 60-71 (C4-B4, scala cromatica)
- Pot (0-7):     MIDI CC 1-8
- Button (0-7):  MIDI CC 16-23

MIDI Channel: 1
Connection: USB MIDI

--------------------------------------
LEZIONE: COS'È IL MIDI?
--------------------------------------
MIDI (Musical Instrument Digital Interface) è un protocollo
che permette a strumenti musicali e computer di comunicare.

TIPI DI MESSAGGI MIDI:

1. NOTE ON/OFF:
   - Invia quando una nota inizia o finisce
   - Parametri: Nota (0-127), Velocity (0-127)
   - I nostri touch pad inviano note 60-71 (un'ottava cromatica)

2. CONTROL CHANGE (CC):
   - Invia valori di controllo continui
   - Parametri: CC Number (0-127), Value (0-127)
   - Potenziometri → CC 1-8 (modulazione, volume, ecc.)
   - Bottoni → CC 16-23 (on/off o toggle)

MAPPING:
Touch 0  → Note 60 (C4  - Do)
Touch 1  → Note 61 (C#4 - Do#)
Touch 2  → Note 62 (D4  - Re)
Touch 3  → Note 63 (D#4 - Re#)
Touch 4  → Note 64 (E4  - Mi)
Touch 5  → Note 65 (F4  - Fa)
Touch 6  → Note 66 (F#4 - Fa#)
Touch 7  → Note 67 (G4  - Sol)
Touch 8  → Note 68 (G#4 - Sol#)
Touch 9  → Note 69 (A4  - La)
Touch 10 → Note 70 (A#4 - La#)
Touch 11 → Note 71 (B4  - Si)

Pot 0 → CC 1  (Modulation Wheel - standard)
Pot 1 → CC 2  (Breath Controller)
Pot 2 → CC 3
Pot 3 → CC 4  (Foot Controller)
Pot 4 → CC 5  (Portamento Time)
Pot 5 → CC 6  (Data Entry MSB)
Pot 6 → CC 7  (Channel Volume - standard)
Pot 7 → CC 8  (Balance)

Button 0-7 → CC 16-23 (General Purpose)

--------------------------------------

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
<><><><><><><><><><><><><><><><><><><>
*/

#include <Artboard.h>
Artboard artboard;

// Configurazione MIDI
const int MIDI_CHANNEL = 1;      // Canale MIDI (1-16)
const int BASE_NOTE = 60;        // Nota base (C4 - Do centrale)
const int VELOCITY = 127;        // Velocity fissa (massima)
const int TOUCH_THRESHOLD = 6000; // Soglia per rilevare il tocco

// Soglia per rilevare cambiamenti significativi nei pot
const int POT_THRESHOLD = 8;     // Minimo cambiamento per inviare CC (su scala 0-127)

// Array per memorizzare gli stati precedenti
bool touchStates[12] = {false};   // Stato precedente dei touch (note on/off)
int potValues[8] = {-1};          // Ultimi valori MIDI inviati dai pot (-1 = mai inviato)
bool buttonStates[8] = {false};   // Stato precedente dei bottoni


// ----- SETUP -----

void setup() {
  Serial.begin(9600);
  
  // Inizializza tutti gli stati
  for (int i = 0; i < 12; i++) {
    touchStates[i] = false;
  }
  
  for (int i = 0; i < 8; i++) {
    potValues[i] = -1;
    buttonStates[i] = false;
  }
  
  Serial.println("=================================");
  Serial.println("Artboard MIDI Controller");
  Serial.println("=================================");
  Serial.println("MIDI Channel: 1");
  Serial.println("Touch 0-11  → Notes 60-71 (C4-B4)");
  Serial.println("Pot 0-7     → CC 1-8");
  Serial.println("Button 0-7  → CC 16-23");
  Serial.println("=================================");
  Serial.println();
  
  // Piccolo delay per stabilizzare le letture iniziali
  delay(100);
}


// ----- LOOP -----

void loop() {

  // --- 1. GESTIONE TOUCH PAD (MIDI NOTES) ---
  //
  // I touch pad inviano Note On quando vengono toccati
  // e Note Off quando vengono rilasciati.
  // Usiamo edge detection per inviare il messaggio MIDI
  // solo quando lo stato cambia.
  
  for (int i = 0; i < 12; i++) {
    int touchValue = artboard.touch(i);
    bool isPressed = (touchValue > TOUCH_THRESHOLD);
    
    // Controlla se lo stato è cambiato
    if (isPressed != touchStates[i]) {
      int midiNote = BASE_NOTE + i;  // Note 60-71
      
      if (isPressed) {
        // Touch premuto → Note On
        usbMIDI.sendNoteOn(midiNote, VELOCITY, MIDI_CHANNEL);
        Serial.print("Note ON:  ");
        Serial.print(midiNote);
        Serial.print(" (Touch ");
        Serial.print(i);
        Serial.println(")");
      }
      else {
        // Touch rilasciato → Note Off
        usbMIDI.sendNoteOff(midiNote, 0, MIDI_CHANNEL);
        Serial.print("Note OFF: ");
        Serial.print(midiNote);
        Serial.print(" (Touch ");
        Serial.print(i);
        Serial.println(")");
      }
      
      touchStates[i] = isPressed;
    }
  }


  // --- 2. GESTIONE POTENZIOMETRI (MIDI CC) ---
  //
  // I potenziometri leggono valori 0-1023, che mappiamo
  // su valori MIDI 0-127.
  // Inviamo il CC solo se il valore è cambiato abbastanza
  // per evitare di saturare il bus MIDI con messaggi inutili.
  
  for (int i = 0; i < 8; i++) {
    int potReading = artboard.pot(i);
    
    // Mappa da 0-1023 a 0-127 (range MIDI)
    int midiValue = map(potReading, 0, 1023, 0, 127);
    
    // Controlla se il valore è cambiato abbastanza
    if (potValues[i] == -1 || abs(midiValue - potValues[i]) >= POT_THRESHOLD) {
      int ccNumber = i + 1;  // CC 1-8
      
      usbMIDI.sendControlChange(ccNumber, midiValue, MIDI_CHANNEL);
      
      Serial.print("CC ");
      Serial.print(ccNumber);
      Serial.print(": ");
      Serial.print(midiValue);
      Serial.print(" (Pot ");
      Serial.print(i);
      Serial.println(")");
      
      potValues[i] = midiValue;
    }
  }


  // --- 3. GESTIONE BOTTONI (MIDI CC) ---
  //
  // I bottoni inviano CC con valore 127 quando premuti
  // e 0 quando rilasciati.
  // Usiamo edge detection per inviare solo ai cambiamenti di stato.
  
  for (int i = 0; i < 8; i++) {
    bool isPressed = (artboard.button(i) == LOW);  // LOW = premuto
    
    // Controlla se lo stato è cambiato
    if (isPressed != buttonStates[i]) {
      int ccNumber = 16 + i;  // CC 16-23
      int midiValue = isPressed ? 127 : 0;
      
      usbMIDI.sendControlChange(ccNumber, midiValue, MIDI_CHANNEL);
      
      Serial.print("CC ");
      Serial.print(ccNumber);
      Serial.print(": ");
      Serial.print(midiValue);
      Serial.print(" (Button ");
      Serial.print(i);
      Serial.print(isPressed ? " PRESSED" : " RELEASED");
      Serial.println(")");
      
      buttonStates[i] = isPressed;
    }
  }


  // --- 4. LETTURA MESSAGGI MIDI IN ARRIVO (opzionale) ---
  //
  // Leggi eventuali messaggi MIDI in arrivo dal computer.
  // Questo è utile se vuoi che l'Artboard riceva anche MIDI,
  // ad esempio per controllare LED o altro feedback visivo.
  
  while (usbMIDI.read()) {
    // Processa i messaggi MIDI in arrivo
    // (Puoi aggiungere qui la logica per rispondere a MIDI in ingresso)
  }


  // Piccolo delay per stabilità
  delay(5);
}
