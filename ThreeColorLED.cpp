/*
   ThreeColorLED - Library for managing color selection & flashing on
		three-lead / three-color LEDs.  Built for Electronic Goldmine part G6159,
		but should work with any LED that can be red, green, or (red+green=) yellow.

		(c) 2016 - Joshua Heling - jrh@netfluvia.org
		released under BSD license
*/

#include "Arduino.h"
#include "ThreeColorLED.h"

ThreeColorLED::ThreeColorLED(int greenPin, int redPin) {
	_pinGreen = greenPin;
	_pinRed = redPin;
	
	pinMode(_pinGreen, OUTPUT);
	pinMode(_pinRed, OUTPUT);
	
	_state = A;    // used to track blinking.  When we blink, it's between states A and B
	_last_state_change = millis();
	
	// init values
	_color = TCL_CLR_GREEN;
	_blinkColor = TCL_CLR_NONE;
	_blinkFreq = TCL_BLINK_NONE;
	saveState();  // to init _*_saved 
}

void ThreeColorLED::setColor(unsigned short int color) {
	_color = color;
	_changeLED(_color);
}

void ThreeColorLED::setBlinkColor(unsigned short int blinkColor) {
	if ((blinkColor >= TCL_CLR_NONE) && (blinkColor <= TCL_CLR_YELLOW)) {
		_blinkColor = blinkColor;		
	}
	// intentionally don't actually change the color here - that will happen in update()
}

void ThreeColorLED::setBlinkFreq(unsigned int blinkFreq) {
	_blinkFreq = blinkFreq;
}

void ThreeColorLED::setBlink(unsigned short int blinkColor, unsigned short int blinkFreq) {
	setBlinkColor(blinkColor);
	setBlinkFreq(blinkFreq);
}

void ThreeColorLED::set(unsigned short int color, unsigned short int blinkColor, 
												unsigned short int blinkFreq) {
	setColor(color);
	setBlinkColor(blinkColor);
	setBlinkFreq(blinkFreq);																										
}

void ThreeColorLED::saveState() {
	_color_saved = _color;
	_blinkColor_saved = _blinkColor;
	_blinkFreq_saved = _blinkFreq;
}

void ThreeColorLED::restoreState() {
	_color = _color_saved;
	_blinkColor = _blinkColor_saved;
	_blinkFreq = _blinkFreq_saved;	
}

void ThreeColorLED::update() {
	// nothing to do unless we're blinking
	if (_blinkFreq != TCL_BLINK_NONE) {
		if (millis() > _last_state_change + _blinkFreq) {
			// time to blink
			if (_state == A) {
				// state A is the primary color, so when we blink we change to the other
				_changeLED(_blinkColor);
				_state = B;
			} else {
				_changeLED(_color);
				_state = A;
			}
			_last_state_change = millis();			
		}
	}
}

// make the LED display the given color
void ThreeColorLED::_changeLED(unsigned short int c) {
	switch (c) {
		case TCL_CLR_NONE:
			_LED_off();
			break;
		case TCL_CLR_GREEN:
			_LED_green();
			break;
		case TCL_CLR_RED:
			_LED_red();
			break;
		case TCL_CLR_YELLOW:
			_LED_yellow();
			break;	
		default:
		  // no-op
			break;
	}			
}

void ThreeColorLED::_LED_off() {
	digitalWrite(_pinRed, LOW);
	digitalWrite(_pinGreen, LOW);
}

void ThreeColorLED::_LED_green() {
	digitalWrite(_pinRed, LOW);
	digitalWrite(_pinGreen, HIGH);
}

void ThreeColorLED::_LED_red() {
	digitalWrite(_pinRed, HIGH);
	digitalWrite(_pinGreen, LOW);
}

void ThreeColorLED::_LED_yellow() {
	digitalWrite(_pinRed, HIGH);
	digitalWrite(_pinGreen, HIGH);
}