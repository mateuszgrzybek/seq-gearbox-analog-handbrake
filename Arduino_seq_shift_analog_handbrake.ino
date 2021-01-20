#include <Joystick.h>

void setup() {
  // init throttle analog pin
  pinMode(A0, INPUT); 

  // init momentary push pins
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  Joystick.begin();
}

// throttle analog input ranges
const int throttleLowerInputRange = 0;
const int throttleUpperInputRange = 1023;
// throttle mapped ranges
const int throttleLowerMappedRange = 0;
const int throttleUpperMappedRange = 255;


const int pinToButtonMapAnalog = A0;
const int pinToButtonMapDigital = 4 ;

int lastButtonState[2] = {0,0};

void loop() {

  // read analog pin value (the amount of handbrake pull)
  int potentiometerState = analogRead(A0);
  // map the value read from the above pin
  int mappedPotentiometerState = map(potentiometerState, throttleLowerInputRange, throttleUpperInputRange, throttleLowerMappedRange, throttleUpperMappedRange);
  {
    Joystick.setThrottle(mappedPotentiometerState);
  }

  int currentPin4State = !digitalRead(4);
  int currentPin5State = !digitalRead(5);
  
  // read digital pin values
  if (currentPin4State != lastButtonState[0]) 
  {
      Joystick.setButton(4, currentPin4State);
      lastButtonState[0] = !lastButtonState[0];
  }

  if (currentPin5State != lastButtonState[1])
  {
      Joystick.setButton(5, currentPin5State);
      lastButtonState[1] = !lastButtonState[1];
  }

  delay(50);
}
