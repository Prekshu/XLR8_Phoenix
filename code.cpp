#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "analogWrite.h"


const char* ssid = "esp32_10";
const char* password = "vyass1234";

AsyncWebServer server(80);

int inp1=14;
int inp2=18;
int inp3=4;
int inp4=15;

int pwm1=13;
int pwm2=5;

int led=2;


void setup(){
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);

  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);

  pinMode(led, OUTPUT);


  analogWrite(pwm1,255);
  analogWrite(pwm2,255);
  

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
    
    if(request->hasArg("up")){
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);

      digitalWrite(led, HIGH);
    }

    if(request->hasArg("down")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
      
    }

    if(request->hasArg("left")){
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
    }
    
    if(request->hasArg("right")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);
    }
    
    if(request->hasArg("off")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, LOW);    

      digitalWrite(led, LOW);
    }

    if(request->hasArg("slow")){
      analogWrite(pwm1, 176);
      analogWrite(pwm2, 176);  
    }

    if(request->hasArg("fast")){
      analogWrite(pwm1, 255);
      analogWrite(pwm2, 255);  
    }
    
    request->send_P(200, "text/plain", "");
  });
  

  server.begin();
}
 
void loop(){
  
}
