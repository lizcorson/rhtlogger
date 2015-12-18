# rhtlogger
Just a simple little temperature/relative humidity Arduino data logger. A sensor detects the current temperature and relative humidity. An LCD display updates every 5 seconds, and the values are logged to file once per minute.

## Status

As of Dec 17, I think I'm pretty pleased with the code and all the parts. I'll be comparing the DHT22 and the HTU21D and selecting one. Once I select the better sensor, I plan to build a housing for the project. I am planning to learn how to use a laser cutter.

## Parts Used

- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8
- Sparkfun RHT03 (aka DHT22) https://www.sparkfun.com/products/10167
- Clone of Sparkfun RHT Board HTU21D http://www.ebay.com/itm/310951642577?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT (original: https://www.sparkfun.com/products/12064)
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F

## Libraries Used

- New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
- RTClib https://github.com/adafruit/RTClib
- DHT https://github.com/adafruit/DHT-sensor-library
- HTU21D https://github.com/sparkfun/HTU21D_Breakout/tree/V_H1.2_L1.1.0/Libraries/Arduino

## Photo

Currently I am using both a DHT22 and an HTU21D.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec17.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_front.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_top.jpg)