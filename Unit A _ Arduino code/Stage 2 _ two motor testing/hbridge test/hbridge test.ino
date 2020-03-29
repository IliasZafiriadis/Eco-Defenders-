#define enA 6
#define in1 5
#define in2 7
#define swt 13


void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(swt, OUTPUT);  
  digitalWrite(swt,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);

}
void loop() {
  analogWrite(enA, 255); 
  delay(2000);
  analogWrite(enA, 0); 
  delay(2000);
  Serial.println("i'm not fine");
}
