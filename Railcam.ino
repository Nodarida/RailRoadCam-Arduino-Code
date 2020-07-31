int ir_pin = 4;
int hitObject = false;
int reedPin = 7;
int hitReed = false;
int motor = 2;
int turnmotor = 3;
int counter = 0;
int Home = 0; // für die variable noch serielle verbindung schreiben ausm frontend
int fahrerlaubnis = 1; // für faherlaubnis go command ausm fronend
int positionP = 5;
//int eingabeSerial = 0;
//int eingabeKorrigiert = 0;
//int setMotor(int wert);
void setup() {
  Serial.begin(9600);
  pinMode(ir_pin, INPUT);
  pinMode(reedPin, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(turnmotor, OUTPUT);
  
}
String serialInput = "";
void loop() {
  while (Serial.available() > 0) {
    char serialChar = Serial.read();
    if (isDigit(serialChar) || serialChar == 'p' || 'h') {
      serialInput += serialChar;
    }
    if (serialChar == '\n') {
      if (serialInput.charAt(0) == 'p') {
        serialInput.remove(0, 1);
        positionP = serialInput.toInt();
        Serial.println("DONE > " + serialInput);
        serialInput = "";
      }
      if (serialInput.charAt(0) == 'h') {
        positionP = 0; //Homeschwelle
        Serial.println("DONE > " + serialInput);
        serialInput = "";
      }
              if ( (fahrerlaubnis == 1) && (counter <= 6)) { // zahl muss mit Stellenangabenvariable (counterinput ausm frontend) ausgetauscht werden
      digitalWrite(motor, HIGH);
    }
    else {
      digitalWrite(motor, LOW);
      fahrerlaubnis = 0;
    }
    }


    // counterschleife
    int irState = digitalRead(ir_pin);
    if ( (irState == 1) && (hitObject == false) ) {
      counter++;
      hitObject = true;
      Serial.print ("Counter = ");
      Serial.println( counter );
    }
    else if ( (irState == 0) && (hitObject == true) ) {
      hitObject = false;
    }
    int State = digitalRead(reedPin);
    if ( (State == 1) && (hitReed == false) ) {
      counter = 0;
      hitReed = true;
      Serial.println( "Reed An" );
      //Serial.println( counter );
    }
    // Reedkontaktabfrage
    else if ( (State == 0) && (hitReed == true) ) {
      hitReed = false;
    }


    

    // homingfunktion
    if ( (Home == 1) && (hitReed == false)) {
      digitalWrite(turnmotor, HIGH);
    }
  }
}
