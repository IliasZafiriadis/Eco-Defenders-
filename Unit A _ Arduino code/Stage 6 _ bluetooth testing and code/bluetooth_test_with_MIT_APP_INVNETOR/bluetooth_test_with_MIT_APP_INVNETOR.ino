#include <SoftwareSerial.h>
SoftwareSerial Arduino(9,8);

int RecievedValue2=0;
int RecievedValue3=0;
String answer;
bool send_Command = false;
int data;

void setup() {
Serial.begin(9600);
Arduino.begin(9600);
}

void loop() {
while (Arduino.available()) {
delay(10);  
if (Arduino.available() >0) {
answer += char( Arduino.read()); //makes the string answer
 }
}

 if(answer!=""){
 data = answer.toInt();
 Serial.println(data);

if (data == 5){Arduino.println("fine");}
delay(20);
if (data == 1000){
send_Command = true;
Serial.print(send_Command);
Serial.println("ok");
Arduino.println("ok");     }                     // command to retrieve sensor data from I2C BUS and send them via buetooth to the mediator phone.
else{
send_Command = false;
//Serial.println("nope");
delay(10);}


if (data >=2000 && data <=2255){
  RecievedValue2 = data-2000; 
// power for thruster 1.
Serial.print("x"); Serial.println(RecievedValue2); Serial.print(" | ");
Arduino.println(RecievedValue2);
delay(20);}

else if (data >=3000 && data <=3510){
  RecievedValue3 = data-3255; 
// power for thruster 2.
Serial.print(" y "); Serial.print(RecievedValue3);Serial.print(" | ");
Arduino.println(RecievedValue3); 
delay(20);}
 
   answer="";
 } 
}
