
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<SoftwareSerial.h>
SoftwareSerial s(D7,D6); //RX  TX




/* Maping nodeMCU and Arduino */
//Pin LED 15/5/4/0/2/14/12/13/15>>D-0/1/2/3/4/5/6/7/8/ 
/****************************************************/
const int digiinoutpin = 5; // Chage for in/out pin decleration
int count=0;

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "MI MAX 2"      //change here
#define WLAN_PASS       "11221122"    //change here
/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "managment.unlimitenablement.co.in"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "team13/team13"    //<tennant name/user name>
#define AIO_KEY         "fourtech777"    //<password>
/************ Global State (you don't need to change this!) ******************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/****************************** Feeds ***************************************/
// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, "s/us");
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");
/*************************** Sketch Code ************************************/
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
void setup() {

  s.begin(9600);
 
 
  Serial.begin(9600);
  delay(10);
  Serial.println(F("Demo"));
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  Serial.print("MAC: "); Serial.println(WiFi.macAddress());
  MQTT_connect();
   if (! photocell.publish("100,NodeMCU,WIFI module")) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  if (! photocell.publish("110,S25000051,MQTT test model,Rev0.1")) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  // Setup MQTT subscription for onoff feed.
  //mqtt.subscribe(&onoffbutton);
  String data;
}
void loop() {
  



  
   //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
   MQTT_connect();
  delay(5000);
    count++;  
     // Now we can publish stuff!
//  Serial.print(F("\nSending Meter Reading value: "));   
//    String data123="200,Gas,m3,"+String(count);
//    Serial.print(data123.c_str());
//    Serial.println("...");  
//    if (! photocell.publish(data123.c_str())) {
//      Serial.println(F("publish Failed"));
//    } else {
//      Serial.println(F("publish Send...."));
//    }
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
