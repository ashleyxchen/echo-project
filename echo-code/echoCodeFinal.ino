#include <Servo.h>
Servo servo;

const int signal = A0;
const int signalThreshold = 250;
int signalState;
int servoState;
const int openPos = 170; 
const int closedPos = 100; 

void setup() {
  Serial.begin(9600);
  
  pinMode(signal, INPUT);

  servo.attach(9);
  servo.write(openPos);
  servoState = openPos;
}


void loop() {
  // read
  signalState = analogRead(signal);

  // print signal
  Serial.print("Voltage: ");
  Serial.print(signalState);
  Serial.println();

  // moving servo
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



