
#include "DeviceType.h"
#include "InputHelper.h"
#include "Validator.h"
#include "InstalledDevice.h"

#include <fstream>              // ifstream để đọc file thiết bị lắp đặt trước khi xóa
#include <iostream>             
#include <iomanip>              //setw() để căn cột bảng
#include <sstream>
#include <stdexcept>            // invalid_argument để báo dữ liệu không hợp lệ
#include <vector>               

using namespace std;

// LOP DEVICETYPE

// ham khoi tao mac dinh
DeviceType::DeviceType()
    : Entity(""), tenLoai(""), chucNang(""), nhaSanXuat("") {
}
// ham khoi tao co tham so
DeviceType::DeviceType(const string& maLoai,
                       const string& tenLoai,
                       const string& chucNang,
                       const string& nhaSanXuat)
    : Entity(""), tenLoai(""), chucNang(""), nhaSanXuat("") {

    string ma = Validator::catKhoangTrang(maLoai);
        // kiem tra tham so truyen vao co hop le khong
    if (!Validator::kiemTraMaHopLe(ma)) {
        throw invalid_argument("Ma loai khong hop le");
    }

    setId(ma);

    if (!setTenLoai(tenLoai)) {
        throw invalid_argument("Ten loai khong hop le");
    }

    if (!setChucNang(chucNang)) {
        throw invalid_argument("Chuc nang khong hop le");
    }

    if(!setNhaSanXuat(nhaSanXuat)){
        throw invalid_argument("Nha san xuat khong hop le");
    }
}

// Getter
string DeviceType::getTenLoai() const {
    return tenLoai;
}
string DeviceType::getChucNang() const {
    return chucNang;
}
string DeviceType::getNhaSanXuat() const {
    return nhaSanXuat;
}

// Setter
bool DeviceType::setTenLoai(const string& tenMoi) {
    string s = Validator::catKhoangTrang(tenMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    tenLoai = s;
    return true;
}
bool DeviceType::setChucNang(const string& chucNangMoi) {
    string s = Validator::catKhoangTrang(chucNangMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    chucNang = s;
    return true;
}
bool DeviceType::setNhaSanXuat(const string& nsxMoi) {
    string s = Validator::catKhoangTrang(nsxMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    nhaSanXuat = s;
    return true;
}

// In duong ke bang
void DeviceType::inDuongKeBang() {
    cout << "+"
         << string(12, '-') << "+"
         << string(25, '-') << "+"
         << string(32, '-') << "+"
         << string(22, '-') << "+\n";
}

// In tieu de bang
void DeviceType::inTieuDeBang() {
    cout << "\n";
    inDuongKeBang();
    cout << "| " << left << setw(10) << "Ma Loai" << " "
         << "| " << setw(23) << "Ten Loai Thiet Bi" << " "
         << "| " << setw(30) << "Chuc Nang Chinh" << " "
         << "| " << setw(20) << "Nha San Xuat" << " |\n";
    inDuongKeBang();
}

// Nhap thong tin loai thiet bi
void DeviceType::input() {
    string s;

    while (true) {
        s = InputHelper::getString("Nhap ten loai thiet bi (VD: BBU, RRU): ");
        if (setTenLoai(s)) {
            break;
        }
        cout << "Ten loai khong duoc chua dau |. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap chuc nang chinh: ");
        if (setChucNang(s)) {
            break;
        }
        cout << "Chuc nang khong duoc chua dau |. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap nha san xuat: ");
        if (setNhaSanXuat(s)) {
            break;
        }
        cout << "Nha san xuat khong duoc chua dau |. Hay nhap lai.\n";
    }
}

// Hien thi thong tin chi tiet
void DeviceType::display() const {
    cout << "  - Ma loai thiet bi : " << id << "\n";
    cout << "  - Ten loai         : " << tenLoai << "\n";
    cout << "  - Chuc nang chinh  : " << chucNang << "\n";
    cout << "  - Nha san xuat     : " << nhaSanXuat << "\n";
}

// Hien thi mot dong trong bang
void DeviceType::displayRow() const {
    // Chi rut gon ban hien thi; khong sua du lieu cua doi tuong.
    string maHienThi = id;
    string tenHienThi = tenLoai;
    string chucNangHienThi = chucNang;
    string nsxHienThi = nhaSanXuat;

    if (!Validator::kiemTraDoDai(maHienThi, 10)) {
        maHienThi = maHienThi.substr(0, 7) + "...";
    }
    if (!Validator::kiemTraDoDai(tenHienThi, 23)) {
        tenHienThi = tenHienThi.substr(0, 20) + "...";
    }
    if (!Validator::kiemTraDoDai(chucNangHienThi, 30)) {
        chucNangHienThi = chucNangHienThi.substr(0, 27) + "...";
    }
    if (!Validator::kiemTraDoDai(nsxHienThi, 20)) {
        nsxHienThi = nsxHienThi.substr(0, 17) + "...";
    }

    cout << "| " << left << setw(10) << maHienThi << " "
         << "| " << setw(23) << tenHienThi << " "
         << "| " << setw(30) << chucNangHienThi << " "
         << "| " << setw(20) << nsxHienThi << " |\n";
}

// Chuyen thong tin thanh chuoi de luu file
// Dinh dang: maLoai|tenLoai|chucNang|nhaSanXuat
string DeviceType::toString() const {
    return id + "|" + tenLoai + "|" + chucNang + "|" + nhaSanXuat;
}

// Doc thong tin tu file
void DeviceType::fromString(const string& line) {
    stringstream ss(line);

    string ma;
    string ten;
    string cn;
    string nsx;

    if (!getline(ss, ma, '|') ||
        !getline(ss, ten, '|') ||
        !getline(ss, cn, '|') ||
        !getline(ss, nsx)) {
        throw invalid_argument("Dong du lieu khong dung dinh dang");
    }

    // Kiem tra co thua truong du lieu khong
    if (Validator::chuaKyTuPhanCach(nsx)) {
        throw invalid_argument("Dong du lieu co thua truong");
    }

    // Constructor dung lai cac setter de kiem tra tung truong.
    // Chi thay doi doi tuong hien tai khi ca ban ghi hop le.
    DeviceType duLieuMoi(ma, ten, cn, nsx);
    *this = duLieuMoi;
}

// Cap nhat thong tin
// Nhan Enter thi giu nguyen gia tri cu
void DeviceType::updateInfo() {
    string s;
    cout << "\nNhan Enter neu muon giu nguyen gia tri cu.\n";

    while (true) {
        s = InputHelper::getString("Ten loai moi (" + tenLoai + "): ", true);
        if (s.empty()) {
            break;
        }
        if (setTenLoai(s)) {
            break;
        }
        cout << "Ten loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Chuc nang moi (" + chucNang + "): ", true);
        if (s.empty()) {
            break;
        }
        if (setChucNang(s)) {
            break;
        }
        cout << "Chuc nang khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nha san xuat moi (" + nhaSanXuat + "): ", true);
        if (s.empty()) {
            break;
        }
        if (setNhaSanXuat(s)) {
            break;
        }
        cout << "Nha san xuat khong hop le. Hay nhap lai.\n";
    }
}

