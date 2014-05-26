// MECH2110 Assignment - Warman Project
// Robot Control

#include <Servo.h>
#define LEFTTURN 2700         //Delay for left turn
#define RIGHTTURN 2600				//Delay for right turn

Servo leftwheel;
Servo rightwheel;

const int analogInPin0 = A0;  //top Analog input pin that the sensors are attached to
const int analogInPin1 = A1;  //bottom
const int analogInPin2 = A2;  //front

const int motorDir = 12;
const int motorPWM = 3;
const int motorBrake = 9;
const int motorTrip = 2;

int sensor0Value = 0;        // value read from the pot
int sensor1Value = 0;
int sensor2Value = 0;

int leftval;
int rightval;

void setup()
{
  pinMode(3, OUTPUT);
  //leftwheel.attach(6);
  //rightwheel.attach(5);
  Serial.begin(9600);
}

void loop()
{
  while(sensor2Value < 550)				// follow edge till reach pole
  {
    sensor0Value = analogRead(analogInPin0);
    sensor1Value = analogRead(analogInPin1);
    sensor2Value = analogRead(analogInPin2);
    if(sensor0Value < 300 && sensor1Value >= 300)
    {
      leftval = 0;
      rightval = 140;
    }else if(sensor0Value < 300 && sensor1Value < 300)
    {
      leftval = 80;
      rightval = 140;
    }else if(sensor0Value >= 300 && sensor1Value >= 300)
    {
      leftval = 0;
      rightval = 110;
    }
      // print the results to the serial monitor:
      Serial.print("\n sensor0 = " );                       
      Serial.print(sensor0Value);      
      Serial.print("\t sensor1 = " );                       
      Serial.print(sensor1Value);      
      Serial.print("\t sensor2 = " );                       
      Serial.print(sensor2Value);      
    leftwheel.write(leftval);
    rightwheel.write(rightval);
  }
  
  delay(400);												//After delay of 400ms, turn left
  leftval = 179;
  rightval = 140;
  leftwheel.write(leftval);
  rightwheel.write(rightval);
  delay(LEFTTURN);
  
  leftval = 30;											//Drive forward
  rightval = 150;
  leftwheel.write(leftval);
  rightwheel.write(rightval);
  delay(5150);
  
  sensor2Value = analogRead(analogInPin2);	//Refresh front sensor value
  
  while(sensor2Value < 500)									//Continue driving till second pole seen
  {
    sensor2Value = analogRead(analogInPin2);
  }
  
  leftval = 179;														//Reverse for 1.5 sec
  rightval = 40;
  leftwheel.write(leftval);
  rightwheel.write(rightval); 
  delay(1500);
  
  leftval = 0;															//Turn right
  rightval = 0;
  leftwheel.write(leftval);
  rightwheel.write(rightval);
  delay(RIGHTTURN);

  leftval = 98;															//Stop servos
  rightval = 96;
  leftwheel.write(leftval);
  rightwheel.write(rightval);

  																					//run DC motor
  digitalWrite(motorBrake, LOW);
  digitalWrite(motorDir, HIGH);
  analogWrite(motorPWM, 255);								//Motor speed set to max
 
  delay(5000);															//Run for 5 sec then stop with brake
  digitalWrite(motorBrake, HIGH);
  analogWrite(motorPWM, 0);  
  
  while(1);
}
