void setup() {
//initialize the serial communication:
Serial.begin(9600);
pinMode(12, INPUT); //Setup for leads off detection LO +
pinMode(13, INPUT); //Setup for leads off detection LO -
 
}
 
void loop() {
 
if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
Serial.println('*');
}
else{
//envie o valor da entrada analógica 0:
Serial.println(analogRead(A0));
}
//Aguarde um pouco para evitar que os dados seriais fiquem saturados
delay(1);
}
