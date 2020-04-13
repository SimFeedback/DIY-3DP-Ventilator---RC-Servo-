#include <Servo.h>

// servo setup
Servo myservoR;
Servo myservoL;
const unsigned int SERVO_R_PIN = 9;
const unsigned int SERVO_L_PIN = 8;

// initial ventilator vars
int volume = 100; // 0 - 100
int frequency = 15; // frequency of the punp
int acceleration = 1000; // acceleration time in ms 

// calculation vars
//int posR = 0;    // variable to store the servo position

const int servoR_Min = 175;
const int servoR_Max = 143;

const int servoL_Min = 5;
const int servoL_Max = 37;


void setup() {
  Serial.begin(9600);
  Serial.write("Connected\n");
  
  // attach servo pins
  myservoR.attach(SERVO_R_PIN);
  myservoL.attach(SERVO_L_PIN);

  // move servos to start position
  myservoR.write(servoR_Min);
  myservoL.write(servoL_Min);

  delay(1000);
}



void loop() {

//  myservoR.write(servoR_Min);
//  myservoL.write(servoL_Min);
//  delay(60 / frequency * 1000 / 2);
//
//  myservoR.write(servoR_Max);
//  myservoL.write(servoL_Max);
//  delay(60 / frequency * 1000 / 2);
//  return;


  Serial.write("Loop\n");

  // close
  float posR = 0;
  float posL = 0;
  for(int i=0; i<1000; i++) {
    posR += (float)(servoR_Min - servoR_Max) / 1000.0;  // calc step
    int pos = max(servoR_Max, servoR_Min - posR); // calc abs step and limit
    myservoR.write(pos);

    posL += (float)(servoL_Max - servoL_Min) / 1000.0;
    pos = min(servoL_Max, servoL_Min + posL);
    myservoL.write(pos);
    
    delay(60 / frequency * 1000 / 2 / 1000 / 5); 
  }


  // open
  posR = 0;
  posL = 0;
  for(int i=0; i<1000; i++) {
    posR += (float)(servoR_Min - servoR_Max) / 1000.0;
    int pos = min(servoR_Min, servoR_Max + posR);
    myservoR.write(pos);
    

    posL += (float)(servoL_Max - servoL_Min) / 1000.0;
    pos = max(servoL_Min, servoL_Max - posL);
    myservoL.write(pos);
    
    delay(60 / frequency * 1000 / 2 / 1000); 
  }

  delay(300);

//  myservoR.write(servoR_Min);
//  delay(60 / frequency * 1000 / 2);
//  myservoR.write(servoR_Max);
//  delay(60 / frequency * 1000 / 2);
 
}

