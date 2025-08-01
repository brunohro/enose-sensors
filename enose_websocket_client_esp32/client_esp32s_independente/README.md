# 🔌 ESP32 com Sensores MQ5 e MQ8 + WebSocket

Este projeto utiliza um **ESP32** para ler sensores de gás **MQ5** e **MQ8**, calcular a média de suas leituras e enviar os dados via **WebSocket** para um servidor.

## 🚀 Funcionalidades

- Conexão com rede **Wi-Fi**
- Leitura dos sensores **MQ5 (Gás LPG/GLP)** e **MQ8 (Hidrogênio)**
- Cálculo de **média de 10 leituras** por sensor
- Envio dos dados médios para um servidor via **WebSocket**

---

## 🛠️ Componentes Utilizados

| Componente           | Descrição                        |
| -------------------- | -------------------------------- |
| ESP32                | Microcontrolador Wi-Fi/Bluetooth |
| MQ5                  | Sensor de gás LPG/GLP            |
| MQ8                  | Sensor de hidrogênio             |
| Jumpers e protoboard | Conexões e prototipagem          |

---

## ⚙️ Conexões

| Sensor | Pino ESP32 |
| ------ | ---------- |
| MQ5    | GPIO34     |
| MQ8    | GPIO35     |


## 📶 Configuração Wi-Fi e WebSocket

No código, edite as seguintes linhas com seus dados:

```cpp
const char* ssid = "Redmi_Note_Java";
const char* password = "12345678";
const char* websocket_server = "192.168.147.91";
const int websocket_port = 8765;
```
