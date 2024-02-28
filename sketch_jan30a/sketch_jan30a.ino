  #include "LedServo.h"
  #include <Wire.h>
  // check push
  /* Địa chỉ của DS1307 */
  const byte DS1307 = 0x68;
  /* Số byte dữ liệu sẽ đọc từ DS1307 */
  const byte NumberOfFields = 7;
  
  /* khai báo các biến thời gian */
  int second, minute, hour, day, wday, month, year;

  LedServo ledservo;
  LedServo ledservo2;
  LedServo ledservo3;
  LedServo ledservo4;

  int giay = 0;
  int phut = 0;

  void testCountServo(LedServo& lsv, unsigned int wait = 1000);

  void setup() {
    ledservo.init(12, 11, 10, 9, 8, 7, 6);
    ledservo2.init(A0, A1, A2, A3, A4, A5, A6);
    ledservo3.init( 41, 43, 45, 47, 49, 51, 53);
    ledservo4.init( 25, 27, 29, 31, 33, 35, 37);
    delay(1000);
    Serial.begin(9600);
    Wire.begin();
    /* cài đặt thời gian cho module */
    //setTime(14, 44, 00, 6, 2, 2, 24); // 12:30:45 CN 08-02-2015
    Serial.println("Started...........");
  }

  void loop() {

      /* Đọc dữ liệu của DS1307 */
      readDS1307();
      /* Hiển thị thời gian ra Serial monitor */
      digitalClockDisplay();
      showLegServoTime();

      // testCountServo(ledservo,1);
      // testCountServo2(ledservo2,1);
      // testCountServo3(ledservo3, 1);
      // testCountServo4(ledservo4, 1);
      /*giay++;  
      if (giay == 60)phut++;
      giay %= 60;
      phut % 60;
      delay(1000);*/
    //delay(1000);
  }

  void showLegServoTime(){
    ledservo.displayNumber(hour/10);
    ledservo2.displayNumber(hour%10);
    ledservo3.displayNumber(minute/10);
    ledservo4.displayNumber(minute%10);
    delay(2000);
  }

  /*void readServo() {
    int readServo[7] = { 0 };
    ledservo.readCurrentServoPostion(readServo);
    if(phut < 10 )Serial.print('0');
    Serial.print(phut);
    Serial.print(" : ");
    if(giay < 10 )Serial.print('0');
    Serial.print(giay);
    Serial.println();
  }*/

  void readDS1307()
  {
          Wire.beginTransmission(DS1307);
          Wire.write((byte)0x00);
          Wire.endTransmission();
          Wire.requestFrom(DS1307, NumberOfFields);
          
          second = bcd2dec(Wire.read() & 0x7f);
          minute = bcd2dec(Wire.read() );
          hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
          wday   = bcd2dec(Wire.read() );
          day    = bcd2dec(Wire.read() );
          month  = bcd2dec(Wire.read() );
          year   = bcd2dec(Wire.read() );
          year += 2000;    
  }

  /* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
  int bcd2dec(byte num)
  {
          return ((num/16 * 10) + (num % 16));
  }
  /* Chuyển từ Decimal sang BCD */
  int dec2bcd(byte num)
  {
          return ((num/10 * 16) + (num % 10));
  }

  void digitalClockDisplay(){
      // digital clock display of the time
      Serial.print(hour);
      printDigits(minute);
      printDigits(second);
      Serial.print(" ");
      Serial.print(day);
      Serial.print(" ");
      Serial.print(month);
      Serial.print(" ");
      Serial.print(year); 
      Serial.println(); 
  }

  void printDigits(int digits){
      // các thành phần thời gian được ngăn chách bằng dấu :
      Serial.print(":");
          
      if(digits < 10)
          Serial.print('0');
      Serial.print(digits);
  }

  /* cài đặt thời gian cho DS1307 */
  void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
  {
          Wire.beginTransmission(DS1307);
          Wire.write(byte(0x00)); // đặt lại pointer
          Wire.write(dec2bcd(sec));
          Wire.write(dec2bcd(min));
          Wire.write(dec2bcd(hr));
          Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
          Wire.write(dec2bcd(d)); 
          Wire.write(dec2bcd(mth));
          Wire.write(dec2bcd(yr));
          Wire.endTransmission();
  }


  void testCountServo3(LedServo& lsv, unsigned int wait) {
      lsv.displayNumber(int(minute/10));
      //readServo();
      delay(wait);
    }
  void testCountServo4(LedServo& lsv, unsigned int wait) {
      lsv.displayNumber(minute % 10);
      //readServo();
      delay(wait);
  }
  void testCountServo(LedServo& lsv, unsigned int wait){
    lsv.displayNumber(int ( hour / 10));
    //readServo();
    delay(wait);
  }
  void testCountServo2(LedServo& lsv, unsigned int wait){
    lsv.displayNumber(hour % 10);
    //readServo();
    delay(wait);
  }
  void testOnAllServo() {
    ledservo.writeServoSeg(SEG_A, ledservo.onOffPosition[0][ON_LED]);
    ledservo.writeServoSeg(SEG_B, ledservo.onOffPosition[1][ON_LED]);
    ledservo.writeServoSeg(SEG_C, ledservo.onOffPosition[2][ON_LED]);
    ledservo.writeServoSeg(SEG_D, ledservo.onOffPosition[3][ON_LED]);
    ledservo.writeServoSeg(SEG_E, ledservo.onOffPosition[4][ON_LED]);
    ledservo.writeServoSeg(SEG_F, ledservo.onOffPosition[5][ON_LED]);
    ledservo.writeServoSeg(SEG_G, ledservo.onOffPosition[6][ON_LED]);
    //readServo();
    delay(2000);
  }

  void testOffAllServo() {
    ledservo.writeServoSeg(SEG_A, ledservo.onOffPosition[0][OFF_LED]);
    ledservo.writeServoSeg(SEG_B, ledservo.onOffPosition[1][OFF_LED]);
    ledservo.writeServoSeg(SEG_C, ledservo.onOffPosition[2][OFF_LED]);
    ledservo.writeServoSeg(SEG_D, ledservo.onOffPosition[3][OFF_LED]);
    ledservo.writeServoSeg(SEG_E, ledservo.onOffPosition[4][OFF_LED]);
    ledservo.writeServoSeg(SEG_F, ledservo.onOffPosition[5][OFF_LED]);
    ledservo.writeServoSeg(SEG_G, ledservo.onOffPosition[6][OFF_LED]);
    //readServo();
    delay(2000);
  }