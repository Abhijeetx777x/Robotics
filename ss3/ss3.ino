// Wall Following Robot
// Uses ultrasonic sensor to maintain constant distance from right wall
// Stops automatically after 2 minutes

// Pin definitions
const int trigPinSide = 11;  // Ultrasonic sensor trigger
const int echoPinSide = 10;  // Ultrasonic sensor echo
const int trigPinFront = 2;  // Ultrasonic sensor trigger
const int echoPinFront = 6;  // Ultrasonic sensor echo
const int ENA = 3;           // Enable motor A (Right motor) analogue
const int IN1 = 5;           // Motor A input 1 digital
const int IN2 = 4;           // Motor A input 2
const int IN3 = 7;           // Motor B input 1
const int IN4 = 8;           // Motor B input 2
const int ENB = 9;           // Enable motor B (Left motor)

// Parameters
const float TARGET_DISTANCE = 15.0;    // Target distance from wall in cm
const float DISTANCE_TOLERANCE = 3.0;  // Tolerance range (±cm)
const float TOO_CLOSE = 5.0;           // Dangerously close distance (cm)
const float MAX_DISTANCE = 30.0;       // Max distance to still consider wall present
const float NO_WALL = 50.0;            // No wall detected threshold (cm)
const int LEFT_BASE_SPEED = 160;       // Base motor speed (0-255)
const int RIGHT_BASE_SPEED = 170;      // Base motor speed (0-255)
const int TURN_SPEED = 30;             // Speed difference for turning

const float FRONT_DISTANCE_LIMIT = 5.0;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(trigPinSide, OUTPUT);
  pinMode(echoPinSide, INPUT);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  stopMotors();
  delay(3000);
}

void loop() {
  // Check if 2 minutes have passed
  float front_distance = measureDistance(trigPinFront, echoPinFront);
  float distance = measureDistance(trigPinSide, echoPinSide);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm ");

  if (front_distance <= FRONT_DISTANCE_LIMIT) {
    stopMotors();
    delay(5000);
  } else if (distance <= TOO_CLOSE) {
    turnLeftStronger();
    Serial.println("Action: STRONG LEFT - Too close to wall!");
    delay(50);
  } else if (distance < TARGET_DISTANCE - DISTANCE_TOLERANCE) {
    turnLeft();
    Serial.println("Action: Turn left");
    delay(50);
  } else if (distance > MAX_DISTANCE && distance < NO_WALL) {
    turnRightStronger();
    Serial.println("Action: STRONG RIGHT - Wall too far!");
    delay(50);
  } else if (distance >= NO_WALL) {
    turnRightStronger();
    Serial.println("Action: SEARCHING - No wall detected!");
    delay(50);
  } else if (distance > TARGET_DISTANCE + DISTANCE_TOLERANCE) {
    turnRight();
    Serial.println("Action: Turn right");
    delay(50);
  } else {
    goForward();
    Serial.println("Action: Forward");
    delay(50);
  }

  delay(100);
}

// Measure distance using ultrasonic sensor
float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2;

  if (distance > 400) distance = 400;

  return distance;
}

// Motor control functions
void goForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, RIGHT_BASE_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, LEFT_BASE_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, RIGHT_BASE_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, LEFT_BASE_SPEED - TURN_SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, RIGHT_BASE_SPEED - TURN_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, LEFT_BASE_SPEED);
}

void turnLeftStronger() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, RIGHT_BASE_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, LEFT_BASE_SPEED - (TURN_SPEED * 2));
}

void turnRightStronger() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, RIGHT_BASE_SPEED - (TURN_SPEED * 2));
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, LEFT_BASE_SPEED);
}


void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}