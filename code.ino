#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define BLYNK_TEMPLATE_ID "TMPL6mbR1_w19"
#define BLYNK_TEMPLATE_NAME "irr"
#define BLYNK_AUTH_TOKEN "EB3h9uOVPGlk0z09MkmCowuH0H0aJtUw"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
const int mo = 16;
#define DHTPIN 14 // DHT11 sensor pin D5
const int sensorPin = A0;
int sensorValue;
float moi;

#define DHTTYPE DHT11 // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Rafa1";
char pass[] = "abc21cba";



BLYNK_WRITE(V0)   //Virtual Pin V0 declared in Blynk Console & App
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(mo, HIGH);
    Serial.println("LIGHT ON");
  }
  if(value == 0)
  {
     digitalWrite(mo, LOW);
     Serial.println("LIGHT OFF");
  }
}


void setup()
{
 Serial.begin(9600);
 dht.begin();
 Blynk.begin(auth, ssid, pass);
  pinMode(mo, OUTPUT);
  pinMode(sensorPin, INPUT);
  Wire.begin();
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  
}

void loop()
{
 Blynk.run();
 float temp = dht.readTemperature();
 float hum = dht.readHumidity();
  Serial.println(temp);
Serial.println(hum);
 if (isnan(temp) || isnan(hum)) {
 Serial.println(temp);
Serial.println(hum);
 Serial.println("Failed to read from DHT sensor!");
  
 
 return;
 }
 //////////////////////////////////////////
 sensorValue = analogRead(sensorPin);  

 Serial.print("Moisture Sensor Value:");
 Serial.println(sensorValue); 
 //Display the Moisture Percentage
int sen= 1024-sensorValue;
Serial.println(sen); 
 moi= ((sen/1023.00) * 100.00);

 Serial.print("Moisture Percentage = ");
 Serial.println(moi);
 
 lcd.setCursor(0,0);
 lcd.print("temp=");
 lcd.print(temp);
 lcd.print("C");
 
 lcd.setCursor(0,1);
delay(1000);
lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Humidity=");
 lcd.print(hum);
 lcd.setCursor(0,1);
 
 delay(1000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("moisture=");
 lcd.print(moi);
 lcd.print("%");
 lcd.setCursor(0,1);
 delay(1000);
lcd.clear();
Blynk.virtualWrite(V1, temp);
 Blynk.virtualWrite(V2, hum);
 Blynk.virtualWrite(V3, moi);
 delay(2000);
}
