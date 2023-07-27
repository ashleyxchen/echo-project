#include <Servo.h>
Servo servo;

const int signal = A5;
const int LED = 2;
const int signalThreshold = 250;
int signalState;
int servoState;
const int openPos = 170; 
const int closedPos = 104; 

void setup() {
  Serial.begin(9600);
  
  pinMode(signal, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);

  servo.attach(9);
  servo.write(openPos);
  servoState = openPos;

  // uncomment to execute unit test
  // unittest_main()
}


void loop() {
  // read
  signalState = analogRead(signal);

  // print signal
  Serial.print("Voltage: ");
  Serial.print(signalState);
  Serial.println();

  // moving servo
  setServo(signalState);
}

void setServo(int signalState) {
    if (signalState > signalThreshold) {
    if(servoState == openPos){
      servo.write(closedPos);
      servoState = closedPos;
       Serial.print(servoState);
    }
    else {
      servo.write(openPos);
      servoState = openPos;
       Serial.print(servoState);
    }
    delay(2000);
  } 
}
