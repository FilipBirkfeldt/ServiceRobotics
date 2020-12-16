int last;
//Setup breakSwitch
void frontSensorSetup() {

  //Front Switch
  pinMode(INPUT, breakSwitch);

}

// 85 volt isch 14 cm
// returns true if front sensor is closer to wall than wallInFrontLimit
boolean wallInFront() {
  for (int i = 0; i < sensorBuff; i++) {
    avgDist[i] = analogRead(IRPin);
  }
  int avg = _avgDist(avgDist);
  if (avg > wallInFrontLimit) {
    return true;
  } else {
    return false;
  }
}

// returns true if front sensor is closer to something than wallNearLimit
boolean wallNear() {
  for (int i = 0; i < sensorBuff; i++) {
    avgDist[i] = analogRead(IRPin);
  }
  int avg = _avgDist(avgDist);
  if (avg > wallNearLimit) {
    return true;
  } else {
    return false;
  }
}
//Private average function
int _avgDist(int dist[]) {
  int avg = 0;
  for (int i = 0; i < sensorBuff; i++) {
    avg += avgDist[i];
  }
  return avg / sensorBuff;
}


//Returns true of front switch is pressed
boolean frontSwitch() {
  return !digitalRead(breakSwitch);
}
