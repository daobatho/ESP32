TÌM HIỂU VỀ RTOS
---
[Tài liệu tham khảo RTOS](https://www.freertos.org/Documentation/00-Overview)
[Tài liệu tham khảo RTOS](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/toc.md)

# TASK
## TASK STATE
- 1 Task có thể ở 1 trong các trạng thái sau
	- Running: Khi một tác vụ thực sự được thực thi, nó được cho là ở trạng thái Đang chạy. Nó hiện đang sử dụng bộ xử lý. 
	Nếu bộ xử lý mà RTOS đang chạy chỉ có một lõi thì chỉ có thể có một tác vụ ở trạng thái Đang chạy tại bất kỳ thời điểm nào.
	- Ready: Nhiệm vụ sẵn sàng là những nhiệm vụ có thể thực thi (chúng không ở trạng thái Bị chặn hoặc Bị tạm dừng) nhưng hiện 
	không thực thi vì một nhiệm vụ khác có mức độ ưu tiên bằng hoặc cao hơn đã ở trạng thái Đang chạy.
	- Blocked: Một tác vụ được cho là ở trạng thái Bị chặn nếu nó hiện đang chờ một sự kiện tạm thời hoặc sự kiện bên ngoài. 
	Ví dụ: nếu một tác vụ gọi vTaskDelay() thì nó sẽ chặn (được đặt vào trạng thái Bị chặn) cho đến khi hết thời gian trì hoãn - một
	sự kiện tạm thời. Các tác vụ cũng có thể chặn để chờ hàng đợi, semaphore, nhóm sự kiện, thông báo hoặc sự kiện semaphore. Các tác 
	vụ ở trạng thái Bị chặn thường có một khoảng thời gian 'hết thời gian', sau đó tác vụ sẽ hết thời gian chờ và được bỏ chặn, ngay 
	cả khi sự kiện mà tác vụ đang chờ chưa xảy ra. Các tác vụ ở trạng thái Bị chặn không sử dụng bất kỳ thời gian xử lý nào và không 
	thể được chọn để vào trạng thái Đang chạy.
	- Suspended: Giống như các tác vụ ở trạng thái Bị chặn, các tác vụ ở trạng thái Bị treo không thể được chọn để chuyển sang trạng 
	thái Đang chạy, nhưng các tác vụ ở trạng thái Bị treo không có thời gian chờ. Thay vào đó, các tác vụ chỉ vào hoặc thoát khỏi trạng 
	thái Tạm dừng khi được lệnh rõ ràng thực hiện điều đó thông qua các lệnh gọi API vTaskSuspend() và xTaskResume() tương ứng.

- Ví dụ 
[Xem code mẫu](TaskStae.ino)
![Alt](anh1.PNG)

[Xem code mẫu](blocked_ptiority.ino)
![Alt](anh2.PNG)

- Ví dụ suspeding & resuming
[xem code mẫu](suspeding_resuming.ino)
![Alt](anh3.PNG)