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
sensors.requestTemperatures();
  Serial.print(" Temperature--> "); Serial.println (sensors.getTempCByIndex(0));   Serial.print(" C ");


}
