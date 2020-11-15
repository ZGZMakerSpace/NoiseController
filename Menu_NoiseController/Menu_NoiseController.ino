#include "configuration.h"

//Valor umbral de cada color
int green_threshold = 20;
int yellow_threshold = 50;
int red_threshold = 60;

int BRIGHTNESS = 10;

#include "micro.h"
#include "lights.h"
#include "menu_def.h"


void setup() {
  pinMode(encBtn,INPUT_PULLUP);
  pinMode(SPEAKER, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Arduino Menu Library");Serial.flush();
  encoder.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PINR>(ledsR, NUM_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PINY>(ledsY, NUM_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PING>(ledsG, NUM_LEDS);  // GRB ordering is assumed
  lcd.begin(20,4);

  nav.showTitle=false;
  lcd.setCursor(0, 0);
  lcd.print("Semaforo acustico");
  lcd.setCursor(0, 1);
  lcd.print("Zaragoza Maker Space");
  FastLED.setBrightness( BRIGHTNESS ); // CONFIGUARACION INICIAL DEL BRILLO MATRICES LED
  delay(2000);
}


void loop() {
    nav.poll();
    float micro_reading = readMicro();

    
    
   if (millis() > refresh_time) {

    Serial.print(micro_reading,4);
    Serial.println();
    light_micro( micro_reading );
    
    refresh_time = millis() + SERIAL_REFRESH_TIME;
  }
}
