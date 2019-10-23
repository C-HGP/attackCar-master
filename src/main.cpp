#include <Arduino.h>
#include <STM32FreeRTOS.h>

int pin_left_forward = D10;
int pin_left_backwards = D11;
int pin_right_forward = D3;
int pin_right_backwards = D5;

TaskHandle_t xHandle = NULL;
void drive(void *pvParameters);

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

  xTaskCreate(
        drive,
        (const portCHAR *)"Go",   // Human readable name
        (configSTACK_DEPTH_TYPE)64,   // Stack size
        (void *)1,                // A pvParameters to use by the task
        (UBaseType_t)1,               // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
        (TaskHandle_t *)NULL          // Task handle for external manipulation of task
    );
}
void loop() {
  
}

void drive(void *pvParameters)
{
  digitalWrite(pin_right_forward, HIGH);
  digitalWrite(pin_left_forward, HIGH);
  digitalWrite(pin_right_backwards, LOW);
  digitalWrite(pin_left_backwards, LOW);
}

