#ifndef LEDSERVO_H
#define LEDSERVO_H

#include "Servo.h"
#include <Arduino.h>


#define ON_LEDSERVO_DEFAULT 90
#define OFF_LEDSERVO_DEFAULT 0
#define ON_LEDSERVO_DEFAULT_2 90
#define OFF_LEDSERVO_DEFAULT_2 180
#define ON_LED 0
#define OFF_LED 1

enum ServoSegment {
  SEG_A,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  SEG_G
};

class LedServo {
  Servo servoA, servoB, servoC, servoD, servoE, servoF, servoG;
  int numbers[17][7];
public:
  int onOffPosition[7][2];
  LedServo();
  void init(int pina, int pinb, int pinc, int pind, int pine, int pinf, int ping);
  void loadServoOnOffPosition(int onOffPosition[7][2]);
  void displayNumber(int num);
  void writeServoSeg(ServoSegment, int);
  void readCurrentServoPostion(int[7]);
};

#endif
