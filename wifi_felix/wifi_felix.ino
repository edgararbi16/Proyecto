#include <WiFi.h>

const char* ssid = "IFP";         // Nombre de la red WiFi
const char* password = "ifpformacion"; // Contraseña de la red WiFi

IPAddress localIP(192, 168, 1, 123); // Dirección IP estática
IPAddress gateway(192, 168, 1, 1);    // Puerta de enlace
IPAddress subnet(255, 255, 255, 0);   // Máscara de subred
IPAddress dns(8, 8, 8, 8);            // Dirección IP del servidor DNS (puedes usar otra dirección si lo prefieres)

void setup() {
  Serial.begin(115200);

  // Conectar a la red WiFi
  Serial.printf("Conectando a %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Asignar la dirección IP estática
  WiFi.config(localIP, gateway, subnet, dns);

  // Imprimir la dirección IP asignada
  Serial.print("\nIP asignada: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Tu código aquí
}