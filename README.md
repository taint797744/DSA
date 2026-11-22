# 🛒 QUẢN LÝ GIỎ HÀNG TRỰC TUYẾN (Online Shopping Cart)

> **Bài tập Dự án Học phần:** Cấu trúc Dữ liệu và Giải thuật  
> **Cấu trúc dữ liệu chính:** Danh sách liên kết đôi (Doubly Linked List)  
> **Ngôn ngữ:** C++ (chuẩn C++11)

---

## 📖 Mô tả Dự án

Chương trình mô phỏng hệ thống **giỏ hàng mua sắm trực tuyến** hoàn chỉnh, được xây dựng hoàn toàn bằng **Danh sách liên kết đôi (Doubly Linked List)** thủ công qua con trỏ thuần trong C++, không sử dụng thư viện trừu tượng hóa có sẵn (`std::list`).

Người dùng tương tác qua giao diện Menu dòng lệnh (CLI) để thực hiện các thao tác: duyệt kho hàng, thêm sản phẩm vào giỏ, xem giỏ hàng 2 chiều (xuôi/ngược), cập nhật số lượng, xóa sản phẩm và đặt đơn hàng (Checkout) với hóa đơn được lưu ra file.

---

## ✨ Chức năng chính

| STT | Chức năng | Mô tả |
|:---:|:---|:---|
| 1 | Xem danh mục kho hàng | Hiển thị bảng 5 sản phẩm mẫu có sẵn (Mã SP, Tên, Giá, Tồn kho) |
| 2 | Thêm mặt hàng vào giỏ | Nếu SP chưa có → tạo node mới móc vào `tail`. Nếu đã có → cộng dồn số lượng |
| 3 | Xem giỏ hàng (Duyệt xuôi) | Duyệt từ `head` → `tail`, hiển thị bảng chi tiết + tổng tiền tạm tính |
| 4 | Xem giỏ hàng (Duyệt ngược) | Duyệt từ `tail` → `head`, hiển thị món mới thêm gần nhất trước |
| 5 | Cập nhật số lượng | Tìm node theo Mã SP, cập nhật `quantity` mới (nhập 0 → tự động xóa) |
| 6 | Xóa một mặt hàng | Xử lý đầy đủ 4 trường hợp con trỏ: node duy nhất, đầu, cuối, giữa |
| 7 | Làm rỗng giỏ hàng | Vòng lặp `delete` từng node, gán `head = tail = nullptr` |
| 8 | Tạo đơn hàng (Checkout) | In hóa đơn chi tiết, ghi lưu vào file `orders.txt`, làm rỗng giỏ |

---

## 🏗️ Cấu trúc Dữ liệu

### Node Danh sách liên kết đôi (`CartNode`)

```
         ┌──────────────────────────────────────────────┐
         │                  CartNode                     │
         ├──────────┬───────────────────────┬────────────┤
         │  prev *  │  id | name | price | qty  │  next *  │
         └──────────┴───────────────────────┴────────────┘
```

### Giỏ hàng (`ShoppingCart`) — Quản lý DSLK đôi

```
  head                                                          tail
   │                                                             │
   ▼                                                             ▼
┌──────┐     ┌──────┐     ┌──────┐     ┌──────┐     ┌──────┐
│ SP01 │◄───►│ SP03 │◄───►│ SP02 │◄───►│ SP05 │◄───►│ SP04 │
│      │next │      │next │      │next │      │next │      │
│ prev │◄────│ prev │◄────│ prev │◄────│ prev │◄────│ prev │
│=null │     │      │     │      │     │      │     │next= │
│      │     │      │     │      │     │      │     │ null │
└──────┘     └──────┘     └──────┘     └──────┘     └──────┘
```

---

## 📂 Cấu trúc Thư mục

```
QuanLyGioHang/
├── main.cpp                  # Mã nguồn C++ duy nhất (đầy đủ chức năng)
├── orders.txt                # File lưu lịch sử đơn hàng (tự tạo khi Checkout)
├── Bao_Cao_Du_An_Gio_Hang.docx  # Báo cáo Word theo chuẩn 8 mục của học phần
└── README.md                 # Tài liệu hướng dẫn (file này)
```

---

## 🚀 Hướng dẫn Biên dịch và Chạy

### Yêu cầu
- Trình biên dịch C++ hỗ trợ chuẩn **C++11** trở lên (GCC, Clang, MSVC đều được)

### Cách 1: Dùng dòng lệnh (Terminal / CMD)

```bash
# Biên dịch
g++ -std=c++11 -o main main.cpp

# Chạy chương trình
./main          # Linux / macOS
main.exe        # Windows
```

