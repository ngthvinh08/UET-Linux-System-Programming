# Hướng dẫn cài Ubuntu Dual Boot

**Link hướng dẫn cài Ubuntu (Dual Boot):**

[https://www.youtube.com/watch?v=g0qrydSnV4g](https://www.youtube.com/watch?v=g0qrydSnV4g&utm_source=chatgpt.com)

---

## **Note (Laptop ASUS)**

Một số dòng laptop ASUS sản xuất trước năm 2025 thường sử dụng card Wi-Fi của MediaTek, vốn không tương thích với driver trong kernel Ubuntu 24.04. Người dùng có thể cân nhắc thay thế bằng card Intel – vốn có khả năng hỗ trợ Linux tốt hơn.

### **Recommend**

**Card Intel Wi-Fi 6E AX210**

### **Trải nghiệm cá nhân**

Mình đã từng thay card này ở máy cũ, hoạt động rất ổn định.

Khi mua trên Shopee thì nên đọc kỹ phần đánh giá của shop để tránh rủi ro. Việc lắp đặt khá đơn giản, có nhiều video hướng dẫn trên YouTube.

Nếu gặp khó khăn, có thể liên hệ trực tiếp mình để được hỗ trợ.

---

## **Note (Laptop ACER)**

Một số dòng laptop Acer (ví dụ Nitro 5) có thiết lập **SATA Mode** mặc định là **RAID**, khiến việc boot OS từ SSD, HDD hoặc USB gặp lỗi *“unable to find location”*.

RAID mặc định gộp nhiều ổ cứng vật lý để tăng tốc độ xử lý, nhưng lại gây cản trở khi cài đặt hệ điều hành mới. Điều này khiến việc dual-boot hoặc cài độc lập một OS trở nên bất khả thi nếu không đổi chế độ này.

### **Recommend**

Có thể tham khảo thêm các thảo luận trên Reddit về lỗi *“unable to find location”* ở các dòng máy khác.

Ngoài ra, thử sử dụng kernel version thấp hơn để kiểm tra khả năng tương thích.

### **Trải nghiệm cá nhân (Minh Phương)**

Theo kinh nghiệm của mình, với riêng dòng Acer, cách cài các distro Linux khá giống nhau (mình dùng Ubuntu 26.04).

Thường chỉ cần tải file ISO của distro về rồi boot. Với các distro phổ biến, mình khuyến nghị cách tải này; còn với các distro đặc thù khác, mọi người có thể tự tìm hiểu thêm.

---

## **Solution**

### **S1: Backup dữ liệu**

Backup toàn bộ dữ liệu quan trọng trước khi thực hiện.

### **S2: Chuẩn bị partition**

Vào **Disk Management**, đảm bảo có ít nhất **7GB** để chứa file boot OS và thêm dung lượng cho dữ liệu của OS khác.

Tách 2 partition từ ổ `C:\`:

* Một partition **7GB**, định dạng **FAT32** (ổ `D:\`).
* Một partition **trống** để cài OS (ổ `E:\`).

### **S3: Copy file ISO**

Copy file ISO Ubuntu vào ổ `D:\`.

*Tùy chọn:* Có thể khóa ổ `D:\` bằng EFI ID để tránh thay đổi dữ liệu.

### **S4: Truy cập BIOS**

Restart máy, vào BIOS bằng **F12** (hoặc **F2** nếu máy boot nhanh).

### **S5: Cấu hình BIOS**

Trong BIOS:

* Tắt **Secure Boot** và **Fast Boot**.
* Bật **F12 Boot Menu**.
* Đặt **Supervisor Password**.
* Nhấn `Ctrl + S` để hiện menu ẩn, sau đó đổi **SATA Mode** từ **RAID/Intel RST** sang **AHCI**.

### **S6: Boot và cài Ubuntu**

Save & Exit BIOS.

Boot lại, chọn **“Try or Install Ubuntu”** từ GRUB và tiến hành cài đặt.

---

## **[Trong trường hợp dual-boot với Windows]**

* Nếu gặp lỗi **INACCESSIBLE_BOOT_DEVICE**, hãy bật **Safe Mode** trong Windows trước khi đổi SATA Mode. Nếu quên, dùng chế độ **Recovery** để khởi động lại Windows.

* Windows 10/11 thường cài theo chuẩn **UEFI**, vì vậy hãy chọn boot mode là **UEFI**.

* Sau khi cài Linux, có thể xóa file ISO trong ổ `D:\` và gộp lại với ổ `E:\` để làm dữ liệu mới. Nhớ bật lại flag boot cho Windows nếu đã tạm tắt.

---

# **WARNING!!!**

* Đây là cách dual-boot không sử dụng ứng dụng hỗ trợ như **Rufus**, có thể gây mất dữ liệu nếu thao tác sai.

* Luôn **backup dữ liệu** trước khi thực hiện.

* Một số dòng máy khác (**Dell, ASUS, HP, Lenovo**) cũng cần đổi sang **AHCI** (ASUS có thể chỉ cần tắt **“Enable VMD Controlled”**).

* Các bước trên dựa trên **kinh nghiệm cá nhân**, không phải hướng dẫn chính thức. Có thể tham khảo thêm trên Reddit hoặc liên hệ qua email: **[aiies10022006@gmail.com](mailto:aiies10022006@gmail.com)**.

---

**Zem.**
