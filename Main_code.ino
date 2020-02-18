// Top Left Sensor Pins
// Input int according to the connections
const int topLeftTrigPin = 2;
const int topLeftEchoPin = 3;

// Top Right Sensor Pins
const int topRightTrigPin = 4;
const int topRightEchoPin = 5;

// Bottom Sensor Pins
const int bottomPin = 34;

//Buzzer Pin
const int buzzerPin = 6;

// Vibration Module Pin
const int vibrationPin = 28;

// Push Button Pin
const int buttonPin = 7;

// LED
const int LED1 = 31;

// Setting up the type of the communication the pin will be doing with Arduino.
void setup() {
  Serial.begin(9600);
  pinMode(topLeftTrigPin, OUTPUT);
  pinMode(topLeftEchoPin, INPUT);
  pinMode(topRightTrigPin, OUTPUT);
  pinMode(topRightEchoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(vibrationPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH); 
  
  Serial.println("Welcome to the smart walking stick user interface. ");
  Serial.println("Hope you liked the musical greeting. ");
  delay(2000);
}

void loop() {
 
boolean isActive = true;  
int buttonState = 1;

  int topLeftDistance = ultrasonicDistance(topLeftTrigPin, topLeftEchoPin);
  int topRightDistance = ultrasonicDistance(topRightTrigPin, topRightEchoPin);
  
  double bottomDistance;
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if(buttonState == LOW) {
    isActive = false;
    bottomDistance = pushButtonSensor(); 
    feedbackLower(bottomDistance);
  }
  
  if((topLeftDistance <= 100 || topRightDistance <= 100) && isActive) {
    // add audio file functionality
    feedbackUpper(topLeftDistance, topRightDistance);
  }
}

// Takes ints for the pin numbers of the echo pin and trig pin. Calculates
// the distance of the object from the sensor every 1 second and prints out
// the distance to the serial monitor. Returns the distance.
int ultrasonicDistance(int trigPin, int echoPin) {
  long duration;
  int distance;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(300);
  return distance;
}

void feedbackLower(double bottomDistance) {
  if(bottomDistance <= 20) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(30);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(30);
  }
  else if(bottomDistance <= 50) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(70);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(70);
  }
  else if(bottomDistance <= 70) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(100);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  else if(bottomDistance <= 100) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(200);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(vibrationPin, LOW);
  }
}

// 
void feedbackUpper(int topLeftDistance, int topRightDistance) {
  Serial.println(topLeftDistance);
  Serial.println(topRightDistance);
  if(topLeftDistance <= 30 || topRightDistance <= 30) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(30);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(30);
  }
  else if(topLeftDistance <= 55 || topRightDistance <= 55) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(70);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(70);
  }
  else if(topLeftDistance <= 70 || topRightDistance <= 70) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(100);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } 
  else if(topLeftDistance <= 85 || topRightDistance <= 85){
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(200);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
    else if(topLeftDistance <= 100 || topRightDistance <= 100) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(vibrationPin, HIGH);
    delay(300);
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(300);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(vibrationPin, LOW);
  } 
}

double pushButtonSensor() {
  double duration, inches, cm;
  pinMode(bottomPin, OUTPUT);
  digitalWrite(bottomPin, LOW);
  delayMicroseconds(2);
  digitalWrite(bottomPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(bottomPin, LOW);

  pinMode(bottomPin, INPUT);
  duration = pulseIn(bottomPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  return cm;
}

double microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

double microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}


