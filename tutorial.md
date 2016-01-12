# Tutorial
Here's how to put together your own version of my project. 

## Parts Used

- SainSmart Arduino Uno http://smile.amazon.com/dp/B00E5WJSHK
- Arrela Data Logger Shield http://smile.amazon.com/dp/B00KHYHKT8 (I see this is no longer available - http://smile.amazon.com/dp/B00M1M8N90/ is probably a comparable replacement)
- Clone of Sparkfun RHT Board HTU21D http://www.ebay.com/itm/310951642577?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT (original: https://www.sparkfun.com/products/12064)
- Frentaly i2c LCD http://www.ebay.com/itm/IIC-I2C-TWI-1602-Serial-Blue-Backlight-LCD-Display-For-Arduino-/221935534466?roken=cUgayN&soutkn=mKrU7F
- Momentary button https://www.sparkfun.com/products/11993
- 10k Ω resistor
- tiny breadboard and/or protoshield with tiny breadboard http://www.ebay.com/itm/221739124245

## Assembly

Follow the circuit diagram. It's a mess, so I will explain here as well.

FIRST OF ALL, make sure everything is disconnected from power whenever you're wiring stuff!

Place the data logging shield on top of the Arduino. Optionally, put the protoshield and tiny breadboard on top of that, or just put your tiny breadboard on top of the data logging shield. I recommend putting everything together on the breadboard first and then soldering it to the protoshield once you're sure everything works.

Connect the A4 and A5 pins to the breadboard. I've used green for A5/SCL and yellow for A4/SDA. Connect the SDA and SCL lines to both the LCD and the HTU21D. You'll note that the fritzing diagram uses the part SHT15, because that's the closest I could find. I re-labelled the pins to be in the same order as the HTU21D.

Next, power. Connect 3.3V directly to VCC for the HTU21D. Everything else uses 5V. Connect 5V to the breadboard. Connect 5V to the LCD and one end of the button.

Ground: connect ground to the LCD and the HTU21D.

Button: the other end of the button is connected to a rail on the breadboard. Wire one spot on the rail to pin 8, and in another put the 10k pullup resistor. Connect the other end of the resistor to the ground rail.

![alt tag](https://github.com/lizcorson/rhtlogger/blob/master/circuitdiagram/rhtlogger_HTU21D.png)

## Code

Download all the code in this repository. You'll want to use **rhtlogger2** as the main sketch. All the libraries required are in the library folder.

First, run the **i2cscanner** sketch to determine the address of your LCD. It will be either 0x27 or 0x3F.

Next, run the **rtclcdtest** sketch. Be sure to set the right i2c address for your LCD. This will set the clock on the RTC, and the time will display on the LCD. Mine tends to gain a few minutes per week, and you can also run this sketch to re-sync the time. If you're having problems with the LCD, this site has some variations on the LCD code: http://arduino-info.wikispaces.com/LCD-Blue-I2C#v1

Now your clock is set and your LCD is working, so you can proceed to upload the main sketch, **rhtlogger2**. Again, be sure to update the i2c address for the LCD.

Let it run for a few minutes, then pull the SD card to ensure it's writing to file. If it is, you're all set! If not, maybe your board uses a different chip select pin. Try the SD card library example sketches to try to get your SD card working.