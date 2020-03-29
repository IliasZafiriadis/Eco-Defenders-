#define power 13

const int TurbiditySensor = A5;

float Turbidity;

void setup() {
Serial.begin(9600);

pinMode(power, OUTPUT);
digitalWrite(power,HIGH); 
}

void loop() {   
  Turbidity= analogRead(TurbiditySensor)  * (5.0 / 1024.0) + 2000.0/*bluetooth "id" code */;
  Serial.print(" Turbididy--> "); Serial.println (Turbidity-2000.0);
  delay(100);
  } 
