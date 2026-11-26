// Verze v3 - Kompletní řídicí software pro chytrý odpadkový koš
// Základ kódu byl vytvořen s pomocí AI (Google Gemini, 2026) a upraven autorem.
#include <Servo.h>

// Definice pinů
const int PIN_TRIG = 9;        // Ultrazvukový senzor - Trigger
const int PIN_ECHO = 8;        // Ultrazvukový senzor - Echo
const int PIN_SERVO = 10;      // Servomotor (PWM)
const int PIN_TLACITKO = 2;    // Tlačítko pro ruční režim
const int PIN_LED_ZELENA = 4;  // LED indikace - otevřeno
const int PIN_LED_CERVENA = 5; // LED indikace - zavřeno
const int PIN_BUZZER = 6;      // Piezo bzučák

// Parametry a proměnné
const int PRAH_VZDALENOSTI = 20;        // Vzdálenost pro otevření v cm
const int UHEL_ZAVRENO = 0;             // Úhel serva při zavřeném víku
const int UHEL_OTEVRENO = 90;           // Úhel serva při otevřeném víku
const unsigned long CAS_OTEVRENI = 3000; // Doba otevření víka (ms)

Servo vikoServo;
bool manualniRezim = false;
bool posledniStavTlacitka = HIGH;

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TLACITKO, INPUT_PULLUP); // Využití interního pull-up rezistoru
  pinMode(PIN_LED_ZELENA, OUTPUT);
  pinMode(PIN_LED_CERVENA, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  vikoServo.attach(PIN_SERVO);
  nastavZavreno();

  Serial.begin(9600);
}

// Funkce pro změření vzdálenosti v cm pomocí HC-SR04
long zmerVzdalenost() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long trvani = pulseIn(PIN_ECHO, HIGH, 30000); // Timeout 30 ms
  if (trvani == 0) return 999;                  // Žádná překážka v dosahu
  return trvani * 0.034 / 2;                    // Převod na centimetry
}

void nastavOtevreno() {
  vikoServo.write(UHEL_OTEVRENO);
  digitalWrite(PIN_LED_ZELENA, HIGH);
  digitalWrite(PIN_LED_CERVENA, LOW);
  tone(PIN_BUZZER, 1000, 100); // Krátké pípnutí při otevření
}

void nastavZavreno() {
  vikoServo.write(UHEL_ZAVRENO);
  digitalWrite(PIN_LED_ZELENA, LOW);
  digitalWrite(PIN_LED_CERVENA, HIGH);
  tone(PIN_BUZZER, 500, 100);  // Hlubší pípnutí při zavření
}

void loop() {
  // 1. Obsluha tlačítka (ruční režim)
  bool stavTlacitka = digitalRead(PIN_TLACITKO);
  if (posledniStavTlacitka == HIGH && stavTlacitka == LOW) {
    manualniRezim = !manualniRezim;
    if (manualniRezim) {
      Serial.println("Rucni rezim: ZAPNUTO (viko trvale otevreno)");
      nastavOtevreno();
    } else {
      Serial.println("Rucni rezim: VYPNUTO (navrat do automatiky)");
      nastavZavreno();
    }
    delay(200); // Jednoduchý debounce tlačítka
  }
  posledniStavTlacitka = stavTlacitka;

  // 2. Automatický režim (pouze pokud není aktivní ruční otevření)
  if (!manualniRezim) {
    long vzdalenost = zmerVzdalenost();

    if (vzdalenost > 0 && vzdalenost <= PRAH_VZDALENOSTI) {
      Serial.println("Detekovana ruka -> OTEVIRAM VIKO!");
      nastavOtevreno();
      delay(CAS_OTEVRENI);
      Serial.println("ZAVIRAM VIKO...");
      nastavZavreno();
    }
  }

  delay(50);
}