// LOP DEVICETYPEMANAGER

// Constructor
DeviceTypeManager::DeviceTypeManager()
    : repo("data/device_types.txt") {
}

// Hien thi menu
void DeviceTypeManager::hienThiMenu() const {
    cout << "\n===== QUAN LY LOAI THIET BI =====\n";
    cout << "1. Them loai thiet bi\n";
    cout << "2. Xem danh sach\n";
    cout << "3. Tim kiem\n";
    cout << "4. Cap nhat\n";
    cout << "5. Xoa\n";
    cout << "0. Quay lai\n";
    cout << "=================================\n";
}

// Chay chuong trinh
void DeviceTypeManager::chayChuongTrinh() {
    while (true) {
        try {
            hienThiMenu();
            int luaChon = InputHelper::getInt("Nhap lua chon: ", 0, 5);

            if (luaChon == 0) {
                break;
            }

            switch (luaChon) {
                case 1:
                    themMoi();
                    break;
                case 2:
                    xemDanhSach();
                    break;
                case 3:
                    timKiem();
                    break;
                case 4:
                    capNhat();
                    break;
                case 5:
                    xoa();
                    break;
            }
        }
        catch (const ios_base::failure& e) {
            // InputHelper nem ngoai le khi luong nhap ket thuc.
            // Thoat menu de tranh lap lai lien tuc khi khong con du lieu.
            cout << "Dung nhap lieu: " << e.what() << "\n";
            break;
        }
        catch (const exception& e) {
            cout << "Da xay ra loi: " << e.what() << "\n";
        }
    }
}

// Them loai thiet bi
void DeviceTypeManager::themMoi() {
    cout << "\n--- THEM LOAI THIET BI ---\n";

    string maNhap;

    while (true) {
        maNhap = InputHelper::getString("Nhap ma loai (VD: LT01): ");

        if (!Validator::kiemTraMaHopLe(maNhap)) {
            cout << "Ma loai khong hop le. Hay nhap lai.\n";
            continue;
        }

        if (repo.exists(maNhap)) {
            cout << "Ma loai da ton tai. Hay nhap ma khac.\n";
            continue;
        }

        break;
    }

    DeviceType dt;
    dt.setId(maNhap);
    dt.input();

    if (repo.add(dt)) {
        cout << "Them loai thiet bi thanh cong!\n";
    }
    else {
        cout << "Them that bai. Khong the luu file.\n";
    }
}

