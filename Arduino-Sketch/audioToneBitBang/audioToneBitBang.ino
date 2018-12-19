/*
  
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(14, OUTPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);  
}

// the loop function runs over and over again forever
void loop() { 
  digitalWrite(14,HIGH);
  delay(1);
  digitalWrite(14,LOW);
  delay(1);
}
