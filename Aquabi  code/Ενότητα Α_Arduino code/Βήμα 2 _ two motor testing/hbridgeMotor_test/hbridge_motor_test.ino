// Πηγή:https://www.instructables.com/id/How-to-Use-L298n-to-Control-Dc-Motor-With-Arduino/
int in1 = 9;  
int in2 = 8; 
void setup() {
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
}

void TurnMotorA(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void TurnOFFA(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void TurnMotorA2(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}
void loop() {
  TurnMotorA(); 
  delay(3000);
  TurnOFFA();
  delay(2000);
  TurnMotorA2(); 
  delay(3000);
  TurnOFFA();
  delay(2000);
}
