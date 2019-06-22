#include<ESP8266WiFi.h>
#include<ThingSpeak.h>
#include<Ultrasonic.h>

#ifndef STASSID
#define STASSID "DEADSHOT"
#define STAPSK "Htauifg2632"
#endif
 const char* ssid=STASSID;
 const char* password = STAPSK;
 char thingspeakAddress[]= "api.thingspeak.com";
 unsigned long channelID =  798700;
 char* writeAPIKey ="MEIAFXMQAYSO8IPA";
 //char* readAPIKey ="J9RAJBCK31XHOVNT";
 unsigned int TSfield1 = 1;
 unsigned int TSfield2 = 2;
 unsigned int TSfield3 = 3;

 WiFiClient client ;
 void setup()
 {
  Serial.begin(115200);
  Serial.println("Start");
  connectwifi();
  pinMode(D6,INPUT);
  delay(1000);
 }

void loop()
{
  float readValue= digitalRead(D6);
  float readValue2= digitalRead(D1);
  float readValue3= digitalRead(D3);
  Serial.println("IR sensorVal = "+ String(readValue));
 write2TSData(readValue,readValue2,readValue3);
 //read_data_from_thingspeak(channelID,TSfield1);
  delay(2000);
}

int connectwifi()
{
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  ThingSpeak.begin(client);
}

 int write2TSData(float field1Data,float field2Data, float field3Data)
{
  ThingSpeak.setField(TSfield1,field1Data);
  ThingSpeak.setField(TSfield2,field2Data);
  ThingSpeak.setField(TSfield3,field3Data);
  int writeSuccess = ThingSpeak.writeFields(channelID,writeAPIKey);
  return writeSuccess;
}

/*int read_data_from_thingspeak(long TSchannel,unsigned int TSfield)
{
  float data=ThingSpeak.readFloatField(TSchannel,TSfield,readAPIKey);
  Serial.println("Read data from thing speak: " + String(data,9));
  return(data);
}*/
