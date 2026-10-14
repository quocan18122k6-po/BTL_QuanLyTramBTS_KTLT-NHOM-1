#include "InstalledDevice.h"
#include "Validator.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

//LOP INSTALLEDDEVICE

InstalledDevice::InstalledDevice()
    : Entity(""), soSerial(""), maLoai(""), maTram(""),
      ngayLapRap(), trangThai("") {
}

InstalledDevice::InstalledDevice(const std::string& maThietBi,
                                 const std::string& soSerial,
                                 const std::string& maLoai,
                                 const std::string& maTram,
                                 const Date& ngayLapRap,
                                 const std::string& trangThai)
    : Entity(""), soSerial(""), maLoai(""), maTram(""),
      ngayLapRap(), trangThai("") {

    std::string ma = Validator::catKhoangTrang(maThietBi);

    if (!Validator::kiemTraMaHopLe(ma)) {
        throw std::invalid_argument("Ma thiet bi khong hop le");
    }
    setId(ma);

    if (!setSoSerial(soSerial)) {
        throw std::invalid_argument("So serial khong hop le");
    }
    if (!setMaLoai(maLoai)) {
        throw std::invalid_argument("Ma loai thiet bi khong hop le");
    }
    if (!setMaTram(maTram)) {
        throw std::invalid_argument("Ma tram khong hop le");
    }
    if (!setNgayLapRap(ngayLapRap)) {
        throw std::invalid_argument("Ngay lap rap khong hop le");
    }
    if (!setTrangThai(trangThai)) {
        throw std::invalid_argument("Trang thai khong hop le");
    }
}

// Getter
std::string InstalledDevice::getSoSerial() const {
    return soSerial;
}

std::string InstalledDevice::getMaLoai() const {
    return maLoai;
}

std::string InstalledDevice::getMaTram() const {
    return maTram;
}

Date InstalledDevice::getNgayLapRap() const {
    return ngayLapRap;
}

std::string InstalledDevice::getTrangThai() const {
    return trangThai;
}

// Setter
bool InstalledDevice::setSoSerial(const std::string& serialMoi) {
    std::string s = Validator::catKhoangTrang(serialMoi);
    if (!Validator::kiemTraSoSerial(s)) {
        return false;
    }

    soSerial = s;
    return true;
}

bool InstalledDevice::setMaLoai(const std::string& maLoaiMoi) {
    std::string s = Validator::catKhoangTrang(maLoaiMoi);
    if (!Validator::kiemTraMaHopLe(s)) {
        return false;
    }

    maLoai = s;
    return true;
}

bool InstalledDevice::setMaTram(const std::string& maTramMoi) {
    std::string s = Validator::catKhoangTrang(maTramMoi);
    if (!Validator::kiemTraMaHopLe(s)) {
        return false;
    }

    maTram = s;
    return true;
}

bool InstalledDevice::setNgayLapRap(const Date& ngayMoi) {
    if (!Date::kiemTraHopLe(ngayMoi.getNgay(),
                            ngayMoi.getThang(),
                            ngayMoi.getNam())) {
        return false;
    }

    ngayLapRap = ngayMoi;
    return true;
}

bool InstalledDevice::setNgayLapRap(const std::string& chuoiNgay) {
    std::string s = Validator::catKhoangTrang(chuoiNgay);
    Date ngayTam;

    if (!ngayTam.napTuChuoi(s)) {
        return false;
    }

    ngayLapRap = ngayTam;
    return true;
}

bool InstalledDevice::setTrangThai(const std::string& trangThaiMoi) {
    std::string s = Validator::catKhoangTrang(trangThaiMoi);

    if (Validator::laChuoiRong(s) || Validator::chuaKyTuPhanCach(s)) {
        return false;
    }

    trangThai = s;
    return true;
}

