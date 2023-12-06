#include <PID_v1_bc.h>

#define EchoPIN 3
#define TrigPIN 2
#define PIN_OUTPUT 5

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
float duration;
int PWM;
//Specify the links and initial tuning parameters
double Kp=13.41, Ki=4.024, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
 Setpoint = 200;

 //turn the PID on
 myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
  pinMode(EchoPIN, INPUT);
  pinMode(TrigPIN, OUTPUT);
  pinMode(PIN_OUTPUT, OUTPUT);
}

void loop()
{
 Input = getDistance();
 myPID.Compute();
 PWM = map(Output,255,0,0,255);
 analogWrite(PIN_OUTPUT, PWM);
 Serial.println(PWM);
 delay(10);
}

float getDistance() {
  //send trigger signal
  digitalWrite(TrigPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPIN, LOW);
  //calculate duration
  duration = pulseIn(EchoPIN, HIGH);
  //return distance
  return (duration / 2) / 29.1;
}
