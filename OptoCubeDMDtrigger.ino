const int pinDMD=2;

void setup() {
  Serial.begin(9600);
  pinMode(pinDMD,OUTPUT);
}

void loop() {
  while(Serial.available()>0){
    int received_value = Serial.read();
    //Serial.println(received_value);
    if (received_value=='H'){
      Serial.println("HIGH");
      digitalWrite(pinDMD,HIGH);
    }
    if (received_value=='L'){
      Serial.println("LOW");
      digitalWrite(pinDMD,LOW);
    }
  }
}
