
#include <Arduino.h>
#include <DHT.h>
#include <esp_system.h>

#define PINO_DHT 15
#define TIPO_DHT DHT22

DHT dht(PINO_DHT, TIPO_DHT);

String identificadorExecucao;
unsigned long contadorLeituras = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Identifica esta execução do ESP32.
  identificadorExecucao = String(esp_random(), HEX);

  Serial.println("TCC - Monitoramento IoT de Madeiras");
}

void loop() {
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler sensor DHT22");
  } else {
    contadorLeituras++;

    String identificador = "ESP32-WOKWI-" +
                          identificadorExecucao + "-" +
                          String(contadorLeituras);

    Serial.print("{\"dispositivo\":\"ESP32-WOKWI\",");
    Serial.print("\"identificador_leitura\":\"");
    Serial.print(identificador);
    Serial.print("\",\"temperatura\":");
    Serial.print(temperatura, 2);
    Serial.print(",\"umidade\":");
    Serial.print(umidade, 2);
    Serial.println("}");
  }

  delay(10000);
}
