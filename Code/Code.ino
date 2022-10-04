// ###############################################################################################################################
// #
// # Code for "3 x 120mm Arduino controlled RGB LED fan holder" project: https://www.printables.com/de/model/285755-3-x-120mm-arduino-controlled-rgb-led-fan-holder
// #
// # Code by https://github.com/AWSW-de 
// #
// # Released under license: GNU General Public License v3.0: https://github.com/AWSW-de/3-x-120mm-Arduino-controlled-RGB-LED-fan-holder/blob/main/LICENSE
// #
// ###############################################################################################################################
/*   
      ___           ___           ___           ___                    ___           ___           ___     
     /\  \         /\__\         /\  \         /\__\                  /\  \         /\  \         /\  \    
    /::\  \       /:/ _/_       /::\  \       /:/ _/_                /::\  \       /::\  \       /::\  \   
   /:/\:\  \     /:/ /\__\     /:/\ \  \     /:/ /\__\              /:/\:\  \     /:/\:\  \     /:/\:\  \  
  /::\~\:\  \   /:/ /:/ _/_   _\:\~\ \  \   /:/ /:/ _/_            /::\~\:\  \   /:/  \:\  \   /::\~\:\__\ 
 /:/\:\ \:\__\ /:/_/:/ /\__\ /\ \:\ \ \__\ /:/_/:/ /\__\          /:/\:\ \:\__\ /:/__/_\:\__\ /:/\:\ \:|__|
 \/__\:\/:/  / \:\/:/ /:/  / \:\ \:\ \/__/ \:\/:/ /:/  /          \/_|::\/:/  / \:\  /\ \/__/ \:\~\:\/:/  /
      \::/  /   \::/_/:/  /   \:\ \:\__\    \::/_/:/  /              |:|::/  /   \:\ \:\__\    \:\ \::/  / 
      /:/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /               |:|\/__/     \:\/:/  /     \:\/:/  /  
     /:/  /       \::/  /       \::/  /       \::/  /                |:|  |        \::/  /       \::/__/   
     \/__/         \/__/         \/__/         \/__/                  \|__|         \/__/         ~~       
      ___       ___           ___                    ___           ___           ___                       
     /\__\     /\  \         /\  \                  /\  \         /\  \         /\__\                      
    /:/  /    /::\  \       /::\  \                /::\  \       /::\  \       /::|  |                     
   /:/  /    /:/\:\  \     /:/\:\  \              /:/\:\  \     /:/\:\  \     /:|:|  |                     
  /:/  /    /::\~\:\  \   /:/  \:\__\            /::\~\:\  \   /::\~\:\  \   /:/|:|  |__                   
 /:/__/    /:/\:\ \:\__\ /:/__/ \:|__|          /:/\:\ \:\__\ /:/\:\ \:\__\ /:/ |:| /\__\                  
 \:\  \    \:\~\:\ \/__/ \:\  \ /:/  /          \/__\:\ \/__/ \/__\:\/:/  / \/__|:|/:/  /                  
  \:\  \    \:\ \:\__\    \:\  /:/  /                \:\__\        \::/  /      |:/:/  /                   
   \:\  \    \:\ \/__/     \:\/:/  /                  \/__/        /:/  /       |::/  /                    
    \:\__\    \:\__\        \::/__/                               /:/  /        /:/  /                     
     \/__/     \/__/         ~~                                   \/__/         \/__/                      
*/


// ###############################################################################################################################
// #
// # Code version:
// #
// ###############################################################################################################################
String code_version = "V1.0.0";


// ###############################################################################################################################
// # Includes:
// #
// # You will need to add the following libraries to your Arduino IDE to use the project:
// # - Adafruit NeoPixel              // by Adafruit: https://github.com/adafruit/Adafruit_NeoPixel
// #
// ###############################################################################################################################
#include <Adafruit_NeoPixel.h>        // RGB LED library


// ###############################################################################################################################
// # Hardware settings:
// ###############################################################################################################################
int FanPWM = D7;                      // Fan PWM pin
int FanRPM = D6;                      // Fan RPM pin
int PushButtonInput1 = D1;            // Push button - set PWM Fan speed
int PushButtonInput2 = D2;            // Push button - set the LED animation
int PushButtonInput3 = D3;            // Push button - set the LED brightness
int LEDPIN = D5;                      // Fan LED pin


// ###############################################################################################################################
// # LED and fan settings:
// ###############################################################################################################################
int LEDNUMBER = 8;                    // Fan LED amount
int LEDBRIGHTNESS = 255;              // Fan LED default brightness (0-255)
int fanspeed = 0;                     // Default fan speed (0-255)
int FanSpdButtonCount = 0;            // Variable for the button presses to switch between fan speeds
int LEDModeButtonCount = 0;           // Variable for the button presses to switch between the LED modes
int LEDBrightnessButtonCount = 0;     // Variable for the button presses to switch between the LED brightness modes
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUMBER, LEDPIN, NEO_GRB + NEO_KHZ800);


