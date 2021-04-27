/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
  Titolo progetto: Artboard v2
  Descrizione: potenziometri
  by daniele murgia © 2021 MIT License
  --------------------------------------
  <><><><><><><><><><><><><><><><><><><>
*/
/*      TEENSY 3.6 PINOUT     */
int pot1 = 31; //  D31 = A12
int pot2 = 32 ; // D32 = A13
int pot3 = 33 ; // D33 = A14
int pot4 = 34 ; // D34 = A15
int pot5 = 35 ; // D35 = A16
int pot6 = 36 ; // D36 = A17
int pot7 = 37 ; // D37 = A18
int pot8 = 38 ; // D38 = A19


void setup() {
  Serial.begin(9600);

}

void loop() {
  //dichiaro una nuova variabile intera in cui viene assegnato il valore analogico letto dal pin pot1
  int valpot1 = analogRead(pot1);
  int valpot2 = analogRead(pot2);
  int valpot3 = analogRead(pot3);
  int valpot4 = analogRead(pot4);
  int valpot5 = analogRead(pot5);
  int valpot6 = analogRead(pot6);
  int valpot7 = analogRead(pot7);
  int valpot8 = analogRead(pot8);

  //stampo i risultati sul serial monitor
  Serial.print(":P1 ");
  Serial.print(valpot1);
  Serial.print(":P2 ");
  Serial.print(valpot2);
  Serial.print(":P3 ");
  Serial.print(valpot3);
  Serial.print(":P4 ");
  Serial.print(valpot4);
  Serial.print(":P5 ");
  Serial.print(valpot5);
  Serial.print(":P6 ");
  Serial.print(valpot6);
  Serial.print(":P7 ");
  Serial.print(valpot7);
  Serial.print(":P8 ");
  Serial.println(valpot8);


  delay(100);

}
