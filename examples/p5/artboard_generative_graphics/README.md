# Artboard Generative Graphics

Pattern generativi minimalisti in stile Sol LeWitt, controllati in tempo reale da Artboard.

![Sol LeWitt Wall Drawing](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6e/Sol_LeWitt_-_Wall_Drawing_260_at_Akron_Art_Museum.jpg/800px-Sol_LeWitt-_Wall_Drawing_260_at_Akron_Art_Museum.jpg)

## Descrizione

Questo esempio genera grafiche minimaliste algoritmiche ispirate alle opere di Sol LeWitt, con parametri controllati in tempo reale dai potenziometri e pulsanti di Artboard.

L'artista Sol LeWitt è famoso per i suoi "Wall Drawings" - istruzioni scritte che vengono eseguite da altre persone per creare opere d'arte. Questo progetto traduce quel concetto in algoritmi generativi controllabili.

## Pattern Disponibili

1. **Parallel Lines** (Linee Parallele): Linee verticali con variazione controllabile
2. **Concentric Circles** (Cerchi Concentrici): Cerchi e archi dal centro
3. **Grid** (Griglia): Pattern a griglia con elementi variabili (linee, cerchi, quadrati)
4. **Mixed** (Misto): Combinazione di strutture multiple

## Controlli Artboard

- **Potenziometro 0**: Numero di linee/elementi (10-200)
- **Potenziometro 1**: Spaziatura/margine (2-50 pixel)
- **Potenziometro 2**: Rotazione (0-360°)
- **Potenziometro 3**: Variazione/complessità (0-100%)
- **Pulsante 1**: Pattern "Parallel Lines"
- **Pulsante 2**: Pattern "Concentric Circles"
- **Pulsante 3**: Pattern "Grid"
- **Pulsante 4**: Pattern "Mixed"
- **Touch 0**: Rigenera il pattern corrente

## Controlli Tastiera (opzionali)

- **1-4**: Cambia pattern
- **Spazio**: Rigenera pattern
- **S**: Salva immagine come JPG

## Setup

### Hardware
1. Artboard con Teensy 3.6
2. Cavo USB per connessione

### Software
1. Carica lo sketch Arduino (`artboard_generative_graphics.ino`) su Teensy
2. Apri `index.html` in Chrome (richiesto per Web Serial API)
3. Clicca sul pulsante "Connect" e seleziona la porta seriale di Artboard
4. Inizia a controllare i pattern con i potenziometri e pulsanti!

## Tecnologie Utilizzate

- **p5.js**: Libreria JavaScript per grafica generativa
- **p5.web-serial**: Comunicazione Web Serial API senza server
- **Teensy 3.6**: Microcontrollore per lettura controlli

## Web Serial API

Questo esempio usa la Web Serial API per comunicare direttamente tra browser e Artboard, senza bisogno di server intermediari.

Requisiti:
- Browser: Chrome/Edge (versione 89+)
- Sistema: Windows, macOS, Linux, ChromeOS
- Connessione: HTTPS o localhost

## Filosofia del Progetto

Ispirato alle opere concettuali di Sol LeWitt, questo progetto esplora:
- **Istruzioni vs Esecuzione**: L'algoritmo è l'istruzione, il computer l'esecutore
- **Variazione controllata**: Parametri definiti ma con casualità limitata
- **Minimalismo**: Forme semplici, regole chiare
- **Riproducibilità**: Stesso algoritmo, risultati simili ma unici

## Estensioni Possibili

- Aggiungere più pattern (onde sinusoidali, frattali, Truchet tiles)
- Salvare sequenze di pattern come animazioni
- Utilizzare più touch input per controlli aggiuntivi
- Integrare il colore controllato dai potenziometri
- Esportare le "istruzioni" (parametri) come file JSON

## Riferimenti

- [Sol LeWitt - Wall Drawings](https://massmoca.org/sol-lewitt/)
- [p5.js Examples](https://p5js.org/examples/)
- [Generative Art Theory](https://www.artnome.com/news/2018/8/8/why-love-generative-art)
- [Web Serial API](https://web.dev/serial/)

## Variante: Sol LeWitt Original

Per un esempio più fedele allo stile originale di Sol LeWitt, vedi il progetto:
https://github.com/frmurgia/sol_lewitt

## Licenza

MIT
