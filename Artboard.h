#ifndef Artboard_h
#define Artboard_h

#include "Arduino.h"

#define Artboard_IO_READ 0
#define Artboard_IO_WRITE 1

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
    int signalPin;
    int enablePin;
    int currentChannel;  // Canale MUX Touch
    int currentChannelB; // Canale MUX Bottoni
    int lastIO;
};

#endif