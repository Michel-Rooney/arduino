#include <string>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFi.h>

const char* ssid = "Teka";          
const char* password = "Myan1983";  

WiFiServer server(80);

String header;
const int trigPin = 5;
const int echoPin = 18;
long duration;
float distanceCm;
float distanceInch;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
String distanciaCm;

#define SOUND_SPEED 0.034

void setup() {
  Serial.begin(115200);      
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

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


void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  distanciaCM = String(distanceCm);

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(3000);
  
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
            
            client.println("<h2>Distancia em CM: " + dist_Cm + "</h2>");
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
