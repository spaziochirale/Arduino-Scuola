v#include <Wire.h>                  // Libreria per la comunicazione I2C
#include <LiquidCrystal_I2C.h>     // Libreria per il display LCD I2C
#include <DHT.h>                   // Libreria per il sensore DHT11

// Configurazione del sensore DHT11
#define DHTPIN 2                   // Il sensore è collegato al pin 2
#define DHTTYPE DHT11              // Stiamo usando un sensore di tipo DHT11
DHT dht(DHTPIN, DHTTYPE);          // Creazione di un oggetto DHT

// Configurazione del display LCD
#define LCD_ADDRESS 0x3F           // Indirizzo del display LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2); // Display 16 colonne, 2 righe

// Configurazione dei LED
#define GREEN_LED 10               // LED verde collegato al pin 10
#define YELLOW_LED 11              // LED giallo collegato al pin 11
#define RED_LED 12                 // LED rosso collegato al pin 12

void setup() {
  // Inizializzazione del display
  lcd.init();                      // Avvia il display
  lcd.backlight();                 // Accende la luce del display
  lcd.print("Attendi...");         // Mostra un messaggio iniziale

  // Inizializzazione del sensore DHT11
  dht.begin();
  delay(2000);                     // Aspetta 2 secondi per iniziare

  // Configurazione dei pin dei LED come uscite
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Spegne tutti i LED all'avvio
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  // Legge la temperatura dal sensore
  float temperatura = dht.readTemperature();

  // Se c'è un errore di lettura, mostra un messaggio
  if (isnan(temperatura)) {
    lcd.clear();
    lcd.print("Errore sensore!");
    delay(2000);                   // Aspetta 2 secondi e riprova
    return;
  }

  // Mostra la temperatura sul display
  lcd.clear();
  lcd.setCursor(0, 0);             // Posiziona il testo sulla prima riga
  lcd.print("Temp: ");
  lcd.print(temperatura);          // Mostra la temperatura
  lcd.print(" C");

  // Controlla la temperatura e accende il LED corrispondente
  if (temperatura >= 10 && temperatura <= 14) {
    digitalWrite(GREEN_LED, HIGH); // Accende il LED verde
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  } else if (temperatura >= 15 && temperatura <= 19) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH); // Accende il LED giallo
    digitalWrite(RED_LED, LOW);
  } else if (temperatura >= 20) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);    // Accende il LED rosso
  } else {
    // Spegne tutti i LED se la temperatura è sotto 10 gradi
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }

  delay(2000);                     // Aspetta 2 secondi prima della prossima lettura
}
