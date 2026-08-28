#include <SPI.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================
// OLED
// =====================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 26
#define OLED_SCL 27

Adafruit_SSD1306 display(
SCREEN_WIDTH,
SCREEN_HEIGHT,
&Wire,
-1
);

// =====================================
// RADIO
// =====================================

#define CE_PIN 22
#define CSN_PIN 21

RF24 radio(CE_PIN, CSN_PIN);

const byte endereco[6] = "00001";

// =====================================
// BATERIA GATEWAY
// =====================================

#define BAT_ADC 34

// =====================================
// DADOS RECEBIDOS
// =====================================

struct DadosClima
{
float temperatura;
float umidade;
float bateriaTX;
uint32_t contador;
};

DadosClima dados;

unsigned long ultimoPacote = 0;
bool semSinal = true;

// =====================================

float lerBateriaGateway()
{
int leitura = analogRead(BAT_ADC);

float tensaoGPIO =
leitura * 3.3 / 4095.0;

// divisor 100k / 100k

float tensaoBateria =
tensaoGPIO * 2.0;

return tensaoBateria;
}

// =====================================

int calculaPercentual(float v)
{
const float VMIN = 3.30;
const float VMAX = 4.20;

int pct =
((v - VMIN) * 100.0) /
(VMAX - VMIN);

if (pct < 0) pct = 0;
if (pct > 100) pct = 100;

return pct;
}

// =====================================

void telaSemSinal()
{
display.clearDisplay();

display.setTextColor(WHITE);

display.setTextSize(2);

display.setCursor(12,10);
display.println("SEM");

display.setCursor(12,38);
display.println("SINAL");

display.display();
}

// =====================================

void mostrarDados()
{
float batGW =
lerBateriaGateway();

int pctGW =
calculaPercentual(
batGW);

int pctTX =
calculaPercentual(
dados.bateriaTX);

display.clearDisplay();

display.setTextColor(WHITE);

display.setTextSize(1);

display.setCursor(0,0);
display.println("ESTACAO REMOTA");

display.drawLine(
0,
10,
127,
10,
WHITE);

display.setCursor(0,14);
display.print("GW ");
display.print(batGW,2);
display.print("V ");
display.print(pctGW);
display.print("%");

display.setCursor(0,26);
display.print("TX ");
display.print(dados.bateriaTX,2);
display.print("V ");
display.print(pctTX);
display.print("%");

display.setCursor(0,40);
display.print("T:");
display.print(
dados.temperatura,
1);
display.print("C");

display.setCursor(68,40);
display.print("U:");
display.print(
dados.umidade,
1);
display.print("%");

display.setCursor(0,54);
display.print("PKT:");
display.print(
dados.contador);

display.display();
}

// =====================================

void setup()
{
Serial.begin(115200);

Serial.println();
Serial.println("BOOT");

analogReadResolution(12);

Wire.begin(
OLED_SDA,
OLED_SCL);

delay(100);

if (!display.begin(
SSD1306_SWITCHCAPVCC,
0x3C))
{
Serial.println(
"ERRO OLED");

while (1);
}

display.clearDisplay();

display.setTextSize(2);
display.setTextColor(WHITE);

display.setCursor(0,20);
display.println("GATEWAY");

display.display();

delay(1500);

Serial.println("OLED OK");

SPI.begin(
18,
19,
23,
21);

Serial.println(
"TESTANDO RADIO");

if (!radio.begin())
{
Serial.println(
"ERRO RADIO");

display.clearDisplay();

display.setCursor(0,20);
display.println(
"RADIO ERRO");

display.display();

while (1);
}

Serial.println(
"RADIO OK");

radio.setChannel(100);

radio.setDataRate(
RF24_250KBPS);

radio.setPALevel(
RF24_PA_LOW);

radio.openReadingPipe(
0,
endereco);

radio.startListening();

ultimoPacote = millis();

telaSemSinal();

Serial.println(
"Gateway pronto");
}

// =====================================

void loop()
{
if (radio.available())
{
radio.read(
&dados,
sizeof(dados));

ultimoPacote = millis();

semSinal = false;

float batGW =
lerBateriaGateway();

Serial.println(
"---------------------");

Serial.print("GW: ");
Serial.print(
batGW,
2);
Serial.println("V");

Serial.print("TX: ");
Serial.print(
dados.bateriaTX,
2);
Serial.println("V");

Serial.print("Temp: ");
Serial.print(
dados.temperatura,
1);
Serial.println(" C");

Serial.print("Umid: ");
Serial.print(
dados.umidade,
1);
Serial.println(" %");

Serial.print("Pacote: ");
Serial.println(
dados.contador);

mostrarDados();
}

if (
millis() -
ultimoPacote >
15000)
{
if (!semSinal)
{
telaSemSinal();

semSinal = true;

Serial.println(
"SEM SINAL");
}
}
}


