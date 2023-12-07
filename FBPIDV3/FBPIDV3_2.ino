// Include the apropriat libraries.
#include <Bonezegei_HCSR04.h>
#include <PID_v1.h>
// Declare the pins
#define enA 9
#define in1 6
#define in2 7
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 13;
//Start the Ultrasonic sensor librie.
Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);

//Define the variables assosiated with the PID system.
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp= 2.27; 
double Ki=1.3; 
double Kd=1.5;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
// Initialize the direction of rotation.
int rotDirection = 0;
int count2new = 0;
// Set up the Code.
void setup() {
  //These first three pins conect to the L298N Motor driver
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //Initialize in1 and in2 in the off position (refer to the L298N Datasheet)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //Set the baud rate.
  Serial.begin(9600);
  //initialize the input variable in the PID.
  Input = ultrasonic.getDistance();
  // Declare the setpoint to be 50cm. 
  //This is how high you want the ball to be.
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}
//Start the loop!
void loop()
{
  //This finds the distance from the Ultrasonic sensor at the top.
  double d = ultrasonic.getDistance();
  // This changes the input to be measured instead from the bottom.
  Input = 84-d;

  if (Input == Setpoint)
  {
    count2new += 1;
    if(count2new >= 500)
    {
      Setpoint = random(40)+20;
      count2new = 0;
    }
  }
  // This calculates the PID for the system and gives the output.
  myPID.Compute();
  // This maps the output from the myPID.Compute function to a reasonable output to the motor.
  // It was discoverd that if the lower value of the maped function is anything less than 200, the ball falls to the ground. :(
  // Send the output to the Motor.
  analogWrite(enA, Output);
  // Set the motor designation to on (see L298N Datasheet)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  rotDirection = 1;

  Serial.print("Setpoint ");
  Serial.print("  ");
  Serial.print(Setpoint);
  Serial.print("  ");
  Serial.print("countdown to change ");
  Serial.print(500-count2new);
  Serial.print(" Input: ");
  Serial.print(Input);
  Serial.print("  ");
  Serial.print(" Output: ");
  Serial.println(Output);

  //delay(100);
}