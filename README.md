# rhtlogger
A temperature/relative humidity Arduino data logger. A sensor detects the current temperature and relative humidity. An LCD display updates every 3 seconds, and the values are logged to file every 30 seconds.

## Status

I soldered everything on to the proto shield, but I couldn't get the system to work reliably after that. I decided to completely redo everything using a Pro Mini because the stacking shields were annoying me. All of the new parts are still compatible with the same code.

## Parts Used

- Pro Mini Clone (5V) http://www.ebay.com/itm/231348215568 -- I especially like this new model because the A4/A5 I2C pins are in a much more convenient location
- Micro SD Card SPI module http://www.ebay.com/itm/Micro-SD-and-Memory-Card-Breakout-Shield-Module-via-SPI-For-Arduino-Regulated-/131426645939 - one that says Catalex on the back and has a voltage regulator
- DS3231 RTC http://www.ebay.com/itm/191782504379
- Clone of Sparkfun RHT Board HTU21D http://www.ebay.com/itm/310951642577?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT (original: https://www.sparkfun.com/products/12064)
- 5V to 3.3V stepdown module http://www.ebay.com/itm/111896908030 (for the sensor, which is 3.3V)
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F
- Momentary button https://www.sparkfun.com/products/11993
- 10k Ω resistor

Removed:
- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8 (I see this is no longer available - http://smile.amazon.com/dp/B00M1M8N90/ is probably a comparable replacement)
- tiny breadboard and/or protoshield with tiny breadboard http://www.ebay.com/itm/221739124245
- DHT22 sensor https://www.sparkfun.com/products/10167

## Libraries Used

- New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
- RTClib https://github.com/adafruit/RTClib
- HTU21D https://github.com/sparkfun/HTU21D_Breakout/tree/V_H1.2_L1.1.0/Libraries/Arduino

## Sample Data

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/sampledata/2015-12-29.PNG)

## Photo

New breadboard prototype with the Pro Mini.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/feb12_all.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/feb12_front.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/feb12_back.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/feb12_top.jpg)

Proto-shield setup, which failed. 

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/protofail.jpg)

Original prototype with both DHT22 and HTU21D.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec17.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_front.jpg)
![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec16_top.jpg)

