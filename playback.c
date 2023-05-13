#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#include <ezButton.h>
#include <avr/power.h>  // Power Saving Methods

#define slaveSelect 10  //Slave Select/Chip select pi of the SD card module
#define playRand 2      //Play Random music button Input
#define record 3        //Record audio button input
#define mic A0          //Mic analog input pin


/* DDR register - PIN = Input or Output
   PORT register - PIN = HIGH or LOW
   PIN register - reads pinMode(), Input
*/

// File root;
// TMRpcm player;

/* All code that deals with audio, files, the SD card, and SPI module comes from 
https://www.instructables.com/Arduino-Becomes-Talking-Tom/ */

int audio_files = 0;
int flag = 0;

// ezButton values for debouncing
ezButton play(playRand);  // ezButton button1(pin_num);
ezButton rec(record);

int main(void) {
  /* Inputs or Outputs? */
  DDRB |= _BV(DDB1);  // Pin 9 for output LED for analong microphone input
  DDRD &= B11110011;  // Pins 2 and 3 set as input for the pushbuttons
  DDRB &= B000011;    // Pins 10 through 13 are inputs for SPI Communication

  /* Turn on the Analog and the audio */
  PORTC |= _BV(PORTC0);  // A0 for MAX4466
  PORTB |= _BV(PORTB1);  // Pin 9 for the audio outpout

  play.setDebounceTime(750);  // 750 ms of debounce time
  rec.setDebounceTime(750);   // 750 ms of debounce time

  player.speakerPin = 9;  // PWM pin for audio output
  player.setVolume(5);    // 0 to 7 volume level for output
  player.quality(1);

  pinMode(playRand, INPUT);
  pinMode(record, INPUT);
  pinMode(mic, INPUT);

  root = SD.open("/");  //open SD card root directory as a 'root' file object
  printAudioFiles();
  if (SD.exists("record.wav")) {
    SD.remove("record.wav");
    Serial.println("Previous Recording Removed!");
  }

  delay(1000);          //Delay to see normal power level first
  ADCSRA = 0;           // disable ADC by setting ADCSRA register to 0
  power_adc_disable();  //disable the clock to the ADC module
  delay(1000);          //delay to see just ADC off power level
  SPCR = 0;             //disable SPI by setting SPCR register to 0
  power_spi_disable();  //disable the clock to the SPI module
  delay(1000);          //delay to see just ADC and SPI off power level
  power_all_disable();


  while (1) {
    LowPower.deepSleep(1000);
    play.loop();  // Loop the debouncing methods
    rec.loop();   // Loop the debouncing methods

    root.rewindDirectory();
    int playButtonState = digitalRead(playRand);  // Read play button state
    int recordButtonState = digitalRead(record);  // Read record button state

    if (player.isPlaying()) {
      // if any audio file is still playing print PLAYING AUDIO
      Serial.println("PLAYING AUDIO");
    }

    //invoke playRandAudio() function when play button is pressed
    if (playButtonState == HIGH) {
      Serial.println("");
      Serial.println("Playing Random Audio");
      playRandAudio();
      delay(1000);
    }

    // Handle the recording and playback function
    while (recordButtonState == HIGH) {
      if (flag == 0) {
        SD.remove("record.wav");
        Serial.println("");
        Serial.println("...Start Speaking...");
        player.startRecording("record.wav", 48000, mic);
        flag = 1;
      }
      recordButtonState = digitalRead(record);
    }

    if (flag == 1) {
      player.stopRecording("record.wav");
      Serial.println("...Recording Stopped!!...");
      Serial.println("...Playing the Recorded Audio...");
      player.play("record.wav");
      flag = 0;
    }
  }
}

// Function to print the name of all .wav files present in the SD card
void printAudioFiles() {
  while (1) {
    File entry = root.openNextFile();
    if (!entry) {
      // exit loop if no more files are left to read
      break;
    }

    uint8_t nameLen = String(entry.name()).length();           //get the length of the file name
    String ext = String(entry.name()).substring(nameLen - 4);  // save the extension of the file in 'ext' string

    // check for .wav files in sd card and print their name
    if (ext.equalsIgnoreCase(".wav")) {
      Serial.println(entry.name());
      audio_files = audio_files + 1;
    } else {
      // close this file if its not .wav file
      entry.close();
    }
  }
  Serial.println("");
}

// Function to randomly pick an audio file from the sd card and play it
void playRandAudio() {
  // generate a random file name
  int randomNum = random(audio_files);
  String file_name = String("audio_");
  file_name += randomNum + 1;
  file_name += ".wav";

  Serial.println("");
  Serial.println("Random File Chosen: ");
  Serial.println(file_name);

  while (1) {
    File entry = root.openNextFile();
    if (!entry) {
      Serial.println("We never made it.");
      // exit loop if no more files are left to read
      break;
    }
    Serial.println("Entered the loop");

    // check if name of current file is same as the randomly generated file
    if (file_name.equalsIgnoreCase(String(entry.name()))) {
      Serial.println("...Playing File...");
      Serial.println(entry.name());
      player.play(entry.name());
      return;
    } else {
      // close this file if its not .wav file
      entry.close();
    }
  }
  Serial.println("");
  return;
}