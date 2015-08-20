#define AMOUNT 7

void rainbow(int wait) {
  byte change = (20*AMOUNT)/wait;
  
  for (int i=0;i<PIXEL_COUNT;i++) {
    colors[i] = CHSV(colors[i].hue + change, 255, 255);
    leds[i] = colors[i];
  }
  
  FastLED.show();
 
  FastLED.delay(wait);
}
