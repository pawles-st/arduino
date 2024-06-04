#define LED 13

int dot_length = 75;
int dash_length = 3 * dot_length;
int signal_break_length = dot_length;
int letter_break_length = 3 * dot_length;

int DOT = 0;
int DASH = 1;

volatile char serial_input;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    serial_input = Serial.read();
    switch (serial_input) {
      case 'p':
        emit_signal(DOT);
        emit_signal(DASH);
        emit_signal(DASH);
        emit_signal(DOT);
        break;
      case 'a':
        emit_signal(DOT);
        emit_signal(DASH);
        break;
      case 'w':
        emit_signal(DOT);
        emit_signal(DASH);
        emit_signal(DASH);
        break;
      case 'e':
        emit_signal(DOT);
        break;
      case 'l':
        emit_signal(DOT);
        emit_signal(DASH);
        emit_signal(DOT);
        emit_signal(DASH);
        break;
      case '9':
        emit_signal(DASH);
        emit_signal(DASH);
        emit_signal(DASH);
        emit_signal(DASH);
        emit_signal(DOT);
        break;
      default:
        Serial.println("?");
    }
  }
  emit_letter_break();
  Serial.println(".");
}

void emit_signal(int type) {
  emit_break();
  if (type == 0) { // dot
    digitalWrite(LED, HIGH);
    delay(dot_length);
  } else { // dash
    digitalWrite(LED, HIGH);
    delay(dash_length);
  }
}

void emit_break() {
  digitalWrite(LED, LOW);
  delay(signal_break_length);
}

void emit_letter_break() {
  digitalWrite(LED, LOW);
  delay(letter_break_length);
}
