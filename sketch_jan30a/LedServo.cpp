#include "LedServo.h"

LedServo::LedServo() {
  int temp[17][7] = {// sửa mảng chỗ này để thêm (2 chỗ )
    { ON_LED, ON_LED, ON_LED, ON_LED, ON_LED, ON_LED, OFF_LED },      // 0
    { OFF_LED, ON_LED, ON_LED, OFF_LED, OFF_LED, OFF_LED, OFF_LED },  // 1
    { ON_LED, ON_LED, OFF_LED, ON_LED, ON_LED, OFF_LED, ON_LED },     // 2
    { ON_LED, ON_LED, ON_LED, ON_LED, OFF_LED, OFF_LED, ON_LED },     // 3
    { OFF_LED, ON_LED, ON_LED, OFF_LED, OFF_LED, ON_LED, ON_LED },    // 4
    { ON_LED, OFF_LED, ON_LED, ON_LED, OFF_LED, ON_LED, ON_LED },     // 5
    { ON_LED, OFF_LED, ON_LED, ON_LED, ON_LED, ON_LED, ON_LED },      // 6
    { ON_LED, ON_LED, ON_LED, OFF_LED, OFF_LED, OFF_LED, OFF_LED },   // 7
    { ON_LED, ON_LED, ON_LED, ON_LED, ON_LED, ON_LED, ON_LED },       // 8
    { ON_LED, ON_LED, ON_LED, ON_LED, OFF_LED, ON_LED, ON_LED },       // 9
    {ON_LED, ON_LED, ON_LED, ON_LED, OFF_LED, ON_LED, ON_LED},
    {OFF_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED },        //zero   11
    {OFF_LED,OFF_LED,OFF_LED,ON_LED,OFF_LED,OFF_LED,OFF_LED},         // bật dưới  12
    {ON_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED},         // bật trên   13 
    {OFF_LED,OFF_LED,OFF_LED,OFF_LED,ON_LED,ON_LED,OFF_LED},           //  bật trái  14
    {OFF_LED,OFF_LED,OFF_LED,ON_LED,ON_LED,OFF_LED,OFF_LED},   // trái dưới 15
    {ON_LED,OFF_LED,OFF_LED,OFF_LED,OFF_LED,ON_LED,OFF_LED}    // trái trên 16
  };
  memcpy(numbers, temp, sizeof(temp));

  int onOffPos[7][2] = {
    { ON_LEDSERVO_DEFAULT_2, OFF_LEDSERVO_DEFAULT_2 },  //A
    { ON_LEDSERVO_DEFAULT_2, OFF_LEDSERVO_DEFAULT_2 },  //B
    { ON_LEDSERVO_DEFAULT_2, OFF_LEDSERVO_DEFAULT_2 },  //C
    { ON_LEDSERVO_DEFAULT, OFF_LEDSERVO_DEFAULT },  //D
    { ON_LEDSERVO_DEFAULT, OFF_LEDSERVO_DEFAULT },  //E
    { ON_LEDSERVO_DEFAULT, OFF_LEDSERVO_DEFAULT },  //F
    { ON_LEDSERVO_DEFAULT, OFF_LEDSERVO_DEFAULT },  //G
  };
  loadServoOnOffPosition(onOffPos);
}

void LedServo::init(int pina, int pinb, int pinc, int pind, int pine, int pinf, int ping) {
  servoA.attach(pina);
  servoB.attach(pinb);
  servoC.attach(pinc);
  servoD.attach(pind);
  servoE.attach(pine);
  servoF.attach(pinf);
  servoG.attach(ping);
  
  writeServoSeg(SEG_A, onOffPosition[0][ON_LED]);
  writeServoSeg(SEG_B, onOffPosition[1][ON_LED]);
  writeServoSeg(SEG_C, onOffPosition[2][ON_LED]);
  writeServoSeg(SEG_D, onOffPosition[3][ON_LED]);
  writeServoSeg(SEG_E, onOffPosition[4][ON_LED]);
  writeServoSeg(SEG_F, onOffPosition[5][ON_LED]);
  writeServoSeg(SEG_G, onOffPosition[6][ON_LED]);
  //delay(1000);
}
void LedServo::loadServoOnOffPosition(int onOffPosition[7][2]) {
  memcpy(this->onOffPosition, onOffPosition, sizeof(this->onOffPosition));
}
void LedServo::displayNumber(int num) {
  servoA.write(onOffPosition[0][numbers[num][0]]);
  servoB.write(onOffPosition[1][numbers[num][1]]);
  servoC.write(onOffPosition[2][numbers[num][2]]);
  servoD.write(onOffPosition[3][numbers[num][3]]);
  servoE.write(onOffPosition[4][numbers[num][4]]);
  servoF.write(onOffPosition[5][numbers[num][5]]);
  servoG.write(onOffPosition[6][numbers[num][6]]);
}

void LedServo::writeServoSeg(ServoSegment ss, int val) {
  switch (ss) {
    case SEG_A:
      servoA.write(val);
      break;
    case SEG_B:
      servoB.write(val);
      break;
    case SEG_C:
      servoC.write(val);
      break;
    case SEG_D:
      servoD.write(val);
      break;
    case SEG_E:
      servoE.write(val);
      break;
    case SEG_F:
      servoF.write(val);
      break;
    case SEG_G:
      servoG.write(val);
      break;
    default:
      break;
  }
}

void LedServo::readCurrentServoPostion(int outputReadServo[7]) {
  outputReadServo[0] = servoA.read();
  outputReadServo[1] = servoB.read();
  outputReadServo[2] = servoC.read();
  outputReadServo[3] = servoD.read();
  outputReadServo[4] = servoE.read();
  outputReadServo[5] = servoF.read();
  outputReadServo[6] = servoG.read();
}