// Xem danh sach loai thiet bi
void DeviceTypeManager::xemDanhSach() {
    cout << "\n--- DANH SACH LOAI THIET BI ---\n";

    const vector<DeviceType>& danhSach = repo.getAll();

    if (danhSach.empty()) {
        cout << "Hien chua co du lieu.\n";
        return;
    }

    DeviceType::inTieuDeBang();

    for (const DeviceType& dt : danhSach) {
        dt.displayRow();
    }

    DeviceType::inDuongKeBang();

    cout << "Tong cong: " << danhSach.size() << " ban ghi.\n";
}

// Tim kiem loai thiet bi theo ma
void DeviceTypeManager::timKiem() {
    cout << "\n--- TIM KIEM LOAI THIET BI ---\n";
    string maTim = InputHelper::getString("Nhap ma loai can tim: ");

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        cout << "Khong tim thay loai thiet bi co ma: "
             << maTim << "\n";
    }
    else {
        cout << "\nThong tin loai thiet bi:\n";
        dt->display();
    }
}

// Cap nhat thong tin loai thiet bi
void DeviceTypeManager::capNhat() {
    cout << "\n--- CAP NHAT LOAI THIET BI ---\n";
    string maTim = InputHelper::getString("Nhap ma loai can sua: ");

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        cout << "Khong tim thay loai thiet bi.\n";
        return;
    }

    cout << "\nThong tin hien tai:\n";
    dt->display();

    // Sua tren ban sao truoc khi luu
    DeviceType banSao = *dt;
    banSao.updateInfo();

    if (repo.update(maTim, banSao)) {
        cout << "Cap nhat thanh cong!\n";
    }
    else {
        cout << "Cap nhat that bai. Khong the luu file.\n";
    }
}

// Xoa loai thiet bi
void DeviceTypeManager::xoa() {
    cout << "\n--- XOA LOAI THIET BI ---\n";
    string maTim = InputHelper::getString("Nhap ma loai can xoa: ");

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        cout << "Khong tim thay loai thiet bi.\n";
        return;
    }

    cout << "\nThong tin loai thiet bi muon xoa:\n";
    dt->display();

    string xacNhan;
    while (true) {
        xacNhan = InputHelper::getString("Ban co chac muon xoa? (y/n): ");
        if (xacNhan == "y" || xacNhan == "Y" ||
            xacNhan == "n" || xacNhan == "N") {
            break;
        }
        cout << "Hay nhap y hoac n.\n";
    }

    if (xacNhan == "y" || xacNhan == "Y") {
        // Doc file moi nhat de kiem tra tham chieu truoc khi xoa.
        // Dung InstalledDevice::fromString(), khong tu viet lai quy tac doc.
        ifstream fileThietBi("data/installed_devices.txt");
        if (!fileThietBi.is_open()) {
            cout << "Khong the kiem tra file data/installed_devices.txt.\n";
            cout << "Chua xoa loai thiet bi. Hay kiem tra file du lieu.\n";
            return;
        }

        string dong;
        int soDong = 0;
        while (getline(fileThietBi, dong)) {
            soDong++;
            if (Validator::laChuoiRong(dong)) {
                continue;
            }

            InstalledDevice thietBi;
            try {
                thietBi.fromString(dong);
            }
            catch (const exception& e) {
                // Khong xoa khi du lieu loi lam cho viec kiem tra khong day du.
                cout << "Du lieu thiet bi lap dat loi tai dong " << soDong
                     << ": " << e.what() << "\n";
                cout << "Hay sua dong loi truoc khi xoa loai thiet bi.\n";
                return;
            }

            if (thietBi.getMaLoai() == maTim) {
                cout << "Khong the xoa: thiet bi " << thietBi.getId()
                     << " dang tham chieu loai nay.\n";
                return;
            }
        }

        if (fileThietBi.bad() || !fileThietBi.eof()) {
            cout << "Loi khi doc file thiet bi lap dat. Chua xoa loai thiet bi.\n";
            return;
        }

        if (repo.remove(maTim)) {
            cout << "Da xoa loai thiet bi.\n";
        }
        else {
            cout << "Xoa that bai. Khong the luu file.\n";
        }
    }
    else {
        cout << "Da huy thao tac xoa.\n";
    }
}