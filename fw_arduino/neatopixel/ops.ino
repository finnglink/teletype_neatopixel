// -------------------------------------------------------------------------------------------
// OPs
// -------------------------------------------------------------------------------------------

void opFunctions(bool isRequest, uint8_t data[]) {
  uint8_t op = data[0];
  switch (op) {
    case 1:                    op_NP_C(data);      break;
    case 2:                    op_NP_A(data);      break;
    case 3:                    op_NP_AH(data);     break;
    case 4:                    op_NP_P(data);      break;
    case 5:                    op_NP_PH(data);     break;
    case 6:                    op_NP_B(data);      break;
  }
}
// -------------------------------------------------------------------------------------------

void op_NP_C(uint8_t data[]) { 
  FastLED.clear(true);
}

void op_NP_A(uint8_t data[]) { 
  const int8_t red = data[1];
  const int8_t green = data[2];
  const int8_t blue = data[3];
  controlLeds(-1, red, green, blue);
}

void op_NP_AH(uint8_t data[]) { 
  const int8_t hue = data[1];
  const int8_t sat = data[2];
  const int8_t val = data[3];
  controlLedsHSV(-1, hue, sat, val);
}

void op_NP_P(uint8_t data[]) { 
  const int8_t pixel = data[1];
  const int8_t red = data[2];
  const int8_t green = data[3];
  const int8_t blue = data[4];
  controlLeds(pixel, red, green, blue);
}

void op_NP_PH(uint8_t data[]) { 
  const int8_t pixel = data[1];
  const int8_t hue = data[2];
  const int8_t sat = data[3];
  const int8_t val = data[4];
  controlLedsHSV(pixel, hue, sat, val);
}

void op_NP_B(uint8_t data[]) { 
  const int8_t brightness = data[1];
  FastLED.setBrightness(brightness);
  FastLED.show();
}
