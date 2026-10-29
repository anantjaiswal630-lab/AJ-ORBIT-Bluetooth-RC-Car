
/*
  =====================================================
                  AJ-ORBIT
          BLUETOOTH RC CAR - V1.0
  =====================================================

  Brand       : AJ-ORBIT
  Project     : Bluetooth Controlled RC Car
  Controller  : Arduino Uno
  Motor Driver: Adafruit Motor Shield V1
  Bluetooth   : HC-05 / HC-06
  Author      : AJ-ORBIT Engineering

  COMMANDS:
  F = Forward       B = Backward
  L = Turn Left     R = Turn Right
  G = Forward Left  I = Forward Right
  H = Backward Left J = Backward Right
  S = Stop

  SPEED:
  0-9 = Speed levels
  q   = Maximum speed

  LIBRARY:
  AFMotor library for Adafruit Motor Shield V1

  SAFETY:
  Motors stop if Bluetooth commands time out.
  Test with wheels lifted before driving.

  AJ-ORBIT | Build Beyond Limits
  =====================================================
*/

#include <AFMotor.h>
#include <SoftwareSerial.h>

// Bluetooth RX, TX
// Arduino Uno: D14 = A0, D15 = A1
SoftwareSerial bluetoothSerial(14, 15);

// Motor connections: Adafruit Motor Shield V1
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Configuration
char command = 'S';
int carSpeed = 200;
const int turnSpeedFactor = 3;

// Stop if no Bluetooth command is received
const unsigned long commandTimeout = 1000;
unsigned long lastCommandTime = 0;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  stopCar();

  Serial.println(F("================================"));
  Serial.println(F(" AJ-ORBIT Bluetooth RC Car V1.0"));
  Serial.println(F(" Build Beyond Limits"));
  Serial.println(F("================================"));
  Serial.println(F("Bluetooth ready."));

  lastCommandTime = millis();
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();
    lastCommandTime = millis();

    switch (command) {
      case 'F': moveForward();     break;
      case 'B': moveBackward();    break;
      case 'L': turnLeft();        break;
      case 'R': turnRight();       break;
      case 'G': forwardLeft();     break;
      case 'H': backwardLeft();    break;
      case 'I': forwardRight();    break;
      case 'J': backwardRight();   break;
      case 'S': stopCar();         break;

      case '0': carSpeed = 120;    break;
      case '1': carSpeed = 135;    break;
      case '2': carSpeed = 150;    break;
      case '3': carSpeed = 165;    break;
      case '4': carSpeed = 180;    break;
      case '5': carSpeed = 195;    break;
      case '6': carSpeed = 210;    break;
      case '7': carSpeed = 225;    break;
      case '8': carSpeed = 240;    break;
      case '9': carSpeed = 250;    break;
      case 'q': carSpeed = 255;    break;

      default:
        // Ignore unknown commands
        break;
    }
  }

  // Fail-safe: stop if commands stop arriving.
  if (millis() - lastCommandTime > commandTimeout) {
    stopCar();
  }
}

// Apply speed to all four motors
void setAllSpeeds(int speedValue) {
  motor1.setSpeed(speedValue);
  motor2.setSpeed(speedValue);
  motor3.setSpeed(speedValue);
  motor4.setSpeed(speedValue);
}

void moveForward() {
  setAllSpeeds(carSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  setAllSpeeds(carSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  setAllSpeeds(carSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  setAllSpeeds(carSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void forwardLeft() {
  motor1.setSpeed(carSpeed / turnSpeedFactor);
  motor2.setSpeed(carSpeed / turnSpeedFactor);
  motor3.setSpeed(carSpeed);
  motor4.setSpeed(carSpeed);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void forwardRight() {
  motor1.setSpeed(carSpeed);
  motor2.setSpeed(carSpeed);
  motor3.setSpeed(carSpeed / turnSpeedFactor);
  motor4.setSpeed(carSpeed / turnSpeedFactor);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backwardLeft() {
  motor1.setSpeed(carSpeed / turnSpeedFactor);
  motor2.setSpeed(carSpeed / turnSpeedFactor);
  motor3.setSpeed(carSpeed);
  motor4.setSpeed(carSpeed);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void backwardRight() {
  motor1.setSpeed(carSpeed);
  motor2.setSpeed(carSpeed);
  motor3.setSpeed(carSpeed / turnSpeedFactor);
  motor4.setSpeed(carSpeed / turnSpeedFactor);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopCar() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
