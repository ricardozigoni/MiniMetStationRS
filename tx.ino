#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

// ======================================
// AHT10
// ======================================

#define SDA_PIN 0
#define SCL_PIN 1

Adafruit_AHTX0 aht;

// ======================================
// RADIO E01
// ======================================

#define CE_PIN 20
#define CSN_PIN 21

#define SCK_PIN 4
#define MISO_PIN 5
#define MOSI_PIN 6

RF24 radio(CE_PIN, CSN_PIN);

const byte endereco[6] = "00001";

// ======================================

struct DadosClima
{
float temperatura;
float umidade;
uint32_t contador;
};

DadosClima dados;

// ======================================

void setup()
{
Serial.begin(115200);

delay(2000);

Serial.println();
Serial.println("========================");
Serial.println("ESTACAO METEOROLOGICA");
Serial.println("========================");

// AHT10

Wire.begin(SDA_PIN, SCL_PIN);

if (!aht.begin())
{
Serial.println("ERRO AHT10");

while (1);
}

Serial.println("AHT10 OK");

// SPI

SPI.begin(
SCK_PIN,
MISO_PIN,
MOSI_PIN,
CSN_PIN
);

// RADIO

if (!radio.begin())
{
Serial.println("ERRO RADIO");

while (1);
}

Serial.println("RADIO OK");

radio.setChannel(100);
radio.setDataRate(RF24_250KBPS);
radio.setPALevel(RF24_PA_LOW);

radio.openWritingPipe(endereco);

radio.stopListening();

dados.contador = 0;

Serial.println("TRANSMISSOR PRONTO");
}

// ======================================

void loop()
{
sensors_event_t humidity;
sensors_event_t temp;

aht.getEvent(&humidity, &temp);

dados.temperatura =
temp.temperature;

dados.umidade =
humidity.relative_humidity;

dados.contador++;

bool status =
radio.write(
&dados,
sizeof(dados));

Serial.println("---------------------");

Serial.print("Pacote: ");
Serial.println(dados.contador);

Serial.print("Temperatura: ");
Serial.print(dados.temperatura, 1);
Serial.println(" C");

Serial.print("Umidade: ");
Serial.print(dados.umidade, 1);
Serial.println(" %");

Serial.print("Transmissao: ");

if (status)
Serial.println("OK");
else
Serial.println("FALHOU");

delay(5000);
}


