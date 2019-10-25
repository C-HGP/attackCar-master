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

//Libaries
#include <Arduino.h>
#include <STM32FreeRTOS.h>

//Declare pins
int pin_left_forward = D10;
int pin_left_backwards = D11;
int pin_right_forward = D4;
int pin_right_backwards = D6;
bool go = true;
bool turning = false;

bool left = true; 

TaskHandle_t xHandle = NULL;

//Declare functions
void drive(void *pvParameters);
void randomizer(void *pvParameters);
void turn(void *pvParameters);

void setup() {
  xTaskCreate(
      drive,
      (const portCHAR *)"Go",     // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  xTaskCreate(
      randomizer,
      (const portCHAR *)"Random", // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  xTaskCreate(
      turn,
      (const portCHAR *)"Turn", // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  vTaskStartScheduler();
}
void loop() {
  // FreeRTOS based, does not use loop
}

// Function for casually driving
void drive(void *pvParameters) {
  for (;;)
  {
    pinMode(pin_left_forward, OUTPUT);
    pinMode(pin_left_backwards, OUTPUT);
    pinMode(pin_right_forward, OUTPUT);
    pinMode(pin_right_backwards, OUTPUT);

    if (go)
    {
      digitalWrite(pin_right_forward, HIGH);
      digitalWrite(pin_left_forward, HIGH);
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, LOW);
    }
    else
    {
      digitalWrite(pin_right_forward, LOW);
      digitalWrite(pin_left_forward, LOW);
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, LOW);
    }
    vTaskDelay(5);
  }
}
void turn(void *pvParameters) {
  int counter = 0;
  for (;;)
  {
    pinMode(pin_left_forward, OUTPUT);
    pinMode(pin_left_backwards, OUTPUT);
    pinMode(pin_right_forward, OUTPUT);
    pinMode(pin_right_backwards, OUTPUT);  
        
    if(turning == true)
    {
      
      if(left == true)
      {
        digitalWrite(pin_right_forward, LOW);
        digitalWrite(pin_left_forward, HIGH);
        digitalWrite(pin_right_backwards, LOW);
        digitalWrite(pin_left_backwards, LOW);
        counter++;
        
        if (counter == 500){
          left = false;  
          go = true;
          turning = false;
          counter=0;
        }
      }
      else
      {
        digitalWrite(pin_right_forward, HIGH);
        digitalWrite(pin_left_forward, LOW);
        digitalWrite(pin_right_backwards, LOW);
        digitalWrite(pin_left_backwards, LOW);
        counter++;
        
        if (counter == 500){
          left = true;
          go = true;
          turning = false;
          counter=0;
        }
      }
    }
    vTaskDelay(5);
  }
}
//Function to randomize a stop for the robot
void randomizer(void *pvParameters)
{
  for (;;)
  {
    int randNr = random(1, 5);
    //int dir = random(1,2);
    if (randNr == 3)
    {
      //direction = D10;  
      go = false;
      turning = true;
    }
    vTaskDelay(1000);
  }
}