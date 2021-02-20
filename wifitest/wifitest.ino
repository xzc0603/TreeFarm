#include <ESP8266WiFi.h>
#define PORT 9000

WiFiClient client; // 클라이언트 대리자를 선언합니다
WiFiServer server(PORT);

String dataClient;
const char* ssid = "KB603"; // ex) sungMI
const char* pass = "0537517755"; // ex) 12345
 
//#define LED 2 // GPIO 2

void setup() { // 처음, 한번만 실행되는 함수입니다
  Serial.begin(115200); // 통신속도를 설정합니다
//  Serial.println("test TCPIP "); // 제목을 송신합니다
//
//  Serial.print("Port : ");
//  Serial.println(PORT);
 
  WiFi.begin(ssid, pass); // TCPIP 를 시작합니다
  while (WiFi.status() != WL_CONNECTED) { // 연결시까지 대기합니다
//    Serial.print(".");
    delay(200); // 20밀리초 지연을 진행합니다
  }

//  Serial.print("Point : ");
//  Serial.println(ssid); // 무선네트워크 ID
//
//  Serial.println("Alarm IP : ");
//  Serial.println(WiFi.localIP()); // ex) 192.168.0.28

  delay(200);
  server.begin();
} 

void loop() {   // 메인루프입니다
   while(!client.connected())// TCPIP 가 끈어진 상태면?
   client = server.available(); 
   while (client.connected())// TCPIP 가 연결된 상태면?
   { 
      String rxbuf="",txbuf=""; //버퍼
      if (client.available())rxbuf=client.readStringUntil('\n');
      if (Serial.available())txbuf=Serial.readStringUntil('\n');
      if(rxbuf.length())Serial.println(rxbuf);
      if(txbuf.length())client.print(txbuf);
   }   
}
