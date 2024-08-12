// Task handles
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

void setup() {
  Serial.begin(115200);

  // Create Task1 with higher priority
  xTaskCreate(
    Task1,       // Function that implements the task
    "Task1",     // Name of the task
    1000,        // Stack size in words
    NULL,        // Task input parameter
    2,           // Priority of the task
    &Task1Handle // Task handle
  );

  // Create Task2 with lower priority
  xTaskCreate(
    Task2,       // Function that implements the task
    "Task2",     // Name of the task
    1000,        // Stack size in words
    NULL,        // Task input parameter
    1,           // Priority of the task
    &Task2Handle // Task handle
  );
}

void loop() {
  // Main loop does nothing, all work is done in the tasks
}

void Task1(void *pvParameters) {
  for (;;) {
    Serial.println("Task1 is Running");
    // Simulate some work by delaying for 1000ms
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

void Task2(void *pvParameters) {
  for (;;) {
    Serial.println("Task2 is Running");
    // Simulate some work by delaying for 500ms
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
