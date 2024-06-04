#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "Wheels.h"

// piny dla sonaru (HC-SR04)
#define TRIG A0
#define ECHO A1

// pin kontroli serwo (musi być PWM)
#define SERVO 3

// LCD
byte LCDAddress = 0x27;
LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

// WHEELS
Wheels w;

unsigned long prev_time = 0;
unsigned long start_time;
unsigned long sonar_delay = 100;

Servo serwo;

void setup() {
  
  pinMode(TRIG, OUTPUT);    // TRIG startuje sonar
  pinMode(ECHO, INPUT);     // ECHO odbiera powracający impuls

  Serial.begin(9600);

  serwo.attach(SERVO);

  lcd.init();
  lcd.backlight();
  
/* patrz przed siebie */
  delay(1000);
  serwo.write(90);

  start_time = millis();

  w.attach(7,8,5,12,11,10);
  w.setSpeed(100);
  w.forward();
}

void loop() {
  while (true) {
    unsigned long curr_time = millis();
    if (curr_time - prev_time > sonar_delay) {
      Serial.println("looking...");
      prev_time = curr_time;
      unsigned int distance = lookAndTellDistance(90);
      if (distance < 100) {
        w.stop();
      }
    } else if (curr_time - start_time > 2000) {
      break;
    }
  }
  /* rozejrzyj się w zakresie od 0 stopni (patrz na jedną burtę)
 *  do 180 stopni (patrz na prawą burtę). Wydrukuj na konsoli
 *  kierunek patrzenia i najbliżej widziany obiekt (pojedynczy pomiar)
 */
  //for(byte angle = 0; angle <= 180; angle+= 20) {
  //  lookAndTellDistance(angle);
  //  delay(500);
  //}
}

unsigned int lookAndTellDistance(byte angle) {
  
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(angle);

  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  serwo.write(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
  distance = tot/58;

  lcd.setCursor(0, 1);
  Serial.print(": widzę coś w odległości ");
  Serial.println(distance);
  lcd.print("D=");
  lcd.print(distance);

  return distance;
}