// In duong ke bang (Toi uu gon gang, khong lo go thieu ky tu)
void InstalledDevice::inDuongKeBang() {
    std::cout << "+" << std::string(12, '-')
              << "+" << std::string(18, '-')
              << "+" << std::string(12, '-')
              << "+" << std::string(12, '-')
              << "+" << std::string(14, '-')
              << "+" << std::string(16, '-') << "+\n";
}

// In tieu de bang (Da them khoang dem cuoi cot de thang hang 100%)
void InstalledDevice::inTieuDeBang() {
    std::cout << "\n";
    inDuongKeBang();
    std::cout << "| " << std::left << std::setw(10) << "Ma TB" << " "
              << "| " << std::setw(16) << "So Serial" << " "
              << "| " << std::setw(10) << "Ma Loai" << " "
              << "| " << std::setw(10) << "Ma Tram" << " "
              << "| " << std::setw(12) << "Ngay Lap" << " "
              << "| " << std::setw(14) << "Trang Thai" << " |\n";
    inDuongKeBang();
}

// In mot dong trong bang
void InstalledDevice::displayRow() const {
    std::cout << "| " << std::left << std::setw(10) << id << " "
              << "| " << std::setw(16) << soSerial << " "
              << "| " << std::setw(10) << maLoai << " "
              << "| " << std::setw(10) << maTram << " "
              << "| " << std::setw(12) << ngayLapRap.toString() << " "
              << "| " << std::setw(14) << trangThai << " |\n";
}

// In thong tin chi tiet
void InstalledDevice::display() const {
    std::cout << "  - Ma thiet bi lap dat : " << id << "\n";
    std::cout << "  - So Serial           : " << soSerial << "\n";
    std::cout << "  - Ma loai thiet bi    : " << maLoai << "\n";
    std::cout << "  - Ma tram BTS         : " << maTram << "\n";
    std::cout << "  - Ngay lap rap        : " << ngayLapRap.toString() << "\n";
    std::cout << "  - Trang thai          : " << trangThai << "\n";
}

// Nhap thong tin tu ban phim
void InstalledDevice::input() {
    std::string s;

    while (true) {
        std::cout << "Nhap so serial (VD: SR-1001): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        if (setSoSerial(s)) {
            break;
        }
        std::cout << "So serial khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap ma loai thiet bi (VD: LT01): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        if (setMaLoai(s)) {
            break;
        }
        std::cout << "Ma loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap ma tram BTS (VD: BTS01): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        if (setMaTram(s)) {
            break;
        }
        std::cout << "Ma tram khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap ngay lap rap (dd/mm/yyyy): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        if (setNgayLapRap(s)) {
            break;
        }
        std::cout << "Ngay khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Nhap trang thai (VD: Hoat dong, Canh bao, Hong): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        if (setTrangThai(s)) {
            break;
        }
        std::cout << "Trang thai khong hop le. Hay nhap lai.\n";
    }
}

// Chuyen thong tin thanh chuoi de luu file
std::string InstalledDevice::toString() const {
    return id + "|" + soSerial + "|" + maLoai + "|" + maTram + "|" +
           ngayLapRap.toString() + "|" + trangThai;
}

