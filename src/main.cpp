/*
-Suicide Car- 
The objective is to attack harmless walls at incredible speed.

By Robin & CHP
2019

*/ 
/**
 * #TODO
 * - ADD TASK FOR RANDOM GENERATION
 * - ADD TASK FOR TURNING 
 * - INTERRUPT DRIVING WHEN RANDOM NUMBER IS GIVEN 
 * 
 * 
 * */

#include <Arduino.h>
#include <STM32FreeRTOS.h>

int pin_left_forward = D10;
int pin_left_backwards = D11;
int pin_right_forward = D3;
int pin_right_backwards = D5;
bool go = false;

TaskHandle_t xHandle = NULL;
void drive(void *pvParameters);

void randomizer(void *pvParameters);

void setup() {
  // put your setup code here, to run once:
  
  xTaskCreate(
        drive,
        (const portCHAR *)"Go",   // Human readable name
        (configSTACK_DEPTH_TYPE)64,   // Stack size
        (void *)NULL,                // A pvParameters to use by the task
        (UBaseType_t)1,               // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
        (TaskHandle_t *)NULL          // Task handle for external manipulation of task
    );
  
  xTaskCreate(
        randomizer,
        (const portCHAR *)"Random",   // Human readable name
        (configSTACK_DEPTH_TYPE)64,   // Stack size
        (void *)NULL,                // A pvParameters to use by the task
        (UBaseType_t)1,               // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
        (TaskHandle_t *)NULL          // Task handle for external manipulation of task
    );

  vTaskStartScheduler();
}
void loop() {
  
}

void drive(void *pvParameters)
{
  for(;;)
  {
    pinMode(pin_left_forward, OUTPUT); 
    pinMode(pin_left_backwards, OUTPUT); 
    pinMode(pin_right_forward, OUTPUT); 
    pinMode(pin_right_backwards, OUTPUT);
    if(go)
    { 
      digitalWrite(pin_right_forward, HIGH);
      digitalWrite(pin_left_forward, HIGH);
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, LOW);
    }
    vTaskDelay(5);
  }
}

void randomizer(void *pvParameters)
{
  for(;;)
  {
    int randNr = random(1,5);
    if(randNr == 3)
    {
      go = false;
    }
    vTaskDelay(5000);
 }
}

