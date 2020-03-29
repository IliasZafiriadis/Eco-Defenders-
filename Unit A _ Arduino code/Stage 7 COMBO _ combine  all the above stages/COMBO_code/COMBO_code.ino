#include <SoftwareSerial.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS A0

SoftwareSerial Arduino(9,10);
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

#define power 13
const int sensor2 = A5;

String answer;
bool send_Command = false;
int data;

float sensorData1;
float sensorData2;

int RecievedValue2=0;
int RecievedValue3=0;

// Motor A connections
int enA =6;
int in1 = 7;
int in2 = 5;
//motorB connections 
int enB=3;
int in3=2;
int in4=4;
int Speed;

void setup(){//________________________________MAIN__PROCEDURE___________________________________
Serial.begin(9600);
Arduino.begin(9600);
sensors.begin(); 
pinMode(power, OUTPUT);
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
digitalWrite(power,LOW);
}

void loop(){//________________________________MAIN__PROCEDURE___________________________________
get_SpeedDataAndCommands_Phone ();
 if (send_Command){
   digitalWrite(power, HIGH);
   delay(40);
   get_sensorData1_Raw_And_Send_Phone();
   delay(10);
   digitalWrite(power, LOW);
  }
 Reset();
 send_ControllerData_SpeedControllers();
delay(100);

}


void get_SpeedDataAndCommands_Phone (){//______________________________________PROCEDURE___________________________________
while (Arduino.available()) {
delay(10);  
if (Arduino.available() >0) {
answer += char( Arduino.read());
//Serial.print(answer);//makes the string answer
 }
}

 if(answer!=""){
 data = answer.toInt();
//Serial.println(data);

if (data == 5){Arduino.println("fine"); Serial.println("Fine!");}
delay(20);
if (data == 1000){
send_Command = true;
//Serial.print(send_Command);
Serial.println("ok");
Arduino.println("ok");     }                     // command to retrieve sensor data from I2C BUS and send them via buetooth to the mediator phone.
else{
send_Command = false;
//Serial
Serial.println("nope");
delay(10);}


if (data >=2000 && data <=2255){
  RecievedValue2 = data-2000; 
// power for thruster 1.
//Serial.print("x");
//Serial.println(RecievedValue2);
//Arduino.println(RecievedValue2);
delay(20);}

else if (data >=3000 && data <=3510){
  RecievedValue3 = data-3255; 
// power for thruster 2.
//Arduino.println(RecievedValue3);Serial.print(" y "); Serial.print(RecievedValue3);Serial.print(" | ");
delay(20);}
 
   answer="";
 } 
}
void Reset(){// ______________________________________PROCEDURE___________________________________
send_Command=false;
}

void get_sensorData1_Raw_And_Send_Phone(){//______________________________________PROCEDURE___________________________________

  do  {
  sensorData1=0;
  for (int i=1; i <= 5; i++) { 
   sensors.requestTemperatures();
   sensorData1 = sensorData1 + sensors.getTempCByIndex(0);
   delay(10);}
   sensorData1 = sensorData1/5.0;
  }while(isnan(sensorData1));

  
  sensorData1= sensorData1 + 1000.0; //turbifity  
  Serial.print(" --> "); Serial.println (sensorData1-1000.0);
  delay(50); 
  Arduino.print (String(round(sensorData1 * 100.0), HEX));
   
   do  {
  sensorData2=0;
  for (int i=1; i <= 10; i++) { 
  sensorData2 = sensorData2 + analogRead(sensor2);
   delay(100);}
   sensorData2 = sensorData2/10.0;
  }while(isnan(sensorData2));

  delay(200);
  
  sensorData2= sensorData2  * (5.0 / 1024.0) + 2000.0; //temperature  
  Serial.print(" !--> "); Serial.println (sensorData2-2000);
  Arduino.print (String(round(sensorData2 * 100.0), HEX));
  
  delay(400);
  Arduino.print (String(round(5 * 100.0), HEX));} 

void send_ControllerData_SpeedControllers(){// ______________________________________PROCEDURE___________________________________
int motorA;
int motorB;
boolean rotation;

if (isnan(RecievedValue2)){ RecievedValue2=0;}
if (isnan(RecievedValue3)){ RecievedValue3=0;}

if (RecievedValue3<=0){ Speed = RecievedValue3*(-1); digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); rotation=false;}
if (RecievedValue3>0){Speed = RecievedValue3; digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); rotation=true;}

if (RecievedValue2>=128){ motorA= map ( 128*Speed , 0 , 128*255 /*32640*/, 0 , 255); }
else if (RecievedValue2<128){ motorA= map ( RecievedValue2*Speed , 0 , 128*255 /*32640*/ , 0 , 255); }

if (255-RecievedValue2>=128){motorB= map ( 128*Speed , 0 , 128*255 /*32640*/ , 0 , 255);}
else if (255-RecievedValue2<128){motorB= map ( (255-RecievedValue2)*Speed , 0 , 128*255 /*32640*/ , 0 , 255);}

analogWrite(enA,motorA);
analogWrite(enB,motorB);
Serial.print(motorA); Serial.print(" A ||  "); Serial.print(motorB); Serial.print(" B | ");
if (!rotation){Serial.println("Backwards");} else if (rotation){Serial.println("Forward");}
/*Arduino.print(motorA); Arduino.print(" A ||  "); Arduino.print(motorB); Arduino.print(" B | ");
if (!rotation){Arduino.println("Backwards");} else if (rotation){Arduino.println("Forward");}*/

}
