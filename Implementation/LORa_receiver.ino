#include <SoftwareSerial.h>
SoftwareSerial ss(11, 12);
int a1=0;
int b1=0;
String response;
void setup()
{
Serial.begin(9600);
ss.begin(9600);

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
}


int ESPwait1(String stopstr, int timeout_secs)
{
  bool found = false;
  char c;
  long timer_init;
  long timer;

  response="";
  timer_init = millis();
  while (!found) {
  timer = millis();
  if (((timer - timer_init) / 1000) > timeout_secs) { // Timeout?
  Serial.println("!Timeout!");
  return 0;  // timeout
  }
    if (ss.available()) 
    {
      c = ss.read();
      response += c;
      if (response.endsWith(stopstr)) {
      found = true;
      delay(10);
      }
    } // end Serial1_available()
  } // end while (!found)
  return 1;
}

void loop()
{
 if(ss.available())
  {    
  char c;
  c=ss.read();
  if(c=='*')
    {
      if(ESPwait1("#",3))
      {
      char * strtokIndx;
      response.remove(response.length()-1);
      strtokIndx = strtok(const_cast<char*>(response.c_str()),",");      // get the first part - the string
      a1 = atoi(strtokIndx);
      
      strtokIndx = strtok(NULL, ","); 
      b1 = atoi(strtokIndx);
            
      Serial.println(a1);
      Serial.println(b1);
if(a1==1)
{
 digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 delay(5000);
 digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
a1=0;
}

if(a1==2)
{
 digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);     
 delay(5000);
 digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
a1=0;
}

      response=""; }
    }
  }
}