// Doc thong tin tu mot dong trong file
void InstalledDevice::fromString(const std::string& line) {
    if (Validator::laChuoiRong(line)) {
        return; // Bo qua dong trong an toan o cuoi file
    }

    std::stringstream ss(line);
    std::string ma, serial, loai, tram, ngay, tt;

    if (!std::getline(ss, ma, '|') ||
        !std::getline(ss, serial, '|') ||
        !std::getline(ss, loai, '|') ||
        !std::getline(ss, tram, '|') ||
        !std::getline(ss, ngay, '|') ||
        !std::getline(ss, tt)) {
        throw std::invalid_argument("Dong du lieu khong dung dinh dang");
    }

    // Kiem tra so truong du lieu
    if (tt.find('|') != std::string::npos) {
        throw std::invalid_argument("Dong du lieu co thua truong");
    }

    ma = Validator::catKhoangTrang(ma);
    serial = Validator::catKhoangTrang(serial);
    loai = Validator::catKhoangTrang(loai);
    tram = Validator::catKhoangTrang(tram);
    ngay = Validator::catKhoangTrang(ngay);
    tt = Validator::catKhoangTrang(tt);

    if (!Validator::kiemTraMaHopLe(ma)) {
        throw std::invalid_argument("Ma thiet bi khong hop le");
    }
    if (!Validator::kiemTraSoSerial(serial)) {
        throw std::invalid_argument("So serial khong hop le");
    }
    if (!Validator::kiemTraMaHopLe(loai)) {
        throw std::invalid_argument("Ma loai thiet bi khong hop le");
    }
    if (!Validator::kiemTraMaHopLe(tram)) {
        throw std::invalid_argument("Ma tram khong hop le");
    }

    Date ngayTam;
    if (!ngayTam.napTuChuoi(ngay)) {
        throw std::invalid_argument("Ngay lap rap khong hop le");
    }

    if (Validator::laChuoiRong(tt) || Validator::chuaKyTuPhanCach(tt)) {
        throw std::invalid_argument("Trang thai khong hop le");
    }

    // Chi gan du lieu sau khi kiem tra xong
    id = ma;
    soSerial = serial;
    maLoai = loai;
    maTram = tram;
    ngayLapRap = ngayTam;
    trangThai = tt;
}

// Cap nhat thong tin, Enter de giu gia tri cu
void InstalledDevice::updateInfo() {
    std::string s;

    std::cout << "\nNhan Enter neu muon giu nguyen gia tri cu.\n";

    while (true) {
        std::cout << "So serial moi (" << soSerial << "): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        s = Validator::catKhoangTrang(s);
        if (s.empty()) break;
        if (setSoSerial(s)) break;
        std::cout << "So serial khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Ma loai moi (" << maLoai << "): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        s = Validator::catKhoangTrang(s);
        if (s.empty()) break;
        if (setMaLoai(s)) break;
        std::cout << "Ma loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Ma tram moi (" << maTram << "): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        s = Validator::catKhoangTrang(s);
        if (s.empty()) break;
        if (setMaTram(s)) break;
        std::cout << "Ma tram khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Ngay lap rap moi (" << ngayLapRap.toString() << "): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        s = Validator::catKhoangTrang(s);
        if (s.empty()) break;
        if (setNgayLapRap(s)) break;
        std::cout << "Ngay khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        std::cout << "Trang thai moi (" << trangThai << "): ";
        if (!std::getline(std::cin, s)) {
            throw std::runtime_error("Khong doc duoc du lieu tu ban phim");
        }
        s = Validator::catKhoangTrang(s);
        if (s.empty()) break;
        if (setTrangThai(s)) break;
        std::cout << "Trang thai khong hop le. Hay nhap lai.\n";
    }
}

// ================= LOP INSTALLEDDEVICEMANAGER =================

InstalledDeviceManager::InstalledDeviceManager()
    : repo("data/installed_devices.txt") {
}

void InstalledDeviceManager::hienThiMenu() const {
    std::cout << "\n===== QUAN LY THIET BI LAP DAT =====\n";
    std::cout << "1. Them thiet bi\n";
    std::cout << "2. Xem danh sach\n";
    std::cout << "3. Tim kiem\n";
    std::cout << "4. Cap nhat\n";
    std::cout << "5. Xoa\n";
    std::cout << "0. Quay lai\n";
    std::cout << "====================================\n";
}

