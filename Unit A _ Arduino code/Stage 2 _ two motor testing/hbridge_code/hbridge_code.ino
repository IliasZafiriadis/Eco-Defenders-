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
void setup() {
Serial.begin(9600);
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
}

void loop() {
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

}
