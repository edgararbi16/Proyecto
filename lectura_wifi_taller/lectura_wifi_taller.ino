#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>

// Constantes
#define SDA_PIN 22
#define RST_PIN 27
#define LED_PIN 2 // Pin del LED AZUL

// Parámetros de red WiFi
const char* ssid = "TP-TALLER"; // Nombre de tu red WiFi
const char* password = "Alg0qwe!"; // Contraseña de tu red WiFi

// Variables
byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SDA_PIN, RST_PIN);

void setup() {
  // Inicialización del puerto serie
  Serial.begin(115200);
  Serial.println(F("Inicializando Sistema"));
 
  SPI.begin();
  rfid.PCD_Init();
  Serial.print(F("Lector: "));
  rfid.PCD_DumpVersionToSerial();

  // Inicialización del pin del LED
  pinMode(LED_PIN, OUTPUT);
  
  // Conexión a la red WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  // Esperar a que se conecte a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conexión WiFi establecida");

  // Mostrar la dirección IP
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Encender el LED cuando la conexión WiFi se establezca
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  readRFID();
}

void readRFID(void) {
  // Leer tarjeta RFID
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  // Buscar nuevas tarjetas
  if (!rfid.PICC_IsNewCardPresent())
    return;
  
  // Verificar si se ha leído el NUID
  if (!rfid.PICC_ReadCardSerial())
    return;
  
  // Almacenar NUID en el arreglo nuidPICC
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  Serial.print(F("RFID en decimal: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  
  // Detener la tarjeta PICC
  rfid.PICC_HaltA();
  
  // Detener la encriptación en PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
