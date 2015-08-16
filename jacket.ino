#include <FastLED.h>

#define LED_PIN     17
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define PIXEL_COUNT    90

#define BRIGHTNESS  64

CRGB leds[PIXEL_COUNT];

byte newColor[90][3];
byte prevColor[90][3];

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, PIXEL_COUNT);
  FastLED.setCorrection(Typical8mmPixel);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither( 0 );
  FastLED.show();
}

void loop()  {
    for(int pixel = 0;pixel< PIXEL_COUNT;pixel++) {
    boolean done = true;
    for(int i = 0;i < 3;i++) {
      if (newColor[pixel][i] != prevColor[pixel][i]) {
        done = false;
      }
    }
    
    if (done) {
      random16_add_entropy(random());

      newColor[pixel][0] = random8();
      newColor[pixel][1] = random8(200,256);
      newColor[pixel][2] = random8(200,256);
    }
    
    leds[pixel].setHSV(prevColor[pixel][0], prevColor[pixel][1], prevColor[pixel][2]);
    
    for(int i = 0;i < 3;i++) {
      if (newColor[pixel][i] > prevColor[pixel][i]) {
        prevColor[pixel][i]++;
      } else if (newColor[pixel][i] < prevColor[pixel][i]) {
        prevColor[pixel][i]--;
      }
    }
  }
  
  FastLED.show();
 
  FastLED.delay(20);
}
