// Testovací kód v1 - Měření vzdálenosti (základ s pomocí AI - Google Gemini, 2026)
const int PIN_TRIG = 9;
const int PIN_ECHO = 8;

void setup() {
  pinMode(PIN_TRIG, OUTPUT); // Pin 9 vysílá signál ven
  pinMode(PIN_ECHO, INPUT);  // Pin 8 přijímá odraz dovnitř
  Serial.begin(9600);        // Spustí textový výpis na obrazovku
}

void loop() {
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
  delay(500);
}