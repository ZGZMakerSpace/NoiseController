#include <FastLED.h>


CRGB ledsR[NUM_LEDS];
CRGB ledsY[NUM_LEDS]; 
CRGB ledsG[NUM_LEDS];  

// Control 
void control_spotlight( int semaphore, bool on_off ){
  if( on_off ){
    switch( semaphore ){
      case 1:
        //Encender Luz VERDE
        fill_solid( ledsG, 64, CRGB::Green);
        FastLED.show();
        break;
      case 2: 
         //Encender Luz AMARILLA
    
          fill_solid( ledsY, 64, CRGB::Yellow);
          FastLED.show();
          break;
      case 3:
        //Encender Luz ROJA
        
        fill_solid( ledsR, 64, CRGB::Red);
        FastLED.show();

        if( speaker_on ){
          digitalWrite(SPEAKER, HIGH);
          delay(1000);
          digitalWrite(SPEAKER, LOW);
          delay(1000);
        }
        break;
    }
  }else{
    switch( semaphore ){
      case 1:
        //Apagar Luz VERDE
        fill_solid( ledsG, 64, CRGB::Black);
        FastLED.show();
        break;
      case 2: 
         //Apagar Luz AMARILLA
          fill_solid( ledsY, 64, CRGB::Black);
          FastLED.show();
          if( speaker_on ){
           digitalWrite(SPEAKER, LOW);
          }
          break;
      case 3:
        //Apagar luz ROJA
        
        fill_solid( ledsR, 64, CRGB::Black);
        FastLED.show();
        break;
    }
  }
  
}


void light_micro( float value ){

  if ( value > green_threshold ){
    control_spotlight(1, true );
  }
  
  if(value > yellow_threshold ){
    control_spotlight(2, true );
  }
  
  if(value > red_threshold ){
    control_spotlight(3, true );
  }

  if(value < yellow_threshold ){
    control_spotlight(2, false );
  }

  if(value < red_threshold ){
    control_spotlight(3, false );
  }

  if ( value < green_threshold ){
    control_spotlight(1, false );
  }
}
