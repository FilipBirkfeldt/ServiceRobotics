//Maze logic parameters
uint8_t leftway = 0;
uint8_t leftWayHome = 0;
uint8_t currentMazeId = 0;
uint8_t rightWay = 0;
uint16_t nudge = 1000;

//Called by drive logic when choice is detected. Goes to left or rightsided maze handler.
void currentMazeSide () {
  if (currentMazeId == 0) {
    mazeRightSide();
  } else {
    mazeLeftSide();
  }
}
//Returns in what case of rightWay the robot is
uint8_t getRightCount() {
  return rightWay;
}
//Returns what case of leftWay the robot is
uint8_t getLeftCount() {
  return leftway;
}
//Increments right way "manually".
void incrementRight() {
  rightWay++;
}
//What choices the robot will take when introduced to each of them in left way.
void mazeLeftSide() {
  Serial.println("mazeLeft");
  Serial.println(leftway);
  switch (leftway) {
    case 0:
      _left();
      leftway ++;
      break;
    case 1:
      forward();
      delay(100);
      leftway ++;
      break;
    case 2:
      _left();
      leftway ++;
      break;
    case 3:
      _left();
      leftway ++;
      break;
    case 4:
      _left();
      leftway ++;
      break;
    case 5:
      forward();
      delay(100);
      leftway ++;
      break;
    case 6:
      _left();
      leftway ++;
      break;
    //CASE SEX ÄR VÄSTERSVÄNGEN SOM INTE ÄR ETT VAL
    case 7:
      _left();
      leftway ++;
      break;

    case 8:
      forward();
      delay(100);
      leftway ++;
      break;
    case 9:
      _right();
      leftway ++;
      break;
    case 10:
      _left();
      leftway ++;
      break;
    case 11:
      _right();
      leftway ++;
      break;
  }
}
//What choices the robot will take when introduced to each of them in right way.
void mazeRightSide() {
  Serial.println("mazeRight");
  Serial.println(rightWay);
  switch (rightWay) {
    case 0:
      _left();
      rightWay ++;
      break;
    case 1:
      _left();
      rightWay ++;
      break;
    case 2:
      forward();
      delay(100);
      rightWay ++;
      break;
    case 3:
      forward();
      delay(100);
      rightWay ++;
      break;
    case 4:
      _left();
      rightWay ++;
      break;
    case 5:
      _left();
      rightWay ++;
      break;
    case 6:
      forward();
      delay(100);
      rightWay ++;
      break;
    case 7:
      _right();
      rightWay ++;
      break;
    case 8:
      _left();
      currentMazeId++;
      break;

  }
}
//Nudges the robot past the choice state so that it can continue on line.
void _left() {
  strongLeft();
  delay(nudge);
  while (!getLine()) {
    strongLeft();
  }
  //calibrateDrive();
}
//Nudges the robot past the choice state so that it can continue on line.
void _right() {
  strongRight();
  delay(nudge);
  while (!getLine()) {
    strongRight();
  }
  //calibrateDrive();
}
