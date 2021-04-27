
#   **Artboard**
##   **prototyping board for artist**
##   **V 2.0**
[see the video](https://www.youtube.com/watch?v=JZZfKKglsCU&feature=youtu.be)


During the pandemic period, I made this pcb to teach physical computing to my students.
Artboard is a breakout board board for teensy 3.6 made for artists, designers and musicians.



*main features:*


• 12 capacitive inputs

• 8 potentiometers

• 8 Buttons

• 5  PWM outs

• 16 external in/out digital/analog or capacitive

• prototype area with external power

• stereo audio output

• stereo audio input

• 8 diglta rgb led

• 1 ESP-12S

• predisposition for teensy audioshield

• predisposition for ESP-01 in case of emergency

##   **library**

constructor artboard();


##   **Function**

 artboard.touch(int channel);

  this funtion Read from the chosen channel of touch multiplexer.

  artboard.button(int channel);

   this funtion Read from the chosen channel of button multiplexer.
   return a digital outpu (HIGH or LOW, 0 1)






![Drag Racing](https://github.com/frmurgia/Artboard_library/blob/master/art-board_01.jpg)
