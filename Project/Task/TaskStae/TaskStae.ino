#include <DHT.h>
// Define DHT sensor type and pin
#define DHTPIN 4       // DHT sensor pin
#define DHTTYPE DHT11   // DHT11 or DHT22

DHT dht(DHTPIN, DHTTYPE);

// Task handles
TaskHandle_t TaskDHTHandle = NULL;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Create a task to read DHT sensor data
  xTaskCreatePinnedToCore(
    TaskDHT,         // Function that implements the task
    "TaskDHT",       // Name of the task
    10000,           // Stack size in words
    NULL,            // Task input parameter
    1,               // Priority of the task
    &TaskDHTHandle,  // Task handle
    1);              // Core where the task should run
}

void loop() {
  // Main loop does nothing, all work is done in the TaskDHT function
}

void TaskDHT(void *pvParameters) {
  (void) pvParameters;
      // Read temperature and humidity from the DHT sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  for (;;) {
    // Indicate that the task is in the Running state
    Serial.println("Task is in the Running state");

    // Check if any reads failed and exit early (to try again)
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      // Print the temperature and humidity values to Serial Monitor
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" *C ");
    }

    // Task delay for a while to avoid flooding Serial Monitor
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}