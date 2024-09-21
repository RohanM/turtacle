#include <SoftwareSerial.h>
#include <SabertoothSimplified.h>

const int PIN_GO = 2;
const int PIN_FORWARD = 3;
const int PIN_LEFT = 4;
const int PIN_RIGHT = 5;
const int PIN_SPEED = A0;
const int PIN_MOTOR_CONTROLLER = 12;

const int MOTOR_STEER = 1;
const int MOTOR_DRIVE = 2;

SoftwareSerial SWSerial(NOT_A_PIN, PIN_MOTOR_CONTROLLER); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST(SWSerial); // Use SWSerial as the serial port.


void setup() {
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_GO, INPUT);
  pinMode(PIN_FORWARD, INPUT);

  SWSerial.begin(9600);

  Serial.begin(9600);
}

int left, right, go, forward, speed;
int direction, power;

void loop() {
  left = digitalRead(PIN_LEFT);
  right = digitalRead(PIN_RIGHT);
  go = digitalRead(PIN_GO);
  forward = digitalRead(PIN_FORWARD);
  speed = analogRead(PIN_SPEED);

  /*
  Serial.print(left); Serial.print(", ");
  Serial.print(right); Serial.print(", ");
  Serial.print(go); Serial.print(", ");
  Serial.print(forward); Serial.print(", ");
  Serial.print(speed); Serial.println("");
  */

  // Steering
  if (left) {
    ST.motor(MOTOR_STEER, 127);
  } else if (right) {
    ST.motor(MOTOR_STEER, -127);
  } else {
    ST.motor(MOTOR_STEER, 0);
  }

  // Drive
  if (go) {
    direction = forward ? 1 : -1;
    power = speed / 1024.0 * 128.0;
    /*
    Serial.print(direction); Serial.print(", ");
    Serial.print(power); Serial.print(", ");
    Serial.print(direction * power); Serial.println();
    */
    ST.motor(MOTOR_DRIVE, direction * power);

  } else {
    ST.motor(MOTOR_DRIVE, 0);
  }

  delay(50);
}
