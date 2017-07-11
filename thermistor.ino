/*
 * Asador de mazorcas - HGL Team
 * Lectura de termistores
 * 2017
*/

#define THERMISTOR1 A0
#define THERMISTOR2 A1

#define THERMISTORNOMINAL 100000
#define TEMPERATURENOMINAL 25   
#define BCOEFFICIENT 4066
#define SERIESRESISTOR 4700    

#define NUMSAMPLES 5

int samples1[NUMSAMPLES];
int samples2[NUMSAMPLES];

float temperature1 = 0;
float temperature2 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t i;
  float average1;
  float average2;
 
  for (i=0; i< NUMSAMPLES; i++) {
   samples1[i] = analogRead(THERMISTOR1);
   samples2[i] = analogRead(THERMISTOR2);
   delay(10);
  }
 
  average1 = 0;
  average2 = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average1 += samples1[i];
     average2 += samples2[i];
  }
  average1 /= NUMSAMPLES;
  average2 /= NUMSAMPLES;
 
  //Serial.println(average1);
  //Serial.println(average2);
 
  // convert the value to resistance
  average1 = 1023 / average1 - 1;
  average1 = SERIESRESISTOR / average1;
  average2 = 1023 / average2 - 1;
  average2 = SERIESRESISTOR / average2;
  //Serial.print("Thermistor resistance "); 
  //Serial.println(average1);
  //Serial.println(average2);

  temperature1 = average1 / THERMISTORNOMINAL;     // (R/Ro)
  temperature1 = log(temperature1);                  // ln(R/Ro)
  temperature1 /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature1 += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature1 = 1.0 / temperature1;                 // Invert
  temperature1 -= 273.15;                         // convert to C

  temperature2 = average2 / THERMISTORNOMINAL;     // (R/Ro)
  temperature2 = log(temperature2);                  // ln(R/Ro)
  temperature2 /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature2 += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature2 = 1.0 / temperature2;                 // Invert
  temperature2 -= 273.15;                         // convert to C

  Serial.print("Temperaturas"); 
  Serial.println(temperature1);
  Serial.println(temperature2);

  delay(1000);
}
