// Tạo một semaphore nhị phân
SemaphoreHandle_t xBinarySemaphore;

// Tài nguyên dùng chung (ví dụ, một biến đếm)
volatile int sharedResource = 0;

// Task 1 cố gắng truy cập vào tài nguyên dùng chung
void task1(void *pvParameters) {
    while (1) {
        // Thử chiếm semaphore
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {
            // Đã chiếm được semaphore, truy cập vào tài nguyên
            Serial.println("Task 1 accessing shared resource.");
            sharedResource++;
            Serial.print("Shared Resource (Task 1): ");
            Serial.println(sharedResource);

            // Thả semaphore sau khi hoàn thành công việc
            xSemaphoreGive(xBinarySemaphore);

            // Delay để mô phỏng công việc đang được thực hiện
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

// Task 2 cố gắng truy cập vào tài nguyên dùng chung
void task2(void *pvParameters) {
    while (1) {
        // Thử chiếm semaphore
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {
            // Đã chiếm được semaphore, truy cập vào tài nguyên
            Serial.println("Task 2 accessing shared resource.");
            sharedResource++;
            Serial.print("Shared Resource (Task 2): ");
            Serial.println(sharedResource);

            // Thả semaphore sau khi hoàn thành công việc
            xSemaphoreGive(xBinarySemaphore);

            // Delay để mô phỏng công việc đang được thực hiện
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void setup() {
    Serial.begin(115200);

    // Tạo semaphore nhị phân
    xBinarySemaphore = xSemaphoreCreateBinary();

    // Khởi tạo semaphore ở trạng thái "được cấp" để task đầu tiên có thể truy cập ngay
    xSemaphoreGive(xBinarySemaphore);

    // Tạo các task
    xTaskCreate(task1, "Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 2048, NULL, 1, NULL);
}

void loop() {
    // Vòng lặp chính không cần thực hiện gì cả
}
