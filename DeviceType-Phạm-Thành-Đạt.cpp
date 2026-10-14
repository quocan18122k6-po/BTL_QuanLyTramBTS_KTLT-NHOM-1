#include "DeviceType.h"
#include "Validator.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

// ================= LOP DEVICETYPE =================

// Constructor mac dinh
DeviceType::DeviceType()
    : Entity(""), tenLoai(""), chucNang(""), nhaSanXuat("") {
}

// Constructor co tham so
DeviceType::DeviceType(const std::string& maLoai,
                       const std::string& tenLoai,
                       const std::string& chucNang,
                       const std::string& nhaSanXuat)
    : Entity(""), tenLoai(""), chucNang(""), nhaSanXuat("") {

    std::string ma = Validator::catKhoangTrang(maLoai);

    if (!Validator::kiemTraMaHopLe(ma)) {
        throw std::invalid_argument("Ma loai khong hop le");
    }

    setId(ma);

    if (!setTenLoai(tenLoai)) {
        throw std::invalid_argument("Ten loai khong hop le");
    }

    if (!setChucNang(chucNang)) {
        throw std::invalid_argument("Chuc nang khong hop le");
    }

    if (!setNhaSanXuat(nhaSanXuat)) {
        throw std::invalid_argument("Nha san xuat khong hop le");
    }
}

// Getter
std::string DeviceType::getTenLoai() const {
    return tenLoai;
}

std::string DeviceType::getChucNang() const {
    return chucNang;
}

std::string DeviceType::getNhaSanXuat() const {
    return nhaSanXuat;
}

// Setter
bool DeviceType::setTenLoai(const std::string& tenMoi) {
    std::string s = Validator::catKhoangTrang(tenMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }

    tenLoai = s;
    return true;
}

bool DeviceType::setChucNang(const std::string& chucNangMoi) {
    std::string s = Validator::catKhoangTrang(chucNangMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }

    chucNang = s;
    return true;
}

bool DeviceType::setNhaSanXuat(const std::string& nsxMoi) {
    std::string s = Validator::catKhoangTrang(nsxMoi);

    if (Validator::laChuoiRong(s) ||
        Validator::chuaKyTuPhanCach(s)) {
        return false;
    }

    nhaSanXuat = s;
    return true;
}

// In duong ke bang
void DeviceType::inDuongKeBang() {
    std::cout << "+"
              << std::string(12, '-') << "+"
              << std::string(25, '-') << "+"
              << std::string(32, '-') << "+"
              << std::string(22, '-') << "+\n";
}

// In tieu de bang
void DeviceType::inTieuDeBang() {
    std::cout << "\n";
    inDuongKeBang();
    std::cout << "| " << std::left << std::setw(10) << "Ma Loai" << " "
              << "| " << std::setw(23) << "Ten Loai Thiet Bi" << " "
              << "| " << std::setw(30) << "Chuc Nang Chinh" << " "
              << "| " << std::setw(20) << "Nha San Xuat" << " |\n";
    inDuongKeBang();
}

// Nhap thong tin loai thiet bi
void DeviceType::input() {
    std::string s;

    while (true) {
        std::cout << "Nhap ten loai thiet bi (VD: BBU, RRU): ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        if (setTenLoai(s)) {
            break;
        }

        std::cout << "Ten loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap chuc nang chinh: ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        if (setChucNang(s)) {
            break;
        }

        std::cout << "Chuc nang khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap nha san xuat: ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        if (setNhaSanXuat(s)) {
            break;
        }

        std::cout << "Nha san xuat khong hop le. Hay nhap lai.\n";
    }
}

// Hien thi thong tin chi tiet
void DeviceType::display() const {
    std::cout << "  - Ma loai thiet bi : " << id << "\n";
    std::cout << "  - Ten loai         : " << tenLoai << "\n";
    std::cout << "  - Chuc nang chinh  : " << chucNang << "\n";
    std::cout << "  - Nha san xuat     : " << nhaSanXuat << "\n";
}

// Hien thi mot dong trong bang
void DeviceType::displayRow() const {
    std::cout << "| " << std::left << std::setw(10) << id << " "
              << "| " << std::setw(23) << tenLoai << " "
              << "| " << std::setw(30) << chucNang << " "
              << "| " << std::setw(20) << nhaSanXuat << " |\n";
}

