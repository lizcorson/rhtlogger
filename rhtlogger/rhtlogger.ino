#include <RTClib.h>
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"


 

#include <SPI.h>
#include <SD.h>      //this includes the SD card libary that comes with the Arduino
#include <TimerOne.h>//this is a library that uses the (16 bit) timer 1 of the arduino to trigger interrupts in certain time intervals.
                     //here we use it to read sensor values precisely every 500ms. 

#include <LiquidCrystal_I2C.h>//this is the special I2C LCD display library that came with the display

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define chipSelect 10//we are using pin#10 as chip select pin for the SD card

volatile float temperature;//this is the variable used in the Interrupt Service Routine (ISR) for 'reporting' the potentiometer value to the main loop.
volatile float rh;
volatile unsigned long sensorTime;//this is the variable use in the ISR to record the time when the sensor was readout.
volatile byte sensorFlag;//this flag is used to communicate to the main loop that a new value was read.

RTC_DS1307 RTC;
// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Wire.begin();
  RTC.begin();  
  dht.begin();

  //set up SD card
  Serial.print("Initializing SD card..."); 
  if (!SD.begin(chipSelect)) { // see if the card is present and can be initialized:
    Serial.println("Card failed, or not present");
    return;//exit the setup function. This quits the setup() and the program counter jumps to the loop().
  }
  Serial.println("card initialized.");//otherwise, tell us that the card was successfully initialized.
  // 500000 = 500 ms
  Timer1.initialize(5000000); // initialize timer1, and set a 5000 ms second period for the interrupt interval (i.e. the ISR will be called
  //every 500000 us to read out the potentiometer that simulates a sensor in this tutorial.
  Timer1.attachInterrupt(readoutRHT);  // attaches the readoutPotentiometer() function as 'Interrupt Service Routine' (ISR) to the timer1 interrupt
  //this means that every time 500000 us have passed, the readoutPotentiometer() routine will be called.
  
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
}

void loop() {
  DateTime now = RTC.now();
  String dataString = "";//instantiate (make) an object of the string class for assembling a text line of the datalog

  if (sensorFlag ==1)    //if there is a sensor reading...
  {
    //temperature = round(temperature*10)/10;
    //rh = round(rh*10)/10;
    char deg = (char)223;
    lcd.setCursor(0,0);
    String printString = String(temperature) + String(deg) + String("F ") + String(rh)  + String("%");
    lcd.print(printString);
    Serial.println(printString);
    lcd.setCursor(0,1);
    lcd.print(getDigitalTime(now));
    dataString = getDigitalTime(now) + String(",") + String(temperature) + String(",") + String(rh); //concatenate (add together) a string consisting of the time and the sensor reading at that time
                         //the time and the reading are separated by a 'comma', which acts as the delimiter enabling to read the datalog.txt file as two columns into
                         //a spread sheet program like excel.            
    
    File dataFile = SD.open("datalog.txt", FILE_WRITE);//open a file named datalog.txt. FILE_WRITE mode specifies to append the string at the end of the file
                         //file names must adhere to the "8.3 format"(max 8 char in the name, and a 3 char extension)
                         //if there is no file of that name on the SD card, this .open method will create a new file.
                         //This line actually instantiates an File object named "datafile"
    sensorFlag = 0;      //reset the sensor reading flag. This prevents the loop from running until a new sensor reading comes from the ISR.    
   
    if (dataFile) {       // if the file is available, write to it ('datafile' is returned 1 if SD.open was successful.
      dataFile.println(dataString);//print the concatenated data string and finish the line with a carriage return (println adds the CR automatically after printing the string)
      dataFile.close();   //close the file. IT is a good idea to always open/close a file before and after writing to it. That way, if someone removes the card the file is most
                          //likely o.k. and can be read with the computer.
      
      Serial.println(dataString);// print the string also to the serial port, so we can see what is going on.
    }  
  // if SD.open is not successful it returns a 0, i.e. the else{} is executed if the file could not be opened/created successfully.
    else {
      Serial.println("error opening datalog.txt");//in that case print an error message
    } 
  }

}

void readoutRHT()//this is the ISR routine that is executed everytime the timer1 interrupt is called.
{
  //sensorValue = analogRead(potentiometerSwiperPin);//read out the potentiometer swiper
  //sensorValue = random(100); // for now this is just a placeholder until I get the actual sensor
  temperature = dht.readTemperature(true);
  rh = dht.readHumidity();
  
  sensorTime = millis();  //note the time
  sensorFlag = 1;         //set the flag that tells the loop() that there is a new sensor value to be printed.
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
