#include <SoftwareSerial.h>
SoftwareSerial ss(11, 12);

int pri=0;
int c;
int cnt=0;

int c1=0;
int c2=0;
int sys=0;
int dum=0;
int dys=0;
int hr=0;
int valid=0;
int p=0;
#include <LiquidCrystal.h> //Load Liquid Crystal Library
LiquidCrystal lcd(2,3,4,5,6,7);  //Create Liquid Crystal Object called LCD
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
int hb=0;
int sp=0;
int cnt1=0;
char data;

String response;
int temppin = A0;
float temp = 0;
int t;
void setup() 
{
Serial.begin(9600);

delay(500);
pinMode(8, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);


ss.begin(9600);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("H:");  
lcd.setCursor(0,1);
lcd.print("T:");  
lcd.setCursor(9,0);
lcd.print("SP02: ");  

lcd.setCursor(6,1);
lcd.print("   ");
lcd.setCursor(6,1);
lcd.print(sys);

lcd.setCursor(12,1);
lcd.print("   ");
lcd.setCursor(12,1);
lcd.print(dys);

lcd.setCursor(2,0);
lcd.print("    ");
lcd.setCursor(2,0);
lcd.print(hr);

   if (!pox.begin()) 
    {
        Serial.println("FAILED");
        for(;;);
    } else 
    {
        Serial.println("SUCCESS");
    }

lcd.setCursor(7,0);
lcd.print("0");
    }

void loop() 
{
  
if(digitalRead(10)==1)
{
p=1;
lcd.setCursor(7,0);
lcd.print("1");
//Serial.println("HP");
while(digitalRead(10)==1);
}

if(digitalRead(8)==1)
{
ss.print("*");
ss.print(1);
ss.print(",");
ss.print(p);
ss.print("#");
//Serial.println("FRONT");
while(digitalRead(8)==1);
}

if(digitalRead(9)==1)
{
ss.print("*");
ss.print(2);
ss.print(",");
ss.print(p);
ss.print("#");
//Serial.println("RIGHT");
while(digitalRead(9)==1);
}

  if(ss.available() >0)
 {
 c=ss.read();
 cnt=cnt+1;
 if(pri==0)
 {
  Serial.println("Measuring...");
  pri=1;
 }
Serial.println(c,DEC);
 if(cnt==1)
 {
 c1=c;
 }
 if(cnt==2)
 {
 c2=c;
 if(c1==85 && c2==0)
 {
 valid=1;
 }
 }
 if(cnt==3 && valid==0)
 {
 cnt=0;
 }
 if(cnt==3 && valid==1)
 {
 sys=c;
 }
 if(cnt==4 && valid==1)
 {
  dum=0;
 }
 if(cnt==5 && valid==1)
 {
  dys=c;
 }
 if(cnt==6 && valid==1)
 {
  hr=c;
 Serial.println("Complete...");
 Serial.print(sys); //send the pulse curve value
 Serial.print(","); //send the pulse curve value
 Serial.print(dys); //send the pulse curve value
 Serial.print(","); //send the pulse curve value
 Serial.println(hr); //send the pulse curve value
 
lcd.setCursor(6,1);
lcd.print("   ");
lcd.setCursor(6,1);
lcd.print(sys);

lcd.setCursor(12,1);
lcd.print("   ");
lcd.setCursor(12,1);
lcd.print(dys);

lcd.setCursor(2,0);
lcd.print("    ");
lcd.setCursor(2,0);
lcd.print(hr);
 }
 }
  temp = analogRead(temppin);
  temp = temp * 0.48828125;
  t=temp;
  if(temp>40)
  {
  digitalWrite(8, HIGH);
  }
  if(temp<36)
  {
  digitalWrite(8, LOW);
  }
    pox.update();  
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
    {
   hb=pox.getHeartRate();
   sp=pox.getSpO2(); 
   tsLastReport = millis();   
lcd.setCursor(14,0);
lcd.print("   ");
lcd.setCursor(14,0);
lcd.print(sp);

lcd.setCursor(2,1);
lcd.print("   ");
lcd.setCursor(2,1);
lcd.print(t);
}
cnt1=cnt1+1;
if(cnt1>1500)
{
    Serial.print("*");
    Serial.print(hr);
    Serial.print(",");
    Serial.print(sp);
    Serial.print(",");
    Serial.print(t);
    Serial.print(",");
    Serial.print(sys);
    Serial.print(",");
    Serial.print(dys);
    Serial.println("#"); 
 cnt1=0;
}
delay(10);
}
