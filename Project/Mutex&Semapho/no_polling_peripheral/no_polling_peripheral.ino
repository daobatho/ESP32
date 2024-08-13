#include <Arduino.h>
#include <DHT.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// Định nghĩa chân và loại cảm biến DHT
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Tạo semaphore nhị phân
SemaphoreHandle_t xBinarySemaphore;

// Tác vụ đọc cảm biến
void readSensorTask(void *pvParameters) {
  // Đọc dữ liệu từ cảm biến
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
    while (1) {
        // Đợi semaphore được đưa bởi ngắt timer
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {

            // Kiểm tra xem việc đọc có thành công hay không
            if (isnan(humidity) || isnan(temperature)) {
                Serial.println("Failed to read from DHT sensor!");
            } else {
                Serial.print("Humidity: ");
                Serial.print(humidity);
                Serial.print("%  Temperature: ");
                Serial.print(temperature);
                Serial.println("°C");
            }
        }
    }
}

// Hàm ngắt timer
void IRAM_ATTR onTimer() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Đưa semaphore
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    // Chuyển tác vụ nếu cần
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Tạo semaphore nhị phân
    xBinarySemaphore = xSemaphoreCreateBinary();

    // Tạo tác vụ đọc cảm biến
    xTaskCreate(readSensorTask, "Read Sensor Task", 2048, NULL, 1, NULL);

    // Cấu hình timer ngắt
    hw_timer_t *timer = timerBegin(0, 80, true); // 80 cho ESP32
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 5000000, true); // 5 giây
    timerAlarmEnable(timer);
}

void loop() {
    // Không cần thực hiện gì trong vòng lặp chính
}