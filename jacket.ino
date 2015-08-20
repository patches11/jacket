#include <FastLED.h>

#define LED_PIN     17
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define PIXEL_COUNT    90

#define BRIGHTNESS  64

CRGB leds[PIXEL_COUNT];
CHSV colors[PIXEL_COUNT];

#define MODES 2

// mode state defintions
#define RAINBOW 0
#define FIRE 1

byte mode;
boolean cycle_modes;
long cycle_time;
long start_time;

void setup() {
  delay(1000);
  
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, PIXEL_COUNT);
  FastLED.setCorrection(Typical8mmPixel);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither( 0 );
  FastLED.show();
  
  for (int i=0;i<PIXEL_COUNT;i++) {
    colors[i] = CHSV(i*5 % 256, 255, 255);
  }
  
  mode = FIRE;
  cycle_modes = false;
  cycle_time = 30000;
  start_time = millis();
}

void loop()  {
  if (mode == RAINBOW) {
    rainbow(20);
  } else if (mode == FIRE) {
    fire(20);
  }
  
  if (cycle_modes && start_time + cycle_time < millis()) {
    mode = (mode + 1) % MODES;
    start_time = millis();
  }
}
