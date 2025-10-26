const int L_SENS = 2;
const int R_SENS = 3;

const int ENA = 5;    
const int IN1 = 6;    
const int IN2 = 7;    


const int ENB = 9;   
const int IN3 = 10;  
const int IN4 = 11;   



int MAX_SPEED = 100; 


void setup() {
  
  Serial.begin(9600);

 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

 
  pinMode(L_SENS, INPUT);
  pinMode(R_SENS, INPUT);
  
 
  Serial.println("Line Follower Initialized.");
  Serial.println("Place the robot on the line. Starting in 3 seconds...");
  delay(3000); 
  Serial.println("GO!");
}

void loop() {
  
  int left_state = digitalRead(L_SENS);
  int right_state = digitalRead(R_SENS);

 
  Serial.print("Left Sensor: ");
  Serial.print(left_state); 
  Serial.print(" | Right Sensor: ");
  Serial.print(right_state);


  
  if (left_state == LOW && right_state == LOW) {
    Serial.println("  ->  Action: GO FORWARD");
    goForward();
  } 
  
  else if (left_state == LOW && right_state == HIGH) {
    Serial.println("  ->  Action: PIVOT LEFT");
    turnLeft();
  } 
  
  
  else if (left_state == HIGH && right_state == LOW) {
    Serial.println("  ->  Action: PIVOT RIGHT");
    turnRight();
  } 
  
 
  else { 
    Serial.println("  ->  Action: STOP");
    stopMotors();
  }
}


void goForward() {
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
  
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255);
}

void turnLeft() {
 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 80);
}

void turnRight() {

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 80);
  

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void stopMotors() {
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}