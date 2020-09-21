#define ON 1
#define OFF 0
#define Rising 1
#define Lowering 0


const int button = 2;   //**********
bool buttonPressed = false;
int previousEstado = LOW;
unsigned long previousTime = 0;
int threshold = 1200;   //1500
int threshold2 = 400;   //500
int threshold3 = 100;
int buttonCount = 0;
int brightnessDirection = 1;
int lampState = 1;


void buttonSetup(){
  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(button), IntCallback, RISING);
}


void buttonController(){
  if(buttonPressed == true){
    int estado = digitalRead(button);
    if(estado == LOW && estado == previousEstado && (millis()-previousTime) > threshold){
      if(buttonCount == 1){
        if(lampState == OFF){
          brightness = 150;
          BrightChanged = true;
          lampState = ON;
        }

        else{
          brightness = 0;
          BrightChanged = true;
          lampState = OFF;
        }
        Serial.print("Enceder/Apagar: ");
        Serial.println(lampState);
      }

      else if(buttonCount == 2){
        EffectChanged = true;
        if(effect < NUM_EFFECTS){
          effect += 1;
        }
        else{
          effect = 1;
        }
        Serial.println("Siguiente efecto");
      }

      else if(buttonCount >=3){
        EffectChanged = true;
        if(effect > 1){
          effect -= 1;
        }
        else{
          effect = NUM_EFFECTS;
        }
        Serial.println("Efecto anterior");
      }
      
      Serial.println("Stop Pressing");
      attachInterrupt(digitalPinToInterrupt(button), IntCallback, RISING);
      buttonPressed = false;
      buttonCount = 0;
      //break;
    }

    else if(estado == HIGH && estado != previousEstado && (millis()-previousTime) > threshold3){
      buttonCount += 1;
      previousTime = millis();
    }
    previousEstado = estado;
  }
}


void IntCallback(){
 //tickerObject.attach(10, callback);     //Reinicia la interrupción si antes ya estaba activada
 buttonPressed = true;
 buttonCount = 1;
 previousTime = millis();
 Serial.println("Interrupción");
 detachInterrupt(digitalPinToInterrupt(button));
}
