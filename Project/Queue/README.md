TÌM HIỂU VỀ RTOS
---
# QUEUE
- Queue là hình thức giao tiếp giữa các task chính. Chúng được sử dụng để gửi tin nhắn giữa các task hoặc giữa task và ngắt
trong hầu hết các trường hợp chúng được sử dụng làm bộ đệm FIFO an toàn cho luồng, dữ liệu mới được gửi đến phía sau Queue mặc
dù cũng có thể gửi đến phía trước . Nếu là được gửi đến phía trc queue thì nó vẫn sẽ được xử lý trc các dữ liệu khác trong queue(tức là ưu tiên hơn)
điều này rất có ích trong các trường hợp khẩn cấp như có 1 ngắt 
- Dữ liệu được gửi vào hàng đợi bằng cách sao chép, nghĩa là dữ liệu (có thể là con trỏ đến bộ đệm lớn hơn) được sao chép vào hàng đợi thay vì chỉ lưu trữ tham chiếu.
- Điều này cho phép task gửi dữ liệu ngay lập tức ghi đè lên biến hoặc bộ đệm mà không lo lắng về việc dữ liệu còn tồn tại trong hàng đợi.
- FreeRTOS tự động quản lý bộ nhớ được sử dụng cho khu vực lưu trữ hàng đợi.
- Dữ liệu có thể được gửi theo kiểu sao chép hoặc theo kiểu tham chiếu (bằng cách gửi con trỏ đến dữ liệu).
```
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

// Định nghĩa các loại tin nhắn có thể gửi qua hàng đợi
typedef enum {
    MSG_INTEGER,   // Tin nhắn chứa một số nguyên
    MSG_STRING     // Tin nhắn chứa một chuỗi ký tự
} MessageType;

// Cấu trúc để lưu trữ thông tin tin nhắn
typedef struct {
    MessageType type;          // Loại tin nhắn (số nguyên hoặc chuỗi)
    union {                    // Dùng union để lưu trữ dữ liệu tùy theo loại tin nhắn
        int integerValue;      // Dữ liệu tin nhắn kiểu số nguyên
        char stringValue[50];  // Dữ liệu tin nhắn kiểu chuỗi ký tự
    } data;
} Message;

```
- Hàng đợi có thể chứa các loại dữ liệu khác nhau bằng cách định nghĩa cấu trúc chứa thông tin về loại tin nhắn và dữ liệu tin nhắn.
- API riêng biệt (FromISR) được cung cấp cho các hàng đợi khi được sử dụng trong ngữ cảnh interrupt để đảm bảo hiệu suất và tránh overhead.
- Ví dụ :
[xem tại đây](queue.ino)
- áp dụng với đọc dht hiển thị lcd
[xem tại đây](dht_lcd_queue.ino)
