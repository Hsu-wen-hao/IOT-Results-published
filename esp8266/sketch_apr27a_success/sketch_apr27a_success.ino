//#include <WiFi.h>
//#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include "StringLog.h"
#include <Servo.h>//宣告


/* WiFi network name and password */
//const char *ssid = "Iwatch";
//const char *pwd = "753753753";

//const char *ssid = "dlink-91EC";
//const char *pwd = "753753753";

const char *ssid = "HINET-5806";
const char *pwd = "home23391234";

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
//const char * udpAddress = "192.168.1.100";
//const char *udpAddress = "172.20.10.3";
//const char *udpAddress = "192.168.0.103";
//const char *udpAddress = "192.168.0.108";
const char *udpAddress = "192.168.1.109";
const int udpPort = 50001;

//create UDP instance
WiFiUDP udp;

const int TOUCH_SENSOR_PIN = D0; //觸碰模組腳位
const int SERVO1_PIN        = D1 ; // 馬達模組腳位
int angle = 0;         // 馬達角度參數
int lastTouchState;    // 紀錄最後觸碰模組參數
int currentTouchState; // 觸碰模組參數

Servo servo1; // 創造一個馬達1

void setup(){
  Serial.begin(115200);
  
  //Connect to the WiFi network
   WiFi.begin(ssid, pwd);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);

  pinMode(D1, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT); // 輸入觸碰
  servo1.attach(SERVO1_PIN);          // 馬達
  //servo2.attach(SERVO_PIN); 
  servo1.write(0);
  currentTouchState = digitalRead(TOUCH_SENSOR_PIN); //讀取有無觸碰參數
}

void loop(){
bailout1:
Serial.println("1");
  //data will be sent to server
  //uint8_t buffer[50] = "hello world";
  uint8_t buffer[50] = "Device_001";
  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write(buffer, 11);
  udp.endPacket();
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();

  Serial.println("2");
  
  //---回傳成功---
  udp.beginPacket(udpAddress, udpPort);
  udp.write("Device_001 return success");
  udp.endPacket();
  
  //receive response from server, it will be HELLO WORLD
  if(udp.read(buffer, 50) > 0){
    Serial.print("Server to client: ");
    Serial.println((char *)buffer);
    //Serial.println(*buffer);

    //---當收到回傳值為a時 啟動馬達
    if(*buffer=='a')
    {
      Serial.println("hello world");
      //digitalWrite(D1, HIGH);
      //servo1.write(0);
      //delay(100);
      //servo1.write(40);
      servo1.write(0);
      delay(100);
      //servo1.write(120);
      //delay(100);
      //servo1.write(80);
      //delay(100);
      //servo1.write(120);
      //delay(100);
      //servo1.write(80);
      //delay(100);
      //delay(3000);
      //digitalWrite(D1, LOW);
      //delay(3000);
      goto bailout1;
    }
    //---當收到回傳值為b時 停止馬達
    else if(*buffer=='b')
    {
      Serial.println("hello world");
      //digitalWrite(D1, LOW);
      //servo1.write(-40);
      servo1.write(130);
      delay(100);
      //digitalWrite(D1, LOW);
      //delay(3000);
      goto bailout;
    }
    else
    {
      Serial.println("no hello world");
    }        
        
  }

 bailout:
  if(digitalRead(TOUCH_SENSOR_PIN) == 1)
  {
    Serial.println("The sensor is touched");
    //digitalWrite(D1, HIGH);
    //servo1.write(90);
    servo1.write(0);
    delay(100);
    /*servo1.write(80);
    delay(100);
    servo1.write(120);
    delay(100);
    servo1.write(80);
    delay(100);
    servo1.write(120);
    delay(100);*/
    //servo1.write(80);
    //delay(100);
    
    //delay(100); 
  }
  else if(digitalRead(TOUCH_SENSOR_PIN) == 0)
  {
    Serial.println("The sensor is not touched");
    //digitalWrite(D1, LOW);
    //servo1.write(120);// 可以按
    servo1.write(130);
    delay(100);
  }
  else
  {
    goto bailout1;
  }
  
  //Wait for 1 second
  delay(1);
}
