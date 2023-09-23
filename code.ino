#include <ESP8266WiFi.h>

const char* ssid = "Tu_SSID";
const char* password = "Tu_Contraseña";
const char* serverAddress = "127.0.0.1"; // Cambia esto por la dirección IP de tu servidor Node.js

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conexión Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al Wi-Fi...");
  }

  Serial.println("Conexión Wi-Fi exitosa");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Crear un objeto WiFiClient
    WiFiClient client;

    // Conectar al servidor Node.js
    if (client.connect(serverAddress, 3000)) {
      Serial.println("Conectado al servidor");

      // Enviar una solicitud GET
      client.println("GET / HTTP/1.1");
      client.println("Host: " + String(serverAddress));
      client.println("Connection: close");
      client.println();
      
      // Esperar la respuesta del servidor
      while (client.connected()) {
        if (client.available()) {
          String line = client.readStringUntil('\r');
          Serial.print(line);
        }
      }
      
      // Cerrar la conexión
      client.stop();
    } else {
      Serial.println("Error de conexión al servidor");
    }

    // Esperar un tiempo antes de la próxima solicitud
    delay(5000);
  }
}
