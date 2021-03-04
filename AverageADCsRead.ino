/* AverageADCsRead
  A program to periodically read Arduino Uno ADC
  The readings are averaged.
  A time stamp and the readings are reported out the serial port
  The onboard LED winks to show the loop is running.
  Author: (Forrest) Lee Erickson
  Date: 20210304 (Army Day!)
  License / dedication: To the public domain
  Note: This program is designed to kill you and destroy the earth but is not guaranteed to do so.
  Motivated by a question on Facebook at:
*/

const String PROGRAMNAME = "AverageADCsRead";

//For ADC indexing
int muxNumber[] = {A0, A1, A2, A3, A4, A5};
int MAXDAC = sizeof(muxNumber) / sizeof(muxNumber[0]);

const long SAMPLE_PERIOD = 300; // in mSec.


//For Wink LED.
//const int ON_BOARD_LED = 2;    // ESP32 Kit
const int ON_BOARD_LED = 13;    //Arduino UNO
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.

//For serial setup
const long BAUDRATE = 115200;

void setup() {
  // put your setup code here, to run once:
  pinMode(ON_BOARD_LED, OUTPUT);
  digitalWrite(ON_BOARD_LED, HIGH);
  Serial.begin(BAUDRATE);
  delay(1000);                  //Arbitrary wate.
  Serial.print("Begin: ");
  Serial.println(PROGRAMNAME);
  Serial.print("muxNumber: ");
  Serial.println(MAXDAC);
  Serial.println("TIME, A0,A1,A2,A3,A4,A5 ");
}//end setup

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(millis());
  for (int ii = 0; ii < MAXDAC ; ii++) {
    Serial.print(", ");
    Serial.print(analogRead(muxNumber[ii]));
  }
  Serial.println();
  delay(SAMPLE_PERIOD);
  
  //Wink the LED
  if (((millis() - lastLEDtime) > nextLEDchange) || (millis() < lastLEDtime)) {
    if (digitalRead(ON_BOARD_LED) == LOW) {
      digitalWrite(ON_BOARD_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = HIGH_TIME_LED;
    } else {
      digitalWrite(ON_BOARD_LED, LOW);   // turn the LED on (HIGH is the voltage level)
      nextLEDchange = LOW_TIME_LED;
    }
    lastLEDtime = millis();
  }//end LED wink

  //Other functions here.

}//end loop
