/*
 * ===================================================================
 * ĐỒ ÁN CHUYÊN NGÀNH: INTEGER OVERFLOW VULNERABILITY RESEARCH SYSTEM
 * File: Integer_Overflow_Vulnerabilities.cpp
 * Phiên bản: 2.0 (Merged Ultimate Edition)
 * Mô tả: Hệ thống nghiên cứu toàn diện về lỗ hổng tràn số nguyên
 * Bao gồm: Core Researcher, OS Security Analyst, và Red Team Operator
 * Author: Vulnerability Research Team
 * ===================================================================
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// ===================================================================
// MODULE 1: VULNERABILITY RESEARCHER (CORE LOGIC)
// ===================================================================

class VulnerabilityResearcher {
public:
    struct PacketHeader {
        uint32_t magic;
        uint16_t data_len;
        uint16_t header_len;
    };

    void vulnerable_multiplication(int a, int b) {
        cout << "\n[!] VULNERABLE MULTIPLICATION (TRÀN SỐ KHI NHÂN)" << endl;
        cout << "    Input: " << a << " * " << b << endl;
        int result = a * b;
        cout << "    Kết quả: " << result << " (0x" << hex << result << dec << ")" << endl;
        
        char* buffer = (char*)malloc(result);
        if (buffer) {
            cout << "    => Cấp phát thành công " << result << " bytes." << endl;
            memset(buffer, 'X', (result > 0 ? result : 1));
            cout << "    => Thực hiện memset thành công (Dễ dẫn đến Heap Overflow)." << endl;
            free(buffer);
        } else {
            cout << "    => LỖI: Cấp phát bộ nhớ thất bại (Size quá lớn hoặc âm)." << endl;
        }
    }

    void vulnerable_addition(int base, int offset) {
        cout << "\n[!] VULNERABLE ADDITION (TRÀN SỐ KHI CỘNG/INDEX)" << endl;
        cout << "    Base: " << base << " + Offset: " << offset << endl;
        int total = base + offset;
        cout << "    Total: " << total << endl;
        
        if (total >= 0) {
            int* array = new int[100];
            if (total < 100) {
                array[total] = 999;
                cout << "    => array[" << total << "] = " << array[total] << " (Thao tác thành công)." << endl;
            } else {
                cout << "    => PHÁT HIỆN: Chống tràn bộ nhớ mảng (Total >= 100)." << endl;
            }
            delete[] array;
        } else {
            cout << "    => CẢNH BÁO: Index âm do tràn số!" << endl;
        }
    }

    void vulnerable_size_conversion(int len) {
        cout << "\n[!] VULNERABLE SIZE CONVERSION (LỖI ÉP KIỂU)" << endl;
        cout << "    Input int: " << len << endl;
        size_t size = (size_t)len;
        cout << "    Converted to size_t: " << size << endl;
        
        if (len < 0) {
            cout << "    => CẢNH BÁO: Số âm chuyển sang size_t trở thành số dương cực lớn!" << endl;
        }
        
        char* buffer = (char*)malloc(size);
        if (buffer) {
            cout << "    => Cấp phát thành công " << size << " bytes." << endl;
            free(buffer);
        } else {
            cout << "    => Cấp phát bộ nhớ thất bại." << endl;
        }
    }

    void vulnerable_packet_parser() {
        cout << "\n[!] NETWORK PACKET PARSING (PHÂN TÍCH GÓI TIN)" << endl;
        PacketHeader packet = {0xDEADBEEF, 0xFFFF, 0xFFFF}; // 65535, 65535
        cout << "    Data Len: " << packet.data_len << ", Header Len: " << packet.header_len << endl;
        
        uint32_t total_size = packet.data_len + packet.header_len;
        cout << "    Calculated Total (uint32): " << total_size << endl;
        
        char* buffer = (char*)malloc(total_size);
        if (buffer) {
            cout << "    => Cấp phát buffer gói tin: " << total_size << " bytes." << endl;
            memset(buffer, 0, total_size);
            free(buffer);
        }
    }

    void safe_multiplication(int a, int b) {
        cout << "\n[+] CHIẾN LƯỢC PHÒNG NGỪA: SAFE MULTIPLICATION" << endl;
        if (a > 0 && b > 0 && a > INT_MAX / b) {
            cout << "    [!] PHÁT HIỆN TRÀN SỐ: Thao tác bị từ chối." << endl;
            return;
        }
        int result = a * b;
        cout << "    Kết quả an toàn: " << result << endl;
    }
};

// ===================================================================
// MODULE 2: OS SECURITY ANALYST (SYSTEM PROTECTIONS)
// ===================================================================

int global_var = 1234;

class OSSecurityAnalyst {
public:
    static void analyze_aslr() {
        int local_var = 10;
        cout << "\n[2.1] PHÂN TÍCH ASLR (Address Space Layout Randomization)" << endl;
        cout << "    Stack Address:  0x" << hex << (uintptr_t)&local_var << endl;
        cout << "    Data Address:   0x" << hex << (uintptr_t)&global_var << endl;
        cout << "    Code Address:   0x" << hex << (uintptr_t)&analyze_aslr << dec << endl;
        cout << "    (*) Chạy lại chương trình để kiểm tra địa chỉ có thay đổi không." << endl;
    }

    static void analyze_dep_nx() {
        cout << "\n[2.2] PHÂN TÍCH DEP/NX (Data Execution Prevention)" << endl;
        unsigned char shellcode[] = { 0x90, 0x90, 0xCC }; 
        cout << "    Shellcode giả lập tại Stack: 0x" << hex << (uintptr_t)shellcode << dec << endl;
        cout << "    => DEP ngăn chặn CPU thực thi mã tại vùng nhớ dữ liệu này." << endl;
    }

    static void analyze_stack_canary() {
        cout << "\n[2.3] PHÂN TÍCH STACK CANARY (BẢO VỆ STACK)" << endl;
        struct {
            char buffer[8];
            uint32_t canary;
            uintptr_t ret_addr;
        } fake_stack;
        
        fake_stack.canary = 0xDEADBEEF;
        cout << "    Canary ban đầu: 0x" << hex << fake_stack.canary << endl;
        
        cout << "    Giả lập ghi đè buffer (Overflow)..." << endl;
        for(int i = 0; i < 10; i++) fake_stack.buffer[i] = 'A';
        
        cout << "    Canary sau khi ghi đè: 0x" << fake_stack.canary << dec << endl;
        if (fake_stack.canary != 0xDEADBEEF) {
            cout << "    [!] CẢNH BÁO: Stack Canary bị hỏng! (Phát hiện tấn công)." << endl;
        }
    }
};

// ===================================================================
// MODULE 3: RED TEAM OPERATOR (EXPLOIT & POC)
// ===================================================================

class RedTeamOperator {
public:
    void trigger_poc() {
        cout << "\n[3.1] RED TEAM: TỰ ĐỘNG TRIGGER CÁC KỊCH BẢN POC" << endl;
        VulnerabilityResearcher res;
        
        cout << "--- PoC 1: Max Int Multiplication ---" << endl;
        res.vulnerable_multiplication(INT_MAX, 2);
        
        cout << "\n--- PoC 2: Square Wrap (65536 * 65536) ---" << endl;
        res.vulnerable_multiplication(65536, 65536);
        
        cout << "\n--- PoC 3: Type Confusion (-1 to size_t) ---" << endl;
        res.vulnerable_size_conversion(-1);
    }
};

// ===================================================================
// MAIN INTERFACE
// ===================================================================

void show_menu() {
    cout << "\n=================================================================" << endl;
    cout << "     HỆ THỐNG PHÂN TÍCH LỖ HỔNG TRÀN SỐ NGUYÊN (V2.0)" << endl;
    cout << "=================================================================" << endl;
    cout << "1. [RESEARCHER] Thử nghiệm các lỗ hổng cơ bản" << endl;
    cout << "2. [OS ANALYST] Phân tích cơ chế bảo vệ của Hệ điều hành" << endl;
    cout << "3. [RED TEAM] Tự động chạy Proof of Concept (PoC)" << endl;
    cout << "0. Thoát chương trình" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Lựa chọn của bạn: ";
}

int main() {
    VulnerabilityResearcher researcher;
    OSSecurityAnalyst analyst;
    RedTeamOperator redteam;
    
    int choice;
    do {
        show_menu();
        if (!(cin >> choice)) break;
        
        switch (choice) {
            case 1: {
                int sub;
                cout << "\n[1] NHÂN hai số (Vulnerable)" << endl;
                cout << "[2] CỘNG Base + Offset (Vulnerable)" << endl;
                cout << "[3] ÉP KIỂU âm sang size_t (Vulnerable)" << endl;
                cout << "---------------------------------------" << endl;
                cout << "[4] NHÂN hai số (SAFE - Kiểm tra trước)" << endl;
                cout << "[5] CỘNG số (SAFE - Kiểm tra trước)" << endl;
                cout << "[6] ÉP KIỂU (SAFE - Kiểm tra trước)" << endl;
                cout << "Lựa chọn: ";
                
                if (!(cin >> sub)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Lỗi nhập liệu! Vui lòng chỉ nhập số." << endl;
                    break;
                }

                if (sub == 1) {
                    int a, b;
                    cout << "Nhập a, b: "; cin >> a >> b;
                    researcher.vulnerable_multiplication(a, b);
                } else if (sub == 2) {
                    int base, offset;
                    cout << "Nhập base, offset: "; cin >> base >> offset;
                    researcher.vulnerable_addition(base, offset);
                } else if (sub == 3) {
                    int len;
                    cout << "Nhập số âm: "; cin >> len;
                    researcher.vulnerable_size_conversion(len);
                } else if (sub == 4) {
                    int a, b;
                    cout << "Nhập a, b: "; cin >> a >> b;
                    researcher.safe_multiplication(a, b);
                } else if (sub == 5) {
                    int base, offset;
                    cout << "Nhập base, offset: "; cin >> base >> offset;
                    if ((offset > 0 && base > INT_MAX - offset) || (offset < 0 && base < INT_MIN - offset)) {
                        cout << "    [!] PHÁT HIỆN TRÀN SỐ CỘNG: Từ chối thao tác." << endl;
                    } else {
                        cout << "    Kết quả an toàn: " << (base + offset) << endl;
                    }
                } else if (sub == 6) {
                    int len;
                    cout << "Nhập số: "; cin >> len;
                    if (len < 0) {
                        cout << "    [!] PHÁT HIỆN LỖI ÉP KIỂU: Không cho phép chuyển số âm sang size_t." << endl;
                    } else {
                        cout << "    Kích thước hợp lệ: " << (size_t)len << endl;
                    }
                }
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            case 2: {
                int sub;
                cout << "\n[1] Phân tích ASLR (Randomization)" << endl;
                cout << "[2] Phân tích DEP/NX (Execution Prevention)" << endl;
                cout << "[3] Phân tích Stack Canary (Stack Protection)" << endl;
                cout << "Lựa chọn: ";
                
                if (!(cin >> sub)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }

                if (sub == 1) {
                    analyst.analyze_aslr();
                    cout << "(*) LƯU Ý: Phải KHỞI ĐỘNG LẠI chương trình hoàn toàn để thấy địa chỉ ASLR thay đổi." << endl;
                } else if (sub == 2) {
                    analyst.analyze_dep_nx();
                } else if (sub == 3) {
                    analyst.analyze_stack_canary();
                }
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            case 3:
                redteam.trigger_poc();
                break;
            case 0:
                cout << "Tạm biệt!" << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ." << endl;
        }
    } while (choice != 0);
    
    return 0;
}