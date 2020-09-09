#define power 13  //Θέτω όπου εμφανίζεται power την τιμή 13 
#define sensor3 A1  //Θέτω όπου εμφανίζεται sensor3 την τιμή Α1 (pH)

//Δεδομένα
float sensorData3;  //Μετρήσεις από τον αισθητήρα pH
bool send_Command = false;  //Πληροφορεί αν έχει σταλλεί εντολή από το android  για να στείλει τις μετρήσεις από τους αισθητήρες

//Μεταβλητές για την εύρεση του pH 
unsigned long int avgValue; 
int buf[10], temp;  

void setup() {
  Serial.begin(9600); //Εκκίνηση επικοινωνίας μεσώ του bluetooth, των αισθητήρων και του monitor
   //Ορίζω το pin ως έξοδο
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
    delay(100);  }  //Περιμένω 1/10 του λεπτού
}
void get_sensorData_Raw_And_Send_Phone() {  //============Διαδικασία για την απολαβή των μετρήσεων και την αποστολή τους στη συσκευή android============
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
