# 📟 Monitor de Sensores MQ com LCD I2C e Arduino

Este projeto utiliza um **Arduino** para ler dados de 4 sensores de gás do tipo **MQ** e exibir suas médias em um **display LCD I2C 16x2**. Os sensores são lidos a cada 10 segundos, e os dados também são enviados pela **porta serial**.

## 🚀 Funcionalidades

- Leitura dos sensores: **MQ3, MQ5, MQ2 e MQ135**
- Cálculo da **média** de 10 amostras para cada sensor
- Exibição das médias no **display LCD I2C 16x2**
- Envio das médias para o **monitor serial** no formato CSV

## 🛠️ Materiais Utilizados

- Arduino Uno (ou similar)
- Sensor MQ3
- Sensor MQ5
- Sensor MQ2
- Sensor MQ135
- Display LCD 16x2 com módulo I2C
- Jumpers e protoboard

## 📄 Esquema de Conexão

| Sensor | Pino Analógico |
| ------ | -------------- |
| MQ3    | A0             |
| MQ5    | A1             |
| MQ2    | A2             |
| MQ135  | A3             |

O módulo LCD I2C é conectado via protocolo **I2C**:

- SDA → A4 (no Uno)
- SCL → A5 (no Uno)

## 🧠 Lógica do Código

- O programa espera **10 segundos**
- Durante esse tempo, coleta **10 amostras** por sensor (1 por segundo)
- Calcula a **média** das leituras
- Exibe os valores médios no **LCD** e no **Serial Monitor**

### 📦 Bibliotecas Usadas

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```
