#include "DHT.h"  // Includiamo la libreria per usare il sensore DHT11

// Indichiamo dove è collegato il sensore e che tipo di sensore stiamo usando
#define DHTPIN 2      // Il sensore DHT11 è collegato al pin digitale 2 di Arduino
#define DHTTYPE DHT11 // Stiamo usando il modello DHT11

// Creiamo un oggetto per controllare il sensore
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Avviamo la comunicazione con il computer per vedere i dati
  Serial.begin(9600);  // Impostiamo la velocità di comunicazione
  Serial.println("DHT11 - Lettura temperatura e umidità");

  // Iniziamo a far funzionare il sensore
  dht.begin();
}

void loop() {
  // Leggiamo il valore dell'umidità (quanta acqua c'è nell'aria)
  float humidity = dht.readHumidity();
  // Leggiamo il valore della temperatura in gradi Celsius
  float temperature = dht.readTemperature();

  // Controlliamo se il sensore sta funzionando bene
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Errore nella lettura dal DHT11"); // Messaggio di errore se il sensore non funziona
    return;  // Interrompe il ciclo se c'è un errore
  }

  // Mostriamo i valori dell'umidità sul computer
  Serial.print("Umidità: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Mostriamo i valori della temperatura sul computer
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Aspettiamo 2 secondi prima di leggere di nuovo i dati
  delay(2000);
}

