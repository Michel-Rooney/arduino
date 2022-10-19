#include <string>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFi.h>

const char* ssid = "Teka";          
const char* password = "Myan1983";  
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
const int output4 = 4;

WiFiServer server(80);


void setup(){
  Serial.begin(115200);
  pinMode(12, INPUT); //Setup for leads off detection LO +
  pinMode(13, INPUT); //Setup for leads off detection LO -
  Serial.print("Conectando:  ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  
}

void loop (){
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
  Serial.println('*');
  }
  else{
  //envie o valor da entrada analógica 0:
  Serial.println(analogRead(output4));
  }
  //Aguarde um pouco para evitar que os dados seriais fiquem saturados
  delay(1);
  WiFiClient client = server.available();
  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("NOVO CLIENTE.");          
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
         
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
           
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("h1{ font-family:Arial; color : #17BEBB ;}");
            client.println("body {background-color: #004E61;}");
            client.println("h2 {color:#715AFF}");
            client.println("p { }</style></head>");
            
            
            client.println("<body><h1>ESP32 Web Server </h1>");
            client.println("<h1>Testando o Ultrasonic</h1>");
            
            client.println("<h2>Distancia em CM: </h2>");
            client.println("<h2>Web Server feito por:<br>Michel Rooney e Juan Severiano</h2>");
            client.println("<meta http-equiv='refresh' content='3' >");
            client.println("</body></html>");
            
            
            client.println();
            
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;     
        }
      }
    }
  }
}
