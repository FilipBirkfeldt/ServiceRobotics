#include <QTRSensors.h>
#include <Servo.h>
#include <HCSR04.h>


// Gripper initialization

Servo grip_servo;
Servo lift_servo;
#define liftPin 6
#define gripPin 5
#define restAngle 135 //Upp i gradantal sänker klon.
#define liftAngle 20
#define gripAngle 55 //Ned i gradantal kniper åt.
#define gripRestAngle 85
boolean holding = false;
boolean gripLifted = false;

//Front sensor initialization
#define sensorBuff 7
#define IRPin A1
int avgDist[sensorBuff];
uint8_t wallInFrontLimit = 75;
uint8_t wallNearLimit = 105;


//Front switch initialization
#define breakSwitch A0

// Wheel drive initialization
Servo leftServo;   //when looking in driving direction
Servo rightServo;  //when looking in driving direction

// Line sensor initialization
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
uint16_t posValue;


//Side sensors initialization
HCSR04 hc(16, new int[2] {17, 18}, 2);
//initialisation of class HCSR04 (trig pin , echo pin, number of sensor)
uint8_t side_distance_limit = 14;


//Open serial port and run setup code for different sensors and servos
void setup()
{
  Serial.begin(9600);
  lineSensorSetup();
  wheelServoSetup();
  gripServoSetup();
  frontSensorSetup();

}

//Loops the main program. Checks for cylinder, lost line or if robot has a choice to make.
//If non of those cases are active it will follow line.
void loop()
{
  if (frontSwitch()) {
    collectCylinder();
  }
  hasLine();
  choiceHandler();
  lineDriveCommander();
  //testSensors();
}

//Print what each sensor detects.
void testSensors() {
  Serial.println("------------------");
  Serial.println("Value: ");
  Serial.println(analogRead(IRPin));
  Serial.print("Wall in front: ");
  Serial.println(wallInFront());
  Serial.println("****");
  Serial.print("Wall near: ");
  Serial.println(wallNear());
//  Serial.print("Left end linesensor: ");
//  Serial.println(leftEndSensor());
//  Serial.print("Right end linesensor: ");
//  Serial.println(rightEndSensor());
//  Serial.print("Left sound sensor: ");
//  Serial.println(wallLeft());
//  Serial.print("Right sound sensor: ");
//  Serial.println(wallRight());
//  Serial.print("Front break switch: ");
//  Serial.println(frontSwitch());
  Serial.println("------------------");
  delay(2000);
}
