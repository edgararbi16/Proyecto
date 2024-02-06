#include <MFRC522.h>
#include <SPI.h>

#define SDA_PIN 22 // Pin SDA
#define SCK_PIN 14 // Pin alternativo para SCK
#define MOSI_PIN 16 // Pin MOSI
#define MISO_PIN 17 // Pin MISO
#define RST_PIN 21 // Pin de reset

MFRC522 mfrc522(SDA_PIN, RST_PIN); // Inicializa el objeto MFRC522

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SDA_PIN); // Inicializa SPI
  mfrc522.PCD_Init(); // Inicializa el lector RFID
  Serial.println("Lector RFID listo para leer...");
}

void loop() {
  // Verifica si hay tarjetas presentes
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Lee el UID de la tarjeta
    Serial.print("UID de la tarjeta:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(); // Imprime una nueva línea
    mfrc522.PICC_HaltA(); // Detiene la comunicación con la tarjeta actual
  }
}
