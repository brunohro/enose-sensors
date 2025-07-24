#include <WiFi.h>
#include <WebSocketsClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//////////////////// CONFIGURAÇÕES /////////////////////////

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi
const char* ssid = "Redmi_Note_Java";
const char* password = "12345678";

// WebSocket
const char* websocket_server = "192.168.147.91";
const int websocket_port = 8765;
WebSocketsClient webSocket;

// Sensores
const int NUM_SENSORES = 2;
const int tempo = 10;  // número de leituras por sensor

struct Sensor {
  const char* nome;
  int pino;
  float leituras[10];
  float media;
};

Sensor sensores[NUM_SENSORES] = {
  {"MQ5", 34, {}, 0},    // GPIO34 (ADC1_CH6)
  {"MQ8", 35, {}, 0},    // GPIO35 (ADC1_CH7)
};

int espera = 0;

////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  // Iniciar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();

  // Conectar WiFi
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi conectado");
  delay(1000);

  // Iniciar WebSocket
  webSocket.begin(websocket_server, websocket_port, "/");
}

void loop() {
  webSocket.loop();

  if (espera == 10) {
    lerSensores();
    enviarWebSocket();
    mostrarNoLCD();
    espera = 0;
  }

  delay(1000);
  espera++;
}

//////////////////// FUNÇÕES //////////////////////////////

void lerSensores() {
  for (int i = 0; i < tempo; i++) {
    for (int s = 0; s < NUM_SENSORES; s++) {
      int leitura = analogRead(sensores[s].pino);
      float valor = (leitura * 100.0) / 4095.0; // ESP32 usa 12 bits: 0–4095
      sensores[s].leituras[i] = valor;
    }
    delay(1000);
  }

  for (int s = 0; s < NUM_SENSORES; s++) {
    float soma = 0;
    for (int i = 0; i < tempo; i++) {
      soma += sensores[s].leituras[i];
    }
    sensores[s].media = soma / tempo;
  }
}

void enviarWebSocket() {
  String mensagem = String(sensores[0].media, 1);
  for (int i = 1; i < NUM_SENSORES; i++) {
    mensagem += "," + String(sensores[i].media, 1);
  }
  webSocket.sendTXT(mensagem);
  Serial.println("Enviado: " + mensagem);
}

void mostrarNoLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("M5:");
  lcd.print(sensores[0].media, 1);
  lcd.print(" M8:");
  lcd.print(sensores[1].media, 1);
}
