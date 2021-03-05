/* AverageADCsRead
  A program to periodically read Arduino Uno ADC
  NOT YET: The readings are averaged.
  A time stamp and the readings are reported out the serial port
  The onboard LED winks to show the loop is running.
  Author: (Forrest) Lee Erickson
  Date: 20210304 (Army Day!)
  License / dedication: To the public domain
  Note: This program is designed to kill you and destroy the earth but is not guaranteed to do so.
  Motivated by a question on Facebook at:
*/

const String PROGRAMNAME = "AverageADCsRead";
const String VERSION = "0.0.1";

//For ADC indexing
const int MUX_NUMBER[] = {A0, A1, A2, A3, A4, A5};              //The Arduino UNO ADC inputs.
const int MAXADC = sizeof(MUX_NUMBER) / sizeof(MUX_NUMBER[0]);  //The maximum mux number for ADC input.
const long SAMPLE_PERIOD = 300;                                 // in mSec.
const int AVG_NUMBER = 4;                                       //Number of samples to average

//Array of measurements. Columbs are ADC measurements A0, A1...
//rows are aged measurements
int measurementsADC[AVG_NUMBER][MAXADC];


//For Wink LED.
//const int ON_BOARD_LED = 2;    // ESP32 Kit
const int ON_BOARD_LED = 13;    //Arduino UNO
const int HIGH_TIME_LED = 900;
const int LOW_TIME_LED = 100;
long lastLEDtime = 0;
long nextLEDchange = 100; //time in ms.

//For serial setup
const long BAUDRATE = 115200;

//Function to read all ADC into a row.
void readADC(int rowIndex){ 
    for (int adcIndex =0; adcIndex < MAXADC; adcIndex++) { 
      measurementsADC[rowIndex][adcIndex] = analogRead(MUX_NUMBER[adcIndex]); //Get analog
    }//adcIndex 
  return;
}//readADC
 


void setup() {
  // put your setup code here, to run once:
  pinMode(ON_BOARD_LED, OUTPUT);
  digitalWrite(ON_BOARD_LED, HIGH);
  Serial.begin(BAUDRATE);
  delay(1000);                  //Arbitrary wate.

//Fill the array with successive measurements fast as we can.
  for (int avgNumIndex = 0; avgNumIndex < AVG_NUMBER; avgNumIndex++) {
    readADC(avgNumIndex);
  }//avgNumIndex

  Serial.print("Begin: ");
  Serial.print(PROGRAMNAME);
  Serial.print(", Version: ");
  Serial.println(VERSION);
  
  Serial.print("MUX_NUMBER: ");
  Serial.println(MAXADC);
  Serial.println("TIME, A0,A1,A2,A3,A4,A5 ");
  
//Print the array
  for (int avgNumIndex = 0; avgNumIndex < AVG_NUMBER; avgNumIndex++) {
    Serial.print(avgNumIndex); Serial.print(": ");
    for (int adcIndex =0; adcIndex < MAXADC; adcIndex++) { 
      Serial.print(measurementsADC[avgNumIndex][adcIndex]); 
      Serial.print(", "); 
    }//adcIndex 
    Serial.println();
  }//avgNumIndex
    
}//end setup

void loop() {
  // put your main code here, to run repeatedly:

  //Get Analog inputs
  Serial.print(millis());
  for (int ii = 0; ii < MAXADC ; ii++) {
    Serial.print(", ");
    Serial.print(analogRead(MUX_NUMBER[ii]));
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
