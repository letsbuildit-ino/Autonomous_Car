void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // led builtin
  pinMode(12, OUTPUT); // headlight leds
  pinMode(13, OUTPUT); // piezo buzzer
}

void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, HIGH);
  delay(500);                       // wait for half a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(12, LOW);
  delay(500);                       // wait for half a second
}
