#include<SoftwareSerial.h>
#include <math.h>
const int x_out = A1; /* connect x_out of module to A1 of UNO board */
const int y_out = A2; /* connect y_out of module to A2 of UNO board */
const int z_out = A3; /* connect z_out of module to A3 of UNO board */
int x_adc_value, y_adc_value, z_adc_value;
SoftwareSerial Serial1(2,3);
#define sensor D5
int sensor=1,i;
int flag=0;
String str="";
char j[61];
void setup()
{
  
  Serial1.begin(9600);
  Serial.begin(9600);
  gsmInit();
  Serial.print("System Ready");
}
void loop()
{
  pinMode(5,INPUT);
   x_adc_value = analogRead(x_out); /* Digital value of voltage on x_out pin */ 
  y_adc_value = analogRead(y_out); /* Digital value of voltage on y_out pin */ 
  z_adc_value = analogRead(z_out); /* Digital value of voltage on z_out pin */ 
  Serial.print("x = ");
  Serial.print(x_adc_value);
  Serial.print("\t\t");
  Serial.print("y = ");
  Serial.print(y_adc_value);
  Serial.print("\t\t");
  Serial.print("z = ");
  Serial.println(z_adc_value);
  
  //Serial.print("\t\t");
  delay(1000);
  Serial.println("normal");
  if(digitalRead(5)==LOW)
  {
  if (Serial.available()>0)
  {
    for(i=0;i<=60;i++)
    {
    j[i]=Serial.read();
    }
  }
  
 sendSMS("x:"+(String)x_adc_value+"y:"+(String)y_adc_value+"z:"+(String)z_adc_value+(char*)j);
  }
//    if(digitalRead(sensor)==1 && flag==0)
//    {
//      
//      if(digitalRead(sensor)==1)
//      {
//       
//        sendSMS("Accident Detected");
//        
//        Serial.println("All sensors are activated");
//     
//        
//        flag=1;
//      }
//    }
//    else if(digitalRead(sensor)==0 && flag==1)
//    {
//      
//      if(digitalRead(sensor)==0)
//      {
//      
//        sendSMS("all is well Don't worry");
//       
//        
//        flag=0;
//      }
//    }
}
 
void sendSMS(String msg)
{
  Serial.println("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.print("AT+CMGS=");
  Serial1.print('"');
  Serial1.print("+919050567850");    // number
  Serial1.print('"');
  Serial1.println();
  
  Serial1.println(msg);
  delay(500);
  Serial1.write(26);
  delay(1000);

  Serial.println("SMS Sent");
  delay(1000);

}
void gsmInit()
{
 
  Serial.println("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial1.println("AT");
    while(Serial1.available()>0)
    {
      if(Serial1.find("OK"))
      {
      Serial.print("OK");
      at_flag=0;
    }
    }
    delay(1000);
  }
  Serial1.println("ATE0");

  Serial.println("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial1.println("AT+CPIN?");
    while(Serial1.available()>0)
    {
      if(Serial1.find("READY"))
      net_flag=0;
      break;
    }
    delay(1000);
  }
   Serial1.println("AT+CNMI=2,2,0,0,0");
   delay(1000);
   Serial1.println("AT+CMGF=1");
   delay(1000);
   Serial1.println("AT+CSMP=17,167,0,0");
  
   Serial1.flush();
}
