#include <Wire.h>  // Includiamo la libreria Wire per comunicare con dispositivi I2C

void setup() {
  Wire.begin();          // Iniziamo la comunicazione I2C
  Serial.begin(9600);    // Avviamo la comunicazione seriale per vedere i risultati sul computer
  Serial.println("Scansione I2C...");  // Messaggio iniziale

  // Iniziamo a cercare i dispositivi I2C sugli indirizzi da 1 a 126
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);      // Proviamo a contattare ogni indirizzo I2C
    if (Wire.endTransmission() == 0) {  // Se riceviamo risposta...
      Serial.print("Dispositivo trovato all'indirizzo 0x");  // Stampiamo il messaggio
      Serial.println(i, HEX);  // Mostriamo l'indirizzo in formato esadecimale
    }
  }
}

void loop() {
  // Il programma non deve fare altro, quindi lasciamo il loop vuoto
}
