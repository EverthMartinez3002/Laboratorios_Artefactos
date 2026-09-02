#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// -----------------------------
// CONFIGURACIÓN DE LA OLED
// -----------------------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Dirección I2C común de la OLED
#define OLED_ADDRESS 0x3C

// -----------------------------
// SENSOR LM35
// -----------------------------

const int lm35Pin = A0;


void setup() {

  Serial.begin(9600);

  // Iniciar comunicación I2C
  Wire.begin();

  // Iniciar OLED
  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("Error al iniciar la pantalla OLED");

    while (1);
  }

  display.clearDisplay();

  display.setTextColor(SH110X_WHITE);

  display.setTextSize(1);

  display.setCursor(10, 20);

  display.println("Iniciando...");

  display.display();

  delay(1500);
}


void loop() {

  // -----------------------------------
  // LEER SENSOR LM35
  // -----------------------------------

  int lectura = analogRead(lm35Pin);


  // -----------------------------------
  // CONVERTIR ADC A VOLTAJE
  // -----------------------------------

  float voltaje =
    lectura * (5.0 / 1024.0);


  // -----------------------------------
  // CONVERTIR VOLTAJE A TEMPERATURA
  //
  // LM35 = 10 mV por grado Celsius
  // 1 V = 100 grados Celsius
  // -----------------------------------

  float temperatura =
    voltaje * 100.0;


  // -----------------------------------
  // MOSTRAR EN MONITOR SERIAL
  // -----------------------------------

  Serial.print("Lectura ADC: ");

  Serial.print(lectura);

  Serial.print(" | Voltaje: ");

  Serial.print(voltaje, 3);

  Serial.print(" V");

  Serial.print(" | Temperatura: ");

  Serial.print(temperatura, 1);

  Serial.println(" C");


  // -----------------------------------
  // MOSTRAR EN OLED
  // -----------------------------------

  display.clearDisplay();

  // Título
  display.setTextColor(SH110X_WHITE);

  display.setTextSize(1);

  display.setCursor(20, 5);

  display.println("TEMPERATURA");


  // Temperatura grande
  display.setTextSize(2);

  display.setCursor(20, 25);

  display.print(temperatura, 1);

  display.print(" C");


  // Mostrar en pantalla
  display.display();


  delay(500);
}