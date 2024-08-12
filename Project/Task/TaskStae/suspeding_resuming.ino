#include <DHT.h>
#include <Arduino.h>

// Định nghĩa loại cảm biến DHT và chân kết nối
#define DHTPIN 4       
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

// Task handle
TaskHandle_t TaskDHTHandle = NULL;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Tạo task đọc DHT
  xTaskCreate(
    TaskDHT,         // Hàm thực hiện task
    "TaskDHT",       // Tên của task
    1000,            // Kích thước stack của task
    NULL,            // Tham số đầu vào của task
    1,               // Độ ưu tiên của task
    &TaskDHTHandle   // Task handle
  );

  // Đình chỉ TaskDHT ngay sau khi khởi tạo
  vTaskSuspend(TaskDHTHandle);
}

void loop() {
  // Main loop không làm gì cả, mọi công việc được thực hiện trong task

  // Sau 10 giây, kích hoạt lại TaskDHT
  delay(10000);
  Serial.println("Resuming TaskDHT...");
  vTaskResume(TaskDHTHandle);
}

void TaskDHT(void *pvParameters) {
  (void) pvParameters;
      // Đọc độ ẩm và nhiệt độ từ cảm biến DHT
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  for (;;) {
    // Kiểm tra nếu đọc thất bại
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      // In ra giá trị độ ẩm và nhiệt độ
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" *C");
    }

    // Task này sẽ bị đình chỉ sau khi đọc dữ liệu
    Serial.println("Suspending TaskDHT...");
    vTaskSuspend(NULL); // Đình chỉ chính task này
  }
}
