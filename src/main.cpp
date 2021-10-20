#include "Button.hpp"
#include "CallbackButton.hpp"
#include "DirectDigital.hpp"
#include "Function.hpp"
#include "RotaryEncoder.hpp"
#include <Arduino.h>

const int submitPin = 8;

void doShit();
volatile bool doneShit = false;

FunctionalInterrupts::Function doShitFunction{doShit};
Input::CallbackButton submit{submitPin, doShitFunction};

Input::Button reset{9};
Input::RotaryEncoder rotary{18, 19, 40};

void setup() {
  DirectDigital::Setup();
  DirectDigital::PinInit(submitPin);
  pinMode(submitPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() {
  /*{
    unsigned long startTime = micros();
    for (int i = 0; i < 10000; ++i) {
      int result = DirectDigital::Read(submitPin);
      ++result;
    }
    unsigned long endTime = micros();
    Serial.println("DirectDigital:");
    Serial.println(endTime - startTime);
  }
  {
    unsigned long startTime = micros();
    for (int i = 0; i < 10000; ++i) {
      int result = digitalRead(submitPin);
      ++result;
    }
    unsigned long endTime = micros();
    Serial.println("OrigDigital:");
    Serial.println(endTime - startTime);
  }*/
  if (submit.Pressed())
    Serial.println("Pressed");
  if (submit.Released())
    Serial.println("Released");
  if (reset.Pressed())
    rotary.Reset();
  if (doneShit) {
    Serial.println("Done shit");
    doneShit = false;
  }
  int16_t delta = rotary.Delta();
  if (delta != 0) {
    Serial.print(rotary.Position());
    Serial.print(", ");
    Serial.print(delta);
    Serial.print("\n");
  }
}

void printErrorCode(int code) {}

void doShit() { doneShit = true; }
