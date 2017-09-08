# watch

In late 2014 I wanted to make a watch. Smartwatches were starting to pick up and get some press, but none of the ones on the market fit my needs. Really I just wanted a simple one with a bright, clear display. I suppose it's more of a plain old digital watch, actually, as it won't connect to my phone. [[1]](https://github.com/seth10/watch#footnote-1)

I didn't make much progress besides getting the components then, it being my senior year of high school and all. But now (mid 2017), I'm getting back into it and really enjoying this project. It's great coming back to it with a greater understanding of nearly every aspect of this project.

The primary hardware components I have are two [Adafruit Trinket](https://www.adafruit.com/product/1501)s, two [Pro Trinket](https://www.adafruit.com/product/2000)s ([Hackaday limited edition](store.hackaday.com/products/trinket-pro-with-black-solder-mask-and-the-hackaday-io-logo) :D), one 14-segment [quad-alphanumeric display](https://www.adafruit.com/product/1912), and two OLED displays (one [SPI](https://www.banggood.com/0_96-Inch-White-IIC-I2C-OLED-Display-Module-12864-LED-For-Arduino-p-932606.html), one [I2C](https://www.banggood.com/0_96-Inch-I2C-IIC-SPI-Serial-128-x-64-OLED-LCD-LED-Display-Module-p-922246.html)).


## OLED Watch (oled.ino)

[![An SSD1306 display connected to an Arduino Micro with a button on a mini breadboard. The display shows the time.](https://user-images.githubusercontent.com/5026621/30225234-b481d25c-949f-11e7-8eb5-cba1e0080de6.gif)](https://user-images.githubusercontent.com/5026621/30225277-ecf068f6-949f-11e7-8711-a96d4bbf0ddd.gif)
This is the primary sketch. While the 14-segment display is nice, it is rather thick. The OLED display is fantastically thin and great for this type of wearable project. It also uses considerably less power.
The current sketch supports showing the time (obviously), nicely formatted hours (i.e. 12 instead of 0 for midnight/noon), a blinking colon separator (once a second), and an AM/PM display. You can also use a single button with different timed press sequences to set the time. You can find a video of me setting the time [here](https://www.youtube.com/watch?v=HO-wcZnRYFU).
The timer and interrupt code would need to be adapted for the Trinket, but the Pro Trinket's chip (ATmega328) is more similar to that of the Arduino Micro (ATmega32U4), perfect! Note that the capacitor seen in the above media is not necessary as there is software debouncing.


## Raw OLED Control (oled_raw.ino)

[![An SSD1306 display showing a pattern akin to the Sierpinski Triangle with a white rectangle filled in the middle](https://user-images.githubusercontent.com/5026621/30033770-4db9cc00-916b-11e7-905f-29efedaccacb.jpg)](https://gist.github.com/seth10/ca02c15ec7c7a890c90d330c6ff3a877)
The Trinket is unable to use the Adafruit_SSD1306 library (and thereby the Adafruit-GFX-Library) as-is. The OLED display is 128 pixels wide by 64 pixels tall. The Trinket would need 1024 bytes to buffer the display (8192 pixels / 8 bits per byte = 1024 bytes), but the Trinket has only 512 bytes of SRAM. Instead of buffering and writing the entire display, we can write raw data and commands. That is what this example does.
Currently it sends 32 commands as the initialization sequence (various configurations, see [`Adafruit_SSD1306::begin`](https://github.com/seth10/watch/blob/master/libraries/Adafruit_SSD1306/Adafruit_SSD1306.cpp#L68) for more detail). Then, it fills the screen with a pattern akin to Sierpinski's Triangle. Finally, it demonstrates specifying an area and drawing only to it.


## Trinket Recovery (trinketloader.ino)

![A Trinket with an Arduino MEGA connected to reprogram the prior's bootloader](https://user-images.githubusercontent.com/5026621/30007224-bea07ff2-90d7-11e7-9f0a-85935a7f6e46.jpg)
When I wanted to try idea 2 of [#4](https://github.com/seth10/watch/issues/4), the Trinket wouldn't enter the bootloader, it would just stay at a solid red light. I ended up finding my old Arduino Mega and using it to [repair the bootloader](https://learn.adafruit.com/introducing-trinket/repairing-bootloader). The [`trinketloader` sketch](https://github.com/seth10/watch/tree/master/trinketloader) is from Adafruit. I modified one line to force it to recognize my Trinket. I was able to recover it after removing the jumper from the Arduino's 5V to the Trinket's VBAT+ and powering the Trinket via microUSB. However, after soldering on breadboard headers and playing with it a bit, it's stuck once again and I can't recover it.


## A Simple OLED Test (oled_test_simple.ino)

![An SSD1306 OLED display running a section of the Adafruit example program](https://user-images.githubusercontent.com/5026621/30039453-0db7c0a6-919f-11e7-9e2b-c3571a3c316c.gif)<br>
This is a highly minimized version of the ssd1306_128x64_i2c example included with the Adafruit_SSD1306 library. It's basically just the "text display tests" section.


## 14-Segment Display Brightness Test (14seg_brightness.ino)

[![A 14-segment display showing off its 16-step dimming circuit](https://user-images.githubusercontent.com/5026621/30039880-153ce918-91a5-11e7-87af-88e76f2bf572.gif)](https://www.youtube.com/watch?v=We3GuKf2hUQ)<br>
By [default](https://github.com/seth10/watch/blob/master/libraries/Adafruit_LED_Backpack/Adafruit_LEDBackpack.cpp#L213), the quad-alphanumeric display is at brightness 15. When I ran my [brightness test](https://github.com/seth10/watch/issues/4#issue-254842419), it lasted 6 hours. Lowering the brightness to 0 made it last 9 hours on a 105mAh battery. Note brightness 15 is, in fact, _very_ bright.


# 14-Segment Test of Each Segment (14seg_segments.ino)

![A 14-segment display showing each of the 14 individual segments and digit separators](https://user-images.githubusercontent.com/5026621/30087281-c80245ca-926d-11e7-8784-35df6026a98d.gif)<br>
Simple enough, this sketch shows each of the 14 segments (and digit separators) and their indices. Given the `Adafruit_AlphaNum4::writeDigitAscii` method this knowledge shouldn't be necessary. Note you can turn on the digits separator by appending a boolean argument of `true`, i.e.
```
alpha4.writeDigitAscii(1, '3', true);
alpha4.writeDigitAscii(2, '1');
alpha4.writeDigitAscii(3, '4');
```


## Standby Test (14seg_standby.ino)

[<img alt="An HT16K33 LED controller entering standby mode and being woken by a pushbutton trigger a pin change (falling-edge) interrupt" src="https://user-images.githubusercontent.com/5026621/30085897-a3fd9d8e-9266-11e7-8833-a1698b0e676d.gif" width="100%">](https://www.youtube.com/watch?v=lc1ocVeB3as)<br>
The 14-segment display uses a lot of power. Much more so than the OLED display. To help mitigate this, we can make the HT16K33 LED controller enter standby mode. I still need to run a battery test but this should save a _ton_ of power.

On the Arduino Micro I couldn't wake the LED controller directly from the interrupt service routine. This is because the I2C transaction takes some time. When I did this in the ISR the Arduino locked up (I couldn't upload code to it without manually pressing the reset button). Instead I set the `wakeup` flag to `true`, which should be almost instant, and handle that in the `loop()` method. This _does_ work.

I figured out how to do this from [the datasheet](https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf#page=13). The System Setup Register has a single significant bit which "Defines internal system oscillator [state]" where "{0}:Turn off System oscillator (standby mode)" and "{1}:Turn on System oscillator (normal operation mode)." I was able to verify this in the Adafruit LED Backpack library, where [it writes `0x21` to turn on the oscillator](https://github.com/seth10/watch/blob/master/libraries/Adafruit_LED_Backpack/Adafruit_LEDBackpack.cpp#L209). What's interesting here is that both the command and data are in this one byte. The first (most-significant) nibble is 2h (hex), which matches 0010b (binary) as specified in the datasheet. The low nibble is 1h for turning the oscillator on, but sending the data 0h would turn it off.


## Trinket Timer Test (trinket_timer.ino)

![An Adafruit Trinket microcontroller blinking its built-in LED at two hertz](https://user-images.githubusercontent.com/5026621/30088755-4910717a-9276-11e7-9a77-8c60baadc64a.gif)
This sketch turns the built-in LED on for half a second, then off for half a second. It uses the hardware timer. Although it's not even a dozen significant lines of code, it's a minimal complete example.


#### Footnote 1
Maybe I could use a [Feather](https://www.adafruit.com/feather) [with an ESP8266](https://www.adafruit.com/product/3404) to make a real "smart" watch. I was actually thinking of getting a [basic Feather](https://www.adafruit.com/product/2771) now and snapping off the proto space. This would take up less space than the Pro Trinket and [LiIon/LiPoly Backpack](https://www.adafruit.com/product/2124), as the Feather [has built-in charging](https://forums.adafruit.com/viewtopic.php?f=52&t=122640#p612296). However, this would be another $20 and I want to make something using what I have, even if it might end up slightly larger.

#### Footnote 2
Pinouts: [Trinket](https://learn.adafruit.com/introducing-trinket/pinouts#usb-pins) (note pins 4/5 are used for USB programming), [Pro Trinket](https://learn.adafruit.com/introducing-pro-trinket/pinouts), [LiPoly/LiIon Backpack](https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack/pinouts).
![](https://cdn-learn.adafruit.com/assets/assets/000/025/645/original/trinket5.png?1432753823)
![](https://cdn-learn.adafruit.com/assets/assets/000/025/646/original/adafruit_products_pro5.png?1432753967)
