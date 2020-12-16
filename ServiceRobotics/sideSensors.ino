//Values for regulation wheel speed based on left distance sensor.
int basespeedaa = 105;
int basespeedbb = 105;

double kp = 2;
double kd = 1.5;


const uint8_t maxspeedaa = 120;
const uint8_t maxspeedbb = 120;
void sideSensorSetup() {

  //No code needed.
}


//Returns true if wall is closer to left side than side distance limit
boolean wallLeft() {
  if (hc.dist(0) > side_distance_limit) {
    return false;
  }
  if (hc.dist(0) < side_distance_limit) {
    return true;
  }
}
//Returns true if wall is closer to right side than side distance limit
boolean wallRight() {
  if (hc.dist(1) < side_distance_limit) {
    return true;
  }
  if (hc.dist(1) > side_distance_limit) {
    return false;
  }
}
//Reads left distance sensor and regulates wheel speed to be as close to 12 cm as possible.
void Wall_p_cont() {
  int error = 12 - hc.dist(0);
  int motorSpeed = error * kp;
  int speeda = basespeedaa + motorSpeed;
  int speedb = basespeedaa - motorSpeed;

  if (speeda > maxspeedaa) {
    speeda = maxspeedaa;
  }
  if (speedb > maxspeedbb) {
    speedb = maxspeedbb;
  }
  if (speeda < 90) {
    speeda = 90;
  }
  if (speedb < 90) {
    speedb = 90;
  }
  //motorspeedb = 180 - motorspeedb;
  speeda = 180 - speeda;
  Serial.println(speeda);
  Serial.println(speedb);
  Serial.println(hc.dist(0));
  leftServo.write(speeda);
  rightServo.write(speedb);
