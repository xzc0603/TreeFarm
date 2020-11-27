#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

#define DHTPIN 2     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Servo servo;      //Servo 클래스로 servo객체 생성
int soil = A2;
int dcmt = 3;
int servoPin = 4;
int angle = 70; // servo position in degrees 

unsigned int arr[6] = {0,}; //순서대로 0온도, 1습도, 2EC, 3미세먼지, 4CO₂, 5조도 센서



void setup() {
  #include "init.h"
  
}

void loop() {
  //#include "functions.h"
  dht22();
  
  int cds = analogRead(A1);
  arr[5] = cds;
  Serial.print("cds값은:");
  Serial.println(arr[5]);

  void servomt();
}


void dht22(){
    float t = dht.readTemperature(); // Read temperature as Celsius (the default)
    float h = dht.readHumidity();  
    arr[0]= t;
    arr[1]= h;
    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }    
    Serial.print(F("Humidity: "));
    Serial.print(arr[1]);
    Serial.print(F("%  Temperature: "));
    Serial.print(arr[0]);
    Serial.println(F("°C "));
  }

void servomt(){
  int value = analogRead(soil);
  arr[2] = value;
  Serial.print("센서 값");
  Serial.println(arr[2]);
  delay(500);
  
  if(value <=100){
    digitalWrite(3, 1);
   
      for(angle = 80; angle < 135; angle++) 
    { 
      servo.write(angle); 
      delay(15); 
    } 
    
    for(angle = 135; angle >80; angle--) 
    { 
      servo.write(angle); 
      delay(15); 
    }
    for(angle = 80; angle < 135; angle++) 
    { 
      servo.write(angle); 
      delay(15); 
    } 
    for(angle = 135; angle > 80; angle--)                   
    { 
      servo.write(angle); 
      delay(15); 
    }
  }
  
  else if(value >600){
    digitalWrite(3, 0);
  }

  }  