void InstalledDeviceManager::chayChuongTrinh() {
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

// Them thiet bi moi
void InstalledDeviceManager::themMoi() {
    std::cout << "\n--- THEM THIET BI LAP DAT ---\n";

    std::string maNhap;
    while (true) {
        std::cout << "Nhap ma thiet bi (VD: TB01): ";
        if (!std::getline(std::cin, maNhap)) {
            return;
        }

        maNhap = Validator::catKhoangTrang(maNhap);
        if (!Validator::kiemTraMaHopLe(maNhap)) {
            std::cout << "Ma thiet bi khong hop le. Hay nhap lai.\n";
            continue;
        }

        if (repo.find(maNhap) != nullptr) {
            std::cout << "Ma thiet bi da ton tai. Hay nhap ma khac.\n";
            continue;
        }
        break;
    }

    InstalledDevice tb;
    tb.setId(maNhap);
    tb.input();

    // Kiem tra serial co bi trung voi thiet bi khac khong
    const std::vector<InstalledDevice>& danhSach = repo.getAll();
    for (const InstalledDevice& item : danhSach) {
        if (item.getSoSerial() == tb.getSoSerial()) {
            std::cout << "So serial da duoc su dung. Hay them lai thiet bi.\n";
            return;
        }
    }

    if (repo.add(tb)) {
        std::cout << "Them thiet bi thanh cong!\n";
    }
    else {
        std::cout << "Them that bai. Khong the luu file.\n";
    }
}

void InstalledDeviceManager::xemDanhSach() {
    std::cout << "\n--- DANH SACH THIET BI LAP DAT ---\n";

    const std::vector<InstalledDevice>& danhSach = repo.getAll();
    if (danhSach.empty()) {
        std::cout << "Hien chua co du lieu.\n";
        return;
    }

    InstalledDevice::inTieuDeBang();
    for (const InstalledDevice& tb : danhSach) {
        tb.displayRow();
    }
    InstalledDevice::inDuongKeBang();
    std::cout << "Tong cong: " << danhSach.size() << " ban ghi.\n";
}

void InstalledDeviceManager::timKiem() {
    std::cout << "\n--- TIM KIEM THIET BI LAP DAT ---\n";
    std::cout << "Nhap ma thiet bi can tim: ";

    std::string maTim;
    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        std::cout << "Khong tim thay thiet bi co ma: " << maTim << "\n";
    }
    else {
        tb->display();
    }
}

void InstalledDeviceManager::capNhat() {
    std::cout << "\n--- CAP NHAT THIET BI LAP DAT ---\n";
    std::cout << "Nhap ma thiet bi can sua: ";

    std::string maTim;
    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        std::cout << "Khong tim thay thiet bi.\n";
        return;
    }

    std::cout << "\nThong tin hien tai:\n";
    tb->display();

    InstalledDevice banSao = *tb;
    banSao.updateInfo();

    // Khong cho phep dung serial cua thiet bi khac
    const std::vector<InstalledDevice>& danhSach = repo.getAll();
    for (const InstalledDevice& item : danhSach) {
        if (item.getId() != maTim &&
            item.getSoSerial() == banSao.getSoSerial()) {
            std::cout << "So serial nay da duoc thiet bi khac su dung.\n";
            return;
        }
    }

    if (repo.update(maTim, banSao)) {
        std::cout << "Cap nhat thanh cong!\n";
    }
    else {
        std::cout << "Cap nhat that bai. Khong the luu file.\n";
    }
}

void InstalledDeviceManager::xoa() {
    std::cout << "\n--- XOA THIET BI LAP DAT ---\n";
    std::cout << "Nhap ma thiet bi can xoa: ";

    std::string maTim;
    if (!std::getline(std::cin, maTim)) {
        return;
    }

    maTim = Validator::catKhoangTrang(maTim);
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        std::cout << "Khong tim thay thiet bi.\n";
        return;
    }

    std::cout << "\nThong tin thiet bi muon xoa:\n";
    tb->display();

    std::cout << "Ban co chac muon xoa? (y/n): ";
    std::string xacNhan;
    if (!std::getline(std::cin, xacNhan)) {
        return;
    }

    if (xacNhan == "y" || xacNhan == "Y") {
        if (repo.remove(maTim)) {
            std::cout << "Da xoa thiet bi lap dat.\n";
        }
        else {
            std::cout << "Xoa that bai. Khong the luu file.\n";
        }
    }
    else {
        std::cout << "Da huy thao tac xoa.\n";
    }
}