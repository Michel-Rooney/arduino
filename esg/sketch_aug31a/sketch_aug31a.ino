#define sensorpin A0

void setup() {
//initialize the serial communication:
Serial.begin(9600);
pinMode(34, INPUT); //Setup for leads off detection LO +
pinMode(35, INPUT); //Setup for leads off detection LO -

}
 
void loop() {
 
if((digitalRead(34) == 1)||(digitalRead(35) == 1)){
Serial.println('*');
}
else{
//envie o valor da entrada analógica 0:
Serial.println(analogRead(sensorpin));
}
//Aguarde um pouco para evitar que os dados seriais fiquem saturados
delay(1);
}
