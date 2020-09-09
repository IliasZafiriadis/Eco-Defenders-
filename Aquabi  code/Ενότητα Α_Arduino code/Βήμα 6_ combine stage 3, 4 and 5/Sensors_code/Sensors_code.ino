//Βιβλιοθήκες για την μέτρηση της θερμοκρασίας από τον αισθητήρα μοντέλου DS18B20
#include <DallasTemperature.h>  
#include <OneWire.h>  

#define ONE_WIRE_BUS A0   //Θέτω όπου εμφανίζεται ο τίτλος την τιμή Α0
//Ορίζω αντικείμενα και τις ιδιότητές τους, ώστε να μπορέσω να αξιοποιήσω τις παραπάνω βιβλιοθήκες
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire); 

#define power 13  //Θέτω όπου εμφανίζεται power την τιμή 13 
#define sensor3 A1  //Θέτω όπου εμφανίζεται sensor3 την τιμή Α1 (pH)
#define sensor2 A2  //Θέτω όπου εμφανίζεται sensor2 την τιμή Α2 (Θολερότητα)

//Δεδομένα
bool send_Command = false;  //Πληροφορεί αν έχει σταλλεί εντολή από το android  για να στείλει τις μετρήσεις από τους αισθητήρες
float sensorData1;  //Μετρήσεις από τον αισθητήρα θερμοκρασίας
float sensorData2;  //Μετρήσεις από τον αισθητήρα θολερότητας
float sensorData3;  //Μετρήσεις από τον αισθητήρα pH
//Μεταβλητές για την εύρεση του pH 
unsigned long int avgValue; 
int buf[10], temp;  

void setup() {
  Serial.begin(9600); //Εκκίνηση επικοινωνίας μεσώ του bluetooth, των αισθητήρων και του monitor
  sensors.begin();  
  //Ορίζω αυτά τα pin ως εξόδους
  pinMode(power, OUTPUT);
  digitalWrite(power, LOW); //Μηδενίζω  , αρχικά, την τάση που λαμβάνουν οι αισθητήρες
}

void loop() {
    if (send_Command) { //Αν έχει ληφθεί εντολή αποστολής δεδομένων, 
    digitalWrite(power, HIGH);  //Ανοίγω την τάση για τους αισθητήρες,
    delay(40);  //Περιμένω 40 χιλιοστά του δευτερολέπτου,
    get_sensorData_Raw_And_Send_Phone();  //Παίρνω  τις μετρήσεις από τους αισθητήρες θερμοκρασίας, θολερότητας και turbidity
    delay(10);  //Περιμένω  10 χιλιοστά του δευτερολέπτου
    digitalWrite(power, LOW);   } //Μηδενίζω  την τάση.
    delay(100); //Περιμένω 1/10 του λεπτού
}

void get_sensorData_Raw_And_Send_Phone() {  //============Διαδικασία για την απολαβή των μετρήσεων και την αποστολή τους στη συσκευή android============
  /*Παίρνω 5 συνεχόμενες μετρήσεις (με 10 χιλιοστά του δευτερολέπτου διαφορά) από τον αισθητήρα θερμοκρασίας,
  τις αθροίζω, στην μεταβλητή sensorData1 και βγάζω τον μέσο όρο. 
  Όσο ο μέσος όρος δεν είναι αριθμός (δηλαδή έγινε σφάλμα), 
  επαναλαμβάνω αυτή τη διαδικασία.*/
  do  { 
    sensorData1 = 0;  
    for (int i = 1; i <= 5; i++) {  
      sensors.requestTemperatures();  
      sensorData1 = sensorData1 + sensors.getTempCByIndex(0); 
      delay(10);  
    } 
    sensorData1 = sensorData1 / 5.0;  
  } while (isnan(sensorData1)); 
  
  
  sensorData1 = sensorData1 + 1000.0; //Πρόσθετω σε αυτήν γνωστό αριθμό, 1000, ώστε να αλλάξει το πεδίο ορισμού του αισθητήρα και το πρόγραμμα android να την ξεχωρίζει.
  Serial.print(" --> "); Serial.println (sensorData1 - 1000.0); //Πρόβαλλω την μέτρηση από τον αισθητήρα θερμοκρασίας στο monitor
  delay(30);  //Περιμένω 30 χιλιοστά  του δευτερολέπτου.
  
  /*Παίρνω 5 συνεχόμενες μετρήσεις (με 10 χιλιοστά του δευτερολέπτου διαφορά) από τον αισθητήρα θολερότητας,
    τις αθροίζω, στην μεταβλητή sensorData2 και βγάζω τον μέσο όρο. 
    Όσο ο μέσος όρος δεν είναι αριθμός (δηλαδή έγινε σφάλμα), 
    επαναλαμβάνω αυτή τη διαδικασία.*/
  do  { 
    sensorData2 = 0;  
    for (int i = 1; i <= 10; i++) { 
      sensorData2 = sensorData2 + analogRead(sensor2);  
      delay(50);  } 
    sensorData2 = sensorData2 / 10.0; 
  } while (isnan(sensorData2)); 
  
  delay(500);   //Περιμένω μισό δευτερόλεπτο.
  sensorData2 = sensorData2 * (5.0 / 1024.0) + 2000.0; //Ορίζω ως μονάδα μέτρησης της θελερότητας το 1V (volt) και προσθέτω 2000, ώστε να αλλάξει το πεδίο ορισμού του αισθητήρα με στόχο, το πρόγραμμα android να την ξεχωρίζει.
  
  
  Serial.print(" !--> "); Serial.println (sensorData2-2000.0);  //Πρόβαλλω την μέτρηση από τον αισθητήρα θολερότητας στο monitor.
  delay(500); //Περιμένω μισό δευτερόλεπτο.
   
  sensorData3 = find_pH(sensor3) + 3000.0; /*Εκτελώ τη διαδικασία find_pH για να πάρω μέτρηση από τον αισθητήρα pH
  και προσθέτω σε αυτήν γνωστό αριθμό, 1000, 
  ώστε να αλλάξει το πεδίο ορισμού του αισθητήρα και 
  το πρόγραμμα android να την ξεχωρίζει.*/
   
  Serial.print(" ->-> "); Serial.println (sensorData3 - 3000.0);  //Πρόβαλλω την μέτρηση από τον αισθητήρα pH στο monitor.
  delay(400); //Περιμένω 4/10 του δευτερολέπτου.
  
} 

float find_pH (int sensor_pin) {// ============Διαδικασία για να βρεθεί μία ακριβή μέτρηση από τον αισθητήρα pH============
  /*Πηγή: https://circuitdigest.com/microcontroller-projects/arduino-ph-meter, με πρόσθετη, μία ενέργεια. */
  
  for (int i = 0; i < 10; i++)  
  { 
    buf[i] = analogRead(sensor_pin);  
    delay(10);  
  } 
  for (int i = 0; i < 9; i++) 
  { 
    for (int j = i + 1; j < 10; j++)  
    { 
      if (buf[i] > buf[j])  
      { 
        temp = buf[i];  
        buf[i] = buf[j];  
        buf[j] = temp;  
      } 
    } 
  } 
  avgValue = 0; 
  for (int i = 2; i < 8; i++) 
    avgValue += buf[i]; 
  float pHVol = (float)avgValue * 5.0 / 1024 / 6; 
  float phValue = -5.70 * pHVol + 21.34;  //Ρυθμίζω την τιμή βάσει των σφαλμάτων του αισθητήρα.
  delay(20);  
  return phValue; 
} 
