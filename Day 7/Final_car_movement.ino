void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // led builtin
  pinMode(12, OUTPUT); // headlight leds
  pinMode(11, OUTPUT); // piezo buzzer
  
  pinMode(2, OUTPUT); // move backwards   
  pinMode(3, OUTPUT); // move forward 

  pinMode(4, OUTPUT); // turn right 
  pinMode(5, OUTPUT); // turn left 
  digitalWrite(6, HIGH); // PWM moving f/b
  digitalWrite(7, HIGH); // PWM turning l/r
  
}

void loop() {
  digitalWrite(11, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(12, HIGH);
  delay(200);
  digitalWrite(11, LOW);
  
  digitalWrite(3, HIGH);
  delay(4000);
  digitalWrite(3, LOW);
  delay(50);
  digitalWrite(2, HIGH);
  delay(4300);
  digitalWrite(2, LOW);

  
}
