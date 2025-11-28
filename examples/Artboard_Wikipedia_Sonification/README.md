# Artboard Wikipedia Sonification

Questo esempio sonorizza in tempo reale i contributi a Wikipedia, ispirato al progetto ["Listen to Wikipedia"](http://listen.hatnote.com/).

![Listen to Wikipedia](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/Listen_to_Wikipedia.png/800px-Listen_to_Wikipedia.png)

## Descrizione

Il progetto si connette allo stream EventStreams di Wikipedia e genera suoni e feedback visivi diversi per ogni tipo di modifica:

- **Nuove pagine**: Suono cristallino alto (1000-1500 Hz), LED verde
- **Modifiche piccole**: Suono morbido medio (500-800 Hz), LED blu
- **Modifiche grandi**: Suono profondo basso (200-300 Hz), LED rosso
- **Bot edits**: Suono meccanico (300 Hz), LED giallo

## Hardware Richiesto

- Artboard con Teensy 3.6
- Teensy Audio Shield (per l'uscita audio)
- Modulo WiFi ESP12S (già integrato su Artboard)
- Altoparlanti o cuffie collegate all'uscita audio

## Librerie Necessarie

```cpp
#include <WiFiEsp.h>      // Comunicazione WiFi
#include <Audio.h>        // Teensy Audio Library
#include <Artboard.h>     // Libreria Artboard
```

Installa le librerie tramite Arduino Library Manager:
- WiFiEsp
- Audio (Teensy Audio Library - installata con Teensyduino)

## Setup

1. Modifica le credenziali WiFi nel file `.ino`:
   ```cpp
   char ssid[] = "YOUR_WIFI_SSID";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```

2. Carica il codice su Teensy 3.6

3. Collega altoparlanti all'uscita audio dello shield

4. Apri il Serial Monitor (115200 baud) per vedere i log

## Controlli

- **Potenziometro 0**: Controllo volume
- **Potenziometro 1**: Modulazione pitch (trasposizione)
- **LED RGB**: Feedback visivo del tipo di evento

## Come Funziona

Il progetto utilizza l'API EventStreams di Wikipedia:
```
https://stream.wikimedia.org/v2/stream/recentchange
```

Questa API fornisce uno stream Server-Sent Events (SSE) in tempo reale di tutte le modifiche che avvengono su Wikipedia in tutte le lingue.

### Parsing degli Eventi

Gli eventi arrivano in formato JSON. Il codice estrae:
- `type`: tipo di evento (new, edit, log, etc.)
- `bot`: se la modifica è stata fatta da un bot
- `length` e `oldlength`: per calcolare la dimensione della modifica

### Sintesi Audio

Utilizza la Teensy Audio Library con:
- `AudioSynthWaveform`: generatori di forme d'onda (sine, triangle, square)
- `AudioEffectEnvelope`: envelope ADSR per modellare il suono
- `AudioMixer4`: mixer per combinare sorgenti audio
- `AudioOutputI2S`: uscita audio I2S per l'Audio Shield

## Varianti Possibili

- **Filtro per lingua**: modificare lo stream URL per ascoltare solo una Wikipedia specifica (es. `/v2/stream/recentchange/it.wikipedia`)
- **Mappatura custom**: cambiare le frequenze e i colori associati agli eventi
- **Pattern ritmici**: usare i trigger per creare pattern ritmici invece di note singole
- **Visualizzazione p5.js**: inviare dati via seriale a p5.js per creare visualizzazioni (vedi esempio p5)

## Risorse

- [Wikipedia EventStreams](https://wikitech.wikimedia.org/wiki/Event_Platform/EventStreams)
- [Listen to Wikipedia](http://listen.hatnote.com/) - Progetto originale
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [Stream API Documentation](https://stream.wikimedia.org/)

## Crediti

Ispirato a "Listen to Wikipedia" di Hatnote (Stephen LaPorte e Mahmoud Hashemi)

## Licenza

MIT
