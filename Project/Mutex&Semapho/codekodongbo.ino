#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Tài nguyên dùng chung
volatile int sharedResource = 0;

// Task 1 truy cập tài nguyên dùng chung
void task1(void *pvParameters) {
    while (1) {
        // Truy cập và thay đổi tài nguyên
        Serial.println("Task 1 accessing shared resource.");
        sharedResource++;
        Serial.print("Shared Resource (Task 1): ");
        Serial.println(sharedResource);

        // Giả lập một công việc mất thời gian
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Task 2 truy cập tài nguyên dùng chung
void task2(void *pvParameters) {
    while (1) {
        // Truy cập và thay đổi tài nguyên
        Serial.println("Task 2 accessing shared resource.");
        sharedResource++;
        Serial.print("Shared Resource (Task 2): ");
        Serial.println(sharedResource);

        // Giả lập một công việc mất thời gian
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void setup() {
    Serial.begin(115200);

    // Tạo các task
    xTaskCreate(task1, "Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 2048, NULL, 1, NULL);
}

void loop() {
    // Không cần thực hiện gì trong vòng lặp chính
}
