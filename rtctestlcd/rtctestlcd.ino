// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
 
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>//this is the special I2C LCD display library that came with the display

 
RTC_DS1307 RTC;
// set the LCD address to 0x27 or 0x3F for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

 
void setup () {
//    Serial.begin(57600);
    Serial.begin(38400);
    Wire.begin();
    RTC.begin();
 
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  //uncomment to adjust time regardless of whether it's set
  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
 
}
 
void loop () {
    DateTime now = RTC.now();
 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
 
    Serial.print(" since 1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
 
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.unixtime() + 7 * 86400L + 30);
 
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
 
    Serial.println();
    delay(1000);
    
    //Serial.println(getDigitalTime(now));
    lcd.setCursor(0,0);
    lcd.print(getDigitalDate(now));
    lcd.setCursor(0,1);
    lcd.print(getDigitalTimeOnly(now));
}

String getDigitalDate (DateTime now) {
    String result = String(now.year()) + '/' + now.month() + '/' + now.day();    
    return result;
}
String getDigitalTimeOnly (DateTime now) {
  String hourstring = "";
  String minstring = "";
  String secstring = "";
  String ampm = "";  
  
  //add zeros to front of 1 character time components  
  if (now.hour() < 10) {
    hourstring = String(0) + String(now.hour());
    ampm = "AM";
  }
  else if (now.hour() > 12) {
    int adjHour = now.hour() - 12;
    if (adjHour < 10) {
      hourstring = String(0) + String(adjHour);
    }
    else {
      hourstring = String(adjHour);  
    }
    ampm = "PM";
  }
  if (now.minute() < 10) {
    minstring = String(0) + String(now.minute());
  }
  else {
    minstring = String(now.minute());
  }
  if (now.second() < 10) {
    secstring = String(0) + String(now.second());
  }
  else {
    secstring = String(now.second());
  }

  
  String result = hourstring + ':' + minstring + ':' + secstring + ' ' + ampm;  
  return result;
}
