#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>//this is the special I2C LCD display library that came with the display
#include <SPI.h>
#include <SD.h>      //this includes the SD card libary that comes with the Arduino
#include "SparkFunHTU21D.h"
//#include <TimerOne.h>//this is a library that uses the (16 bit) timer 1 of the arduino to trigger interrupts in certain time intervals.
                     //here we use it to read sensor values precisely every 500ms. 

#define chipSelect 10//we are using pin#10 as chip select pin for the SD card
#define buttonPin 8 
long lastFileWrite = 0;
long lastDisplayWrite = 0;
int powerStatus = 1;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 200;

// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
HTU21D myHumidity;
RTC_DS1307 RTC;
 
void setup () {
  Serial.begin(38400);
  Wire.begin();
  RTC.begin();
  myHumidity.begin();

  pinMode(buttonPin, INPUT);
 
  /*if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }*/
  //uncomment to adjust time regardless of whether it's set
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();

  //set up SD card
  Serial.print("Initializing SD card..."); 
  if (!SD.begin(chipSelect)) { // see if the card is present and can be initialized:
    Serial.println("Card failed, or not present");
    lcd.setCursor(0,0);
    lcd.print("SD Card Fail"); //notify of SD card fail
    delay(3000); // wait 3 sec so user sees message
    return;//exit the setup function. This quits the setup() and the program counter jumps to the loop().
  }
  Serial.println("card initialized.");//otherwise, tell us that the card was successfully initialized.
  //TimerOne is breaking my code and I don't know why so I'm rewriting it to not use it
  //int intervalSeconds = 1;
  //int intervalus = intervalSeconds*1000000;
  /*Timer1.initialize(intervalus); // initialize timer1, and set a 5000 ms second period for the interrupt interval (i.e. the ISR will be called
  //every 500000 us to read out the potentiometer that simulates a sensor in this tutorial.
  Timer1.attachInterrupt(readoutRHT);  // attaches the readoutPotentiometer() function as 'Interrupt Service Routine' (ISR) to the timer1 interrupt
  //this means that every time 500000 us have passed, the readoutPotentiometer() routine will be called.
  */
 
}
 
void loop () {
  DateTime now = RTC.now();

  //check for button press
  int buttonRead = digitalRead(buttonPin);
  
  if (buttonRead && (unsigned long)(millis() - lastDebounceTime) > debounceDelay) { // if button is pressed AND it's been at least 200 ms since the last press
    //flip power status
    if (powerStatus == 1) {
      powerStatus = 0; 
      Serial.println("Powering down.");
      Serial.println(buttonRead);
      lcd.noBacklight();//this turns the backlight off
      lcd.clear();
    }
    else {
      powerStatus = 1;
      Serial.println("Powering up.");
      Serial.println(buttonRead);
      lcd.backlight(); // turn backlight on    
    }
    lastDebounceTime = millis(); // set new button-last-pressed time
  }

  //only write to file every 30 sec
  if ((unsigned long)(millis() - lastFileWrite) >= 30000) {
    float temperature = myHumidity.readTemperature()*1.8+32; //convert to F
    float rh = myHumidity.readHumidity();
    //write to SD time and value
    String dataString = getDigitalTime(now) + String(",") + String(temperature) + String(",") + String(rh); //concatenate (add together) a string consisting of the time and the sensor reading at that time
       
    File dataFile = SD.open("rhtlog.txt", FILE_WRITE);//open a file named datalog.txt. FILE_WRITE mode specifies to append the string at the end of the file
                         //file names must adhere to the "8.3 format"(max 8 char in the name, and a 3 char extension)
                         //if there is no file of that name on the SD card, this .open method will create a new file.
                         //This line actually instantiates an File object named "datafile"      
   
    if (dataFile) {       // if the file is available, write to it ('datafile' is returned 1 if SD.open was successful.
      dataFile.println(dataString);//print the concatenated data string and finish the line with a carriage return (println adds the CR automatically after printing the string)
      dataFile.close();   //close the file. IT is a good idea to always open/close a file before and after writing to it. That way, if someone removes the card the file is most
                        //likely o.k. and can be read with the computer.
      lastFileWrite = millis();
      Serial.println(dataString);// print the string also to the serial port, so we can see what is going on.
    }  
    else { // if SD.open is not successful it returns a 0, i.e. the else{} is executed if the file could not be opened/created successfully.
      Serial.println("error opening timelog.txt");//in that case print an error message
      lcd.setCursor(0,1);
      lcd.print("File Error"); 
      lastFileWrite = millis(); // still set this marker bc I don't want it to constantly try to write to file if there's an error
    }
    
    //sensorFlag = 0;      //reset the sensor reading flag. This prevents the loop from running until a new sensor reading comes from the ISR.    
  }

  //update the display every 5 seconds
  if ((unsigned long)(millis() - lastDisplayWrite) >= 3000 && powerStatus) {
    float dispT = myHumidity.readTemperature()*1.8+32; //convert to F
    float dispRH = myHumidity.readHumidity();
    char deg = (char)223;
    String printString = String(dispT) + String(deg) + String("F ") + String(dispRH)  + String("%  ");
    
    //Serial.println(getDigitalTime(now));
    lcd.setCursor(0,0);
    String printTime = getLCDDateTime(now) + "  ";
    lcd.print(printTime);
    lcd.setCursor(0,1);
    lcd.print(printString); 
    lastDisplayWrite = millis();
  }
    
}

/*void readoutRHT()//this is the ISR routine that is executed everytime the timer1 interrupt is called.
{
  temperature = myHumidity.readTemperature()*1.8+32; //convert to F
  rh = myHumidity.readHumidity();
  
  sensorTime = millis();  //note the time
  sensorFlag = 1;         //set the flag that tells the loop() that there is a new sensor value to be printed.
}*/

String getDigitalDate (DateTime now) {
    String result = String(now.year()) + '/' + now.month() + '/' + now.day();    
    return result;
}

String getLCDDateTime (DateTime now) {
  String hourstring = "";
  String minstring = "";
  String secstring = "";  
  
  String yearstring = String(now.year()-2000);
  
  //add zeros to front of 1 character time components  
  if (now.hour() < 10) {
    hourstring = String(0) + String(now.hour());
  }
  else {
    hourstring = String(now.hour());
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
  String result = String(now.month()) + '/' + String(now.day()) + '/' + String(yearstring) + ' ' + hourstring + ':' + minstring + ':' + secstring;  
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
String getDigitalTime (DateTime now) {
  String hourstring = "";
  String minstring = "";
  String secstring = "";  
  
  //add zeros to front of 1 character time components  
  if (now.hour() < 10) {
    hourstring = String(0) + String(now.hour());
  }
  else {
    hourstring = String(now.hour());
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
  String result = String(now.year()) + '/' + String(now.month()) + '/' + String(now.day()) + ' ' + hourstring + ':' + minstring + ':' + secstring;  
  return result;
}
