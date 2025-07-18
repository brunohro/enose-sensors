//////////////////////////ESTRUTURAS//////////////////////////////
/////////////////////////////////////////////////////////////////

const int NUM_SENSORES = 4; // alterar se adicionar mais sensores

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

int tempo = 10; // segundos
int espera = 0;

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (espera == 10) { // ajustável
        lerTodosSensores();
        imprimirMedias();
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
            float valor = (leitura * 100.0) / 1024.0; // escala de 0 a 100
            sensores[s].leituras[i] = valor;
        }
        delay(1000); // espera 1 segundo entre as leituras
    }

    for (int s = 0; s < NUM_SENSORES; s++) {
        float soma = 0;
        for (int i = 0; i < tempo; i++) {
            soma += sensores[s].leituras[i];
        }
        sensores[s].media = soma / tempo;
    }
}

//////////////////////////IMPRIMIR MEDIAS////////////////////////
/////////////////////////////////////////////////////////////////

void imprimirMedias() {
    // Envia os dados como: 10.42,6.98
    Serial.print(sensores[0].media);
    for (int s = 1; s < NUM_SENSORES; s++) {
        Serial.print(",");
        Serial.print(sensores[s].media);
    }
    Serial.println(); // envia newline no final
}
