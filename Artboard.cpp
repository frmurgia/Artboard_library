#include "Arduino.h"
#include "Artboard.h"

// --- Definizioni dei Pin ---
const int TOUCH_CTRL_PINS[4] = {2, 3, 4, 5};
const int TOUCH_SIGNAL_PIN = 30;
const int BUTTON_CTRL_PINS[4] = {24, 25, 26, 27};
const int BUTTON_SIGNAL_PIN = 39;
const int POT_PINS[8] = {31, 32, 33, 34, 35, 36, 37, 38};


/**
* Costruttore
* Imposta solo i valori predefiniti e il flag di inizializzazione.
**/
Artboard::Artboard() {
	_isInitialized = false; // Sarà impostato a true da initialize()
	signalPin = -1; 
	enablePin = -1;
	currentChannel = -1;
	currentChannelB = -1;
	lastIO = -1;
}

/**
* @private
* Funzione di Setup interna.
* Chiamata automaticamente la prima volta che si usa una funzione.
**/
void Artboard::initialize(){
	// Imposta i pin predefiniti
	this->signalPin = TOUCH_SIGNAL_PIN; // Pin 30 per write/dRead
	this->enablePin	= -1; // EN pin non usato di default
	lastIO = Artboard_IO_READ;

	// Setup pin Enable (se mai verrà impostato)
	if(enablePin > -1) {
		pinMode(enablePin, OUTPUT);
		digitalWrite(enablePin, LOW); 
	}

	// Setup pin controllo MUX Touch (pin 2-5)
	for(int i = 0; i < 4; i++){
		pinMode(TOUCH_CTRL_PINS[i], OUTPUT);
		digitalWrite(TOUCH_CTRL_PINS[i], LOW); 
	}
	
	// Setup pin controllo MUX Bottoni (pin 24-27)
	for(int i = 0; i < 4; i++){
		pinMode(BUTTON_CTRL_PINS[i], OUTPUT);
		digitalWrite(BUTTON_CTRL_PINS[i], LOW);
	}

	// Setup pin segnale Bottoni (pin 39)
  pinMode(BUTTON_SIGNAL_PIN, INPUT_PULLUP);

	// Setup pin segnale per write() (inizia come INPUT)
	pinMode(this->signalPin, INPUT);

	// Setup pin Potenziometri
	for (int i = 0; i < 8; i++){
		pinMode(POT_PINS[i], INPUT);
	}

	// Imposta il flag!
	_isInitialized = true;
}


/**
* @public
*/
void Artboard::setEnabled(bool enabled){
	if (!_isInitialized) initialize(); // Setup automatico
	
	if(enablePin != -1){
		digitalWrite(enablePin, enabled ? LOW : HIGH);
	}
}


/**
* @public
* Legge un canale del MUX Touch
**/
int Artboard::touch(int channel){
	if (!_isInitialized) initialize(); // Setup automatico

	if(lastIO != Artboard_IO_READ) {
		pinMode(signalPin, INPUT);
		lastIO = Artboard_IO_READ;
	}
	
	setTouchChannel(channel); 
	return touchRead(TOUCH_SIGNAL_PIN);
}


/**
* @public
* Legge un potenziometro
**/
int Artboard::pot(int pin){
	if (!_isInitialized) initialize(); // Setup automatico

	if (pin < 0 || pin > 7) return 0; 

	long sum = 0;
	int vals[10]; 
	
	for (int i = 0; i < 10; i++) {
		vals[i] = analogRead(POT_PINS[pin]);
		sum += vals[i];
	}

	float smooth = (vals[0] + vals[1] + vals[2] + vals[3] + vals[4]) / 5.0;
	return (int)smooth;
}


/**
* @public
* Legge un canale del MUX Bottoni
**/
int Artboard::button(int channel){
	if (!_isInitialized) initialize(); // Setup automatico
	
	setButtonChannel(channel); 
	return digitalRead(BUTTON_SIGNAL_PIN);
}


/**
* @public
* Converte una lettura touch in HIGH/LOW
**/
int Artboard::dRead(int channel){
	if (!_isInitialized) initialize(); // Setup automatico
	return touch(channel) < 512 ? LOW : HIGH;
}


/**
* @public
* Scrive un valore su un canale
**/
void Artboard::write(int channel, int value){
	if (!_isInitialized) initialize(); // Setup automatico

	if(lastIO != Artboard_IO_WRITE) {
		pinMode(signalPin, OUTPUT);
		lastIO = Artboard_IO_WRITE;
	}
	
	setTouchChannel(channel); 
	digitalWrite(signalPin, value);
}


// --- FUNZIONI PRIVATE ---

/**
* @private
* Imposta il canale del MUX Touch (pin 2-5)
*/
void Artboard::setTouchChannel(int channel){
	if(currentChannel != channel) {
		digitalWrite(TOUCH_CTRL_PINS[0], bitRead(channel,0)); // Pin 2
		digitalWrite(TOUCH_CTRL_PINS[1], bitRead(channel,1)); // Pin 3
		digitalWrite(TOUCH_CTRL_PINS[2], bitRead(channel,2)); // Pin 4
		digitalWrite(TOUCH_CTRL_PINS[3], bitRead(channel,3)); // Pin 5
		currentChannel = channel;
	}
}

/**
 
*/
/**
* @private
* Imposta il canale del MUX Bottoni (pin 24-27)
*/
void Artboard::setButtonChannel(int channel){
	if(currentChannelB != channel) {
		digitalWrite(BUTTON_CTRL_PINS[0], bitRead(channel,0)); // Pin 24
		digitalWrite(BUTTON_CTRL_PINS[1], bitRead(channel,1)); // Pin 25
		digitalWrite(BUTTON_CTRL_PINS[2], bitRead(channel,2)); // Pin 26
		digitalWrite(BUTTON_CTRL_PINS[3], bitRead(channel,3)); // Pin 27
		currentChannelB = channel;

        // AGGIUNGI QUESTA RIGA:
        // Dà al MUX il tempo di stabilizzarsi prima della lettura.
        // 1 microsecondo (1000ns) è un'eternità per un MUX da 50ns.
        delayMicroseconds(1); 
	}
}