#include <ArduinoUnit.h>
#include <Servo.h>

Servo servo;

  test(controlServoTest) {
    // setup
    Servo servoUnderTest;
    int openPos = 170;
    int closedPos = 104;
    int signalThreshold = 250;
    int signalState;

    // Simulate signal > threshold
    // Expected: since openPos, should write closedPos to servo.
    int signalValue = signalThreshold + 10;
    servo.write(openPos); // Reset the servo state
    controlServo(signalValue);

    // Verify servo is closed and servoState variable is updated
    assertEqual(servo.read(), closedPos); 
    assertEqual(servoState, closedPos); 

    // Simulate signal < threshold
    // Expected: since closedPOs, should write openPos to servo.
    signalValue = signalThreshold - 10;
    servo.write(closedPos); // Reset the servo state
    controlServo(signalValue);

    // Verify servo is open and servoState variable is updated
    assertEqual(servo.read(), openPos); 
    assertEqual(servoState, openPos); 
  }

// unittest_main()
