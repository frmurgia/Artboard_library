/*
 * Artboard Generative Graphics
 *
 * Questo esempio invia i dati dai controlli di Artboard a p5.js
 * per generare grafiche minimaliste in stile Sol LeWitt.
 *
 * Controlli:
 * - Potenziometri 0-3: Controllano parametri delle grafiche
 * - Pulsanti 0-3: Cambiano tipo di pattern
 * - Touch 0-3: Trigger per rigenerare il pattern
 *
 * I dati vengono inviati via seriale in formato:
 * pot0,pot1,pot2,pot3,btn0,btn1,btn2,btn3,touch0
 *
 * Usare con p5.js e p5.web-serial library
 */

#include "Artboard.h"

Artboard artboard;

// Previous button states for edge detection
int prevButton[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int prevTouch[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);

  // Initialize LED
  pinMode(13, OUTPUT);

  // Wait for serial connection
  while (!Serial) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

  digitalWrite(13, HIGH);
}

void loop() {
  // Read potentiometers (0-1023)
  int pot0 = artboard.pot(0);
  int pot1 = artboard.pot(1);
  int pot2 = artboard.pot(2);
  int pot3 = artboard.pot(3);

  // Read buttons (HIGH/LOW)
  int btn0 = artboard.button(0);
  int btn1 = artboard.button(1);
  int btn2 = artboard.button(2);
  int btn3 = artboard.button(3);

  // Read touch input
  int touch0 = artboard.touch(0);

  // Detect button press (edge detection)
  int btnPress = 0;
  for (int i = 0; i < 4; i++) {
    int currentBtn = (i == 0) ? btn0 : (i == 1) ? btn1 : (i == 2) ? btn2 : btn3;
    if (currentBtn == HIGH && prevButton[i] == LOW) {
      btnPress = i + 1; // Button 1-4
    }
    prevButton[i] = currentBtn;
  }

  // Detect touch trigger
  int touchTrigger = 0;
  if (touch0 > 1000 && prevTouch[0] <= 1000) {
    touchTrigger = 1;
  }
  prevTouch[0] = touch0;

  // Send data as CSV
  Serial.print(pot0);
  Serial.print(",");
  Serial.print(pot1);
  Serial.print(",");
  Serial.print(pot2);
  Serial.print(",");
  Serial.print(pot3);
  Serial.print(",");
  Serial.print(btnPress);  // 0 or 1-4
  Serial.print(",");
  Serial.println(touchTrigger);  // 0 or 1

  delay(50);  // Send at ~20Hz
}
