int CONT = 0;

void rgbsetdemo(){
  static uint8_t hue;  
  // fade everything out
  leds.fadeToBlackBy(40);

  // let's set an led value
  leds[CONT] = CHSV(hue++,255,255);

  // now, let's first 20 leds to the top 20 leds, 
  leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);
  FastLED.delay(33);

  CONT++;
  
  if(CONT == NUM_LEDS/2){
    CONT = 0;
  }
}