// ###############################################################################################################################
// # Setup function to run at startup:
// ###############################################################################################################################
void setup()
{
  Serial.begin(115200);
  delay(1000);
  fanspeed = 0;
  pinMode(FanPWM, OUTPUT);
  pinMode(PushButtonInput1, INPUT_PULLUP);      // FAN speed
  pinMode(PushButtonInput2, INPUT_PULLUP);      // LED animation
  pinMode(PushButtonInput3, INPUT_PULLUP);      // LED brightness
  strip.begin();
  strip.setBrightness(LEDBRIGHTNESS);
  colorWipe(strip.Color(0, 0, 0), 25);          // LEDs OFF
  delay(1000);
  Serial.println("#########################################");
  Serial.print("# AWSW RGB LED FAN - Version: ");
  Serial.print(code_version);
  Serial.println("    #");
  Serial.println("#########################################");
}


// ###############################################################################################################################
// # Loop funtion to run all the time:
// ###############################################################################################################################
void loop() {
  switch (LEDModeButtonCount) {
    case 0:                                       // Default animation
      colorWipe(strip.Color(255, 255, 255), 50);      // White
      break;
    case 1:                                       // Animation 1
      colorWipe(strip.Color(255, 0, 0), 50);          // Red
      break;
    case 2:                                       // Animation 2
      colorWipe(strip.Color(0, 255, 0), 50);          // Green
      break;
    case 3:                                       // Animation 3
      colorWipe(strip.Color(0, 0, 255), 50);          // Blue
      break;
    case 4:                                       // Animation 4
      colorWipe(strip.Color(0, 255, 255), 50);        // Cyan
      break;
    case 5:                                       // Animation 5
      colorWipe(strip.Color(255, 128, 0), 50);        // Orange
      break;
    case 6:                                       // Animation 6
      colorWipe(strip.Color(255, 255, 255), 50);      // White
      break;
    case 7:                                       // Animation 7
      rainbow(20);                                    // Rainbow
      break;
    case 8:                                       // Animation 8
      rainbowCycle(20);                               // Rainbow cycle
      break;
    case 9:                                       // Goto 0
      Serial.println("LED Mode Button Count Old: " + String(LEDModeButtonCount));
      LEDModeButtonCount = 0;
      Serial.println("LED Mode Button Count New: " + String(LEDModeButtonCount));
      break;
  }

  switch (FanSpdButtonCount) {
    case 0:                                       // Fan Speed HIGH
      fanspeed = 255;
      break;
    case 1:                                       // Fan Speed MEDIUM
      fanspeed = 128;
      break;
    case 2:                                       // Fan Speed LOW
      fanspeed = 1;
      break;
    case 3:                                       // Goto 0
      Serial.println("Fan Speed Count Old: " + String(FanSpdButtonCount));
      FanSpdButtonCount = 0;
      Serial.println("Fan Speed Button Count New: " + String(FanSpdButtonCount));
      break;
  }

  switch (LEDBrightnessButtonCount) {
    case 0:                                       // Brightness LEDs HIGH
      LEDBRIGHTNESS = 255;
      break;
    case 1:                                       // Brightness LEDs MEDIUM
      LEDBRIGHTNESS = 128;
      break;
    case 2:                                       // Brightness LEDs OFF
      LEDBRIGHTNESS = 0;
      break;
    case 3:                                       // Goto 0
      Serial.println("LED BrightnessButton Count Old: " + String(LEDBrightnessButtonCount));
      LEDBrightnessButtonCount = 0;
      Serial.println("LED Brightness Button Count New: " + String(LEDBrightnessButtonCount));
      break;
  }
  analogWrite(FanPWM, fanspeed);
  strip.setBrightness(LEDBRIGHTNESS);
}


// ###############################################################################################################################
// # Button funtions:
// ###############################################################################################################################
void SetFanAndLEDs() {
  //-----------------SET FAN SPEED----------------------
  if (digitalRead(PushButtonInput1) == LOW) {
    Serial.println("Fan Speed Button Count Old: " + String(FanSpdButtonCount));
    FanSpdButtonCount = FanSpdButtonCount + 1;
    Serial.println("Fan Speed Button Count New: " + String(FanSpdButtonCount));
    delay(1000);
  }

  //------------------SET LED MODE---------------------------
  if (digitalRead(PushButtonInput2) == LOW) {
    Serial.println("LED Mode Button Count Old: " + String(LEDModeButtonCount));
    LEDModeButtonCount = LEDModeButtonCount + 1;
    Serial.println("LED Mode Button Count New: " + String(LEDModeButtonCount));
    delay(1000);
  }

  //------------------SET LED BRIGHTNESS---------------------------
  if (digitalRead(PushButtonInput3) == LOW) {
    Serial.println("LED Brightness Button Count Old: " + String(LEDBrightnessButtonCount));
    LEDBrightnessButtonCount = LEDBrightnessButtonCount + 1;
    Serial.println("LED Brightness Button Count New: " + String(LEDBrightnessButtonCount));
    delay(1000);
  }
}


// ###############################################################################################################################
// # LED funtions: Fill the dots one after the other with a color
// ###############################################################################################################################
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    SetFanAndLEDs();
    delay(wait);
  }
}


// ###############################################################################################################################
// # LED funtions: Rainbow color mode
// ###############################################################################################################################
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    SetFanAndLEDs();
    delay(wait);
  }
}


// ###############################################################################################################################
// # LED funtions: Slightly different, this makes the rainbow equally distributed throughout
// ###############################################################################################################################
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    SetFanAndLEDs();
    delay(wait);
  }
}


// ###############################################################################################################################
// # LED funtions: Input a value 0 to 255 to get a color value.
// ###############################################################################################################################
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
