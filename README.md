# 🚀 ĐỒ ÁN CHUYÊN NGÀNH: HỆ THỐNG NGHIÊN CỨU LỖ HỔNG TRÀN SỐ NGUYÊN (V2.1)

## 📋 Giới thiệu
Dự án này là một nền tảng thực nghiệm nhằm nghiên cứu, phân tích và trình diễn lỗi **Tràn số nguyên (Integer Overflow)** — một trong những lỗ hổng bảo mật cơ bản nhưng cực kỳ nguy hiểm trong lập trình C/C++. 

Hệ thống được thiết kế theo mô hình 3 góc nhìn giúp người dùng hiểu rõ từ nguyên nhân, cách phát hiện đến cơ chế phòng thủ.

---

## 🏗️ Phân tích các thành phần chức năng

### 1. [Vulnerability Researcher] - Góc nhìn Lập trình viên
Nhiệm vụ chính là trình diễn các kịch bản lỗi cơ bản trong logic ứng dụng:
- **Nhân hai số**: Trình diễn lỗi tràn số khi kết quả nhân vượt ngưỡng kiểu dữ liệu `int`, dẫn đến việc cấp phát bộ nhớ sai kích thước (Heap Overflow).
- **Cộng địa chỉ (Base + Offset)**: Mô phỏng lỗi tính toán chỉ số mảng, dẫn đến việc truy cập trái phép vào các ô nhớ ngoài phạm vi cho phép.
- **Ép kiểu dữ liệu (Size Conversion)**: Trình diễn lỗi nguy hiểm khi số nguyên có dấu (âm) bị ép sang kiểu không dấu (`size_t`), tạo ra các giá trị cực lớn dễ gây sập hệ thống (Crash).
- **Cơ chế Safe Mode**: Cung cấp các phương pháp kiểm tra toán học ưu việt để **chặn** hoàn toàn các lỗi trên trước khi chúng xảy ra.

### 2. [OS Security Analyst] - Góc nhìn Chuyên gia Hệ điều hành
Nhiệm vụ là phân tích các lớp bảo vệ tầng thấp của Hệ điều hành (Windows/Linux) đối với lỗi tràn số:
- **ASLR (Address Space Layout Randomization)**: Trình bày cơ chế làm xáo trộn địa chỉ bộ nhớ (Stack, Heap, Code) để ngăn chặn kẻ tấn công đoán được vị trí mã độc.
- **DEP/NX (Data Execution Prevention)**: Phân tích cách CPU ngăn chặn việc thực thi mã tại các vùng nhớ dữ liệu, hạn chế tác động của shellcode.
- **Stack Canary**: Minh họa cơ chế "Chim báo bão" trên ngăn xếp giúp phát hiện sớm các hành vi ghi đè dữ liệu bất hợp pháp.

### 3. [Red Team Operator] - Góc nhìn Tấn công (Exploitation)
Nhiệm vụ là tự động hóa các kịch bản tấn công thực tế (Proof of Concept):
- Tự động nạp các payload đặc biệt (Max Int, Wrap Square) để gây lỗi hệ thống mà không cần can thiệp thủ công.
- Kiểm chứng hiệu quả của các cơ chế bảo mật đã thiết lập.

---

## 🛠️ Hướng dẫn Vận hành

### Yêu cầu hệ thống
- Biên dịch bằng **g++** (MinGW/MINGW64).

### Các bước thực hiện
1. **Đóng** chương trình nếu đang chạy.
2. **Build** project:
   ```bash
   g++ -o Integer_Overflow_Vulnerabilities.exe Integer_Overflow_Vulnerabilities.cpp
   ```
3. **Run**:
   ```bash
   ./Integer_Overflow_Vulnerabilities.exe
   ```

### 💡 Lưu ý quan trọng
Để thấy **ASLR** hoạt động (địa chỉ thay đổi), bạn phải **thoát hoàn toàn và khởi động lại** chương trình cho mỗi lần kiểm tra.

---
© 2026 Vulnerability Research Team - Educational Purposes Only
