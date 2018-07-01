 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);


int redLed_2 = 2;
int greenLed_2 = 3;
int redLed_135 = 5;
int greenLed_135 = 4;
int redLed_7 = 7;
int greenLed_7 = 6;
int k1=0;
int smokeA0_135 = A4;
int smokeA0_2 = A5;
int smokeA0_7 = A3;
int count=0;
int solenoidPin = 12;   

int sensorThres_2 =300;
int sensorThres_135 =350;
int sensorThres_7 =350; 
void setup() {
  pinMode(redLed_2, OUTPUT);
  pinMode(greenLed_2, OUTPUT);
  pinMode(smokeA0_2, INPUT);

  pinMode(redLed_135, OUTPUT);
  pinMode(greenLed_135, OUTPUT);
  pinMode(smokeA0_135, INPUT);

  pinMode(redLed_7, OUTPUT);
  pinMode(greenLed_7, OUTPUT);
   pinMode(smokeA0_7, INPUT);
    pinMode(solenoidPin, OUTPUT);
     digitalWrite(solenoidPin, HIGH);
    mySerial.begin(9600); 
  Serial.begin(9600);
}

void loop() {
  int analogSensor_2 = analogRead(smokeA0_2);
 // delay(400);
    int analogSensor_135 = analogRead(smokeA0_135);
    //delay(400);
    int analogSensor_7 = analogRead(smokeA0_7);
    //delay(400);
  

  //Serial.print("Pin A0-MQ2: ");
  Serial.print(analogSensor_2);
  Serial.print(",");
Serial.print("\t\tPin A0-MQ135: ");
  Serial.print(analogSensor_135);
  Serial.print(",");
  Serial.print("\t\tPin A0-MQ7: ");
  Serial.print(analogSensor_7);
  Serial.print(",");
 // Serial.println("before high");
  Serial.println("");
   
  //Serial.println("after high");
   //delay(10000); 
    //Serial.print("high delay ended");

   
  if (analogSensor_2 > sensorThres_2)
  {
    digitalWrite(redLed_2, HIGH);
    digitalWrite(greenLed_2, LOW);
    count=count+1;
   // Serial.println("inside 1st sensor");
  }
  else
  {
    digitalWrite(redLed_2, LOW);
    digitalWrite(greenLed_2, HIGH);
  }
  if (analogSensor_135 > sensorThres_135)
  {
    digitalWrite(redLed_135, HIGH);
    digitalWrite(greenLed_135, LOW);
    
  //  Serial.println("inside 2nd sensor");
    count=count+1;
  }
  else
  {
    digitalWrite(redLed_135, LOW);
    digitalWrite(greenLed_135, HIGH);
  }
  if (analogSensor_7 > sensorThres_7)
  {
    digitalWrite(redLed_7, HIGH);
    digitalWrite(greenLed_7, LOW);
    
  //  Serial.println("inside 3rd sensor");
    count=count+1;
  }
  else
  {
    digitalWrite(redLed_7, LOW);
    digitalWrite(greenLed_7, HIGH);
  }
  
  delay(1000);
 // Serial.println(count);
  Serial.println("");
  if(analogSensor_2 > sensorThres_2 && analogSensor_135 > sensorThres_135 && analogSensor_7 > sensorThres_7 && k1==0){
    k1=1;
    SendMessage();
    delay(10000);
    digitalWrite(solenoidPin, LOW);
    Serial.println("stopping vehicle");
      delay(10000);
   }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917224053356\"\r"); // Replace x with mobile number
  delay(1000);
  char text[300]="Dear User, The emission level of your respective vehicle has exceeded the safe emission standards. Please meet the nearest service center and get your vehicle repaired!.";
  mySerial.print(text);// The SMS text you want to send
  delay(100);
   mySerial.print((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
