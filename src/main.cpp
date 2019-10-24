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
const int pin_left_forward = D10;
const int pin_left_backwards = D11;
const int pin_right_forward = D4;
const int pin_right_backwards = D6;
const int trigPin = D7;
const int echoPin = D8;
long duration, cm;

int led_red = A5;
int led_green = A4;

//bullar
bool go = true;
bool turning = false;
bool left = true;

TaskHandle_t xHandle = NULL;

//Declare functions
void drive(void *pvParameters);
void sensor(void *pvParameters);

void setup() {

  Serial.begin (9600);

  xTaskCreate(
      drive,
      (const portCHAR *)"DriveF",     // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  xTaskCreate(
      sensor,
      (const portCHAR *)"Sensor",     // Human readable name
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
  }
}


void sensor(void *pvParameters) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (;;)
  {
    digitalWrite(trigPin, LOW);
    vTaskDelay(50);
    digitalWrite(trigPin, HIGH);
    vTaskDelay(70);
    digitalWrite(trigPin, LOW);


    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = (duration/2) / 29.1;
  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    vTaskDelay(250);
  }
}
