# Artboard Sequencer

Un sequencer musicale polifonico a 8 step con sintetizzatore a 12 note controllato da Artboard.

![Sequencer Concept](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4e/Roland_TR-808_drum_machine.jpg/800px-Roland_TR-808_drum_machine.jpg)

## Descrizione

Questo progetto trasforma Artboard in un potente sequencer musicale step-based, ispirato alle classiche drum machine e sequencer hardware come TR-808, TR-909 e Elektron.

### Caratteristiche

- **8 Step Sequencer**: Registra e riproduce pattern musicali a 8 step
- **12 Note Polifoniche**: Scala cromatica completa (C3 - B3)
- **Dual Oscillator Synth**: Due oscillatori per nota con mix regolabile
- **4 Forme d'onda**: Sine, Sawtooth, Square, Triangle per ogni oscillatore
- **ADSR Envelope**: Attack e Release regolabili
- **Filtro Modulato**: State Variable Filter con controllo cutoff
- **LFO**: Modulazione Low Frequency per effetti wobble
- **Registrazione in Tempo Reale**: Registra note mentre le suoni
- **Feedback LED**: Indicatori visivi per step corrente e registrazione

## Hardware Richiesto

- **Artboard** con Teensy 3.6
- **Teensy Audio Shield** (per l'uscita audio)
- Altoparlanti o cuffie
- Switch/Interruttore collegato al pin 28 (per Play/Stop)

## Controlli

### Touch Pads (0-11)
Suonano le 12 note della scala cromatica:
- Touch 0: C (Do)
- Touch 1: C# (Do#)
- Touch 2: D (Re)
- Touch 3: D# (Re#)
- Touch 4: E (Mi)
- Touch 5: F (Fa)
- Touch 6: F# (Fa#)
- Touch 7: G (Sol)
- Touch 8: G# (Sol#)
- Touch 9: A (La)
- Touch 10: A# (La#)
- Touch 11: B (Si)

### Potenziometri

| Pot | Funzione | Range | Descrizione |
|-----|----------|-------|-------------|
| 0 | Attack | 1-500ms | Tempo di attack dell'envelope |
| 1 | Release | 10-1000ms | Tempo di release dell'envelope |
| 2 | Osc Mix | 0-100% | Mix tra oscillatore 1 e 2 |
| 3 | Waveform 1 | 0-3 | Forma d'onda osc 1 (Sine/Saw/Square/Tri) |
| 4 | Waveform 2 | 0-3 | Forma d'onda osc 2 (Sine/Saw/Square/Tri) |
| 5 | Filter Cutoff | 100-10000Hz | Frequenza di taglio del filtro |
| 6 | LFO Rate | 0.1-20Hz | Velocità della modulazione LFO |
| 7 | LFO Depth | 0-100% | Intensità della modulazione LFO |

**Nota sul Pot 8**: Il progetto originale prevedeva Pot 8 per il BPM, ma Artboard standard ha solo 8 potenziometri (0-7). Puoi:
- Usare un valore BPM fisso (attualmente 120 BPM)
- Modificare il codice per usare Pot 7 alternativamente
- Aggiungere un potenziometro esterno su un pin libero

### Pulsanti (0-7)
Selezionano lo step da registrare. Tieni premuto un pulsante e suona le note per registrare in quello step.

### Switch On/Off (Pin 28)
- **ON**: Avvia/Ferma il playback del sequencer
- Il LED corrispondente allo step corrente si illumina di verde durante il playback

### LED (0-7)
- **Rosso**: Step in modalità registrazione
- **Verde**: Step corrente durante playback
- **Off**: Step inattivo

## Come Usare

### 1. Registrazione

1. **Seleziona uno step**: Tieni premuto uno dei pulsanti (0-7)
2. **Suona le note**: Mentre tieni premuto il pulsante, tocca i touch pad per suonare le note
3. **Le note vengono registrate**: Tutte le note suonate mentre il pulsante è premuto vengono salvate in quello step
4. **Ripeti**: Rilascia il pulsante e registra gli altri step

**Esempio**:
- Premi Button 0, tocca Touch 0, 4, 7 (accordo C E G), rilascia Button 0
- Premi Button 1, tocca Touch 2, 5, 9 (accordo D F A), rilascia Button 1
- Premi Button 2, tocca Touch 4, 8, 11 (accordo E G# B), rilascia Button 2

### 2. Playback

1. **Attiva lo switch** (pin 28 a LOW/ON)
2. **Il sequencer parte**: Gli step registrati vengono suonati in sequenza
3. **I LED mostrano lo step corrente** in verde
4. **Ferma con lo switch**: Riattiva lo switch per fermare

### 3. Tweaking dei Suoni

Durante la registrazione o il playback, regola i potenziometri per:
- Modificare il timbro (forme d'onda)
- Regolare attack e release
- Modulare il filtro con LFO per effetti wobble
- Creare texture sonore complesse

## Configurazione Audio

Il progetto utilizza la Teensy Audio Library con:

- **24 Oscillatori** (2 per ogni nota)
- **12 Envelope Generator** (uno per nota)
- **12 Note Mixer** (combina i 2 oscillatori per nota)
- **3 Main Mixer** (raggruppano le 12 note)
- **1 LFO** (modulazione)
- **1 State Variable Filter** (filtraggio)
- **I2S Audio Output** (uscita stereo)

### Limiti di Memoria

Teensy 3.6 ha limiti sul numero di oggetti audio e connessioni. Il progetto usa circa 60-70 AudioConnection. Se modifichi il codice e aggiungi altri oggetti, potresti dover:
- Aumentare `AudioMemory()` nel setup
- Ridurre il numero di note polifoniche
- Ottimizzare le connessioni audio

## Consigli e Trucchi

### Pattern Interessanti

- **Bass Pattern**: Usa solo le note basse (Touch 0-4) e forma d'onda Square
- **Arpeggio**: Registra una nota per step (8 note consecutive)
- **Accordi**: Suona più note contemporaneamente su ogni step
- **Poly Rhythm**: Lascia alcuni step vuoti per creare ritmi irregolari

### Sound Design

- **Wobble Bass**: LFO Depth alto, LFO Rate medio, Filter Cutoff basso
- **Pad Atmosferico**: Attack lungo, Release lungo, Sine waves, LFO lento
- **Pluck**: Attack corto, Release corto, Sawtooth wave
- **Lead Synth**: Triangle wave, Filter Cutoff alto, no LFO

### Workflow Creativo

1. Inizia con un semplice pattern di basso (step 0, 2, 4, 6)
2. Aggiungi armonia negli step dispari (1, 3, 5, 7)
3. Tweaka i parametri in tempo reale durante il playback
4. Usa il mix oscillatori per creare movimento timbrico

## Modifiche Possibili

### Aggiungere BPM Control
```cpp
// Nel loop(), sostituisci:
int bpm = 120;
// Con:
bpm = map(artboard.pot(7), 0, 1023, 40, 240);
```

### Aumentare il Numero di Step
```cpp
#define NUM_STEPS 16  // Invece di 8
// Dovrai aggiungere più pulsanti o usare una modalità di page select
```

### Salvare Pattern su SD Card
Aggiungi codice per salvare/caricare i pattern `sequence[]` su SD card usando la libreria SD.

### MIDI Out
Aggiungi supporto MIDI per controllare synth esterni:
```cpp
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
// Invia MIDI note on/off durante il playback
```

### Swing/Shuffle
Aggiungi un parametro per ritardare gli step dispari:
```cpp
if (currentStep % 2 == 1) {
  delay(swingAmount); // Crea groove
}
```

## Troubleshooting

### Nessun suono
- Verifica che il Teensy Audio Shield sia collegato correttamente
- Controlla `AudioMemory()` - aumenta se necessario
- Verifica le connessioni audio nel codice

### Crash o comportamento strano
- Troppi AudioConnection objects - riduci la complessità
- Aumenta `AudioMemory()` (max 200-250 su Teensy 3.6)

### LED non funzionano
- Verifica che FastLED sia installata
- Controlla che il pin 8 sia collegato ai LED WS2812

### Touch non risponde
- Regola la soglia touch nel codice: `if (touchValue > 2000)`
- Prova valori diversi (1000-5000) a seconda del tuo hardware

## Riferimenti

- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/)
- [FastLED Library](https://fastled.io/)
- [TR-808 Wikipedia](https://en.wikipedia.org/wiki/Roland_TR-808)

## Crediti

Ispirato da:
- Roland TR-808, TR-909 (drum machines)
- Elektron Digitakt (modern sequencer)
- Teenage Engineering OP-1 (all-in-one workstation)

## Licenza

MIT License - Daniele Murgia © 2025
