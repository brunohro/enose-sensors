////////////////////////VARIÁVEIS//////////////////////////////
//////////////////////////////////////////////////////////////

// Pinos analógicos dos sensores MQ
const int pin_MQ3 = A0; 
const int pin_MQ5 = A1;

float mediaValoresLidosMQ3 = 0;
float mediaValoresLidosMQ5 = 0;

int tempo = 10; // tempo reduzido para 10 segundos
int espera = 0;

float valoresLidosMQ3[10];
float valoresLidosMQ5[10];

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200); 
}

void loop() {
  
  if (espera == 60) {  // reduzido de 60 para 10
    lerSensores();
    String mensagem = String(mediaValoresLidosMQ3) + "-" + String(mediaValoresLidosMQ5);
    Serial.println(mensagem);
    espera = 0;
  }

  delay(1000); 
  espera++;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void lerSensores() {
  for (int i = 0; i < tempo; i++) {
    int leituraMQ3 = analogRead(pin_MQ3);
    int leituraMQ5 = analogRead(pin_MQ5);

    float valorSensorMQ3 = (leituraMQ3 * 100.0) / 1024.0;
    float valorSensorMQ5 = (leituraMQ5 * 100.0) / 1024.0;

    valoresLidosMQ3[i] = valorSensorMQ3;
    valoresLidosMQ5[i] = valorSensorMQ5;

    delay(1000); // mantém 1 segundo entre as leituras
  }

  float acumuladosMQ3 = 0;
  float acumuladosMQ5 = 0;

  for (int i = 0; i < tempo; i++) {
    acumuladosMQ3 += valoresLidosMQ3[i];
    acumuladosMQ5 += valoresLidosMQ5[i];
  }

  mediaValoresLidosMQ3 = acumuladosMQ3 / tempo;
  mediaValoresLidosMQ5 = acumuladosMQ5 / tempo;
}
