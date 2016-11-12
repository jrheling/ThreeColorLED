/* example of using ThreeColorLED library */

#include <ThreeColorLED.h>

ThreeColorLED tcl(12, 11);


void setup() {
  Serial.begin(9600);
  Serial.println("ThreeColorLED Library Sample");

  tcl.setColor(TCL_CLR_GREEN);

  // Set up interrupt to call tcl.update() - alternatively, you could call from loop() if its easier
  //    and works with your sketch
  //
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  //  (from https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers)
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

// Interrupt is called once a millisecond
SIGNAL(TIMER0_COMPA_vect) {    
  tcl.update();
}

void loop() {
  Serial.println();
  Serial.println("****** Solid Colors");

  tcl.setBlinkFreq(TCL_BLINK_NONE);
  
  Serial.println("Green");
  tcl.setColor(TCL_CLR_GREEN);
  delay(2000);
  
  Serial.println("Red");
  tcl.setColor(TCL_CLR_RED);
  delay(2000);
  
  Serial.println("Yellow");
  tcl.setColor(TCL_CLR_YELLOW);
  delay(2000);
  
  Serial.println("****** Blinking Colors");

  tcl.setBlinkColor(TCL_CLR_NONE);
  tcl.setBlinkFreq(TCL_BLINK_NORM);
  
  Serial.println("Green");
  tcl.setColor(TCL_CLR_GREEN);
  delay(2000);
  
  Serial.println("Red");
  tcl.setColor(TCL_CLR_RED);
  delay(2000);
  
  Serial.println("Yellow");
  tcl.setColor(TCL_CLR_YELLOW);
  delay(2000);
  
  Serial.println("****** Blinking Fast");

  tcl.setBlinkColor(TCL_CLR_NONE);
  tcl.setBlinkFreq(TCL_BLINK_FAST);
  
  Serial.println("Green");
  tcl.setColor(TCL_CLR_GREEN);
  delay(2000);
  
  Serial.println("Red");
  tcl.setColor(TCL_CLR_RED);
  delay(2000);
  
  Serial.println("Yellow");
  tcl.setColor(TCL_CLR_YELLOW);
  delay(2000);
  
  Serial.println("****** Alternating Colors");

  tcl.setBlinkFreq(TCL_BLINK_FAST);
  
  Serial.println("Green/Yellow");
  tcl.setBlinkColor(TCL_CLR_YELLOW);
  tcl.setColor(TCL_CLR_GREEN);
  delay(2000);
  
  Serial.println("Red/Green");
  tcl.setBlinkColor(TCL_CLR_GREEN);
  tcl.setColor(TCL_CLR_RED);
  delay(2000);
  
  Serial.println("Yellow/Red");
  tcl.setBlinkColor(TCL_CLR_RED);
  tcl.setColor(TCL_CLR_YELLOW);
  delay(2000);
  
}

 
