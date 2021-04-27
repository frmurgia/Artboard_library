
#   **Artboard**
##   **prototyping board for artist**
##   **V 2.0**


Artboard is a breakout board board for teensy 3.6 made for artists, designers and musicians.



*main features:*


• 12 capacitive inputs

• 8 potentiometers


• 8 Buttons

• 5  PWM outs

• 12 external in/out

• 8 tactile button

• 1 switch on/off

• teensy audio shield pins

• wifi connection (ESP12S)

• 1 led RGB

• 12 in/out digital/analog/pwm

• prototype area 

• stereo audio output

• stereo audio input

• 8 diglta rgb led

• 1 ESP-12S

• footprints for teensy audioshield



##   **library**

constructor artboard();


##   **Function**

 artboard.touch(int channel);

  this funtion Read from the chosen channel of touch multiplexer.

  artboard.button(int channel);

   this funtion Read from the chosen channel of button multiplexer.
   return a digital outpu (HIGH or LOW, 0 1)


