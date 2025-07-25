#include <WiFi.h>
#include <WebSocketsClient.h>

/////////////////////////VARIÁVEIS////////////////////////////
//////////////////////////////////////////////////////////////

//Id e senha da rede
const char* ssid = "Redmi_Note_Java";
const char* password = "12345678";

//Ip e porta do websocket
const char* websocket_server = "192.168.147.215"; // endereço ip da máquina de Samuel
const int websocket_port = 8765;

WebSocketsClient webSocket;

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Conectado!");
  webSocket.begin(websocket_server, websocket_port, "/");
}

void loop() {
  webSocket.loop();

  if (Serial.available() > 0) {
    String sensor_data = Serial.readStringUntil('\n');
    webSocket.sendTXT(sensor_data);
    Serial.println("MENSAGEM ENVIADA");
  }
 delay(1000);
}