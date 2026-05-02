#include <Servo.h>

Servo myservo;

#define LEFT_SENSOR   2
#define CENTER_SENSOR 3
#define RIGHT_SENSOR  4

#define IN1 8
#define IN2 11
#define IN3 12
#define IN4 13
#define ENA 5
#define ENB 6

#define SERVO_PIN 7
#define PUMP_PIN  A0

int motor_speed = 220;
int scan_speed  = 220;
int turn_time   = 500;
int face_time   = 500;

void set_speed(int spd) {
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
}

void stop_bot() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH);
}

void move_forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turn_left() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turn_right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

bool fire_detected() {
  return (digitalRead(LEFT_SENSOR)   == LOW ||
          digitalRead(CENTER_SENSOR) == LOW ||
          digitalRead(RIGHT_SENSOR)  == LOW);
}

char which_sensor() {
  bool L = digitalRead(LEFT_SENSOR)   == LOW;
  bool C = digitalRead(CENTER_SENSOR) == LOW;
  bool R = digitalRead(RIGHT_SENSOR)  == LOW;

  if (C)       return 'C';
  if (L && R)  return 'C';
  if (L)       return 'L';
  if (R)       return 'R';
  return 'N';
}

void face_fire(char trigger_sensor) {
  if (trigger_sensor == 'C') return;

  set_speed(scan_speed);
  unsigned long start = millis();

  if (trigger_sensor == 'L') {
    turn_left();
    while (millis() - start < (unsigned long)face_time) {
      if (digitalRead(CENTER_SENSOR) == LOW) break;
      delay(10);
    }
  } else if (trigger_sensor == 'R') {
    turn_right();
    while (millis() - start < (unsigned long)face_time) {
      if (digitalRead(CENTER_SENSOR) == LOW) break;
      delay(10);
    }
  }

  stop_bot();
  delay(200);
}

void put_off_fire() {
  stop_bot();

  myservo.write(90);
  delay(500);

  digitalWrite(PUMP_PIN, LOW);
  delay(200);

  for (int i = 60; i <= 120; i++) { myservo.write(i); delay(12); }
  for (int i = 120; i >= 60; i--) { myservo.write(i); delay(12); }
  for (int i = 60; i <= 120; i++) { myservo.write(i); delay(12); }
  for (int i = 120; i >= 90; i--) { myservo.write(i); delay(12); }

  digitalWrite(PUMP_PIN, HIGH);
  delay(200);

  myservo.write(90);
  delay(400);
}

bool scan_for_fire() {
  set_speed(scan_speed);

  turn_left();
  for (int t = 0; t < turn_time; t += 20) {
    delay(20);
    if (fire_detected()) { stop_bot(); return true; }
  }

  turn_right();
  for (int t = 0; t < turn_time; t += 20) {
    delay(20);
    if (fire_detected()) { stop_bot(); return true; }
  }
  stop_bot(); delay(100);
  if (fire_detected()) return true;

  turn_right();
  for (int t = 0; t < turn_time; t += 20) {
    delay(20);
    if (fire_detected()) { stop_bot(); return true; }
  }

  turn_left();
  for (int t = 0; t < turn_time; t += 20) {
    delay(20);
    if (fire_detected()) { stop_bot(); return true; }
  }
  stop_bot(); delay(100);
  if (fire_detected()) return true;

  return false;
}

void setup() {
  pinMode(LEFT_SENSOR,   INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR,  INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);

  pinMode(SERVO_PIN, OUTPUT);
  digitalWrite(SERVO_PIN, LOW);
  delay(200);

  myservo.attach(SERVO_PIN);
  delay(100);
  myservo.write(90);
  delay(600);

  set_speed(motor_speed);
  delay(1000);
}

void loop() {
  bool found = scan_for_fire();

  if (found) {
    char sensor = which_sensor();
    face_fire(sensor);
    put_off_fire();
  } else {
    set_speed(motor_speed);
    move_forward();
    delay(400);
    stop_bot();
    delay(200);
  }
}