// Chuyen thong tin thanh chuoi de luu file
// Dinh dang: maLoai|tenLoai|chucNang|nhaSanXuat
std::string DeviceType::toString() const {
    return id + "|" + tenLoai + "|" + chucNang + "|" + nhaSanXuat;
}

// Doc thong tin tu file
void DeviceType::fromString(const std::string& line) {
    std::stringstream ss(line);

    std::string ma;
    std::string ten;
    std::string cn;
    std::string nsx;

    if (!std::getline(ss, ma, '|') ||
        !std::getline(ss, ten, '|') ||
        !std::getline(ss, cn, '|') ||
        !std::getline(ss, nsx)) {
        throw std::invalid_argument("Dong du lieu khong dung dinh dang");
    }

    // Kiem tra co thua truong du lieu khong
    if (nsx.find('|') != std::string::npos) {
        throw std::invalid_argument("Dong du lieu co thua truong");
    }

    ma = Validator::catKhoangTrang(ma);
    ten = Validator::catKhoangTrang(ten);
    cn = Validator::catKhoangTrang(cn);
    nsx = Validator::catKhoangTrang(nsx);

    if (!Validator::kiemTraMaHopLe(ma)) {
        throw std::invalid_argument("Ma loai khong hop le");
    }

    if (Validator::laChuoiRong(ten) ||
        Validator::chuaKyTuPhanCach(ten)) {
        throw std::invalid_argument("Ten loai khong hop le");
    }

    if (Validator::laChuoiRong(cn) ||
        Validator::chuaKyTuPhanCach(cn)) {
        throw std::invalid_argument("Chuc nang khong hop le");
    }

    if (Validator::laChuoiRong(nsx) ||
        Validator::chuaKyTuPhanCach(nsx)) {
        throw std::invalid_argument("Nha san xuat khong hop le");
    }

    // Chi gan du lieu sau khi kiem tra hop le
    id = ma;
    tenLoai = ten;
    chucNang = cn;
    nhaSanXuat = nsx;
}

// Cap nhat thong tin
// Nhan Enter thi giu nguyen gia tri cu
void DeviceType::updateInfo() {
    std::string s;

    std::cout << "\nNhan Enter neu muon giu nguyen gia tri cu.\n";

    // Cap nhat ten loai
    while (true) {
        std::cout << "Ten loai moi (" << tenLoai << "): ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        s = Validator::catKhoangTrang(s);

        if (s.empty()) {
            break;
        }

        if (setTenLoai(s)) {
            break;
        }

        std::cout << "Ten loai khong hop le. Hay nhap lai.\n";
    }

    // Cap nhat chuc nang
    while (true) {
        std::cout << "Chuc nang moi (" << chucNang << "): ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        s = Validator::catKhoangTrang(s);

        if (s.empty()) {
            break;
        }

        if (setChucNang(s)) {
            break;
        }

        std::cout << "Chuc nang khong hop le. Hay nhap lai.\n";
    }

    // Cap nhat nha san xuat
    while (true) {
        std::cout << "Nha san xuat moi (" << nhaSanXuat << "): ";

        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }

        s = Validator::catKhoangTrang(s);

        if (s.empty()) {
            break;
        }

        if (setNhaSanXuat(s)) {
            break;
        }

        std::cout << "Nha san xuat khong hop le. Hay nhap lai.\n";
    }
}

// ================= LOP DEVICETYPEMANAGER =================

// Constructor
DeviceTypeManager::DeviceTypeManager()
    : repo("data/device_types.txt") {
}

// Hien thi menu
void DeviceTypeManager::hienThiMenu() const {
    std::cout << "\n===== QUAN LY LOAI THIET BI =====\n";
    std::cout << "1. Them loai thiet bi\n";
    std::cout << "2. Xem danh sach\n";
    std::cout << "3. Tim kiem\n";
    std::cout << "4. Cap nhat\n";
    std::cout << "5. Xoa\n";
    std::cout << "0. Quay lai\n";
    std::cout << "=================================\n";
}

