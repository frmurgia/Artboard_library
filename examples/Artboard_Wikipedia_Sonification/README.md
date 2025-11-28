# Artboard Wikipedia Sonification

Sonorizzazione in tempo reale ispirata a ["Listen to Wikipedia"](http://listen.hatnote.com/).

![Listen to Wikipedia](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/Listen_to_Wikipedia.png/800px-Listen_to_Wikipedia.png)

## ⚠️ Nota Importante

Wikipedia EventStreams richiede **HTTPS**, ma l'ESP8266 (ESP12S) con WiFiEsp ha **difficoltà con SSL/HTTPS**. Per questo motivo offriamo **due versioni**:

### 1. Versione Simulata (✅ Raccomandata)
**File**: `Artboard_Wikipedia_Sonification_Simulated.ino`

- ✅ **Funziona sempre** senza connessione internet
- ✅ Genera eventi random che simulano Wikipedia
- ✅ Stessa esperienza sonora e visiva
- ✅ Più affidabile per demo e didattica
- ✅ Controlli interattivi (frequenza eventi, tipo eventi)

**Usa questa versione** se vuoi un esempio che funziona subito!

### 2. Versione Real-Time (⚠️ Sperimentale)
**File**: `Artboard_Wikipedia_Sonification.ino`

- ⚠️ Richiede HTTPS (porta 443)
- ⚠️ ESP8266 potrebbe non supportare SSL facilmente
- ⚠️ Si disconnette frequentemente
- ⚠️ Serve libreria WiFiEspClientSecure (non sempre disponibile)

**Usa questa versione** solo se hai un setup WiFi che supporta SSL o vuoi sperimentare.

---

## Versione Simulata - Guida Rapida

### Hardware Richiesto

- Artboard con Teensy 3.6
- Altoparlanti/cuffie collegati al DAC (pin A21 + GND)
- **NON richiede** WiFi o Internet!

### Caratteristiche

- **Eventi Random**: Simula modifiche Wikipedia in tempo reale
- **4 Tipi di Eventi**:
  - 🟢 **Nuove pagine**: Suono cristallino (1000-1500 Hz), LED verde
  - 🔵 **Modifiche piccole**: Suono morbido (500-800 Hz), LED blu
  - 🔴 **Modifiche grandi**: Suono profondo (200-300 Hz), LED rosso
  - 🟡 **Bot edits**: Suono meccanico (300 Hz), LED giallo

### Controlli

| Pot | Funzione | Range |
|-----|----------|-------|
| 0   | Volume | 0-100% |
| 1   | Frequenza eventi | 100ms - 3s tra eventi |
| 2   | Probabilità Bot | 0-100% (0=solo umani, 100=solo bot) |

### Utilizzo

1. Carica `Artboard_Wikipedia_Sonification_Simulated.ino` su Teensy
2. Collega cuffie al pin A21 (DAC) + GND
3. Apri Serial Monitor (115200 baud) per vedere eventi
4. Regola i potenziometri per cambiare il comportamento
5. Osserva LED e ascolta i suoni!

### Output Seriale

```
=== WIKIPEDIA SONIFICATION (SIMULATED) ===
Generating random Wikipedia-style events...
#1 SMALL EDIT 687Hz size:234
#2 BOT EDIT 300Hz size:567
#3 NEW PAGE 1234Hz size:89
...
--- STATS ---
New: 5 | Bot: 12 | Small: 20 | Large: 13
```

---

## Versione Real-Time - Guida (Avanzata)

### ⚠️ Limitazioni Tecniche

Il file `Artboard_Wikipedia_Sonification.ino` tenta di connettersi al vero stream Wikipedia, ma:

**Problema**: Wikipedia richiede HTTPS (TLS/SSL)
```
https://stream.wikimedia.org/v2/stream/recentchange
```

**Limitazione ESP8266**: La libreria WiFiEsp standard **non supporta** facilmente HTTPS.

### Sintomi del Problema

```
Connecting to Wikipedia EventStreams...
Connected!
Disconnected. Reconnecting...   <-- Si disconnette subito!
```

Il server Wikipedia accetta solo HTTPS e rifiuta connessioni HTTP.

### Soluzioni Possibili

#### Soluzione 1: Usa la Versione Simulata (Consigliata)
È identica come esperienza ma senza problemi di connessione.

#### Soluzione 2: WiFiClientSecure (Avanzato)

Se hai esperienza, prova a modificare il codice per usare `WiFiClientSecure`:

```cpp
// Invece di:
WiFiEspClient client;

// Usa:
WiFiClientSecure client;
client.setInsecure(); // Salta verifica certificato (solo per test!)
```

**Nota**: Richiede librerie aggiuntive e più RAM.

#### Soluzione 3: Proxy HTTP

Crea un proxy locale che converte HTTPS → HTTP:
- Usa un Raspberry Pi o computer con Node.js
- Proxy fa la richiesta HTTPS e la ritrasmette come HTTP
- Artboard si connette al proxy invece che a Wikipedia

Esempio proxy con Node.js (fuori scope di questa guida).

#### Soluzione 4: Usa Teensy WiFi

Se hai un **Teensy con modulo WiFi nativo** (non ESP8266), potrebbe supportare meglio SSL.

---

## Architettura Audio

Entrambe le versioni usano:

### Audio Chain
```
Waveform → Envelope → Multiply → Filter → DAC
```

### Componenti

- **AudioSynthWaveform**: Generatore tono (SINE wave)
- **AudioSynthWaveformDc**: Envelope (attack/decay)
- **AudioEffectMultiply**: Applica envelope al tono
- **AudioFilterStateVariable**: Filtro passa-basso
- **AudioOutputAnalog**: Output DAC (pin A21)

### Parametri Audio per Tipo Evento

| Tipo | Frequenza | Forma d'onda | Filtro |
|------|-----------|--------------|--------|
| Nuovo | 1000-1500 Hz | Sine | High cutoff |
| Piccolo | 500-800 Hz | Sine | Mid cutoff |
| Grande | 200-300 Hz | Sine | Low cutoff |
| Bot | 300 Hz | Sine | Low cutoff |

---

## Confronto Versioni

| Caratteristica | Simulata | Real-Time |
|----------------|----------|-----------|
| Funziona subito | ✅ Sì | ⚠️ No (HTTPS) |
| Richiede WiFi | ❌ No | ✅ Sì |
| Dati reali | ❌ No | ✅ Sì (se funziona) |
| Controlli interattivi | ✅ Sì (3 pot) | ⚠️ Solo volume |
| Affidabilità | ✅ Alta | ⚠️ Bassa |
| Didattico | ✅ Ottimo | ⚠️ Frustrante |

## FAQ

### Q: Perché la versione real-time non funziona?
**A**: Wikipedia richiede HTTPS ma ESP8266 con WiFiEsp non lo supporta facilmente. Usa la versione simulata.

### Q: Come faccio a usare i dati reali di Wikipedia?
**A**: Opzioni:
1. Usa un proxy HTTP locale
2. Usa un modulo WiFi diverso con supporto SSL nativo
3. Usa un Raspberry Pi che fa parsing e invia dati via seriale a Teensy

### Q: La versione simulata è "falsa"?
**A**: No, è una **simulazione** - genera eventi con le stesse caratteristiche statistiche di Wikipedia. È didatticamente equivalente e più affidabile.

### Q: Posso combinare le due versioni?
**A**: Sì! Potresti:
- Usare la versione simulata come fallback se WiFi non connette
- Alternare tra reale e simulato con un pulsante
- Visualizzare statistiche diverse per confrontare

---

## Modifiche Possibili

### Aggiungere Più Tipi di Eventi
```cpp
// Aggiungi eventi per namespace
if (namespace == "Talk") {
  frequency = 800;
  r = 255; g = 0; b = 255; // Magenta
}
```

### Controllare Note Musicali
Invece di frequenze random, mappa a scale musicali:
```cpp
int notes[] = {261, 294, 330, 349, 392, 440, 494}; // C major
frequency = notes[eventType % 7];
```

### Salvare Statistiche su SD
```cpp
#include <SD.h>
File dataFile = SD.open("stats.txt", FILE_WRITE);
dataFile.println("Event,Time,Type,Size");
```

### MIDI Output
Invia eventi come note MIDI:
```cpp
#include <MIDI.h>
MIDI.sendNoteOn(midiNote, velocity, 1);
```

---

## Riferimenti

- [Listen to Wikipedia](http://listen.hatnote.com/) - Progetto originale
- [Wikipedia EventStreams API](https://wikitech.wikimedia.org/wiki/Event_Platform/EventStreams)
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [WiFiEsp Library](https://github.com/bportaluri/WiFiEsp)

## Crediti

Ispirato a "Listen to Wikipedia" di Hatnote (Stephen LaPorte e Mahmoud Hashemi)

## Licenza

MIT
