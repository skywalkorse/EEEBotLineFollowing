/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13 through 220 ohm resistor
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

#define IR0 12  // select the input pin for the potentiometer
#define IR1 14
#define IR2 27
#define IR3 26
#define IR4 25
#define IR5 33



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(IR0,INPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(IR5,INPUT);

  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  int sensorValue0 = analogRead(IR0);
  int sensorValue1= analogRead(IR1);
  int sensorValue2 = analogRead(IR2);
  int sensorValue3= analogRead(IR3);
  int sensorValue4 = analogRead(IR4);
  int sensorValue5 = analogRead(IR5);
  
  Serial.print("First: ");
  Serial.print(sensorValue0);
  Serial.print("\t");
  Serial.print("Second: ");
  Serial.print(sensorValue1);
  Serial.print("\t");
  Serial.print("Third: ");
  Serial.print(sensorValue2);
  Serial.print("\t");
  Serial.print("Fourth: ");
  Serial.print(sensorValue3);
  Serial.print("\t");
  Serial.print("Fifth: ");
  Serial.print(sensorValue4);
  Serial.print("\t");
  Serial.print("Sixth: ");
  Serial.print(sensorValue5);
  Serial.println("");
  
}
