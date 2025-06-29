#include <Wire.h>
#include <FastLED.h>

// I2C
#define MEM_LEN 256                // save I2C data in 8 bit chunks
uint8_t i2cData[MEM_LEN];           // save I2C data in variable "i2cData"
volatile uint8_t received;          // variable to store if there are received I2C messages
void i2cReceiveEvent(int count); // function for receiving I2C messages, count = number of bites
void i2cRequestEvent(void);         // function for receiving I2C messages, count = number of bites

// I2C Address
//  i2c2midi acts as a I2C follower and listens to messages on address 0x45 (69).
#define I2C_ADDRESS 0x45

// parameters set by OPs
int pixel = 0;              
int red = 0;                         
int green = 0;                         
int blue = 0;                          

int brightness = 50;

#define NUM_LEDS 12
#define LED_PIN 5
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// -------------------------------------------------------------------------------------------
// SETUP
// -------------------------------------------------------------------------------------------


void setup() {
  Serial.begin(115200);
  Serial.println("Serial OK");

  Wire.begin(I2C_ADDRESS);  
  Serial.print("I2C initialized: ");

  received = 0;                                    // i2c data initalize
  memset(i2cData, 0, sizeof(i2cData));             // save I2C data in memory
  Wire.onReceive(i2cReceiveEvent);
  //Wire.onRequest(i2cRequestEvent);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear(true);
  FastLED.setBrightness(brightness);
  FastLED.show();

}

// -------------------------------------------------------------------------------------------
// LOOP
// -------------------------------------------------------------------------------------------

void loop() {
  // I2C   
  if(received) {                                
    Serial.print(received); 
    Serial.print(" bytes received: ");
    for (int i = 0; i < received; i++) {
      Serial.print(i2cData[i]);
      Serial.print(" ");
    }
    Serial.println("");


    opFunctions(false, i2cData);                   // call the respective OP with isRequest = false
    received = 0;                                  // reset back to 0
  }

  if (!received) {
    if (Wire.available()) {
      Serial.print("[DEBUG] Wire.available() = ");
      Serial.println(Wire.available());

      while (Wire.available()) {
        int b = Wire.read();
        Serial.print(b);
      }
    }
  }
}