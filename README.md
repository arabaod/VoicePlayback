**WARNING! THIS PROJECT INVOLVES SOLDERING. PLEASE USE SAFETY GEAR WHEN HANDLING EXTREME TEMPERATURES AND ELECTRICAL TOOLS.**

## Description
This project is a device that can play audio from memory. It is built with an Arduino microcontroller, a MAX4466 microphone chip with adjustable gain, a microSD card reader chip, a microSD formatted with FAT32, a female audio jack with USB connecter, 1 1k ohm resistor, 2 10k ohm resistors, 1 10 uF capacitor, 2 push buttons, and connecting wires. The songs will come from the microSD storage. This is a simple project that serves as a prototype for wiring that can be stuffed inside a teddy bear to entertain young children. There is a coding base for this project that can playback a recorded audio using the microphone. It's still in Beta though.

## The Problem
Children's toys are just becoming too expensive these days and yet, their need for development and sonic entertainment has yet to decrease. If the bank account is hurting is time to get creative, provided that the child is old enough to understand electricity and has the mobility skills to push buttons. The playback toy provides an extremely cheap way to play audio to soothe or excite your child.

## Discoveries
### The RC Filter
The TMRpcm library outputs the audio as a PWM signal from an Arduino. The RC filter gives an analog signal which then be played by your computer or through an amplifier or speaker. IT is possible to use an external DAC (Digital to Analog Converter) which is probably a better option for audio quality, but more expensive. The RC filter, the resistor and capacitor in series, acts as a lowpass filter and can still produce some noise. Again, a DAC would have been better. Below is a schematic for an RC filter and it ability to act as a low pass filter - a filter that lets lower frequencies go through and stop higher ones.

![images](https://github.com/arabaod/VoicePlayback/assets/89606106/b9392c55-691f-46f4-ab7c-3dd85e32009d)

### The EZ Button Library
Debouncing the buttons within the different methods and loops in the code became difficult. But having found the EZ Button Library, I could use simple methods to debounce, add more buttons to debounce easily, and even run code when the button is pressed AND released all in one library. The library is found here: https://github.com/ArduinoGetStarted/button 

One issue though is converting the class in the library to C code that can be compiled by the AVR-GCC Toolchain. In your prototyping, you have to debounce both buttons the traditional way with many more lines of code!

## Challenges
Learning how to solder was definitely a journey as I was a bit wary of touching something so hot. It was also my first time, but I think that it turned out well.
With the amount of libraries that were added in the Arduino IDE, it was very difficult to break down objects into simple methods of C libraries.

## Future Features
With all the wiring and soldering, it can be easy to forget that this project is meant for young hands. I will replace the button with keys or colorful button covers because of the attractive colors and greater surface area. It will be harder for a young hand to make a mistake. The next stage of this development will include using a switch to switch between playback mode and record mode. However, this version would require more buttons for input.

The next feature would be to mimic apps of the early 2010's and be able to apply different audio filters. To further explain, someone would record an audio and the device would be able to play it back at a lower pitch, lower speed, higher pitch, higher speed, etc.

## Installation Instructions w/AVR Toolchain
Please follow the instructions on the following link to download and install the AVRDUDE to your OS, preferably a Windows system for ease of use.

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

## REMEMBER!
Uncomment #define buffSize 128 AND #define ENABLE_RECORDING in pcmConfig.h

## Source Material / Credits
The basis for the code that deals with audio and the TMRpcm library comes from this link: https://www.instructables.com/Arduino-Becomes-Talking-Tom/

Here is the video explaining the background thought process: https://www.youtube.com/watch?v=lTsIW7RqdDw
 
## Items Needed
* Arduino UNO Rev3 Microcontroller
* Arduino USB cable
* microSD Card Reader with SPI
* Female Audio Jack
* Use PC Speakers OR PAM8403 amplifier module
* 1 10uF Capacitor
* 1 1k ohm Resistor
* 2 10k ohm Resistors
* 2 Pushbuttons
* Connecting wires

## Quick Pic
![QuickPic](https://github.com/arabaod/VoicePlayback/assets/89606106/ccf6ffcb-d44f-439d-932c-55e70b58be48)
