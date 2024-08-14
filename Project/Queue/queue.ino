// Khai báo kích thước queue và kích thước của dữ liệu
#define QUEUE_SIZE 10
#define ITEM_SIZE sizeof(int)

// Khai báo queue toàn cục
QueueHandle_t myQueue;

// Task gửi dữ liệu vào queue
void senderTask(void *pvParameters) {
    int counter = 0;
    while (true) {
        // Gửi số nguyên vào queue
        if (xQueueSend(myQueue, &counter, portMAX_DELAY) == pdTRUE) {
            Serial.print("Sent: ");
            Serial.println(counter);
            counter++;
        }
        // Delay để mô phỏng công việc khác
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task nhận dữ liệu từ queue
void receiverTask(void *pvParameters) {
    int receivedValue;
    while (true) {
        // Nhận dữ liệu từ queue
        if (xQueueReceive(myQueue, &receivedValue, portMAX_DELAY) == pdTRUE) {
            Serial.print("Received: ");
            Serial.println(receivedValue);
        }
        // Delay để mô phỏng công việc khác
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    Serial.begin(115200);

    // Tạo queue
    myQueue = xQueueCreate(QUEUE_SIZE, ITEM_SIZE);

    // Kiểm tra nếu queue tạo thành công
    if (myQueue == NULL) {
        Serial.println("Failed to create queue.");
        while (true);
    }

    // Tạo các task
    xTaskCreate(senderTask, "Sender Task", 1000, NULL, 1, NULL);
    xTaskCreate(receiverTask, "Receiver Task", 1000, NULL, 1, NULL);
}

void loop() {
    // loop() không làm gì vì các task chạy riêng biệt
}
