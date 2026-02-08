# Thư viện JDY33 Bluetooth Classic cho MSP430G2553

Thư viện này hỗ trợ giao tiếp **Bluetooth Classic JDY-33** với **MSP430G2553 LaunchPad** thông qua UART.  
Project hướng tới mục tiêu **đơn giản – dễ học – dễ mở rộng**, phù hợp cho MSP430 và Bluetooth Classic.

---

## 📌 Tổng quan

- Vi điều khiển: **MSP430G2553 (LaunchPad)**
- Module Bluetooth: **JDY-33**
- Chuẩn Bluetooth: **Bluetooth Classic**
- Chế độ hoạt động: **Slave**
- Giao tiếp: **UART**
- Ngôn ngữ: **C / C++**
- App điện thoại: **Serial Bluetooth Terminal (Android)**

---

## ⚠️ Giới hạn của thư viện

- ❌ Không hỗ trợ BLE
- ❌ Không hỗ trợ Master mode
- ❌ Chỉ dùng cho Bluetooth Classic
- ❌ Chưa hỗ trợ AT command nâng cao

Thư viện tập trung vào **truyền nhận dữ liệu UART ổn định**, không tối ưu cho cấu hình nâng cao.

---

## 🧩 Phần cứng sử dụng

| Thiết bị | Mô tả |
|--------|------|
| MSP430G2553 | LaunchPad của Texas Instruments |
| JDY-33 | Bluetooth Classic UART |
| LED | LED onboard P1.0 |

---

## 🔌 Sơ đồ kết nối phần cứng

Sơ đồ kết nối chi tiết giữa **JDY-33** và **MSP430G2553**:

🔗 Link ảnh sơ đồ kết nối:  
**[link ảnh sơ đồ]**

### Mapping chân cơ bản

| JDY-33 | MSP430G2553 |
|------|------------|
| TXD | RX (UART) |
| RXD | TX (UART) |
| VCC | 3.3V |
| GND | GND |

⚠️ **Lưu ý:** JDY-33 hoạt động mức logic 3.3V, tương thích trực tiếp với MSP430.

---

## 📱 Ứng dụng trên điện thoại

- Tên app: **Serial Bluetooth Terminal**
- Nền tảng: **Android**
- Công dụng:
  - Kết nối Bluetooth Classic
  - Gửi dữ liệu ký tự
  - Nhận chuỗi từ vi điều khiển
  - Quan sát dữ liệu UART theo thời gian thực

---

## 🎥 Demo hoạt động

### ▶️ Kết nối Bluetooth trên app Android

- Mở app Serial Bluetooth Terminal
- Quét thiết bị
- Kết nối JDY-33 với tên đã đặt trước đó
- Gửi / nhận dữ liệu

### ▶️ Demo: Chạy code ví dụ (`src/main.c`)

- MSP430 gửi chuỗi định kỳ mỗi 1–2 giây
- Nhận ký tự từ app để điều khiển LED

🔗 Link clip demo code:  
**[link video demo main.cpp]**

---
