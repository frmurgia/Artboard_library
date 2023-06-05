
  /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
Titolo progetto: touchin 
Descrizione: funzionamento libreria touch

chiamare artboard.touch(i) per leggere l'ingresso capacitivo 
i equivale alla posizione di T
0=do
1=do#
2=re#
ecc.

by Daniele Murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>

*/
#include <Artboard.h> // includiamo la libreria

Artboard artboard;

void setup(){
  Serial.begin(9600);
}


void loop(){
  int t0=artboard.touch(0);
  Serial.println(t0);
  delay(100);
}
