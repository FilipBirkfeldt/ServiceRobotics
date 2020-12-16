int curr_angle;

//Grip servo setup
void gripServoSetup() {
  lift_servo.attach(liftPin);
  lift_servo.write(restAngle);
  grip_servo.attach(gripPin);
  grip_servo.write(gripRestAngle);
}


//Pick up cylinder and put on roof
void collectCylinder() {

  //stay();
  detachServ();
  delay(250);
  grip();
  delay(250);
  lift();
  delay(250);
  unGrip();
  delay(250);
  unLift();
  delay(250);

  grip();
  delay(50);
  lift();
  delay(50);
  unGrip();
  delay(50);
  unLift();
  delay(50);
  attachServ();

}
//Gripper in top position
void gripperUp() {
  grip();
  delay(250);
  lift();
}
//Gripper to just hold cylinder
void holdCylinder() {
  stay();
  grip();
  delay(250);
  lift_servo.write(restAngle - 15);
}
//Close grip
void grip() {
  for (int i = gripRestAngle; i >= gripAngle; i--) {
    grip_servo.write(i);
    delay(10);
  }
  holding = true;
}
//Open grip
void unGrip() {
  for (int i = gripAngle; i <= gripRestAngle; i++) {
    grip_servo.write(i);
    delay(10);
  }
  holding = false;
}
//Lift to lift angle
void lift() {
  gripLifted = true;
  for (int i = restAngle; i >= liftAngle; i--) {
    lift_servo.write(i);
    delay(10);
  }
}
//Lower to restAngle
void unLift() {
  gripLifted = false;
  for (int i = liftAngle; i <= restAngle; i++) {
    lift_servo.write(i);
    delay(10);
  }
}
