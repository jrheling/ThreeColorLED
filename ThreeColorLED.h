/*
   ThreeColorLED - Library for managing color selection & flashing on
		three-lead / three-color LEDs.  Built for Electronic Goldmine part G6159,
		but should work with any LED that can be red, green, or (red+green=) yellow.

		(c) 2016 - Joshua Heling - jrh@netfluvia.org
		released under BSD license
*/

#ifndef ThreeColorLED_h
#define ThreeColorLED_h

#include "Arduino.h"

// TCL_CLR_* sets color of the LED
#define TCL_CLR_NONE 0
#define TCL_CLR_GREEN 1
#define TCL_CLR_RED 2
#define TCL_CLR_YELLOW 3

// TCL_BLINK_* sets frequency (in ms) of blinking.  Other values are possible; defines are 
//     just for convenience
#define TCL_BLINK_NONE 0
#define TCL_BLINK_NORM 1000 
#define TCL_BLINK_FAST 200
#define TCL_BLINK_SLOW 2000

enum BlinkState { A, B };

class ThreeColorLED {
	public:
		ThreeColorLED(int pinGreen, int pinRed);

		// set the color LED is normally set to
		void setColor(unsigned short int color);

		// set the color LED changes to when blinking (if set to TCL_CLR_NONE blinking will be on/off)
		void setBlinkColor(unsigned short int blinkColor);

		// frequency of blink action (in ms)
		void setBlinkFreq(unsigned int blinkFreq);
		
		// convenience wrapper around setBlinkColor and setBlinkFreq
		void setBlink(unsigned short int blinkColor, unsigned short int blinkFreq);

		// wrapper around setColor and setBlink
		void set(unsigned short int color, unsigned short int blinkColor, unsigned short int blinkFreq);

		// saves current blink/color settings - only latest save is retained
		void saveState();
		
		// returns blink/color settings to saved version
		void restoreState();
		
		// call periodically to allow opportunity to blink (ugh - see future improvement below)
		void update();
				
	private:
		int _pinGreen;
		int _pinRed;
		unsigned short int _color;
		unsigned short int _blinkColor;
		int _blinkFreq;
		unsigned short int _color_saved;
		unsigned short int _blinkColor_saved;
		int _blinkFreq_saved;		
		BlinkState _state;
		unsigned long _last_state_change;
		
		void _changeLED(unsigned short int c);
		void _LED_off();
		void _LED_red();
		void _LED_green();		
		void _LED_yellow();		
};

#endif

/* Future Feature Ideas:
    - save/restore an array of settings
		- flash N times (then return to normal)
		- change state for certain amount of time (then return to normal)

  TODO:
  - incorporate interrupt-based timer in TCL class so user doesn't need to call update.  See the
       following for inspiration / guidance:
			* http://stackoverflow.com/questions/33627745/interrupts-on-creating-arduino-library
			* http://www.avrfreaks.net/forum/linking-class-member-function-isr
 			* https://waterproofman.wordpress.com/2007/02/07/avr-interrupts-in-c/
			* Servo library - /Applications/Arduino.app/Contents/Java/libraries/Servo
*/
