#include "Arduino.h"
#include "Artboard.h"


/**
* Construct - no setup
**/
Artboard::Artboard() {
	//
}


/**
* Construct + setup
**/



/**
* @public
*/
// void Artboard::setup(int dPin0, int dPin1, int dPin2, int dPin3, int signalPin, int enablePin){
//
// 	this->dPin0 			= dPin0;
// 	this->dPin1 			= dPin1;
// 	this->dPin2 			= dPin2;
// 	this->dPin3 			= dPin3;
// 	this->signalPin 		= signalPin;
// 	this->enablePin			= enablePin;
// 	currentChannel 			= -1;
// 	lastIO					= -1;
//
// 	// using the EN pin?
// 	if(enablePin>-1) {
// 		pinMode(enablePin, OUTPUT);
// 		digitalWrite(enablePin, LOW); // start enabled
// 	}
//
// 	int pins[4] = {12,24,33,34};
// 	int i 		= 0;
//
// 	for(i=0;i<4;i++){
// 		// set pinMode for the digital control pins
// 		pinMode(pins[i], OUTPUT);
// 		// set all control pins LOW
// 		digitalWrite(pins[i], LOW);
// 	}
// }


/**
* @public
*/
void Artboard::setEnabled(bool enabled){
	if(enablePin!=-1){
		digitalWrite(enablePin, enabled ? LOW : HIGH);
	}
}


/**
* @public
*
**/
int Artboard::touch(int channel){

	this->dPin0 			= dPin0;
	this->dPin1 			= dPin1;
	this->dPin2 			= dPin2;
	this->dPin3 			= dPin3;
	this->signalPin 		= signalPin;
	this->enablePin			= enablePin;
	currentChannel 			= -1;
	lastIO					= -1;

	// using the EN pin?
	if(enablePin>-1) {
		pinMode(enablePin, OUTPUT);
		digitalWrite(enablePin, LOW); // start enabled
	}

	int pins[4] = {2,3,4,5};
	int i 		= 0;

	for(i=0;i<4;i++){
		// set pinMode for the digital control pins
		pinMode(pins[i], OUTPUT);
		// set all control pins LOW
		digitalWrite(pins[i], LOW);
	}


	if(lastIO != Artboard_IO_READ) {
		pinMode(signalPin, INPUT);
		lastIO = Artboard_IO_READ;
	}
	setChannel(channel);
	return touchRead(30);
}


/**
* @public
*
**/
int Artboard::dRead(int channel){
	return touch(channel) < 512 ? LOW : HIGH;
}


/**
* @public
*
**/
void Artboard::write(int channel, int value){
	if(lastIO != Artboard_IO_WRITE) {
		pinMode(signalPin, OUTPUT);
		lastIO = Artboard_IO_WRITE;
	}
	setChannel(channel);
	digitalWrite(signalPin, value);
}


/**
* @private
* set the current Artboard channel [0-15] using 4 digtal pins to write the 4 bit integer
*/
void Artboard::setChannel(int channel){
	if(currentChannel != channel) {
		digitalWrite(2, bitRead(channel,0));
		digitalWrite(3, bitRead(channel,1));
		digitalWrite(4, bitRead(channel,2));
		digitalWrite(5, bitRead(channel,3));
		currentChannel = channel;
	}
}
