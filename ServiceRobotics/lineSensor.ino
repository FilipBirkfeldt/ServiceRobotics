//Values for line regulator.
float Kp = 0.02; //set up the constants value
float Ki = 0;
float Kd = 0.017;
int P;
int I;
int D;
//Set basevalues for straightline (a = left, b = right);
int basespeeda = 110;
int basespeedb = 110;

//Increasing the maxspeed can damage the motors - at a value of 255 the 6V motors will receive 7,4 V
const uint8_t maxspeeda = 180;
const uint8_t maxspeedb = 180;

int lastError = 0;
boolean onoff = false;

//Calibrates line sensor
void lineSensorSetup() {

  Serial.println("LINE CAL STARTED");

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    7, 3, 4, 2, 13, 12, 9, 8
  }, SensorCount);


  delay(500);
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // Call calibrate() 400 times to make calibration take about 10 seconds.

  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }

  Serial.println("LINE CAL DONE");
}

//print function for line sensors
void sensorCheck() {

  posValue = qtr.readLineBlack(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(posValue);

  delay(250);
}

//Waits one second then run PID_controller
void lineDriveCommander() {

  if (!onoff) {
    delay(1000);
    onoff = !onoff;
  }
  if (onoff) {
    PID_control();
  }
}
//Calculates wheelspeed based on position of line on line sensor. Then Runs _updatePWM.
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = 3300 - position;

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P * Kp + I * Ki + D * Kd;

  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;


  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  }

  motorspeeda = 180 - motorspeeda;

  _updatePWM(motorspeeda, motorspeedb);

}
//Sets the new wheel speed from PID controller. Checks so that values are not out of bound.
void _updatePWM(int motorspeeda, int motorspeedb) {
  if (motorspeedb < 0) {
    rightServo.write(0);
  } else if (motorspeedb > 180) {
    rightServo.write(180);
  } else {
    rightServo.write(motorspeedb);
  }
  if (motorspeeda < 0) {
    leftServo.write(0);
  } else if (motorspeeda > 180) {
    leftServo.write(180);
  } else {
    leftServo.write(motorspeeda);
  }

}
//Called from main loop. Calls noLineHandler if line is lost.
void hasLine() {
  posValue = qtr.readLineBlack(sensorValues);
  if (0 == posValue || posValue == 7000) {
    noLineHandler();
  }
}
//Returns true if line sensors is on line, false if outside.
boolean getLine() {
  posValue = qtr.readLineBlack(sensorValues);
  if (0 == posValue || posValue == 7000) {
    return false;
  } else {
    return true;
  }
}

//Returns true if left end line sensor detects line.
boolean leftEndSensor() {
  posValue = qtr.readLineBlack(sensorValues);
  //Serial.println(sensorValues[7]);
  if (sensorValues[7] > 500) {
    return true;
  }
  else {
    return false;
  }
}
//Returns true if right en line sensor detects line.
boolean rightEndSensor() {
  posValue = qtr.readLineBlack(sensorValues);
  //Serial.println(sensorValues[0]);
  if (sensorValues[0] > 500) {
    return true;
  }
  else {
    return false;
  }
}
//Runs PID_controller 100 times to center robot
void calibrateDrive() {
  for (int i = 0; i < 100; i++) {
    PID_control();
  }
}
