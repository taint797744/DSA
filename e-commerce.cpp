#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;


// 1. CẤU TRÚC DỮ LIỆU
// Cấu trúc sản phẩm trong kho hàng mẫu
struct Product {
    string id;
    string name;
    double price;
    int stock;
};

// Cấu trúc một Node trong Danh Sách Liên Kết Đôi (CartItem)
struct CartNode {
    string id;         // Mã sản phẩm
    string name;       // Tên sản phẩm
    double price;      // Đơn giá
    int quantity;      // Số lượng đặt mua

    CartNode* prev;    // Con trỏ tới phần tử đứng trước
    CartNode* next;    // Con trỏ tới phần tử đứng sau

    // Constructor khởi tạo một node mới
    CartNode(string _id, string _name, double _price, int _qty)
        : id(_id), name(_name), price(_price), quantity(_qty), prev(nullptr), next(nullptr) {}
};

// Lớp Quản lý Giỏ hàng bằng Danh sách liên kết đôi
class ShoppingCart {
private:
    CartNode* head;    // Con trỏ trỏ tới đầu danh sách
    CartNode* tail;    // Con trỏ trỏ tới cuối danh sách
    int totalItems;    // Số loại mặt hàng hiện có trong giỏ

public:
    // Khởi tạo giỏ hàng rỗng
    ShoppingCart() : head(nullptr), tail(nullptr), totalItems(0) {}

    // Destructor: Giải phóng toàn bộ bộ nhớ Heap khi chương trình kết thúc
    ~ShoppingCart() {
        clearCart();
    }

    // Kiểm tra giỏ hàng có rỗng hay không
    bool isEmpty() const {
        return head == nullptr;
    }

