
#include "Artboard.h"
Artboard artboard;
int led= 13;

void setup() {
    pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (artboard.button(0) == HIGH) {
        digitalWrite(led,HIGH);
        Serial.println("Change");
        delay(150);
    }
    else{
      digitalWrite(led,LOW);
    }
}