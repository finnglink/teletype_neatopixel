void controlLeds(int pixel, int red, int green, int blue) { 
 if (pixel == -1){
  fill_solid(leds, NUM_LEDS, CRGB(red, green, blue)); //if pixel is -1, control all
 }
 else if (pixel > -1){
  leds[pixel] = CRGB(red, green, blue); //if pixel is 0 or larger, control pixels individually
 }
 FastLED.show();
}

void controlLedsHSV(int pixel, int hue, int sat, int val) { 
 if (pixel == -1){
  fill_solid(leds, NUM_LEDS, CHSV(hue, sat, val)); //if pixel is -1, control all
 }
 else if (pixel > -1){
  leds[pixel] = CHSV(hue, sat, val); //if pixel is 0 or larger, control pixels individually
 }
 FastLED.show();
}