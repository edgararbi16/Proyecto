#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "IFP";   // escribir aquí el SSID de una WiFi
const char* password = "ifpformacion"; // escribir aquí la contraseña de la WiFi 

void setup(){ 
  Serial.begin(9600); // abre un puerto serie y establece la velocidad de transmisión
  delay(2000); 
  Serial.println("Setup start"); 
  WiFi.begin(ssid, password); 
  Serial.println(String("Connecting to ")+ssid);

while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.print(".");
}
Serial.println("\nConnected, IP address: ");
Serial.println(WiFi.localIP());
Serial.println("Setup end");
}
void loop() { 
}
