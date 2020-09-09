#define power 13  //Θέτω όπου εμφανίζεται power την τιμή 13 
void setup() {
  pinMode(power, OUTPUT);//Ορίζω το pin ως εξόδους
  digitalWrite(power, LOW); //Μηδενίζω  , αρχικά, την τάση που λαμβάνουν οι αισθητήρες
}
void loop() {
  digitalWrite(power, HIGH);    // Μεγιστοποιώ  την τάση (5V).
  delay(1000);                       // Περιμένω 1 δευτερόλεπτο.
  digitalWrite(power, LOW);     // Μηδενίζω  την τάση (0V).
  delay(1000);                       // Περιμένω 1 δευτερόλεπτο.
}
