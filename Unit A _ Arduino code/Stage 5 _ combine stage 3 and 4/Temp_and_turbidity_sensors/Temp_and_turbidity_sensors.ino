#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

#define power 13

const int TurbiditySensor = A5;

float Turbidity;
float Temperature;

void setup() {
Serial.begin(9600);
sensors.begin();
pinMode(power, OUTPUT);
digitalWrite(power,HIGH); 
}

void loop() {
  do  {
  Temperature=0;
  for (int i=1; i <= 5; i++) { 
   sensors.requestTemperatures();
   Temperature = Temperature + sensors.getTempCByIndex(0);
   delay(100);}
   Temperature = Temperature/5.0 + 1000.0/*bluetooth "id" code */;
  }while(isnan(Temperature));

 
  Serial.print(" Temperature--> "); Serial.println (Temperature-1000.0);
   
   do  {
  Turbidity=0;
  for (int i=1; i <= 10; i++) { 
  Turbidity = Turbidity + analogRead(TurbiditySensor);
   delay(100);}
   Turbidity = Turbidity/10.0;
  }while(isnan(Turbidity));

  
  Turbidity= Turbidity  * (5.0 / 1024.0) + 2000.0/*bluetooth "id" code */;
  Serial.print(" Turbididy--> "); Serial.println (Turbidity-2000.0);
  
  delay(100);
  } 
