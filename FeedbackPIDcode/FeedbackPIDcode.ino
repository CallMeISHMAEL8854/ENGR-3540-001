#include <Bonezegei_HCSR04.h>
#include <PID_v1.h>

// define the three pins that control the speed of the motor.
#define enA 9
#define in1 6
#define in2 7
// Declare the purpose of the Trig and Echo pins of the Ultrasonic sensor.
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 13;
// Using the Ultrasonic library to initalize the sensor.
Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);

// variables specific to the PID
double Setpoint = 20.0;  // Setpoint for the desired distance (adjust as needed)
double Input, Output;
double Kp;  // Proportional gain
double Ki;  // Integral gain
double Kd;  // Derivative gain
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

float distance;
int rotDirection = 0;
int pressed = false;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //pinMode(button, INPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.begin(9600);
}

void loop() {
  // This code ties the gain constaints to the values of the poptentiomiters.
  //double Kp = analogRead(A0);
  //double Ki = analogRead(A1);
  //double Kd = analogRead(A2);
  //Serial.println(Kp);
  //Serial.println(Ki);
  //Serial.println(Kd);
  int d=ultrasonic.getDistance();
  if(d<0)
  {
    d = 0;
  } 
  double height = 91-d;
  int pwmOutput = map(d, 0, 90, 210 , 255); 
  if(pwmOutput>255)
  {
    pwmOutput = 255;
  } 
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    rotDirection = 1;
     //Serial.print("potvalue: ");
     //Serial.print(potValue);
     //Serial.println(Kp);
     //Serial.println(Ki);
     //Serial.println(Kd);
     //Serial.print(" pwmOutput ");
     Serial.print(" ");
     Serial.print(pwmOutput);
     //Serial.print(" height (cm): ");
     Serial.print(" ");
     Serial.println(height);

    delay(200);
}