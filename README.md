# VoiceModulator

## Description
This project is a night night with a flex sensor to adjust the sensitivity of the light while it is on. It is bulit with an Arduino microcontroller, a photoresistor, a LED, and a flexible sensor. The fully formed design is where the flex sensor would be wrapped aorund a knob that increase or decrease the resistance to the LED. It gives people a chance to decide how much light they or their child wants at night without being blinded. The sensitivity of the "knob" depends on the capabilities of the flex sensor.

## The Problem
Having been involved with very young children, siblings and cousins, putting them to sleep can be tricky. Especially with night anxiety, it can be hard for children to feel safe at night. However, while it is nice to always cater to children. Night lights can be jarring when walking around in the house at night, disrupting your sleepiness when you quickly want to enjoy a midnight snack in the dark in peace. Studies show that night lights can also be helpful for baby brain development.

## Why?
Night lights can be annoying and can be blinding in small spaces. Adults should not have to sacrifice their ability to sleep at night for their child's ability to sleep. Night lights are only affective when the child is awake. After the child falls asleep, the light burns wasted energy.

## Discoveries
During the development of this project, I noticed that the photoresistor naturally increases its resistance in the dark which turned the LED off which was the opposite of what I wanted. To reverse the effect, I switched the position of the photoresistor on a voltage divider.

![image](https://user-images.githubusercontent.com/89606106/230819907-536d9c49-3027-49b1-a75f-3c756ead0d1e.png)

The above schematic shows a voltage divider. Ignore the resistor, R5. At first, my photoresistor was placed at the position of R1, where one pin is connected to the power source which activates the normal "Light Mode." Switching the photoresistor to the position of R2 activates dark mode because lowering the resistance to ground instead will lower the resistance to the LED. Both sensor use voltage divider circuits with pull-down resistors.

Explore this concept more at this link: https://electronics.stackexchange.com/questions/101085/reversing-a-photoresistor

## Challenges
I encountered issues with the consistency in the LED brightness due to the resistor I used for the flex sensor. I used a 1M ohm resistor (due to availability) instead of the 47k ohm resistor that is suggested for use. So, when the photoresistor senses low light and the LED goes bright, the LED either stays bright or becomes very dim. The adjustment process is very abrupt. Also, there is a delay between sensing dark mode and light mode. Patience is key. Another obstacle was trying to break down the Arduino analogRead function to low level C language that can be read by avrdude.

## Future Features
I hope to add an outer casing and more LEDs to make the night light more enticing to a younger audience.

## Installation Instructions w/AVR Toolchain
Please follow the instructions on the following link to download and install the AVRDUDE to your OS, perferably a Windows system for ease of use.

Link: https://tinusaur.com/guides/avr-gcc-toolchain/

Please use your command prompt to type these three commands to check if you have installed the software correctly:

avr-gcc -v
avrdude -v
avr-objcopy -V

### Compilation Process
* Change the directory on your command prompt to where you have downloaded the source code file.
* Check the COM port on which your Arduino is programmed.
* Type: c:\avr-gcc-11.1.0\bin\avr-gcc.exe -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o nightlight.o nighlight.c
* Type: c:\avr-gcc-11.1.0\bin\avr-gcc.exe -mmcu=atmega328p nightlight.o -o nightlight
* Type: c:\avr-gcc-11.1.0\bin\avr-objcopy.exe -O ihex -R .eeprom nightlight nightlight.hex
* Type: c:\avr-gcc-11.1.0\bin\avrdude.exe -patmega328p -Pcom(port#) -carduino -D -U flash:w:nightlight.hex:i

These instructions may differ by version or if you have decided to use a different microcontroller than an Arduino UNO Rev 3.

## Using the Night Light
After installation and applying power to the Arduino, the LED should automatically be on, but dim. You can activate dark mode by covering the photoresistor with any opaque object which will brighten the LED. In dark mode, you can begin to wrap the flex sensor to adjust the brightness.

## Source Material / Credits
Here is a site that introduces the flex sensor and some beginning code to get you started.
Link: https://lastminuteengineers.com/flex-sensor-arduino-tutorial/#:~:text=Connecting%20a%20flex%20sensor%20to,resistor%20and%20the%20flex%20sensor.

Here is a site that introduces the photoresistor and explains its basic functionality and wiring.
Link: https://www.digikey.com/en/maker/blogs/2022/how-to-use-a-phototransistor-with-an-arduino

# Demo
Link: https://youtu.be/2uOLE6uXoPU

## Items Needed
* Arduino UNO Rev3 Microcontroller
* Arduino USB cable
* 1 Photoresistor
* 1 Flex Sensor
* 2 10k ohm Resistors
* 1 LED
* 1 100k ohm Resistor
* 6 wires

## Quick Pic
![20230410_051254](https://user-images.githubusercontent.com/89606106/230872110-2a5a1332-44a5-4360-b48f-2ee5660aeb13.jpg)
