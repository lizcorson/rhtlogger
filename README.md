# rhtlogger
Just a simple little temperature/relative humidity Arduino data logger. A sensor detects the current temperature and relative humidity. An LCD display updates every 3 seconds, and the values are logged to file every 30 seconds.

## Status

The next step is to solder everything onto a protoboard and to make a case. I've also added a tutorial if you want to replicate my project: https://github.com/lizcorson/rhtlogger/blob/master/tutorial.md

## Parts Used

- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8 (I see this is no longer available - http://smile.amazon.com/dp/B00M1M8N90/ is probably a comparable replacement)
- Clone of Sparkfun RHT Board HTU21D http://www.ebay.com/itm/310951642577?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT (original: https://www.sparkfun.com/products/12064)
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F
- Momentary button https://www.sparkfun.com/products/11993
- 10k Ω resistor
- tiny breadboard and/or protoshield with tiny breadboard http://www.ebay.com/itm/221739124245

## Libraries Used

- New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
- RTClib https://github.com/adafruit/RTClib
- HTU21D https://github.com/sparkfun/HTU21D_Breakout/tree/V_H1.2_L1.1.0/Libraries/Arduino

## Sample Data

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/sampledata/2015-12-29.PNG)

## Photo

These photos show both a DHT22 and an HTU21D, but I am only using the HTU21D now.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec17.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_front.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_top.jpg)

