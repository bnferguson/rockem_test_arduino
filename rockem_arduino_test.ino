void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    int user = Serial.parseInt(); 
    int moveLeftRight = Serial.parseInt(); 
    int moveForwardBack = Serial.parseInt(); 
    int punchLeft = Serial.parseInt();
    int punchRight = Serial.parseInt();
    
    if (Serial.read() == '\n') {
      Serial.print(user, DEC);
      Serial.print(moveLeftRight, DEC);
      Serial.print(moveForwardBack, DEC);
      Serial.print(punchLeft, DEC);
      Serial.println(punchRight, DEC);
    }
  }
}

