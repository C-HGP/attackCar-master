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
const int redLED = A0;
const int greenLED = A2;
const int buzzer = D3;
long duration, cm;
bool go = true;
bool turning = false;

bool left = true;

TaskHandle_t xHandle = NULL;

//Declare functions
void drive(void *pvParameters);
void randomizer(void *pvParameters);
void turn(void *pvParameters);
void sensorAttack(void *pvParameters);

void setup()
{
  Serial.begin(9600);
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
      (const portCHAR *)"Turn",   // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  xTaskCreate(
      sensorAttack,
      (const portCHAR *)"Sensor", // Human readable name
      (configSTACK_DEPTH_TYPE)64, // Stack size
      (void *)NULL,               // A pvParameters to use by the task
      (UBaseType_t)1,             // Priority, 3 (configMAX_PRIORITIES - 1) highest, 0 lowest
      (TaskHandle_t *)NULL        // Task handle for external manipulation of task
  );

  vTaskStartScheduler();
}
void loop()
{
  // FreeRTOS based, does not use loop
}

// Function for casually driving
void drive(void *pvParameters)
{
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, HIGH);
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
void turn(void *pvParameters)
{
  int counter = 0;
  for (;;)
  {

    if (turning == true)
    {

      if (left == true)
      {
        pinMode(pin_left_forward, OUTPUT);
        pinMode(pin_left_backwards, OUTPUT);
        pinMode(pin_right_forward, OUTPUT);
        pinMode(pin_right_backwards, OUTPUT);
        digitalWrite(pin_right_forward, LOW);
        digitalWrite(pin_left_forward, HIGH);
        digitalWrite(pin_right_backwards, LOW);
        digitalWrite(pin_left_backwards, LOW);
        counter++;

        if (counter == 500)
        {
          left = false;
          go = true;
          turning = false;
          counter = 0;
        }
      }
      if (left == false)
      {
        pinMode(pin_left_forward, OUTPUT);
        pinMode(pin_left_backwards, OUTPUT);
        pinMode(pin_right_forward, OUTPUT);
        pinMode(pin_right_backwards, OUTPUT);
        digitalWrite(pin_right_forward, HIGH);
        digitalWrite(pin_left_forward, LOW);
        digitalWrite(pin_right_backwards, LOW);
        digitalWrite(pin_left_backwards, LOW);
        counter++;

        if (counter == 500)
        {
          left = true;
          go = true;
          turning = false;
          counter = 0;
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

//Sensor & attack function
void sensorAttack(void *pvParameters)
{
  pinMode(trigPin, OUTPUT_OPEN_DRAIN);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  for (;;)
  {
    //Using engines
    pinMode(pin_left_forward, OUTPUT);
    pinMode(pin_left_backwards, OUTPUT);
    pinMode(pin_right_forward, OUTPUT);
    pinMode(pin_right_backwards, OUTPUT);
    //Start Sensor
    digitalWrite(trigPin, LOW);
    vTaskDelay(50);
    digitalWrite(trigPin, HIGH);
    vTaskDelay(70);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    
    //Debug sensor
    duration = pulseIn(echoPin, HIGH);
    cm = (duration / 2) / 29.1;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    vTaskDelay(25);

    // When sensor spots something in the bounds of 20(?),
    // go into attack mode then back to normal routine
    if (cm < 10){
      // Start attack mode, showing a red light
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      // Stop all
      vTaskSuspendAll();
      // Stop engines
      digitalWrite(pin_right_forward, LOW);
      digitalWrite(pin_left_forward, LOW);
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, LOW);

      //Buzzer
      tone(buzzer, 500);
      delay(500);
      noTone(buzzer);
      delay(500);
      tone(buzzer, 500);
      delay(500);
      noTone(buzzer);

      //reverse
      digitalWrite(pin_right_backwards, HIGH);
      digitalWrite(pin_left_backwards, HIGH);
      delay(1000);
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, LOW);

      //CHARGE FOR THE FUCKING MOTHERLAND
      //FORWARD
      digitalWrite(pin_right_forward, HIGH);
      digitalWrite(pin_left_forward, HIGH);
      delay(4000);
      //STOP
      digitalWrite(pin_right_forward, LOW);
      digitalWrite(pin_left_forward, LOW);
      delay(1000);
      //REVERSE BACK
      digitalWrite(pin_right_backwards, HIGH);
      digitalWrite(pin_left_backwards, HIGH);
      delay(1000);
      //Turn around
      digitalWrite(pin_right_backwards, LOW);
      digitalWrite(pin_left_backwards, HIGH);
      digitalWrite(pin_right_forward, HIGH);
      delay(3000);
      //Forward
      digitalWrite(pin_left_backwards, LOW);
      digitalWrite(pin_left_forward, HIGH);
      delay(1000);

      // Back to normal routine
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      xTaskResumeAll();

    }
  }
}

// Test