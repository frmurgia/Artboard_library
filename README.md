# Artboard Library

Libreria Arduino per breakout board Teensy 3.6.

![Artboard](https://github.com/frmurgia/Artboard_library/blob/master/img/Screenshot%202025-11-06%20alle%2012.03.42.png)


## Caratteristiche Principali

### Input e Controlli
- **12 ingressi capacitivi**
- **8 potenziometri** 
- **8 pulsanti standard** 
- **8 pulsanti tattili** 
- **1 interruttore on/off** 

### Connettività
- **12 pin esterni in/out**
- **12 pin digital/analog/PWM**
- **Connessione WiFi (ESP12S)** - Comunicazione wireless 

### Audio
- **Footprint per Teensy Audio Shield** - Compatibilità con lo shield audio ufficiale
- **Uscita audio stereo** 

### Feedback Visivo
- **8 LED RGB digitali** 

### Processore
- **ESP-12S integrato** 

## Installazione

### Requisiti
- Arduino IDE
- Teensyduino installato
- Teensy 3.6

### Installazione della Libreria

1. Scarica o clona questo repository
2. Copia la cartella `Artboard_library` nella directory delle librerie di Arduino:
   - **Windows**: `Documents/Arduino/libraries/`
   - **Mac**: `~/Documents/Arduino/libraries/`
   - **Linux**: `~/Arduino/libraries/`
3. Installa la libreria **FastLED** tramite Library Manager (per il supporto LED RGB)
4. Riavvia Arduino IDE

Oppure installa tramite Arduino IDE:
1. Vai su `Sketch` → `Include Library` → `Add .ZIP Library...`
2. Seleziona il file ZIP scaricato
3. Installa la libreria **FastLED** tramite Library Manager

## Utilizzo Base

### Inclusione della Libreria

```cpp
#include <Artboard.h>

Artboard artboard;
```

### Lettura degli Input

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Lettura input capacitivi (0-11)
  int touchValue = artboard.touch(0);
  
  // Lettura pulsanti (0-7)
  int buttonState = artboard.button(0);
  
  // Lettura potenziometri (0-7)
  int potValue = artboard.pot(0);
  
  Serial.println(touchValue);
  delay(10);
}
```

## Esempi

La libreria include diversi esempi per iniziare rapidamente:

### Debug e Test
- **debug/Artboard_bottoni**: Test dei pulsanti della board
- **debug/Artboard_TouchIn**: Test degli input capacitivi
- **debug/Artboard_potenziometri**: Test dei potenziometri
- **debug/debug_sistema**: Test completo del sistema

### Audio
- **Artboard_PlayAudioFromSD**: Riproduzione di campioni audio da SD card
- **Artboard_Sequencer**: Sequencer musicale a 8 step con sintetizzatore polifonico a 12 note
- **audio/workshop**: Serie completa di esempi per sintesi audio e processing (w1-w11)
  - Sintesi sonora base, inviluppi, filtri, delay, LFO e altro

Per accedere agli esempi: `File` → `Examples` → `Artboard` o nella cartella `examples/` del repository

## API Reference

### Input Capacitivi
```cpp
artboard.touch(pin)  // pin: 0-11, ritorna valore capacitivo
```

### Pulsanti
```cpp
artboard.button(pin)  // pin: 0-7, ritorna HIGH o LOW
```

### Potenziometri
```cpp
artboard.pot(pin)  // pin: 0-7, ritorna valore 0-1023
```

### LED RGB
```cpp
artboard.setLED(index, r, g, b)  // Imposta LED specifico (0-7)
artboard.setAllLEDs(r, g, b)     // Imposta tutti i LED
artboard.clearLED(index)         // Spegne LED specifico
artboard.clearAllLEDs()          // Spegne tutti i LED
artboard.setBrightness(value)    // Imposta luminosità (0-255)
artboard.updateLEDs()            // Aggiorna i LED manualmente
```

**Nota**: I LED usano la libreria FastLED e sono collegati al pin 8. Assicurati di avere FastLED installata.

### Pin Digitali/Analogici
```cpp
artboard.pinMode(pin, mode)  // Configura modalità pin (0-11)
artboard.digitalWrite(pin, value)  // Scrittura digitale
artboard.digitalRead(pin)  // Lettura digitale
artboard.analogRead(pin)  // Lettura analogica
```

## Specifiche Hardware

- **Microcontrollore**: Teensy 3.6
- **Tensione operativa**: 3.3V
- **Alimentazione**: USB 
- **Dimensioni**: [specificare dimensioni]
- **Connettori**: Header standard 2.54mm

## Pinout

Per il [Pinouts](https://github.com/frmurgia/Artboard_library/blob/master/img/pinout%20wireframe.png) dettagliato e lo schema elettrico, consultare la cartella `img/` del repository.


## Contribuire

Contributi, segnalazioni di bug e richieste di funzionalità sono benvenuti!

1. Fai un Fork del progetto
2. Crea un branch per la tua feature (`git checkout -b feature/AmazingFeature`)
3. Commit delle tue modifiche (`git commit -m 'Add some AmazingFeature'`)
4. Push al branch (`git push origin feature/AmazingFeature`)
5. Apri una Pull Request

## Licenza

MIT

## Crediti

Progetto e sviluppo: Daniele Murgia

## Supporto

Per domande, problemi o suggerimenti:
- Apri un [Issue](https://github.com/frmurgia/Artboard_library/issues) su GitHub

## Risorse Aggiuntive

- [Teensy 3.6 Documentation](https://www.pjrc.com/store/teensy36.html)
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [ESP12S Documentation](https://www.espressif.com/en/products/modules/esp8266)

---

**Made with ❤️ for artists, designers and musicians**
