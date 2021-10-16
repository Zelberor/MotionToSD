#include "FunctionalInterrupts/Function.hpp"
#include "Input/CallbackButton.hpp"
#include <Arduino.h>

const int submitPin = 3;

void doShit();
volatile bool doneShit = false;

FunctionalInterrupts::Function doShitFunction{doShit};
Input::CallbackButton submit{submitPin, doShitFunction};

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() {
  if (submit.Pressed())
    Serial.println("Pressed");
  if (doneShit) {
    Serial.println("Done shit");
    doneShit = false;
  }
}

void printErrorCode(int code) {}

void doShit() { doneShit = true; }
