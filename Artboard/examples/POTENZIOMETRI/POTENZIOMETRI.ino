
/*
  <><><><><><><><><><><><><><><><><><><>
  --------------------------------------
            ART-BOARD
    Prototyping board for atist

  by daniele murgia © 2019-20 MIT License
     sgtmurgia@gmail.com
  --------------------------------------
  <><><><><><><><><><><><><><><><><><><>

*/



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // il potenziometro è saldato al contrario per questo utilizzo la funzione map
  //che mi permette di mappare nuovamente il segnale
   // map(myVariabile, valoreMin, ValoreMax, nuovoValoreMax, nuovoValoreMin);
  int pot1 = map(analogRead(A0), 1023, 0, 0, 1023);
  int pot2 = map(analogRead(A1), 1023, 0, 0, 1023);
  int pot3 = map(analogRead(A2), 1023, 0, 0, 1023);
  int pot4 = map(analogRead(A3), 1023, 0, 0, 1023);
  int pot5 = map(analogRead(A12), 1023, 0, 0, 1023);
  int pot6 = map(analogRead(A13), 1023, 0, 0, 1023);

  Serial.print(":P1 ");
  Serial.print(pot1);
  Serial.print(":P2 ");
  Serial.print(pot2);
  Serial.print(":P3 ");
  Serial.print(pot3);
  Serial.print(":P4 ");
  Serial.print(pot4);
  Serial.print(":P5 ");
  Serial.print(pot5);
  Serial.print(":Y6 ");
  Serial.println(pot6);

  delay(1);        // delay in between reads for stability

}
