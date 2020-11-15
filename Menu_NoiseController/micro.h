#include <SimpleKalmanFilter.h>

//Control señal de ruido mediante Fitro Kalman 
//Speaker Config
bool speaker_on = true;
long refresh_time;

SimpleKalmanFilter simpleKalmanFilter(kalman_measure, kalman_estimation, kalman_variance);

float readMicro(){
   unsigned long startMillis= millis();
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // Recopilar durante la ventana
   unsigned int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
      
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // Actualizar máximo
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // Actualizar mínimo
         }
      }
   }
   unsigned int peakToPeak = signalMax - signalMin;  // Amplitud del sonido
   double volts = (peakToPeak * 100.0) / 1024;  // Convertir a tensión
   float estimated_value = simpleKalmanFilter.updateEstimate(volts);
   return estimated_value;
}
