#include <Servo.h> // library to use servo motor

const int trigPin = 11;  // trigger pin from ultrasonic Sensor
const int echoPin = 12;  // Echo pin from ultrasonic Sensor
const int ledPin = 13; // Pin for controlling the light bulb

long duration; // duration for echo pin for ultrasonic sensor 
int distance;  // store the calculated distance from ultrasonic distance

bool flag=false;  // condition 
int i=0;   // initalise for loop

int target_distance=5;   // distance at which u what to detect

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT); // Setting the LED pin as an output
  Serial.begin(9600);  // For Serial Monitor at the rate of 9600
  myServo.attach(6);  // signal pin from servo motor
  digitalWrite(ledPin,LOW);  // to keep the LED state off
}

void loop() {
// for one half anti-clock cycle
 for(i=15;i<=200;i+=5) 
 {
  flag=false;
  distance=calculateDistance();
  if(distance<target_distance)
  {
    myServo.write(i);
    digitalWrite(ledPin,HIGH);
    delay(2000);
    flag=true;
    i=i-5;    // to use the previous value of i
    continue; // skip the next part of the code and go to next iteration
  }
  else
  {
    digitalWrite(ledPin,LOW);
    flag=false;
  }
  if(!flag){  // if flag state is false then continue on it's track
  myServo.write(i);
  delay(100);
  }
  }
 
// one half clockwise rotation
 for(i=200;i>=15;i-=5)
 {
  flag=false;
  distance=calculateDistance();
  if(distance<target_distance)
  {
    myServo.write(i);
    digitalWrite(ledPin,HIGH);
    delay(2000);
    flag=true;
    i=i+5;    // to use the previous value of i
    continue; // skip the next part of the code and go to next iteration
  }
  else
  {
    digitalWrite(ledPin,LOW);
    flag=false;
  }
  if(!flag){    // if flag state is false then continue on it's track
  myServo.write(i);
  delay(100);
  }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
