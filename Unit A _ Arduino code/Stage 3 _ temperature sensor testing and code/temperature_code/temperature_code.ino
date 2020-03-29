#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

#define power 13
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
   Temperature = Temperature/5.0;
  }while(isnan(Temperature));
  temperature = temperature + 1000.0/*bluetooth "id" code */
  Serial.print(" Temperature--> "); Serial.println (Temperature-1000.0);   Serial.print(" C ");
  delay(100);

}