    // Tìm kiếm một mặt hàng trong giỏ theo Mã sản phẩm (ID)
    CartNode* findItem(const string& id) const {
        CartNode* curr = head;
        while (curr != nullptr) {
            if (curr->id == id) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    // Thêm mặt hàng vào giỏ hàng
    void addItem(const string& id, const string& name, double price, int qty) {
        if (qty <= 0) {
            cout << "[-] So luong them phai lon hon 0!\n";
            return;
        }

        // Bước 1: Kiểm tra xem sản phẩm đã có trong giỏ chưa
        CartNode* existing = findItem(id);
        if (existing != nullptr) {
            existing->quantity += qty;
            cout << "[+] Da cap nhat so luong cho mat hang [" << name << "] thanh cong! (Tong: " << existing->quantity << ")\n";
            return;
        }

        // Bước 2: Tạo node mới nếu sản phẩm chưa tồn tại
        CartNode* newNode = new CartNode(id, name, price, qty);

        // Bước 3: Nối node vào danh sách liên kết đôi
        if (isEmpty()) {
            // Giỏ hàng đang rỗng: node mới vừa là head vừa là tail
            head = tail = newNode;
        } else {
            // Giỏ hàng đã có phần tử: móc vào sau tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        totalItems++;
        cout << "[+] Da them mat hang [" << name << "] vao gio hang thanh cong!\n";
    }

    // Cập nhật số lượng mặt hàng
    bool updateQuantity(const string& id, int newQty) {
        CartNode* item = findItem(id);
        if (item == nullptr) {
            cout << "[-] Khong tim thay mat hang co ma [" << id << "] trong gio hang!\n";
            return false;
        }

        if (newQty <= 0) {
            cout << "[!] So luong <= 0. Tien hanh xoa mat hang khoi gio...\n";
            return removeItem(id);
        }

        item->quantity = newQty;
        cout << "[+] Cap nhat so luong cho [" << item->name << "] thanh cong! (So luong moi: " << newQty << ")\n";
        return true;
    }

    // Xóa một mặt hàng khỏi giỏ hàng (Xử lý đầy đủ các trường hợp con trỏ)
    bool removeItem(const string& id) {
        CartNode* curr = findItem(id);
        if (curr == nullptr) {
            cout << "[-] Khong tim thay mat hang co ma [" << id << "] de xoa!\n";
            return false;
        }

        string removedName = curr->name;

        // Trường hợp 1: Giỏ hàng chỉ có đúng 1 node duy nhất
        if (head == tail) {
            head = tail = nullptr;
        }
        // Trường hợp 2: Node cần xóa nằm ở đầu danh sách (head)
        else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // Trường hợp 3: Node cần xóa nằm ở cuối danh sách (tail)
        else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // Trường hợp 4: Node cần xóa nằm ở giữa danh sách
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        // Thu hồi vùng nhớ Heap của node
        delete curr;
        totalItems--;
        cout << "[+] Da xoa mat hang [" << removedName << "] khoi gio hang!\n";
        return true;
    }

    // Xóa toàn bộ giỏ hàng (Chống rò rỉ bộ nhớ - Memory Leak)
    void clearCart() {
        CartNode* curr = head;
        while (curr != nullptr) {
            CartNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = tail = nullptr;
        totalItems = 0;
    }

    // Tính tổng tiền toàn bộ giỏ hàng
    double calculateTotal() const {
        double total = 0.0;
        CartNode* curr = head;
        while (curr != nullptr) {
            total += (curr->price * curr->quantity);
            curr = curr->next;
        }
        return total;
    }

    // Hiển thị giỏ hàng (Hỗ trợ duyệt xuôi head->tail và duyệt ngược tail->head)
    void displayCart(bool reverseOrder = false) const {
        if (isEmpty()) {
            cout << "\n=======================================================\n";
            cout << "          GIO HANG CUA BAN DANG TRONG!                 \n";
            cout << "=======================================================\n";
            return;
        }

        cout << "\n" << string(70, '=') << "\n";
        if (!reverseOrder) {
            cout << "           CHI TIET GIO HANG (DUYET XUOI: CU -> MOI)                  \n";
        } else {
            cout << "           CHI TIET GIO HANG (DUYET NGUOC: MOI -> CU)                 \n";
        }
        cout << string(70, '=') << "\n";
        cout << left << setw(8) << "MA SP"
             << setw(24) << "TEN SAN PHAM"
             << right << setw(12) << "DON GIA (d)"
             << setw(10) << "SO LUONG"
             << setw(16) << "THANH TIEN (d)" << "\n";
        cout << string(70, '-') << "\n";

        CartNode* curr = (!reverseOrder) ? head : tail;
        while (curr != nullptr) {
            double subtotal = curr->price * curr->quantity;
            cout << left << setw(8) << curr->id
                 << setw(24) << curr->name
                 << right << setw(12) << fixed << setprecision(0) << curr->price
                 << setw(10) << curr->quantity
                 << setw(16) << fixed << setprecision(0) << subtotal << "\n";

            curr = (!reverseOrder) ? curr->next : curr->prev;
        }

        cout << string(70, '-') << "\n";
        cout << right << setw(54) << "TONG CONG TAM TINH: "
             << setw(16) << fixed << setprecision(0) << calculateTotal() << " d\n";
        cout << string(70, '=') << "\n";
    }

    // Tạo đơn hàng (Checkout): In hóa đơn, ghi file và dọn giỏ hàng
    void checkout(const string& customerName, const string& orderId) {
        if (isEmpty()) {
            cout << "[-] Gio hang dang trong, khong the tao don hang!\n";
            return;
        }

        double totalAmount = calculateTotal();

        cout << "\n" << string(55, '=') << "\n";
        cout << "                  HOA DON THANH TOAN                    \n";
        cout << string(55, '=') << "\n";
        cout << " Ma don hang  : " << orderId << "\n";
        cout << " Khach hang   : " << customerName << "\n";
        cout << string(55, '-') << "\n";

        // Ghi lưu trữ ra file orders.txt
        ofstream outFile("orders.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "========================================\n";
            outFile << "DON HANG: " << orderId << " | KHACH: " << customerName << "\n";
        }

        CartNode* curr = head;
        while (curr != nullptr) {
            double sub = curr->price * curr->quantity;
            cout << " - " << left << setw(20) << curr->name
                 << " x" << setw(4) << curr->quantity
                 << " = " << fixed << setprecision(0) << sub << " d\n";

            if (outFile.is_open()) {
                outFile << curr->id << " | " << curr->name << " | SL: " << curr->quantity
                        << " | Don gia: " << curr->price << " | Thanh tien: " << sub << "\n";
            }
            curr = curr->next;
        }

        cout << string(55, '-') << "\n";
        cout << " TONG TIEN THANH TOAN: " << fixed << setprecision(0) << totalAmount << " d\n";
        cout << string(55, '=') << "\n";

        if (outFile.is_open()) {
            outFile << "TONG CONG: " << totalAmount << " d\n";
            outFile << "========================================\n\n";
            outFile.close();
            cout << "[+] Da luu thong tin don hang vao file 'orders.txt'!\n";
        }

        // Sau khi đặt hàng thành công, dọn sạch giỏ
        clearCart();
        cout << "[+] Don hang da duoc tao thanh cong! Gio hang da duoc lam rong.\n";
    }
};

// ==========================================
// 2. KHO HÀNG MẪU & CÁC HÀM TIỆN ÍCH
// ==========================================

// Danh mục các sản phẩm mẫu có sẵn
vector<Product> catalog = {
    {"SP01", "Chuot Logitech G102", 400000, 20},
    {"SP02", "Ban phim co Akko 3087", 950000, 15},
    {"SP03", "Tai nghe Gaming HyperX", 1200000, 10},
    {"SP04", "Lot chuot Gaming RGB", 150000, 50},
    {"SP05", "Gia do Laptop nhom", 250000, 30}
};

// Hiển thị danh mục sản phẩm của cửa hàng
void displayCatalog() {
    cout << "\n" << string(65, '=') << "\n";
    cout << "             DANH MUC SAN PHAM CO SAN TAI CUA HANG               \n";
    cout << string(65, '=') << "\n";
    cout << left << setw(8) << "MA SP"
         << setw(26) << "TEN SAN PHAM"
         << right << setw(15) << "DON GIA (d)"
         << setw(14) << "SO LUONG TON" << "\n";
    cout << string(65, '-') << "\n";
    for (const auto& p : catalog) {
        cout << left << setw(8) << p.id
             << setw(26) << p.name
             << right << setw(15) << fixed << setprecision(0) << p.price
             << setw(14) << p.stock << "\n";
    }
    cout << string(65, '=') << "\n";
}

// Tìm sản phẩm trong kho mẫu theo ID
const Product* findProductInCatalog(const string& id) {
    for (const auto& p : catalog) {
        if (p.id == id) return &p;
    }
    return nullptr;
}

// Hàm hỗ trợ nhập số nguyên an toàn, chống trôi lệnh khi người dùng nhập chữ
int inputInteger(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "[-] Loi: Gia tri nhap vao phai la so nguyen! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 3. CHƯƠNG TRÌNH CHÍNH (MENU ĐIỀU KHIỂN)

int main() {
    ShoppingCart cart;
    int choice;
    int orderCounter = 1001;

    cout << "\n=======================================================\n";
    cout << "   CHUONG TRINH QUAN LY GIO HANG TRUC TUYEN (C++)      \n";
    cout << "   Mon hoc: Cau truc Du lieu va Giai thuat             \n";
    cout << "=======================================================\n";

    do {
        cout << "\n--------------- MENU CHUC NANG ----------------\n";
        cout << "1. Xem danh muc san pham cua cua hang\n";
        cout << "2. Them mat hang vao gio hang\n";
        cout << "3. Xem gio hang (Duyet xuoi: Cu nhat truoc)\n";
        cout << "4. Xem gio hang (Duyet nguoc: Moi nhat truoc)\n";
        cout << "5. Cap nhat so luong mot mat hang trong gio\n";
        cout << "6. Xoa mot mat hang khoi gio hang\n";
        cout << "7. Xoa toan bo gio hang (Lam rong gio)\n";
        cout << "8. Tao don hang (Checkout & In hoa don)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "-----------------------------------------------\n";
        
        choice = inputInteger(">> Vui long chon chuc nang (0-8): ");

        switch (choice) {
            case 1: {
                displayCatalog();
                break;
            }
            case 2: {
                displayCatalog();
                cout << "\n>> Nhap ma san pham can them vao gio (VD: SP01): ";
                string pid;
                cin >> pid;
                const Product* prod = findProductInCatalog(pid);
                if (prod == nullptr) {
                    cout << "[-] Ma san pham khong ton tai trong he thong!\n";
                } else {
                    int qty = inputInteger(">> Nhap so luong can mua: ");
                    if (qty <= 0) {
                        cout << "[-] So luong phai lon hon 0!\n";
                    } else if (qty > prod->stock) {
                        cout << "[-] So luong vuot qua ton kho hien co (" << prod->stock << ")!\n";
                    } else {
                        cart.addItem(prod->id, prod->name, prod->price, qty);
                    }
                }
                break;
            }
            case 3: {
                cart.displayCart(false); // Duyệt xuôi
                break;
            }
            case 4: {
                cart.displayCart(true);  // Duyệt ngược
                break;
            }
            case 5: {
                if (cart.isEmpty()) {
                    cout << "[-] Gio hang dang trong!\n";
                    break;
                }
                cart.displayCart(false);
                cout << "\n>> Nhap ma SP can cap nhat so luong: ";
                string pid;
                cin >> pid;
                int newQty = inputInteger(">> Nhap so luong moi (nhap 0 de xoa): ");
                cart.updateQuantity(pid, newQty);
                break;
            }
            case 6: {
                if (cart.isEmpty()) {
                    cout << "[-] Gio hang dang trong!\n";
                    break;
                }
                cart.displayCart(false);
                cout << "\n>> Nhap ma SP muon xoa khoi gio: ";
                string pid;
                cin >> pid;
                cart.removeItem(pid);
                break;
            }
            case 7: {
                if (cart.isEmpty()) {
                    cout << "[-] Gio hang da dang trong san roi!\n";
                    break;
                }
                cout << ">> Ban co chac chan muon xoa sach gio hang khong? (1: Co / 0: Huy): ";
                int confirm;
                cin >> confirm;
                if (confirm == 1) {
                    cart.clearCart();
                    cout << "[+] Da xoa sach toan bo gio hang!\n";
                } else {
                    cout << "[*] Da huy thao tac.\n";
                }
                break;
            }
            case 8: {
                if (cart.isEmpty()) {
                    cout << "[-] Gio hang dang trong, khong the dat hang!\n";
                    break;
                }
                cart.displayCart(false);
                cout << "\n>> Nhap ten khach hang: ";
                string custName;
                getline(cin, custName);
                if (custName.empty()) custName = "Khach vang lai";

                string orderId = "ORD-" + to_string(orderCounter++);
                cart.checkout(custName, orderId);
                break;
            }
            case 0: {
                cout << "\n[*] Cam on ban da su dung chuong trinh! Tam biet.\n";
                break;
            }
            default: {
                cout << "[-] Lua chon khong hop le! Vui long chon tu 0 den 8.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
