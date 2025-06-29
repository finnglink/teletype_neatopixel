// -------------------------------------------------------------------------------------------
// I2C receive and request events
// -------------------------------------------------------------------------------------------
// handler for receiving I2C messages
void i2cReceiveEvent(int count) {
  for(int i=0; i < count; i++) {
    i2cData[i] = Wire.read();  
  }
  received = count;
}

// hanlder for receiving I2C request messages
void i2cRequestEvent() {
}