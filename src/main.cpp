#include <Arduino.h>
#include <STM32FreeRTOS.h>
int pin_left_forward = D10;
int pin_left_backwards = D11;
int pin_right_forward = D5;
int pin_right_backwards = D3;
enum grej {
  Forward,
  Backwardsssss,
  Still,
  Left,
  Right,
  Circle
};
int state = 2;
int previous_btn, current_btn;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin_left_forward, OUTPUT); //left forward
  pinMode(pin_left_backwards, OUTPUT); //left forward
  pinMode(pin_right_forward, OUTPUT); //left forward
  pinMode(pin_right_backwards, OUTPUT); //left forward
  pinMode(USER_BTN, INPUT); //nucleos ugly pin >:(
}
void loop() {
  // put your main code here, to run repeatedly:
  switch(state) {
    case Forward:
    digitalWrite(pin_right_forward, HIGH);
    digitalWrite(pin_left_forward, HIGH);
    digitalWrite(pin_right_backwards, LOW);
    digitalWrite(pin_left_backwards, LOW);
    break;
    case Backwardsssss:
    digitalWrite(pin_right_forward, LOW);
    digitalWrite(pin_left_forward, LOW);
    digitalWrite(pin_right_backwards, HIGH);
    digitalWrite(pin_left_backwards, HIGH);
    break;
    case Still:
    digitalWrite(pin_right_forward, LOW);
    digitalWrite(pin_left_forward, LOW);
    digitalWrite(pin_right_backwards, LOW);
    digitalWrite(pin_left_backwards, LOW);
    break;
    case Left:
    digitalWrite(pin_left_forward, HIGH);
    digitalWrite(pin_right_forward, LOW);
    digitalWrite(pin_right_backwards, LOW);
    digitalWrite(pin_left_backwards, LOW);
    break;
    case Right:
    digitalWrite(pin_right_forward, HIGH);
    digitalWrite(pin_left_forward, LOW);
    digitalWrite(pin_right_backwards, LOW);
    digitalWrite(pin_left_backwards, LOW);
    break;
    case Circle:
    digitalWrite(pin_left_forward, HIGH);
    digitalWrite(pin_right_forward, LOW);
    digitalWrite(pin_right_backwards, HIGH);
    digitalWrite(pin_left_backwards, LOW);
    break;
  }
  previous_btn = current_btn;
  current_btn = digitalRead(USER_BTN);
  if (current_btn == HIGH && previous_btn == LOW) {
    if (state == 5) state = 0; else state++;
  }
}


