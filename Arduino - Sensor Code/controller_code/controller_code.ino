/*
Simple Temperature Sensor by Malcolm Knapp
Version: 02
Adapted from the open-source LM35DZ Temperature Sensor project for Arduino by Daniel Spillere Andrade
http://www.danielandrade.net
http://creativecommons.org/license/cc-gpl

This program reads the output of an LM35 Temperature sensor and then transmites of a serial connection
*/
int   sensorPin = 0; // analog sensor (photoresistor) input pin
int   rangerPin = 1; // analog sensor (proximity sensor) input pin
int   ledRed    = 9; // red LED PWM pin
int   ledGreen  = 10; // green LED pin
int   ledBlue   = 11; // blue LED pin
float lightVal = 0, rangeVal = 0;
float lightSamples[8]; // variables to make a better precision
float rangeSamples[8]; 
int i; // loop counter

void setup()
{
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledBlue, OUTPUT);
    
    Serial.begin(9600); // start serial communication
}

void loop()
{
    
    for(i = 0;i<= 7;i++){ // gets 8 samples of voltage
      // System Volatge is 5V
      // Analog read max ouput is 1024 units
      // Therefore 4.9mV/unit
      lightSamples[i] = (analogRead(sensorPin)*(3.0/1024) * 100);  // ??
      rangeSamples[i] = (analogRead(rangerPin)*(3.0/1024) * 100);  // ??

      lightVal = lightVal + lightSamples[i]; 
      rangeVal = rangeVal + rangeSamples[i];
      delay(5);
    }
    lightVal = lightVal/8.0; // better precision
    rangeVal = rangeVal/8.0; // better precision
        
    Serial.print("?");
    /*Serial.print(lightVal);
    Serial.print(",");*/
    Serial.print(rangeVal);
    Serial.print("%");
    
    // change the LED values
    
    if (lightVal < 100){
      set_led(rangeVal);
    }  else {
       set_red(HIGH); 
    }
    
    lightVal = 0.0; // reset voltage varible 
    rangeVal = 0.0; // reset voltage varible 

    delay(50); // delay before loop
}

void set_led(float inputVal){
 
  if (inputVal > 255){
     inputVal = 255; 
    analogWrite(ledRed, HIGH);
    analogWrite(ledGreen, HIGH);
    analogWrite(ledBlue, HIGH);
  } else if (inputVal > 128){
    analogWrite(ledRed, HIGH/2);
    analogWrite(ledGreen, HIGH/2);
    analogWrite(ledBlue, HIGH/2);
     
   
  } else {
    analogWrite(ledRed, inputVal);
    analogWrite(ledGreen, inputVal);
    analogWrite(ledBlue, inputVal);
  }
}

void set_red(float value){
   analogWrite(ledRed, value);
  analogWrite(ledGreen, LOW);
   analogWrite(ledBlue, LOW); 
}
