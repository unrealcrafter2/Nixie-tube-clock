#include <RTClib.h>
#include <EEPROM.h>
#include <Wire.h>
RTC_DS3231 rtc;
char t[32];
 int IN1 = 0;
 int IN2 = 0;
 int IN3 = 0;
 int IN4 = 0;
 int Hour = 0;
 int Minute = 0;
 int DST;
void setup() {
    rtc.begin();
 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);  
  pinMode(A1, OUTPUT); 
  pinMode(A2, OUTPUT); 
  pinMode(A3, OUTPUT);
 
     Serial.begin(9600);
     DST = EEPROM.get(0, DST);

if(DST != 0 && DST != 1)  

{     

DST = 1;  

EEPROM.put(0, DST);

}

// Uncomment the following 2 lines if you need to set the DST (if you miss the actual day etc). Change the +1 to -1 in the fall.
// DateTime t2 = rtc.now();   
// rtc.adjust(DateTime(t2.year(), t2.month(), t2.day(), t2.hour()+1, t2.minute(), t2.second()));


}

void loop() {
 DateTime now = rtc.now();   

if (now.dayOfTheWeek() == 0 && now.month() == 3 && now.day() >= 8 && now.day() <= 16 && now.hour() == 2 && now.minute() == 0 && now.second() == 0 && DST == 0)     
{       

rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour()+1, now.minute(), now.second()));       
DST = 1;       
EEPROM.put(0, DST);     

}     
else if(now.dayOfTheWeek() == 0 && now.month() == 11 && now.day() >= 1 && now.day() <= 8 && now.hour() == 2 && now.minute() == 0 && now.second() == 0 && DST == 1)     
{       

rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour()-1, now.minute(), now.second()));       
DST = 0;       
EEPROM.put(0, DST);     
//stolen code for daylight savings
}
 
  if ((now.second() % 2) == 0) {
    digitalWrite(2, HIGH);
    
  }
  else   if ((now.second() % 2) != 0){
  
    digitalWrite(2, LOW);
  }
  Serial.print(now.hour());
 //switch indicator light every odd second
 Minute = now.minute();
 Hour = now.hour();
 if (Hour > 12){
  Hour = Hour - 12;
 }
// room for daylight savings
IN1 = (Hour / 10) % 10;
IN2 = Hour % 10;
IN3 = (Minute / 10) % 10;
IN4 = Minute % 10;

// set Nixies to rtc
 switch(IN1){
  case 0:
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  break;
  case 1:
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  break;
  case 2:
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  break;  
 }
switch (IN2){
  case 0:
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  break;
  case 1:
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  break;
  case 2:
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  break;
  case 3:
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  break;
  case 4:
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  break;
  case 5:
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  break;
  case 6:
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  break;
  case 7:
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  break;
  case 8:
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  break;
  case 9:
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  break;
}
switch (IN3){
  case 0:
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  break;
  case 1:
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  break;
  case 2:
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  break;
  case 3:
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  break;
  case 4:
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  break;
  case 5:
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  break;
  case 6:
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  break;
  case 7:
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  break;
  case 8:
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  break;
  case 9:
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  break;

}switch (IN4){
  case 0:
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  break;
  case 1:
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  break;
  case 2:
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  break;
  case 3:
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  break;
  case 4:
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  break;
  case 5:
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  break;
  case 6:
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  break;
  case 7:
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  break;
  case 8:
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  break;
  case 9:
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  break;
}
delay(200);
//SWITCH THE NIXIES
}
