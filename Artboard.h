#ifndef Artboard_h
#define Artboard_h

#include "Arduino.h"
#include <FastLED.h>

#define Artboard_IO_READ 0
#define Artboard_IO_WRITE 1

// LED Configuration
#define NUM_LEDS 8
#define LED_DATA_PIN 8
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

class Artboard {
  public:
    // --- Funzioni Pubbliche ---

    /**
    * Costruttore
    */
    Artboard();

    /**
    * Abilita o disabilita il MUX (se enPin è usato)
    */
    void setEnabled(bool enabled);

    /**
    * Legge un canale touch
    */
    int touch(int channel);

    /**
    * Legge un potenziometro
    */
    int pot(int pin);

    /**
    * Legge un bottone
    */
    int button(int channel);

    /**
    * Legge un canale touch come digitale (HIGH/LOW)
    */
    int dRead(int channel);

    /**
    * Scrive un valore digitale su un canale touch
    */
    void write(int channel, int value);

    // --- LED Functions ---

    /**
    * Inizializza i LED (chiamata automaticamente)
    */
    void initLEDs();

    /**
    * Imposta il colore di un LED specifico (0-7)
    * @param index indice del LED (0-7)
    * @param r valore rosso (0-255)
    * @param g valore verde (0-255)
    * @param b valore blu (0-255)
    */
    void setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

    /**
    * Imposta il colore di tutti i LED
    * @param r valore rosso (0-255)
    * @param g valore verde (0-255)
    * @param b valore blu (0-255)
    */
    void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);

    /**
    * Spegne un LED specifico
    * @param index indice del LED (0-7)
    */
    void clearLED(uint8_t index);

    /**
    * Spegne tutti i LED
    */
    void clearAllLEDs();

    /**
    * Aggiorna i LED (mostra le modifiche)
    * Chiamata automaticamente dopo setLED(), ma può essere chiamata manualmente
    */
    void updateLEDs();

    /**
    * Imposta la luminosità globale dei LED
    * @param brightness valore luminosità (0-255)
    */
    void setBrightness(uint8_t brightness);

  private:
    // --- Funzioni Private ---

    /**
    * Esegue il setup dei pin una sola volta
    */
    void initialize();

    /**
    * Imposta il canale per il MUX touch (pin 2-5)
    */
    void setTouchChannel(int channel);

    /**
    * Imposta il canale per il MUX bottoni (pin 24-27)
    */
    void setButtonChannel(int channel);

    // --- Variabili Membro (Private) ---
    bool _isInitialized; // Flag per setup automatico
    bool _ledsInitialized; // Flag per setup LED
    int signalPin;
    int enablePin;
    int currentChannel;  // Canale MUX Touch
    int currentChannelB; // Canale MUX Bottoni
    int lastIO;

    // LED array
    CRGB leds[NUM_LEDS];
};

#endif