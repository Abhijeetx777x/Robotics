//Obstacle Avoidance
#include <Servo.h>

// Motor driver pins
const int ENA = 10;        // Right motor enable
const int IN1 = 8;        // Right motor IN1
const int IN2 = 9;        // Right motor IN2
const int IN3 = 7;        // Left motor IN1
const int IN4 = 4;        // Left motor IN2
const int ENB = 5;       // Left motor enable

// Ultrasonic Sensor
const int trigPin = 11;
const int echoPin = 12;

// Servo motor
const int servoPin = 6;
Servo myServo;

long duration;
int distance;

void setup() {
  // Motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo
  myServo.attach(servoPin);

  // Start Serial
  Serial.begin(9600);
}

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);  // speed: 0-255
  analogWrite(ENB, 180);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  myServo.write(90); // look forward
  delay(500);
  int frontDist = readDistance();

  if (frontDist < 20) {
    stopMoving();
    delay(300);

    // Check left
    myServo.write(150);
    delay(500);
    int leftDist = readDistance();

    // Check right
    myServo.write(30);
    delay(500);
    int rightDist = readDistance();

    myServo.write(90);
    delay(200);

    if (leftDist > rightDist) {
      turnLeft();
      delay(600);
    } else {
      turnRight();
      delay(600);
    }
  } else {
    moveForward();
  }
}