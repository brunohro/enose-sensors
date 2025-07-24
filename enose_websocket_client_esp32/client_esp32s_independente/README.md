# 🔌 ESP32 com Sensores MQ5 e MQ8 + LCD + WebSocket

Este projeto utiliza um **ESP32** para ler sensores de gás **MQ5** e **MQ8**, calcular a média de suas leituras e enviar os dados via **WebSocket** para um servidor. As médias também são exibidas em um **LCD I2C 16x2**.

## 🚀 Funcionalidades

- Conexão com rede **Wi-Fi**
- Leitura dos sensores **MQ5 (Gás LPG/GLP)** e **MQ8 (Hidrogênio)**
- Cálculo de **média de 10 leituras** por sensor
- Envio dos dados médios para um servidor via **WebSocket**
- Exibição em tempo real das médias no **LCD**

---

## 🛠️ Componentes Utilizados

| Componente           | Descrição                        |
| -------------------- | -------------------------------- |
| ESP32                | Microcontrolador Wi-Fi/Bluetooth |
| MQ5                  | Sensor de gás LPG/GLP            |
| MQ8                  | Sensor de hidrogênio             |
| LCD 16x2 I2C         | Display para exibição dos dados  |
| Jumpers e protoboard | Conexões e prototipagem          |

---

## ⚙️ Conexões

| Sensor | Pino ESP32 |
| ------ | ---------- |
| MQ5    | GPIO34     |
| MQ8    | GPIO35     |

> _Importante:_ Esses pinos fazem parte do ADC1, ideal para leituras analógicas no ESP32.

### LCD I2C

| LCD | ESP32  |
| --- | ------ |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

## 📶 Configuração Wi-Fi e WebSocket

No código, edite as seguintes linhas com seus dados:

```cpp
const char* ssid = "Redmi_Note_Java";
const char* password = "12345678";
const char* websocket_server = "192.168.147.91";
const int websocket_port = 8765;
```
