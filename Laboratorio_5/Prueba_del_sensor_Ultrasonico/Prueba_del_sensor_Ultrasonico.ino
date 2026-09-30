#define TRIG_PIN 18
#define ECHO_PIN 19

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {

  // Aseguramos que TRIG comience apagado
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Enviamos pulso de 10 microsegundos
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Medimos cuánto tiempo tarda en regresar el eco
  long duracion = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duracion == 0) {

    Serial.println("No se detectó eco");

  } else {

    // Velocidad del sonido ≈ 0.0343 cm/us
    float distancia = (duracion * 0.0343) / 2;

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }

  delay(500);
}