// Chay chuong trinh
void DeviceTypeManager::chayChuongTrinh() {
    while (true) {
        hienThiMenu();

        std::string luaChon;

        std::cout << "Nhap lua chon: ";

        if (!std::getline(std::cin, luaChon)) {
            break;
        }

        luaChon = Validator::catKhoangTrang(luaChon);

        if (luaChon == "0") {
            break;
        }

        try {
            if (luaChon == "1") {
                themMoi();
            }
            else if (luaChon == "2") {
                xemDanhSach();
            }
            else if (luaChon == "3") {
                timKiem();
            }
            else if (luaChon == "4") {
                capNhat();
            }
            else if (luaChon == "5") {
                xoa();
            }
            else {
                std::cout << "Lua chon khong hop le. Hay nhap tu 0 den 5.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Da xay ra loi: " << e.what() << "\n";
        }
    }
}

// Them loai thiet bi
void DeviceTypeManager::themMoi() {
    std::cout << "\n--- THEM LOAI THIET BI ---\n";

    std::string maNhap;

    while (true) {
        std::cout << "Nhap ma loai (VD: LT01): ";

        if (!std::getline(std::cin, maNhap)) {
            return;
        }

        maNhap = Validator::catKhoangTrang(maNhap);

        if (!Validator::kiemTraMaHopLe(maNhap)) {
            std::cout << "Ma loai khong hop le. Hay nhap lai.\n";
            continue;
        }

        if (repo.find(maNhap) != nullptr) {
            std::cout << "Ma loai da ton tai. Hay nhap ma khac.\n";
            continue;
        }

        break;
    }

    DeviceType dt;
    dt.setId(maNhap);
    dt.input();

    if (repo.add(dt)) {
        std::cout << "Them loai thiet bi thanh cong!\n";
    }
    else {
        std::cout << "Them that bai. Khong the luu file.\n";
    }
}

// Xem danh sach loai thiet bi
void DeviceTypeManager::xemDanhSach() {
    std::cout << "\n--- DANH SACH LOAI THIET BI ---\n";

    const std::vector<DeviceType>& danhSach = repo.getAll();

    if (danhSach.empty()) {
        std::cout << "Hien chua co du lieu.\n";
        return;
    }

    DeviceType::inTieuDeBang();

    for (const DeviceType& dt : danhSach) {
        dt.displayRow();
    }

    DeviceType::inDuongKeBang();

    std::cout << "Tong cong: " << danhSach.size() << " ban ghi.\n";
}

// Tim kiem loai thiet bi theo ma
void DeviceTypeManager::timKiem() {
    std::cout << "\n--- TIM KIEM LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can tim: ";

    std::string maTim;

    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        std::cout << "Khong tim thay loai thiet bi co ma: "
                  << maTim << "\n";
    }
    else {
        std::cout << "\nThong tin loai thiet bi:\n";
        dt->display();
    }
}

// Cap nhat thong tin loai thiet bi
void DeviceTypeManager::capNhat() {
    std::cout << "\n--- CAP NHAT LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can sua: ";

    std::string maTim;

    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        std::cout << "Khong tim thay loai thiet bi.\n";
        return;
    }

    std::cout << "\nThong tin hien tai:\n";
    dt->display();

    // Sua tren ban sao truoc khi luu
    DeviceType banSao = *dt;
    banSao.updateInfo();

    if (repo.update(maTim, banSao)) {
        std::cout << "Cap nhat thanh cong!\n";
    }
    else {
        std::cout << "Cap nhat that bai. Khong the luu file.\n";
    }
}

// Xoa loai thiet bi
void DeviceTypeManager::xoa() {
    std::cout << "\n--- XOA LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can xoa: ";

    std::string maTim;

    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* dt = repo.find(maTim);

    if (dt == nullptr) {
        std::cout << "Khong tim thay loai thiet bi.\n";
        return;
    }

    std::cout << "\nThong tin loai thiet bi muon xoa:\n";
    dt->display();

    std::cout << "Ban co chac muon xoa? (y/n): ";

    std::string xacNhan;

    if (!std::getline(std::cin, xacNhan)) {
        return;
    }

    if (xacNhan == "y" || xacNhan == "Y") {
        if (repo.remove(maTim)) {
            std::cout << "Da xoa loai thiet bi.\n";
        }
        else {
            std::cout << "Xoa that bai. Khong the luu file.\n";
        }
    }
    else {
        std::cout << "Da huy thao tac xoa.\n";
    }
}