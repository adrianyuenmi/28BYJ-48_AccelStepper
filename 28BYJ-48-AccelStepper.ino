// 28BYJ-48 but using AccelStepper

#include <AccelStepper.h>

// ORANGE -- COMMON 5V -- PINK is a phase of the stepper
#define IN1   9 // ULN2003 OUT1 <-> 28BYJ-48 ORANGE
#define IN3  10 // ULN2003 OUT3 <-> 28BYJ-48 PINK

// YELLOW -- COMMON 5V -- BLUE is a phase of the stepper
#define IN2  11 // ULN2003 OUT2 <-> 28BYJ-48 YELLOW
#define IN4  12 // ULN2003 OUT4 <-> 28BYJ-48 BLUE

#define DEFAULT_SPEED 200

// If FULL4WIRE, empirical max speed is 400
//AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN2, IN3, IN4);

// If FULL4WIRE, empirical max speed is 800
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN2, IN3, IN4);

float currentSpeed = DEFAULT_SPEED;

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(200.0);
}

void loop() {
  // Set the speed of the motor in steps per second:
  stepper.setSpeed(currentSpeed);
  // Step the motor with constant speed as set by setSpeed():
  stepper.runSpeed();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    bool isSpeedUpdated = true;
    switch (inChar){
      case 'a':
      case 'A':
        currentSpeed -= 1;
        break;

      case 'q':
      case 'Q':
        currentSpeed -= 10;
        break;  

      case 'd':
      case 'D':
        currentSpeed += 1;
        break;

      case 'e':
      case 'E':
        currentSpeed += 10;
        break;  

      // ignore other characters
      default:
        isSpeedUpdated = false;
      break;
    }
    
    if (isSpeedUpdated) {
      Serial.println(currentSpeed);
    }
  }
}
