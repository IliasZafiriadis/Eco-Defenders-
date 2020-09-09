//Βιβλιοθήκες για την μέτρηση της θερμοκρασίας από τον αισθητήρα μοντέλου DS18B20
#include <DallasTemperature.h>  
#include <OneWire.h>

#define ONE_WIRE_BUS A0   //Θέτω όπου εμφανίζεται ο τίτλος την τιμή Α0

//Ορίζω αντικείμενα και τις ιδιότητές τους, ώστε να μπορέσω να αξιοποιήσω τις παραπάνω βιβλιοθήκες
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);  

#define power 13  //Θέτω όπου εμφανίζεται power την τιμή 13 

bool send_Command = false;  //Πληροφορεί αν έχει σταλλεί εντολή από το android  για να στείλει τις μετρήσεις από τους αισθητήρες
float sensorData1;  //Μετρήσεις από τον αισθητήρα θερμοκρασίας

void setup() {
  Serial.begin(9600); //Εκκίνηση επικοινωνίας μεσώ του bluetooth, των αισθητήρων και του monitor
  sensors.begin();  
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
} 
