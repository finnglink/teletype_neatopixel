#include <Wire.h>

//#define MF1 2
//#define MF2 3
//#define MF3 4
int MF_PINS[] = {2, 3, 4};
int faderNum = 0;
int faderValue = 0;

#define MEM_LEN 256    
uint8_t i2cData[MEM_LEN];       
volatile uint8_t received;   
void i2cReceiveEvent(int count);
void i2cRequestEvent(void);         

#define I2C_ADDRESS 0x46

void i2cReceiveEvent(int count) {
  if (count == 1) {
    faderNum = Wire.read();
    Serial.println(faderNum);
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
  Serial.printf("Wrote Fader Value: %i", faderValue);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS, 6, 7, 400000);

  received = 0;                                    // i2c data initalize
  memset(i2cData, 0, sizeof(i2cData));             // save I2C data in memory
  Wire.onReceive(i2cReceiveEvent);
  Wire.onRequest(i2cRequestEvent);


}

void loop() {

}