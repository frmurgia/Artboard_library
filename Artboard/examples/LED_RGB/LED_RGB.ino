 
 
 /*
<><><><><><><><><><><><><><><><><><><>
--------------------------------------
             ART-BOARD
     Prototyping board for atist
    
by daniele murgia © 2019-20 MIT License
      sgtmurgia@gmail.com
--------------------------------------
<><><><><><><><><><><><><><><><><><><>




*//******************** definizione delle costanti **********************************/
int portarossa = 35; // porta 35 da collegare all’anodo “rosso” del modulo RGB
int portaverde = 36; // porta 36 da collegare all’anodo “verde” del modulo RGB
int portablu = 37; // porta 37 da collegare all’anodo “blu” del modulo RBG

/**********************routine di accensione del led ********************************
nelle prossime righe viene definita la routine “colore” che, al momento del lancio, e’
accompagnata da tre variabili (rosso, verde e blu) che contengono i valori dell’intensita’
luminosa, di volta in volta voluta, per ogni singolo led (0 = minima e 255 = massima) */
void colore (unsigned char rosso, unsigned char verde, unsigned char blu)
{
 analogWrite(portarossa, rosso); //attiva il led rosso con l’intensita’ definita nella variabile rosso
 analogWrite(portablu, blu); //attiva il led blu con l’intensita’ definita nella variabile blu
 analogWrite(portaverde, verde); //attiva il led verde con l’intensita’ definita nella variabile verde
}

void setup()
{
 pinMode(portarossa, OUTPUT); // dichiara la porta 11 come porta di output
 pinMode(portaverde, OUTPUT); // dichiara la porta 10 come porta di output
 pinMode(portablu, OUTPUT); // dichiara la porta 9 come porta di output
}

void loop()
{
 // gestione colori (tra parentesi il valore da inserire nei tre parametri (rosso, verde e blu)
 colore(255, 0, 0); // lancia la routine colore, con il parametro rosso a 255, il verde a 0
 // ed il blu a 0 (accende il rosso)
 delay(2000); // aspetta 2 secondi prima di accendere il successivo colore
 colore(0,255, 0); // lancia la routine colore ed accende il verde
 delay(2000); // aspetta 2 secondi
 colore(0, 0, 255); // accende il blu
 delay(2000);
 colore(237,109,0); // accende l’arancione (237 di rosso e 109 di verde)
 delay(2000);
 colore(255,215,0); // accende il giallo (255 di rosso e 215 di verde)
 delay(2000);
 colore(0,46,90); // accende l’indaco (46 di verde e 90 di blu)
 delay(2000);
 colore(128,0,128); // accende il viola (128 di rosso e 128 di blu)
 delay(2000);
 colore(0,0,0); // spegne tutto e ricomincia
 delay(2000);
}
