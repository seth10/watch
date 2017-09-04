# watch

In late 2014 I wanted to make a watch. Smartwatches were starting to pick up and get some press, but none of the ones on the market fit my needs. Really I just wanted a simple one with a bright, clear display. I suppose it's more of a plain old digital watch, actually, as it won't connect to my phone. [[1]](https://github.com/seth10/watch#footnote-1)

I didn't make much progress besides getting the components then, it being my senior year of high school and all. But now (mid 2017), I'm getting back into it and really enjoying this project. It's great coming back to it with a greater understanding of nearly every aspect of this project.

The primary hardware components I have are two [Adafruit Trinket](https://www.adafruit.com/product/1501)s, two [Pro Trinket](https://www.adafruit.com/product/2000)s ([Hackaday limited edition](store.hackaday.com/products/trinket-pro-with-black-solder-mask-and-the-hackaday-io-logo) :D), one 14-segment [quad-alphanumeric display](https://www.adafruit.com/product/1912), and two OLED displays (one [SPI](https://www.banggood.com/0_96-Inch-White-IIC-I2C-OLED-Display-Module-12864-LED-For-Arduino-p-932606.html), one [I2C](https://www.banggood.com/0_96-Inch-I2C-IIC-SPI-Serial-128-x-64-OLED-LCD-LED-Display-Module-p-922246.html)).


## OLED Watch (oled.ino)

[![watch](https://user-images.githubusercontent.com/5026621/30008988-a28e0300-90f2-11e7-8583-e07cc6abd03b.gif)](https://user-images.githubusercontent.com/5026621/30008983-95251370-90f2-11e7-91b8-bbeabd0d093f.gif)<br>
You can find a video of my setting the time [here](https://www.youtube.com/watch?v=HO-wcZnRYFU).

## Trinket Recovery (trinketloader.ino)
![A Trinket with an Arduino MEGA connected to reprogram the prior's bootloader](https://user-images.githubusercontent.com/5026621/30007224-bea07ff2-90d7-11e7-9f0a-85935a7f6e46.jpg)
When I wanted to try idea 2 of [#4](https://github.com/seth10/watch/issues/4), the Trinket wouldn't enter the bootloader, it would just stay at a solid red light. I ended up finding my old Arduino Mega and using it to [repair the bootloader](https://learn.adafruit.com/introducing-trinket/repairing-bootloader). The [`trinketloader` sketch](https://github.com/seth10/watch/tree/master/trinketloader) is from Adafruit. I modified one line to force it to recognize my Trinket. I was able to recover it after removing the jumper from the Arduino's 5V to the Trinket's VBAT+ and powering the Trinket via microUSB. However, after soldering on breadboard headers and playing with it a bit, it's stuck once again and I can't recover it.

#### Footnote 1
Maybe I could use a [Feather](https://www.adafruit.com/feather) [with an ESP8266](https://www.adafruit.com/product/3404) to make a real "smart" watch. I was actually thinking of getting a [basic Feather](https://www.adafruit.com/product/2771) now and snapping off the proto space. This would take up less space than the Pro Trinket and [LiIon/LiPoly Backpack](https://www.adafruit.com/product/2124), as the Feather [has built-in charging](https://forums.adafruit.com/viewtopic.php?f=52&t=122640#p612296). However, this would be another $20 and I want to make something using what I have, even if it might end up slightly larger.
