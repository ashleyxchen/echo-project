#include <Stepper.h>
#define STEPS 100

// const
const int EMG_PIN = A0;             
const int LED_PIN = 13;            
const int BUTTON_PIN = 2;          
const int STEPS_PER_REVOLUTION = 100;  // # of steps per revolution for the stepper motor

// Stepper motor config
const int STEPPER_PIN1 = 8;
const int STEPPER_PIN2 = 9;
const int STEPPER_PIN3 = 10;
const int STEPPER_PIN4 = 11;
// create an instance of the stepper class, specifying the number of steps of the motor and the pins it's attached to
Stepper stepper(STEPS_PER_REVOLUTION, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

// EMG vars
int maxThreshold = 0;
int defaultThreshold = 100;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  stepper.setSpeed(100); 

  runSetupProcess();

  // Device is ready
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  static bool isOpen = true; // Claw Status
  int emgValue = analogRead(EMG_PIN);

  // Turn off device
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(3000);
    if (digitalRead(BUTTON_PIN) == LOW) {
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      while (1) {
        // break code so code stops lol
        // TO DO: add power-saving mode?
      }
    }
  }

  if (emgValue > maxThreshold || emgValue == maxThreshold) {
    if (isOpen) {
      stepper.step(-STEPS_PER_REVOLUTION); // Close claw
    } else {
      stepper.step(STEPS_PER_REVOLUTION); // Open claw
    }
  }
}

void runSetupProcess() {
  int startTime = millis();
  int endTime = startTime + 5000;

  // Blinking LED
  while (millis() < endTime) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);

    int emgValue = analogRead(EMG_PIN);

    // Update max threshold
    if (emgValue > maxThreshold) {
      maxThreshold = emgValue;
    }
  }

  // Set default threshold if maxThreshold not set
  if (maxThreshold == 0) {
    maxThreshold = defaultThreshold;
  }
}
