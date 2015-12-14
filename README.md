# rhtlogger
Just a simple little temperature/relative humidity Arduino data logger.

## Parts Used

- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8
- Sparkfun RHT03 (aka DHT22) https://www.sparkfun.com/products/10167
- Clone of Sparkfun RHT Board HTU21D https://www.sparkfun.com/products/12064
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F

## Libraries Used

- New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
- RTClib https://github.com/adafruit/RTClib

## Photo

This is what the project currently looks like. I'm still waiting on my temperature sensor to arrive so right now the LCD just shows a randomly generated value updating every 5 seconds. (I've ordered two sensors - a knockoff of a more accurate Sparkfun board for cheap on ebay as well as a DHT22 from Sparkfun.)

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/photos/dec12.jpg)