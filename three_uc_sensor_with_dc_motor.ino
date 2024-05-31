// Pin Definitions
int enableA = 9;
int Pin1 = 8;
int Pin2 = 10;
int enableB = 11;
int Pin3 = 12;
int Pin4 = 13;
int trigPin = 2; // Ultrasonic sensor 1 trig pin
int echoPin = 3; // Ultrasonic sensor 1 echo pin
int trigPin2 = 4; // Ultrasonic sensor 2 trig pin
int echoPin2 = 5; // Ultrasonic sensor 2 echo pin
int trigPin3 = 6; // Ultrasonic sensor 3 trig pin
int echoPin3 = 7; // Ultrasonic sensor 3 echo pin

// Variables
long duration;
int distance;
long duration2;
int distance2;
long duration3;
int distance3;

void setup() {
  // Set motor pins as output
  pinMode(enableA, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  
  // Set ultrasonic sensor 1 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set ultrasonic sensor 2 pins
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Set ultrasonic sensor 3 pins
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Move the car forward until an obstacle is detected
  while (true) {
    moveForward();
    
    // Check distance from ultrasonic sensor 1
    distance = getDistance(trigPin, echoPin, 1);
    // Check distance from ultrasonic sensor 2
    distance2 = getDistance(trigPin2, echoPin2, 2);
    // Check distance from ultrasonic sensor 3
    distance3 = getDistance(trigPin3, echoPin3, 3);
    
    // If any sensor detects an obstacle within 25cm, break out of the loop
    if (distance < 25 || distance2 < 25 || distance3 < 25) {
      break;
    }
  }
  
  // Move the car backward and turn right if obstacle detected by sensor 1
  if (distance < 25) {
    stopCar();
    delay(1000); // Brief delay to stop the car completely
    moveBackward(); // Move backward
    delay(1000); // Brief delay to move backward
    turnRight();
  }
  // Turn right if obstacles detected by sensors 2 and 3
  else if (distance2 < 25 || distance3 < 25) {
    stopCar();
    delay(1000); // Brief delay to stop the car completely
    turnRight();
  }
}

// Function to move the car forward
void moveForward() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  analogWrite(enableA, 250); // Adjust speed
  analogWrite(enableB, 250); // Adjust speed
}

// Function to stop the car
void stopCar() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
}

// Function to make the car turn right
void turnRight() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  analogWrite(enableA, 200); // Adjust speed
  analogWrite(enableB, 200); // Adjust speed
  delay(1000); // Adjust the delay based on how long you want the turn to be
}

// Function to move the car backward
void moveBackward() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, HIGH);
  digitalWrite(Pin4, LOW);
}

// Function to measure distance using ultrasonic sensor
int getDistance(int trigPin, int echoPin, int sensorNumber) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  // Print distance for debugging (optional)
  Serial.print("Distance from Sensor ");
  Serial.print(sensorNumber);
  Serial.print(": ");
  Serial.println(distance);
  
  return distance;
}
