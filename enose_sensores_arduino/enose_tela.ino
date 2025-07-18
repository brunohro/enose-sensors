#include <Wire.h>
#include <LiquidCrystal_I2C.h>

////////////////////////// LCD CONFIG ////////////////////////////
/////////////////////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C pode ser 0x27 ou 0x3F

//////////////////////////ESTRUTURAS//////////////////////////////
/////////////////////////////////////////////////////////////////

const int NUM_SENSORES = 4;

struct Sensor {
    const char* nome;
    int pino;
    float leituras[10];
    float media;
};

Sensor sensores[NUM_SENSORES] = {
    {"MQ3", A0, {}, 0},
    {"MQ5", A1, {}, 0},
    {"MQ2", A2, {}, 0},
    {"MQ135", A3, {}, 0},
};

int tempo = 10;
int espera = 0;

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);

    // Inicializa o LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Sistema iniciado");
    delay(2000);
    lcd.clear();
}

void loop() {
    if (espera == 10) {
        lerTodosSensores();
        imprimirMedias();
        mostrarNoLCD();
        espera = 0;
    }

    delay(1000);
    espera++;
}

///////////////////////// LER SENSORES //////////////////////////
/////////////////////////////////////////////////////////////////

void lerTodosSensores() {
    for (int i = 0; i < tempo; i++) {
        for (int s = 0; s < NUM_SENSORES; s++) {
            int leitura = analogRead(sensores[s].pino);
            float valor = (leitura * 100.0) / 1024.0;
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

////////////////////////// IMPRIMIR SERIAL ///////////////////////
/////////////////////////////////////////////////////////////////

void imprimirMedias() {
    Serial.print(sensores[0].media);
    for (int s = 1; s < NUM_SENSORES; s++) {
        Serial.print(",");
        Serial.print(sensores[s].media);
    }
    Serial.println();
}

/////////////////////// MOSTRAR NO LCD ///////////////////////////
/////////////////////////////////////////////////////////////////

void mostrarNoLCD() {
    lcd.clear();

    // Primeira linha: MQ3 e MQ5
    lcd.setCursor(0, 0);
    lcd.print("M3:");
    lcd.print(sensores[0].media, 1);
    lcd.print(" M5:");
    lcd.print(sensores[1].media, 1);

    // Segunda linha: MQ2 e MQ135
    lcd.setCursor(0, 1);
    lcd.print("M2:");
    lcd.print(sensores[2].media, 1);
    lcd.print(" M135:");
    lcd.print(sensores[3].media, 1);
}
