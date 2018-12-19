/*
  
*/

char pin = 12;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() { 
  digitalWrite(pin,HIGH);
  delayMicroseconds(500);
  digitalWrite(pin,LOW);
  delayMicroseconds(500);
}
