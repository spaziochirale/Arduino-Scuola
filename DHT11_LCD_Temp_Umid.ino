#include <Wire.h>                  // Libreria per la comunicazione I2C
#include <LiquidCrystal_I2C.h>     // Libreria per il display LCD I2C
#include <DHT.h>                   // Libreria per il sensore DHT11

// Configurazione del sensore DHT11
#define DHTPIN 2                   // Il sensore è collegato al pin 2
#define DHTTYPE DHT11              // Stiamo usando un sensore di tipo DHT11
DHT dht(DHTPIN, DHTTYPE);          // Creazione di un oggetto DHT

// Configurazione del display LCD
#define LCD_ADDRESS 0x3F           // Indirizzo del display LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2); // Display 16 colonne, 2 righe

void setup() {
  // Inizializzazione del display
  lcd.init();                      // Avvia il display
  lcd.backlight();                 // Accende la luce del display
  lcd.print("Attendi...");         // Mostra un messaggio iniziale

  // Inizializzazione del sensore DHT11
  dht.begin();
  delay(2000);                     // Aspetta 2 secondi per iniziare
}

void loop() {
  // Legge la temperatura e l'umidità dal sensore
  float temperatura = dht.readTemperature();
  float umidita = dht.readHumidity();

  // Se c'è un errore di lettura, mostra un messaggio
  if (isnan(temperatura) || isnan(umidita)) {
    lcd.clear();
    lcd.print("Errore sensore!");
    delay(2000);                   // Aspetta 2 secondi e riprova
    return;
  }

  // Mostra i dati sul display
  lcd.clear();                     // Pulisce lo schermo
  lcd.setCursor(0, 0);             // Posiziona il testo sulla prima riga
  lcd.print("Temp: ");
  lcd.print(temperatura);          // Mostra la temperatura
  lcd.print(" C");

  lcd.setCursor(0, 1);             // Posiziona il testo sulla seconda riga
  lcd.print("Umidita: ");
  lcd.print(umidita);              // Mostra l'umidità
  lcd.print(" %");

  delay(2000);                     // Aspetta 2 secondi prima della prossima lettura
}
