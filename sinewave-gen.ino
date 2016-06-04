/* 50Hz generator , pure sinewave*/

#define SIG1_PIN 2
#define SIG2_PIN 3
#define SEGMENTS 50
#define DIVITIONS SEGMENTS*2

float table[50];
float table1[50];
int table2[50];
int table_inv[50];
int pin;
int state=0;

void setup() {
  Serial.begin(9600);
  pinMode(SIG1_PIN, OUTPUT);
  pinMode(SIG2_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(SIG1_PIN, LOW);
  digitalWrite(SIG2_PIN, LOW);

  for (int i = 0; i < SEGMENTS; i++) {
    table[i] = (float) sin(i * (2 * PI / (float)DIVITIONS));
  }
  changeFrequency(50);
}

void loop() {
  digitalWrite(13, state);
  state = !state;
  for (int j = 0; j < 2; j++) {
    if (j == 0) {
      pin = SIG1_PIN;
    } else {
      pin = SIG2_PIN;
    }
    for (int i = 0; i < SEGMENTS; i++) {
      digitalWrite(pin, HIGH);
      delayMicroseconds(table2[i]);
      digitalWrite(pin, LOW);
      delayMicroseconds(table_inv[i]);

    }
  }
}

void changeFrequency(float freq) {
  float sub_period = 1000000.0 / (freq * DIVITIONS);

  for (int i = 0; i < SEGMENTS; i++) {
    table1[i] = (float)table[i] * sub_period;
  }

  for (int i = 0; i < SEGMENTS; i++) {
    table2[i] = (int)table1[i];
    if (table2[i] == 0) table2[i] = 1;
  }
  
  for (int i = 0; i < SEGMENTS; i++) {
    table_inv[i] = (int)sub_period - table2[i];
  }

}
