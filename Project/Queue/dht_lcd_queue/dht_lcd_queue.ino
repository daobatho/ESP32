#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4       // Chân kết nối DHT11
#define DHTTYPE DHT11  // Loại DHT
#define LCD_ADDRESS 0x27 // Địa chỉ I2C của LCD
#define LCD_COLUMNS 16   // Số cột của LCD
#define LCD_ROWS 2       // Số hàng của LCD

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Cấu trúc dữ liệu cảm biến
struct DHTData {
  float temperature;  // Nhiệt độ
  float humidity;     // Độ ẩm
};

// Hàng đợi để truyền dữ liệu cảm biến
QueueHandle_t dhtDataQueue;

void readDHTTask(void *pvParameter) {
  while (1) {
    DHTData data;
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    
    if (isnan(data.temperature) || isnan(data.humidity)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      xQueueSend(dhtDataQueue, &data, portMAX_DELAY);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); 
  }
}

void displayTask(void *pvParameter) {
  DHTData dhtData;
  
  while (1) {
    if (xQueueReceive(dhtDataQueue, &dhtData, portMAX_DELAY) == pdPASS) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(dhtData.temperature);
      lcd.print("C");
      
      lcd.setCursor(0, 1);
      lcd.print("Hum: ");
      lcd.print(dhtData.humidity);
      lcd.print("%");
    }

    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();      
  lcd.backlight(); 

  dhtDataQueue = xQueueCreate(10, sizeof(DHTData));
  if (dhtDataQueue == NULL) {
    Serial.println("Failed to create DHT data queue");
    while (1);
  }

  xTaskCreate(readDHTTask, "Read DHT Task", 2048, NULL, 1, NULL);
  xTaskCreate(displayTask, "Display Task", 2048, NULL, 1, NULL);
}

void loop() {
  // Không cần làm gì trong loop
}