### Cách 2: Dùng IDE
- **Dev-C++ / Code::Blocks:** Mở file `main.cpp` → Nhấn F9 (Build & Run).
- **Visual Studio:** Tạo Empty Project → Add Existing Item → chọn `main.cpp` → Ctrl+F5.
- **VS Code:** Cài extension C/C++ → mở `main.cpp` → Terminal → chạy lệnh biên dịch ở trên.

---

## 🎮 Hướng dẫn Sử dụng

Sau khi chạy chương trình, menu chức năng sẽ hiển thị:

```
--------------- MENU CHUC NANG ----------------
1. Xem danh muc san pham cua cua hang
2. Them mat hang vao gio hang
3. Xem gio hang (Duyet xuoi: Cu nhat truoc)
4. Xem gio hang (Duyet nguoc: Moi nhat truoc)
5. Cap nhat so luong mot mat hang trong gio
6. Xoa mot mat hang khoi gio hang
7. Xoa toan bo gio hang (Lam rong gio)
8. Tao don hang (Checkout & In hoa don)
0. Thoat chuong trinh
-----------------------------------------------
>> Vui long chon chuc nang (0-8):
```

**Ví dụ nhanh:**
1. Nhấn `1` để xem kho hàng có những sản phẩm nào.
2. Nhấn `2` → nhập mã `SP01` → nhập số lượng `2` → Chuột Logitech G102 được thêm vào giỏ.
3. Nhấn `3` để xem giỏ hàng với bảng chi tiết và tổng tiền.
4. Nhấn `8` để thanh toán → nhập tên → nhận hóa đơn và file `orders.txt` được ghi tự động.

---

## ⏱️ Phân tích Độ phức tạp

| Thao tác | Thời gian | Không gian | Ghi chú |
|:---|:---:|:---:|:---|
| Tìm kiếm (`findItem`) | O(N) | O(1) | Duyệt tuần tự từ `head` |
| Thêm món (`addItem`) | O(N) | O(1) | O(N) do tìm trùng lặp trước khi chèn O(1) |
| Xóa món (`removeItem`) | O(N) | O(1) | O(N) tìm kiếm + O(1) bẻ con trỏ |
| Duyệt giỏ (`displayCart`) | O(N) | O(1) | Hỗ trợ cả 2 chiều xuôi/ngược |
| Tính tổng tiền (`calculateTotal`) | O(N) | O(1) | Cộng dồn `price × quantity` |
| Xóa toàn bộ (`clearCart`) | O(N) | O(1) | Giải phóng từng node trên Heap |

> **N** = số loại mặt hàng hiện có trong giỏ hàng.

---

## 🛡️ Xử lý An toàn

| Vấn đề | Giải pháp trong code |
|:---|:---|
| **Rò rỉ bộ nhớ (Memory Leak)** | Destructor `~ShoppingCart()` tự động gọi `clearCart()` giải phóng toàn bộ node Heap khi kết thúc chương trình |
| **Con trỏ lơ lửng (Dangling Pointer)** | Sau mỗi lần `delete`, các con trỏ `head`/`tail` liên quan được gán `nullptr` ngay lập tức |
| **Lỗi nhập liệu (Invalid Input)** | Hàm `inputInteger()` kiểm tra `cin.fail()`, xóa cờ lỗi `cin.clear()` và xả bộ đệm `cin.ignore()` — không bao giờ bị treo vòng lặp |
| **Thao tác trên giỏ rỗng** | Kiểm tra `isEmpty()` trước mọi thao tác xem/sửa/xóa/checkout |

---

## 👥 Thành viên Nhóm

| Vai trò | Nhiệm vụ chính |
|:---|:---|
| **Thành viên 1** (Trưởng nhóm) | Thiết kế kiến trúc & Cài đặt toàn bộ mã nguồn C++ |
| **Thành viên 2** | Kiểm thử các trường hợp biên & Chụp ảnh màn hình minh chứng |
| **Thành viên 3** | Phân tích giải thuật, vẽ sơ đồ DSLK đôi & Lưu đồ thuật toán |
| **Thành viên 4** | Soạn thảo Báo cáo Word & Viết mục khai thác AI |
| **Thành viên 5** | Tạo dữ liệu mẫu, thiết kế Slide & Kịch bản Demo trực tiếp |

---

## 📝 Ghi chú

- Chương trình sử dụng **font không dấu** trên giao diện Console để tương thích mọi hệ điều hành (Windows CMD, PowerShell, Terminal Linux/macOS) mà không bị lỗi mã hóa ký tự.
- File `orders.txt` được ghi ở chế độ **append** (`ios::app`), nghĩa là mỗi lần checkout sẽ nối tiếp đơn hàng mới vào cuối file mà không ghi đè đơn cũ.
- Danh mục kho hàng mẫu (`catalog`) gồm 5 sản phẩm được khởi tạo cứng trong code. Có thể mở rộng bằng cách đọc từ file `products.txt` nếu cần.
