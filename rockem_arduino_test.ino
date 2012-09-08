int leftPin = 6;
int rightPin = 7;
int rightLimitPin = 11;
int leftLimitPin = 9;
int leftRightCenterPin = 13;

bool movementHaltedLeft = false;
bool movementHaltedRight = false;

// 0 Center Pin 12
// 0 In Pin 8
// 0 Out 10

// 1 In Pin 9
// 1 Out Pin 11
// 1 Center Pin 13

void setup() {
  // Setup Output Pins - THEY MUST START HIGH OR THERE WILL BE FIRE
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  digitalWrite(leftPin, HIGH);
  digitalWrite(rightPin, HIGH); 
  
  // Setup Limit Switches
  pinMode(rightLimitPin, INPUT);
  pinMode(leftLimitPin, INPUT);
  
  Serial.begin(9600);

}

void loop() {
  while (Serial.available() > 0) {
    int user = 0;
    int moveLeftRight = 0; 
    int moveForwardBack = 0; 
    int punchLeft = 0; 
    int punchRight = 0; 

    user = Serial.parseInt();
    moveLeftRight = Serial.parseInt(); 
    moveForwardBack = Serial.parseInt(); 
    punchLeft = Serial.parseInt(); 
    punchRight = Serial.parseInt(); 
    
    if (Serial.read() == '\n') {
      handleLeftRight(moveLeftRight);
      
      if (punchRight == 1) {
        calibrate();
      }

      Serial.print(user, DEC);
      Serial.print(moveLeftRight, DEC);
      Serial.print(moveForwardBack, DEC);
      Serial.print(punchLeft, DEC);
      Serial.println(punchRight, DEC);
    }
  }
}

void calibrate() {
  while (!movementHaltedLeft) {
    moveLeft();
  }

  while (digitalRead(leftRightCenterPin) == HIGH) {
    moveRight();
  }
}

void handleLeftRight(int _moveLeftRight) {
  if (_moveLeftRight == -1) {
    moveRight();
  } else if (_moveLeftRight == 1) {
    moveLeft();
  } else {
    haltLeftRightMovement();   
  }  
}

void moveRight() {
  if (digitalRead(rightLimitPin) == HIGH) {
    movementHaltedRight = false;
    digitalWrite(rightPin, HIGH);
    digitalWrite(leftPin, LOW);
  } else {
    movementHaltedRight = true;
    haltLeftRightMovement();
  }
}

void moveLeft() {
  if (digitalRead(leftLimitPin) == HIGH) {
    movementHaltedLeft = false;
    digitalWrite(rightPin, LOW);
    digitalWrite(leftPin, HIGH);
  } else {
    movementHaltedLeft = true;
    haltLeftRightMovement();
  }
}

void haltLeftRightMovement() {
  digitalWrite(rightPin, HIGH);
  digitalWrite(leftPin, HIGH); 
}