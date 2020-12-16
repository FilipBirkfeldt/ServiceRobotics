//Called by hasLine() in lineSensor when line is lost.
//If case is 8 it means the right lap is done
void noLineHandler() {

  if (getRightCount() == 8) {
    detachServ();
    delay(1000);
    attachServ();
    uTurnHandler();
    incrementRight();
  }
  if (!getLine()) {
    noLine();
  }
}


//Calls maze solver in cases where more than one path is avaiable.
void choiceHandler() {
//  //X or forward T intersection
//  if (leftEndSensor() && rightEndSensor()){
//    currentMazeSide();
//    calibrateDrive();
//  }
//  //Left of right sided T section
//  else if (rightEndSensor() || leftEndSensor()){
//    if (!wallInFront()){
//      currentMazeSide();
//      calibrateDrive();
//    }
//  }

  posValue = qtr.readLineBlack(sensorValues);
  if  (leftEndSensor()) {

    if (!wallInFront()) {
      Serial.println("Välja fram eller vänster");
      currentMazeSide();
      calibrateDrive();
    }

  }
  if  (rightEndSensor()) {
    if (!wallInFront()) {
      Serial.println("Välja fram eller höger");
      currentMazeSide();
      calibrateDrive();
    }

  }
  if (leftEndSensor() && rightEndSensor()) {

    if (wallInFront()) {
      Serial.println("T-section");
      currentMazeSide();
      calibrateDrive();
    }
    else if (!wallInFront()) {
      Serial.println("Cross-section");
      currentMazeSide();
      calibrateDrive();
    }
  }
}

//Called by noLineHandler if case is not 8. 
//Checks if in uTurn or if in right turn with line lost. We will only handle right turns with line lost.
// If uTurn, run uTurnhandler. If right turn, the wheels will be driven by a regulator based on left distance sensor.
//When front wall is detected rotation to right and then follow left wall until line is found.
void noLine() {
  rotateRight();
  delay(150);
  while(!wallNear() && !getLine()){
    Wall_p_cont();
  }
  
  if (wallRight() && wallLeft() && wallNear()) {
      Serial.println("Uturn handler");
      uTurnHandler();
  }
  else if(!wallRight()){
    rotateRight();
    delay(800);
    forward();
    delay(600);
    while(!getLine()){
      Wall_p_cont();
    }
    calibrateDrive();
  }

//  else if ((!wallNear() && wallLeft())) {
//    while ((!wallNear() && wallLeft())) {
//      Wall_p_cont();
//      Serial.println("No line turn right");
//    }
//    rotateRight();
//    delay(800);
//    forward();
//    delay(600);
//    while (!getLine()) {
//      Wall_p_cont();
//    }
//    calibrateDrive();
//  }


}

//Handles uTurn
void uTurnHandler() {
  Serial.println("U TURN");
  // U-Svängen
  detachServ();
  delay(250);
  lift();
  attachServ();
  rotateRight();
  delay(100);
  while (!getLine()) {
    rotateRight();
  }
  detachServ();
  unLift();
  attachServ();
  calibrateDrive();
  stay();
  //unLift();
}
