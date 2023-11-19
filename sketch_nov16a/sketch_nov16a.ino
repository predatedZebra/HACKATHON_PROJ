// Includes the Servo library
#include<LiquidCrystal.h>
#include <Servo.h>. 
// Defines Tirg and Echo pins of the Ultrasonic Sensor
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int trigPin = 8;
const int echoPin = 9;
// Variables for the duration and the distance
long duration;
int distance;
const float reactionTime = 1.5; // Reaction time in seconds
const float gravity = 9.81; // Acceleration due to gravity in m/s^2
// Simulate an initial speed (in meters per second)
float initialSpeed = 20.0;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  lcd.begin(16, 2);
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(10); // Defines on which pin is the servo motor attached
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=30;i<=150;i+=1){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  // Calculate reaction distance
  float reactionDistance = initialSpeed * reactionTime;
  // Calculate deceleration (assuming the final speed is 0)
  float deceleration = (0 - initialSpeed) / reactionTime;
  // Calculate braking distance
  float brakingDistance = (initialSpeed * initialSpeed) / (2 * deceleration);
  // Calculate total stopping distance
  float totalStoppingDistance = reactionDistance + brakingDistance;
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
   if (distance <= totalStoppingDistance) {
      lcd.setCursor(0, 0);
      lcd.print("Alert!!! Brake");
      lcd.setCursor(0, 1);
      if (i >= 30 && i < 60) {
            lcd.print("at your Left");
          } else if (i >= 60 && i < 120) {
            lcd.print("Object in front");
          } else if (i >= 120 && i < 150) {
            lcd.print("at your right");
          }
      } else lcd.clear();
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=150;i>30;i-=1){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
   // Calculate reaction distance
  float reactionDistance = initialSpeed * reactionTime;
  // Calculate deceleration (assuming the final speed is 0)
  float deceleration = (0 - initialSpeed) / reactionTime;
  // Calculate braking distance
  float brakingDistance = (initialSpeed * initialSpeed) / (2 * deceleration);
  // Calculate total stopping distance
  float totalStoppingDistance = (reactionDistance + brakingDistance);
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  if (distance <= totalStoppingDistance) {
      lcd.setCursor(0, 0);
      lcd.print("Alert!!! Brake");
      lcd.setCursor(0, 1);
      if (i >= 30 && i < 60) {
            lcd.print("at your Left");
          } else if (i >= 60 && i < 120) {
            lcd.print("Object in front");
          } else if (i >= 120 && i < 150) {
            lcd.print("at your right");
          }
      } else lcd.clear();
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
