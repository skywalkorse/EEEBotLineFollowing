#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define I2C_SLAVE_ADDR 0x04





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

int x = 0;   //left speed
int y = 0;   //right speed
int z = 92;  //steering angle

int Kp = 60;
float Ki = 0;
int Kd = 20;

float lastE = 0;
float currentE = 0;
float weightedAve = 0;
float u = 0;
float sumE = 0;

const int buttonPin0 = 16;  
const int buttonPin1 = 17;
const int buttonPin2 = 5;

// The button push state value. 
int buttonState0 = 0;  
int buttonState1 = 0; 
int buttonState2 = 0;

//PID parameter for motors
int setSpeed = 0;
float speedFactor = 1.0;

//menu page number
int menu =0;

bool run = false;


// array for the sensors.
const char* number[] = {"First: ", "Second: ", "Third: ", "Fourth: ", "Fifth: ", "Sixth: "};





void setup() {

  //setup the pinmode for the IR sensors
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  //setup the pinmode for the button
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);





  Serial.begin(9600);
  delay(250);

  display.begin(i2c_Address, true);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);


  //display booting text on oled display
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

  //calibration for the IR sensors

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

//drive function, able to move the EEEbot
void drive(int leftMotor, int rightMotor, int angle) {

  Wire.beginTransmission(I2C_SLAVE_ADDR);

  Wire.write((byte)((leftMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor & 0x000000FF));

  Wire.write((byte)((rightMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor & 0x000000FF));


  Wire.write((byte)((angle & 0x0000FF00) >> 8));
  Wire.write((byte)(angle & 0x000000FF));

  Wire.endTransmission();
  delay(100);
}








void loop() {



  

  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  display.clearDisplay();
  display.setCursor(0, 0);

  irVal[0] = analogRead(IR0);
  irVal[1] = analogRead(IR1);
  irVal[2] = analogRead(IR2);
  irVal[3] = analogRead(IR3);
  irVal[4] = analogRead(IR4);
  irVal[5] = analogRead(IR5);

  for(int i = 0; i<=5; i++){
    if(irVal[i]>maxVal[i]){
      irVal[i] = maxVal[i];
    }
    if(irVal[i]<minVal[i]){
      irVal[i] = minVal[i];
    }
  }


  float XiSi = 0;
  int sum = 0;

  for(int i = 0; i<=5 ;i++){

    XiSi += (irVal[i]*(i+1));
    sum += irVal[i];

    if(menu == 0){
      display.print(number[i]);
      display.println(irVal[i]);
    }

  }

  if(menu>5){
    menu = 0;
  }

  while(buttonState1 == HIGH){
    menu++;
    break;
    
  }

  

  if(menu ==1){
    display.print("P: ");
    display.println(Kp);



    if(buttonState2 == HIGH){
      Kp++;
    }
    if(buttonState0 == HIGH&&Kp>0){
      Kp--;
    }
    

    

  
    
  }
  if(menu ==2){
    display.print("I: ");
    display.println(Ki);
    if(buttonState2 == HIGH){
      Ki+=0.1;
    }
    if(buttonState0 == HIGH&&Ki>0){
      Ki-=0.1;
    }

    
  }
  if(menu ==3){
    display.print("D: ");
    display.println(Kd);
    if(buttonState2 == HIGH){
      Kd++;
    }
    if(buttonState0 == HIGH&&Kd>0){
      Kd--;
    }
  }

  if(menu == 4){

    display.print("Motor Speed: ");
    display.println(setSpeed);

    if(buttonState2==HIGH){
      setSpeed+=20;
    }
    if(buttonState0 == HIGH && setSpeed>0){
      setSpeed-=20;
    }


  }

  if (menu == 5){
    display.print("Speed Factor: ");
    display.println(speedFactor);
    if(buttonState0 == HIGH){
      speedFactor-=0.01;
    }
    if(buttonState2 == HIGH && speedFactor<=1){
      speedFactor+=0.01;
    }

  }
    


  

  

  

  weightedAve = XiSi/sum;

  display.print("WA: ");
  display.println(weightedAve);

  display.display();


  currentE = 3.5 - weightedAve;

  sumE +=currentE;

  u = (Kp*currentE)+(Ki*sumE)+(Kd*(currentE-lastE));
  lastE = currentE;

  z = 92 - u;

  

  x = setSpeed-speedFactor*u;
  y = setSpeed+speedFactor*u;

  // if(weightedAve>4.0){
  //   y = -setSpeed;
    
  // }
  // if(weightedAve<3.0){
  //   x = -setSpeed;
  // }



  

  
  
  if(irVal[0]>1000&&irVal[1]>1000&&irVal[2]>1000&&irVal[3]>1000&&irVal[4]>1000&&irVal[5]>1000){
    drive(-90,-90,z);
  }
  else{
    drive(x,y,z);

  }



  
  
  

  
  

  




  

  //raw data test code
  // // int sensorValue0 = analogRead(IR0);
  // // int sensorValue1 = analogRead(IR1);
  // // int sensorValue2 = analogRead(IR2);
  // // int sensorValue3 = analogRead(IR3);
  // // int sensorValue4 = analogRead(IR4);
  // // int sensorValue5 = analogRead(IR5);

  
  
}