#ifndef Artboard_h
#define Artboard_h

#include "Arduino.h"

#define Artboard_IO_READ 0
#define Artboard_IO_WRITE 1

/**
* Artboard control lib for CD74HC4067
*
* Made for / tested with Analog/Digital Artboard Breakout from sparkfun: https://www.sparkfun.com/products/9056
*/
class Artboard {

   public:

	/**
	* Constructor - you'll need to call Artboard::setup later if not passing parameters here.
	*/
    Artboard();

	/**
	* @see Artboard::setup
	*/


	/**
	* setup
	* @param dPin0		- digital control pin0
	* @param dPin1		- digital control pin1
	* @param dPin2		- digital control pin2
	* @param dPin3		- digital control pin3
	* @param signalPin 	- analog io pin to read/write data on - eg: A0
	* @param enablePin 	- optional, use if you have connected the EN (enable) pin to a digtal pin.
	*					 defaults to -1 (unused) if not set here.
	*/
    // void setup(int dPin0, int dPin1, int dPin2, int dPin3, int signalPin=A0, int enablePin=-1);

	/**
	* setEnabled
	* If the EN (enable) pin is connected to a digital output on the arduino,
	* and not just connected to ground, use this to enable/disable all IO pins on the board.
	*/
	void setEnabled(bool enabled);


	/**
	* Read from the chosen channel - the returned value will be in the range of 0 to 1023
	* For reading digital signals, assume a value >= 512 is HIGH and < 512 is LOW - or just use Artboard::dRead, which does that mapping for you.
	* @param channel
	*/
	int touch(int channel);
  /**
  * Read from the chose channell of button multiplex [,0-m7] but also GPIO near breadboard [m8-m15]
  * @param channel
  */
  int button(int channel);



	/**
	* @param channel - channel to read from
	* @return HIGH or LOW
	*/
	int dRead(int channel);


	/**
	* @param channel
	* @param value - HIGH or LOW
	**/
    void write(int channel, int value);


  protected:
	int enablePin; // EN - HIGH==all outputs disabled, LOW==everything is enabled
	int signalPin;
    int dPin0;
    int dPin1;
    int dPin2;
    int dPin3;

	int lastIO;
	int currentChannel;
  int currentChannelB;

	void setChannel(int channel);


};


#endif
