#include <math.h>
#define trigPin 10
#define echoPin 13
#include <dht.h>
#define dht_pin A5
dht DHT;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensePin = 1;
int pump = 0;
int Sonar_buzzer = 6;
int lightSensorPin = A1;
int lightSensorPin2 = A2;
int lightSensorPin3 = A3;
int  light1= 0;
int  light2= 0;
int light3=0;

void moistureDisplay(int m)
{
  lcd.setCursor(0, 0);
  lcd.print("Moisture :"); 
  if(m<=1023 && m>=800)
  {
    //very dry
    lcd.setCursor(11, 0);
  lcd.print("V Dry"); 
    
  }
  else if(m<800 && m>=500)
  {
    //dry
    lcd.setCursor(11, 0);
  lcd.print("Dry  ");
  }
  else if(m<500 && m>=300)
  {
    //wet
    lcd.setCursor(11, 0);
  lcd.print("Ideal");
  }
  else if(m<300 && m>=50)
  {
    //very wet
    lcd.setCursor(11, 0);
  lcd.print("Extra");
  }
}


void Temp_hum_Display(int h,int m)
{
  lcd.setCursor(0, 0);
  lcd.print("Humidity :");
  lcd.setCursor(11, 0); 
  lcd.print(h); 
  lcd.setCursor(0, 1);
  lcd.print("Temperature :");
  lcd.setCursor(14, 1); 
  lcd.print(m); 
  
}










void lightDisplay(int l0,int l1,int l2)
{
  lcd.setCursor(0, 1);
  lcd.print("Light : "); 
  int l=(l0+l1+l2)/3;
  if(l>=500)
  {
    //superbright
    
  lcd.setCursor(8, 1);
  lcd.print("S Bright ");
  }
  else if(l>=200 && l<500)
  {
    //bright
    
  lcd.setCursor(8, 1);
  lcd.print("Bright   ");
  }
  else if(l<200 && l>50)
  {
    //dim
    
  lcd.setCursor(8, 1);
  lcd.print("Dim     ");
  }
  else if(l<=50)
  {
    //dark
    
  lcd.setCursor(8, 1);
  lcd.print("Dark     ");
  }
  
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin (9600);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("WELCOME");
  lcd.setCursor(11, 0);
  lcd.print("TO");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("SMART");
  
  lcd.setCursor(7, 1);
  lcd.print("GARDENING");

   delay(3000);
//  lcd.clear;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(8, OUTPUT);
   pinMode(7, OUTPUT);
  pinMode(Sonar_buzzer, OUTPUT);


}





void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_pin);
  int sensorValue = analogRead(A0); 
  Serial.print("Moisture = ");
  Serial.println( sensorValue);
  delay(300);
   moistureDisplay(sensorValue);
  light1 = analogRead(lightSensorPin);
  light2 = analogRead(lightSensorPin2);
  light3 = analogRead(lightSensorPin3);
  lightDisplay(light1,light2,light3);
  Serial.print("Light = ");
  Serial.println( light2);
   Serial.print("Light1 = ");
  Serial.println( light3);
  Serial.print("Light4 = ");
  Serial.println( light1);
  Serial.print("Light = ");
  Serial.println( (light1+light2+light3)/3);
  Serial.print("Temperature ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity ");
  Serial.println(DHT.humidity);
 if (sensorValue >=500 && sensorValue <=1023)
 {
 digitalWrite(8, HIGH);
 digitalWrite(7, HIGH);
 }
 else
 {
  digitalWrite(8,LOW);
  digitalWrite(7, LOW);
 }
 
  float duration, distance;
  float spdSnd;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  spdSnd = 331.4;
  distance = (duration / 2) * (spdSnd / 10000);
 
  if (distance >= 400 || distance <= 2)
  {
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  if(distance <= 20)
  {
    digitalWrite(Sonar_buzzer,HIGH);
  }
  else
  {
    digitalWrite(Sonar_buzzer,LOW);
  }
  delay(1000);
  lcd.clear();
  Temp_hum_Display(DHT.humidity,DHT.temperature);
  delay(1000);

}
