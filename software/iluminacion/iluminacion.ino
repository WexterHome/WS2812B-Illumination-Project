//AL lado de las variables que tengas que cambiar habrán asteriscos (*)

#include <FastLED.h>

#define FRAMES_PER_SECOND 30
#define NUM_EFFECTS 4   
#define NUM_LEDS 256    //**********
#define DATA_PIN 9      //**********
#define COLOR_ORDER GRB


//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;

///////////Efecto twinkleFox///////////////
#define TWINKLE_SPEED 4
#define TWINKLE_DENSITY 5
#define SECONDS_PER_PALETTE  30
#define AUTO_SELECT_BACKGROUND_COLOR 0
#define COOL_LIKE_INCANDESCENT 1
CRGB gBackgroundColor = CRGB::Black; 
CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;
///////////////////////////////////////////

int effect = 0;
bool EffectChanged = false;
bool BrightChanged = false;
int brightness = 50;


void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(brightness);
  for (int dot = 0; dot<NUM_LEDS; dot++){
    leds[dot].setRGB(255, 0, 0);
    FastLED.show();
    delay(5);
  }
  chooseNextColorPalette(gTargetPalette);
  buttonSetup();
}

void loop(){
  buttonController();
  
  if(BrightChanged == true){
    FastLED.setBrightness(brightness);
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot].setRGB(0, 0, 0);
    }
    BrightChanged = false;
  }
  
  if(EffectChanged == true){
    switch(effect){
      case 1:
        pacifica_loop();
        break;

      case 2:
        pride();
        break;

      case 3:
        rgbsetdemo();
        break;

      case 4:
        EVERY_N_SECONDS( SECONDS_PER_PALETTE ) { 
          chooseNextColorPalette( gTargetPalette ); 
        }
        
        EVERY_N_MILLISECONDS( 10 ) {
          nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
        }
        drawTwinkles(leds);
      break;
    }
  }
  
  FastLED.show();
  delay(1000/FRAMES_PER_SECOND);
}
