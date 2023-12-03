/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <Bonezegei_HCSR04.h>
#include <PID_v1.h>

#define enA 9
#define in1 6
#define in2 7
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 13;
Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int rotDirection = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.begin(9600);
  //initialize the variables we're linked to
  Input = ultrasonic.getDistance();
  //Input = analogRead(PIN_INPUT);
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  double d = ultrasonic.getDistance();
  Input = 90-d;
  myPID.Compute();
  analogWrite(enA, Output);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  rotDirection = 1;

  Serial.print("Setpoint ");
  Serial.print(Setpoint);
  Serial.print(" Input: ");
  Serial.print(Input);
  Serial.print(" Output: ");
  Serial.println(Output);
  delay(200);
}


