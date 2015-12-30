# rhtlogger
Just a simple little temperature/relative humidity Arduino data logger. A sensor detects the current temperature and relative humidity. An LCD display updates every 5 seconds, and the values are logged to file once per minute.

## Status

I've decided to go with the HTU21D sensor as it has a MUCH faster response time. The DHT22 is annoyingly slow and can take half an hour to equilibrate to a new room. For some reason, using TimerOne for interrupts was causing my code to break before even getting out of the setup function. I rewrote it to update the display and the file just using millis time markers. The new code seems to work well.

## Parts Used

- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8
- Clone of Sparkfun RHT Board HTU21D http://www.ebay.com/itm/310951642577?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT (original: https://www.sparkfun.com/products/12064)
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F

## Libraries Used

- New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
- RTClib https://github.com/adafruit/RTClib
- HTU21D https://github.com/sparkfun/HTU21D_Breakout/tree/V_H1.2_L1.1.0/Libraries/Arduino

## Sample Data

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/sampledata/2015-12-29.PNG)

## Photo

Currently I am using both a DHT22 and an HTU21D.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec17.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_front.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_top.jpg)

