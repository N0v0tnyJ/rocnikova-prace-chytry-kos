// Verze v2 - Ultrazvukový senzor + Servomotor (základ kódu s pomocí AI - Google Gemini, 2026)
#include <Servo.h>

const int PIN_TRIG = 9;
const int PIN_ECHO = 8;
const int PIN_SERVO = 10;

Servo vikoServo; // Vytvoření objektu pro ovládání serva

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  vikoServo.attach(PIN_SERVO); // Připojení serva na pin 10
  vikoServo.write(0);          // Výchozí poloha: zavřeno (0 stupňů)
  
  Serial.begin(9600);
}

void loop() {
  // 1. Změření vzdálenosti
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long trvani = pulseIn(PIN_ECHO, HIGH, 30000);
  long vzdalenost = trvani * 0.034 / 2;

  Serial.print("Vzdalenost: ");
  Serial.print(vzdalenost);
  Serial.println(" cm");

  // 2. Rozhodování: Když je ruka do 20 cm, otevři víko
  if (vzdalenost > 0 && vzdalenost <= 20) {
    Serial.println("Detekovana ruka -> OTEVIRAM VIKO!");
    vikoServo.write(90); // Otočí páčku serva na 90 stupňů
    delay(3000);         // Počká 3 sekundy (3000 ms)
    Serial.println("ZAVIRAM VIKO...");
    vikoServo.write(0);  // Vrátí páčku zpět na 0 stupňů
  }

  delay(200);
}