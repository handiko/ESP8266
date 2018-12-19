/*
  
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(12, OUTPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);  
}

// the loop function runs over and over again forever
void loop() { 
  digitalWrite(12,HIGH);
  delay(1);
  digitalWrite(12,LOW);
  delay(1);
}
