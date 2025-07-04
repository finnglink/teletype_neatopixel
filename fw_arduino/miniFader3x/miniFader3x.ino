#include <Wire.h>
#include <ResponsiveAnalogRead.h>

int MF_PINS[] = {2, 3, 4};

ResponsiveAnalogRead analog1(MF_PINS[0], true, 0.5);
ResponsiveAnalogRead analog2(MF_PINS[1], true, 0.5);
ResponsiveAnalogRead analog3(MF_PINS[2], true, 0.5);

int faderNum = 0;
int faderValue = 0;
int rawValue = 0;
static int lastValue = 0;

void i2cReceiveEvent(int count);
void i2cRequestEvent(void);         

#define I2C_ADDRESS 0x46

void i2cReceiveEvent(int count) {
  if (count == 1) {
    faderNum = Wire.read();
    if (faderNum == 0) {
      rawValue = analog1.getValue();
    }
    else if (faderNum == 1) {
      rawValue = analog2.getValue();
    }
    else if (faderNum == 2) {
      rawValue = analog3.getValue();
    }
  }
  else {
    return;
  }
  faderValue = map(rawValue, 0, 4096, 0, 16383);
  count = 0;
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
  analog1.update();
  analog2.update();
  analog3.update();
}