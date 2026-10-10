
#include "DeviceType.h"
#include "Validator.h"
#include <bits/stdc++.h>


// CAI DAT LOP DEVICETYPE

DeviceType::DeviceType() : Entity(""), tenLoai(""), chucNang(""), nhaSanXuat("") {}

DeviceType::DeviceType(const std::string& maLoai, const std::string& tenLoai, 
                       const std::string& chucNang, const std::string& nhaSanXuat)
    : Entity(maLoai), tenLoai(""), chucNang(""), nhaSanXuat("") {
    setTenLoai(tenLoai);
    setChucNang(chucNang);
    setNhaSanXuat(nhaSanXuat);
}

std::string DeviceType::getTenLoai() const { return tenLoai; }
std::string DeviceType::getChucNang() const { return chucNang; }
std::string DeviceType::getNhaSanXuat() const { return nhaSanXuat; }

bool DeviceType::setTenLoai(const std::string& tenMoi) { 
    std::string s = Validator::catKhoangTrang(tenMoi);
    if (Validator::laChuoiRong(s) || Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    this->tenLoai = s;
    return true;
}

bool DeviceType::setChucNang(const std::string& chucNangMoi) { 
    std::string s = Validator::catKhoangTrang(chucNangMoi);
    if (Validator::laChuoiRong(s) || Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    this->chucNang = s;
    return true;
}

bool DeviceType::setNhaSanXuat(const std::string& nsxMoi) { 
    std::string s = Validator::catKhoangTrang(nsxMoi);
    if (Validator::laChuoiRong(s) || Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    this->nhaSanXuat = s;
    return true;
}

void DeviceType::inDuongKeBang() {
    std::cout << "+" << std::string(12, '-') 
              << "+" << std::string(25, '-') 
              << "+" << std::string(32, '-') 
              << "+" << std::string(22, '-') << "+\n";
}

void DeviceType::inTieuDeBang() {
    std::cout << "\n";
    inDuongKeBang();
    std::cout << "| " << std::left << std::setw(10) << "Ma Loai" << " "
              << "| " << std::setw(23) << "Ten Loai Thiet Bi" << " "
              << "| " << std::setw(30) << "Chuc Nang Chinh" << " "
              << "| " << std::setw(20) << "Nha San Xuat" << " |\n";
    inDuongKeBang();
}

// 1. Nhap moi thong tin tu ban phim
void DeviceType::input() {
    std::string buffer;
    while (true) {
        std::cout << "Nhap ten loai thiet bi (VD: BBU, RRU): ";
        std::getline(std::cin, buffer);
        if (!setTenLoai(buffer)) {
            std::cout << "!! Ten loai khong duoc de trong va khong chua ky tu '|'!\n";
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Nhap chuc nang chinh: ";
        std::getline(std::cin, buffer);
        if (!setChucNang(buffer)) {
            std::cout << "!! Chuc nang khong duoc de trong va khong chua ky tu '|'!\n";
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Nhap nha san xuat: ";
        std::getline(std::cin, buffer);
        if (!setNhaSanXuat(buffer)) {
            std::cout << "!! Nha san xuat khong duoc de trong va khong chua ky tu '|'!\n";
            continue;
        }
        break;
    }
}

// 2. Hien thi chi tiet (dang the/card view)
void DeviceType::display() const {
    std::cout << "  - Ma loai thiet bi : " << id << "\n"
              << "  - Ten loai         : " << tenLoai << "\n"
              << "  - Chuc nang chinh  : " << chucNang << "\n"
              << "  - Nha san xuat     : " << nhaSanXuat << "\n";
}

// 3. Hien thi mot dong trong bang danh sach
void DeviceType::displayRow() const {
    std::cout << "| " << std::left << std::setw(10) << id << " "
              << "| " << std::setw(23) << tenLoai << " "
              << "| " << std::setw(30) << chucNang << " "
              << "| " << std::setw(20) << nhaSanXuat << " |\n";
}

// 4. Xuat chuoi luu file text: id|tenLoai|chucNang|nhaSanXuat
std::string DeviceType::toString() const {
    return id + "|" + tenLoai + "|" + chucNang + "|" + nhaSanXuat;
}

// 5. Nap du lieu tu 1 dong doc tu file text
void DeviceType::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string maDoc, tenDoc, cnDoc, nsxDoc;

    if (std::getline(ss, maDoc, '|') &&
        std::getline(ss, tenDoc, '|') &&
        std::getline(ss, cnDoc, '|') &&
        std::getline(ss, nsxDoc)) {
        this->id = Validator::catKhoangTrang(maDoc);
        this->tenLoai = Validator::catKhoangTrang(tenDoc);
        this->chucNang = Validator::catKhoangTrang(cnDoc);
        this->nhaSanXuat = Validator::catKhoangTrang(nsxDoc);
    }
}

// 6. Cap nhat thong tin tuong tac (Enter giu nguyen)
void DeviceType::updateInfo() {
    std::cout << "\n(Nhan Enter neu muon giu nguyen gia tri cu)\n";
    std::string input;

    // Cap nhat Ten loai
    while (true) {
        std::cout << "Ten loai moi (" << this->tenLoai << "): ";
        std::getline(std::cin, input);
        input = Validator::catKhoangTrang(input);
        if (input.empty()) break;
        if (!setTenLoai(input)) {
            std::cout << "!! Ten loai khong duoc chua ky tu '|'!\n";
            continue;
        }
        break;
    }

    // Cap nhat Chuc nang
    while (true) {
        std::cout << "Chuc nang moi (" << this->chucNang << "): ";
        std::getline(std::cin, input);
        input = Validator::catKhoangTrang(input);
        if (input.empty()) break;
        if (!setChucNang(input)) {
            std::cout << "!! Chuc nang khong duoc chua ky tu '|'!\n";
            continue;
        }
        break;
    }

    // Cap nhat Nha san xuat
    while (true) {
        std::cout << "Nha san xuat moi (" << this->nhaSanXuat << "): ";
        std::getline(std::cin, input);
        input = Validator::catKhoangTrang(input);
        if (input.empty()) break;
        if (!setNhaSanXuat(input)) {
            std::cout << "!! Nha san xuat khong duoc chua ky tu '|'!\n";
            continue;
        }
        break;
    }
}

// ================= CAI DAT LOP DEVICETYPEMANAGER =================

DeviceTypeManager::DeviceTypeManager() : repo("data/device_types.txt") {}

void DeviceTypeManager::hienThiMenu() const {
    std::cout << "\n============= QUAN LY LOAI THIET BI =============\n";
    std::cout << "1. Them loai thiet bi moi (Create)\n";
    std::cout << "2. Xem danh sach loai thiet bi (Read)\n";
    std::cout << "3. Tim kiem loai thiet bi (Search)\n";
    std::cout << "4. Cap nhat thong tin loai thiet bi (Update)\n";
    std::cout << "5. Xoa loai thiet bi (Delete)\n";
    std::cout << "0. Quay lai menu chinh\n";
    std::cout << "=================================================\n";
}

void DeviceTypeManager::chayChuongTrinh() {
    int luaChon;
    do {
        hienThiMenu();
        std::cout << ">> Nhap lua chon: ";
        std::string input;
        std::getline(std::cin, input);

        if (!Validator::laSoNguyenDuong(input) && input != "0") {
            std::cout << "!! Lua chon phai la so nguyen hop le!\n";
            continue;
        }
        luaChon = std::stoi(input);

        try {
            switch (luaChon) {
                case 1: themMoi(); break;
                case 2: xemDanhSach(); break;
                case 3: timKiem(); break;
                case 4: capNhat(); break;
                case 5: xoa(); break;
                case 0: break;
                default: std::cout << "!! Chuc nang khong ton tai!\n"; break;
            }
        } catch (const std::exception& e) {
            std::cout << "!! Da xay ra loi: " << e.what() << "\n";
        }
    } while (luaChon != 0);
}

void DeviceTypeManager::themMoi() {
    std::cout << "\n--- THEM LOAI THIET BI MOI ---\n";
    std::string maNhap;
    while (true) {
        std::cout << "Nhap ma loai (VD: LT01): ";
        std::getline(std::cin, maNhap);
        maNhap = Validator::catKhoangTrang(maNhap);
        if (!Validator::kiemTraMaHopLe(maNhap)) {
            std::cout << "!! Ma khong hop le (khong rong, khong chua khoang trang/ky tu '|').\n";
            continue;
        }
        if (repo.timKiemTheoMa(maNhap) != nullptr) {
            std::cout << "!! Ma loai da ton tai trong he thong!\n";
            continue;
        }
        break;
    }

    DeviceType dt;
    dt.setId(maNhap);
    dt.input();
    repo.them(dt);
    std::cout << ">> Them loai thiet bi thanh cong va da luu file!\n";
}

void DeviceTypeManager::xemDanhSach() {
    std::cout << "\n--- DANH SACH LOAI THIET BI ---\n";
    std::vector<DeviceType> danhSach = repo.layTatCa();
    if (danhSach.empty()) {
        std::cout << ">> Hien chua co du lieu nao.\n";
        return;
    }
    DeviceType::inTieuDeBang();
    for (const auto& dt : danhSach) {
        dt.displayRow(); // In tung dong trong bang danh sach
    }
    DeviceType::inDuongKeBang();
    std::cout << ">> Tong cong: " << danhSach.size() << " ban ghi.\n";
}

void DeviceTypeManager::timKiem() {
    std::cout << "\n--- TIM KIEM LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can tim: ";
    std::string maTim;
    std::getline(std::cin, maTim);
    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* kq = repo.timKiemTheoMa(maTim);
    if (kq != nullptr) {
        std::cout << "\n>> Ket qua tim thay:\n";
        kq->display(); // In dang the chi tiet
    } else {
        std::cout << "!! Khong tim thay ban ghi mang ma: " << maTim << "\n";
    }
}

void DeviceTypeManager::capNhat() {
    std::cout << "\n--- CAP NHAT LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can sua: ";
    std::string maTim;
    std::getline(std::cin, maTim);
    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* dt = repo.timKiemTheoMa(maTim);
    if (dt == nullptr) {
        std::cout << "!! Khong tim thay loai thiet bi nay!\n";
        return;
    }

    std::cout << "\n>> Thong tin hien tai:\n";
    dt->display();

    // Goi truc tiep phuong thuc da hinh tu Entity
    dt->updateInfo();

    repo.capNhat(*dt);
    std::cout << ">> Cap nhat va luu file thanh cong!\n";
}

void DeviceTypeManager::xoa() {
    std::cout << "\n--- XOA LOAI THIET BI ---\n";
    std::cout << "Nhap ma loai can xoa: ";
    std::string maTim;
    std::getline(std::cin, maTim);
    maTim = Validator::catKhoangTrang(maTim);

    DeviceType* dt = repo.timKiemTheoMa(maTim);
    if (dt == nullptr) {
        std::cout << "!! Khong tim thay loai thiet bi!\n";
        return;
    }

    std::cout << "\n>> Thong tin ban ghi muon xoa:\n";
    dt->display();

    std::cout << "\n>> Xac nhan xoa? (y/n): ";
    std::string xacNhan;
    std::getline(std::cin, xacNhan);
    if (xacNhan == "y" || xacNhan == "Y") {
        repo.xoa(maTim);
        std::cout << ">> Da xoa ban ghi khoi file thanh cong!\n";
    } else {
        std::cout << ">> Da huy thao tac xoa.\n";
    }
}