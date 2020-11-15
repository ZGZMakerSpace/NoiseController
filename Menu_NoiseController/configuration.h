#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

  #define DATA_PINR    22
  #define DATA_PING    23
  #define DATA_PINY    24
  #define NUM_LEDS    64


  #define LED_TYPE    WS2811
  #define COLOR_ORDER GRB
  #define SPEAKER 25
  
  // LCD /////////////////////////////////////////
  #define RS 2
  #define EN 3
  #define LCDPIN_4 4
  #define LCDPIN_5 5
  #define LCDPIN_6 6
  #define LCDPIN_7 7

  // Encoder /////////////////////////////////////
  #define encA 10
  #define encB 11
  //this encoder has a button here
  #define encBtn 12
  
  
  // Microphone /////////////////////////////////////
  #define sensorPIN A0
  #define sampleWindow 50 // Ancho ventana en mS (50 mS = 20Hz)
  
  // Serial output refresh time
  #define SERIAL_REFRESH_TIME 100

  // Kalman Filter /////////////////////////////////////
  //Measurement Uncertainty - How much do we expect to our measurement vary
  #define kalman_measure 100
  
  //Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value
  #define kalman_estimation 50
  
  //Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
  #define kalman_variance 0.5

  
#endif // _CONFIGURATION_H
