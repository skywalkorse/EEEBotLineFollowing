#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c  //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define IR0 12  // select the input pin for the potentiometer
#define IR1 14
#define IR2 27
#define IR3 26
#define IR4 25
#define IR5 33


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

int maxVal[] = {0, 0, 0, 0, 0, 0};
int minVal[] = {0, 0, 0, 0, 0, 0};

int irVal[] = {0, 0, 0, 0, 0, 0};

static const unsigned char PROGMEM logo16_glcd_bmp[] = { B00000000, B11000000,
                                                         B00000001, B11000000,
                                                         B00000001, B11000000,
                                                         B00000011, B11100000,
                                                         B11110011, B11100000,
                                                         B11111110, B11111000,
                                                         B01111110, B11111111,
                                                         B00110011, B10011111,
                                                         B00011111, B11111100,
                                                         B00001101, B01110000,
                                                         B00011011, B10100000,
                                                         B00111111, B11100000,
                                                         B00111111, B11110000,
                                                         B01111100, B11110000,
                                                         B01110000, B01110000,
                                                         B00000000, B00110000 };


void setup() {


  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);





  Serial.begin(9600);
  delay(250);

  display.begin(i2c_Address, true);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);


  for (int i = 0; i <= 5; i++) {
    display.setCursor(0, 0);
    display.print("EEEbot booting");
    display.display();
    for (int j = 0; j <= 3; j++) {
      delay(100);
      display.print(".");
      display.display();
      delay(100);
    }
    display.clearDisplay();
  }

  display.clearDisplay();

  display.setCursor(0, 0);

  display.println("Place under white surface ");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Calibrating for white");
  display.display();

  maxVal[0] = analogRead(IR0);
  maxVal[1] = analogRead(IR1);
  maxVal[2] = analogRead(IR2);
  maxVal[3] = analogRead(IR3);
  maxVal[4] = analogRead(IR4);
  maxVal[5] = analogRead(IR5);
  
  delay(3000);


  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Place under black surface ");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Calibrating for black");
  display.display();

  minVal[0] = analogRead(IR0);
  minVal[1] = analogRead(IR1);
  minVal[2] = analogRead(IR2);
  minVal[3] = analogRead(IR3);
  minVal[4] = analogRead(IR4);
  minVal[5] = analogRead(IR5);
  
  delay(3000);


  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("1W: ");
  display.print(maxVal[0]);
  display.print(" 1B: ");
  display.println(minVal[0]);

  display.print("2W: ");
  display.print(maxVal[1]);
  display.print(" 2B: ");
  display.println(minVal[1]);

  display.print("3W: ");
  display.print(maxVal[2]);
  display.print(" 3B: ");
  display.println(minVal[2]);

  display.print("4W: ");
  display.print(maxVal[3]);
  display.print(" 4B: ");
  display.println(minVal[3]);

  display.print("5W: ");
  display.print(maxVal[4]);
  display.print(" 5B: ");
  display.println(minVal[4]);

  display.print("6W: ");
  display.print(maxVal[5]);
  display.print(" 6B: ");
  display.println(minVal[5]);

  display.display();

  delay(6000);


  




}



void loop() {

  display.clearDisplay();
  display.setCursor(0, 0);

  irVal[0] = analogRead(IR0);
  irVal[1] = analogRead(IR1);
  irVal[2] = analogRead(IR2);
  irVal[3] = analogRead(IR3);
  irVal[4] = analogRead(IR4);
  irVal[5] = analogRead(IR5);

  for(int i = 0; i<=5 ;i++){
    display.println(irVal[i]);
  }

  display.display();




  

  //raw data test code
  // // int sensorValue0 = analogRead(IR0);
  // // int sensorValue1 = analogRead(IR1);
  // // int sensorValue2 = analogRead(IR2);
  // // int sensorValue3 = analogRead(IR3);
  // // int sensorValue4 = analogRead(IR4);
  // // int sensorValue5 = analogRead(IR5);

  
}