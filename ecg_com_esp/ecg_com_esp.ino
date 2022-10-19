void setup() { 
// initialize the serial communication: 
Serial.begin(115200); 
pinMode(19, INPUT); // Setup for leads off detection LO + 
pinMode(18, INPUT); // Setup for leads off detection LO - 
  
} 
  
void loop() { 
  
if((digitalRead(19) == 1)||(digitalRead(18) == 1)){ 
Serial.println('!'); 
} 
else{ 
// send the value of analog input 0: 
Serial.println(analogRead(4)); 
} 
//Wait for a bit to keep serial data from saturating 
delay(1);
}
