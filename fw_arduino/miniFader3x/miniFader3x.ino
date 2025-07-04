#include <Wire.h>

//#define MF1 2
//#define MF2 3
//#define MF3 4
int MF_PINS[] = {2, 3, 4};
int faderNum = 0;
int faderValue = 0;

void i2cReceiveEvent(int count);
void i2cRequestEvent(void);         

#define I2C_ADDRESS 0x46

void i2cReceiveEvent(int count) {
  if (count == 1) {
    faderNum = Wire.read();
    //Serial.println(faderNum);
    faderValue = map(analogRead(MF_PINS[faderNum]), 0, 4096, 0, 16383);
    count = 0;
  }
  else {
    return;
  }
}

void i2cRequestEvent() {
  Wire.write(faderValue >> 8);
  Wire.write(faderValue & 255);
  //Serial.print('\n');
  Serial.print("Wrote Fader Value: ");
  Serial.println(faderValue);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS, 6, 7, 400000);
  delay(1000);
  Serial.println("I'm alive");
  Wire.onReceive(i2cReceiveEvent);
  Wire.onRequest(i2cRequestEvent);
}

void loop() {

}