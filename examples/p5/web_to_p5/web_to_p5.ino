
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
String val;     // Data received from serial port
int ledPin = 13;  // Arduino built-in LED
bool ledState = false;


int pos = 0;    // variable to store the servo position 
 

void setup() {
   myservo.attach(17);  // attaches the servo on pin 9 to the servo object 
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    val = "";
    if (Serial.available()) {
        // If data is available to read,
        val = Serial.readStringUntil('\n');
        val.trim();
    }

    if (val == "clicked!") {
   
      digitalWrite(ledPin, HIGH); 
      myservo.write(180);              // tell servo to go to position in variable 'pos' 
      delay(15); 
    }
    else if (val == "not clicked!"){
       digitalWrite(ledPin, LOW);
             myservo.write(0);              // tell servo to go to position in variable 'pos' 
      delay(15); 
}
}