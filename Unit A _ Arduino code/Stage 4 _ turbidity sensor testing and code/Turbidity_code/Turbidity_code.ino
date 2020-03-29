#define power 13

const int TurbiditySensor = A5;

float Turbidity;

void setup() {
Serial.begin(9600);
pinMode(power, OUTPUT);
digitalWrite(power,HIGH); 
}

void loop() {
  do  {
  Turbidity=0;
  for (int i=1; i <= 10; i++) { 
  Turbidity = Turbidity + analogRead(TurbiditySensor);
   delay(100);}
   Turbidity = Turbidity/10.0;
  }while(isnan(Turbidity));

  
  Turbidity= Turbidity  * (5.0 / 1024.0) + 2000.0/*bluetooth "id" code */;
  Serial.print(" Turbididy--> "); Serial.println (Turbidity-2000.0);  Serial.print(" volt ");
  
  delay(100);
}
