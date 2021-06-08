void setup() {
  
  pinMode(2, OUTPUT); // move backwards   
  pinMode(3, OUTPUT); // move forward 

  pinMode(4, OUTPUT); // turn right 
  pinMode(5, OUTPUT); // turn left 
}

void loop() {
  
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(600);
  digitalWrite(2, LOW);
  
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(5, HIGH);
  delay(400);
  digitalWrite(5, LOW);
}
