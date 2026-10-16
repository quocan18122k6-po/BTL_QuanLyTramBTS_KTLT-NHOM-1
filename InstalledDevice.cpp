
#include "InstalledDevice.h"
#include "BtsStation.h"
#include "Validator.h"
#include "InputHelper.h"
#include "DeviceType.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

//LOP INSTALLEDDEVICE

InstalledDevice::InstalledDevice()
    : Entity(""), soSerial(""), maLoai(""), maTram(""),
      ngayLapRap(), trangThai("") {
}

InstalledDevice::InstalledDevice(const string& maThietBi,
                                 const string& soSerial,
                                 const string& maLoai,
                                 const string& maTram,
                                 const Date& ngayLapRap,
                                 const string& trangThai)
    : Entity("") {

    string ma = Validator::catKhoangTrang(maThietBi);
    if (!Validator::kiemTraMaHopLe(ma)) {
        throw invalid_argument("Ma thiet bi khong hop le");
    }
    setId(ma);

    if (!setSoSerial(soSerial)) {
        throw invalid_argument("So serial khong hop le");
    }
    if (!setMaLoai(maLoai)) {
        throw invalid_argument("Ma loai thiet bi khong hop le");
    }
    if (!setMaTram(maTram)) {
        throw invalid_argument("Ma tram khong hop le");
    }
    if (!setNgayLapRap(ngayLapRap)) {
        throw invalid_argument("Ngay lap rap khong hop le");
    }
    if (!setTrangThai(trangThai)) {
        throw invalid_argument("Trang thai khong hop le");
    }
}

// Getter
string InstalledDevice::getSoSerial() const {
    return soSerial;
}
string InstalledDevice::getMaLoai() const {
    return maLoai;
}
string InstalledDevice::getMaTram() const {
    return maTram;
}
Date InstalledDevice::getNgayLapRap() const {
    return ngayLapRap;
}
string InstalledDevice::getTrangThai() const {
    return trangThai;
}

// Setter
bool InstalledDevice::setSoSerial(const string& serialMoi) {
    string s = Validator::catKhoangTrang(serialMoi);
    if (!Validator::kiemTraSoSerial(s)) {
        return false;
    }
    soSerial = s;
    return true;
}
bool InstalledDevice::setMaLoai(const string& maLoaiMoi) {
    string s = Validator::catKhoangTrang(maLoaiMoi);
    if (!Validator::kiemTraMaHopLe(s)) {
        return false;
    }
    maLoai = s;
    return true;
}
bool InstalledDevice::setMaTram(const string& maTramMoi) {
    string s = Validator::catKhoangTrang(maTramMoi);
    if (!Validator::kiemTraMaHopLe(s)) {
        return false;
    }
    maTram = s;
    return true;
}
// nap chong ham setNgayLapRap
bool InstalledDevice::setNgayLapRap(const Date& ngayMoi) {
    if (!Date::kiemTraHopLe(ngayMoi.getNgay(),
                            ngayMoi.getThang(),
                            ngayMoi.getNam())) {
        return false;
    }
    ngayLapRap = ngayMoi;
    return true;
}
bool InstalledDevice::setNgayLapRap(const string& chuoiNgay) {
    string s = Validator::catKhoangTrang(chuoiNgay);
    Date ngayTam;
    if (!ngayTam.napTuChuoi(s)) {
        return false;
    }
    ngayLapRap = ngayTam;
    return true;
}

bool InstalledDevice::setTrangThai(const string& trangThaiMoi) {
    string s = Validator::catKhoangTrang(trangThaiMoi);
    if (Validator::laChuoiRong(s) || Validator::chuaKyTuPhanCach(s)) {
        return false;
    }
    trangThai = s;
    return true;
}

// In duong ke bang
void InstalledDevice::inDuongKeBang() {
    cout << "+" << string(12, '-')
         << "+" << string(18, '-')
         << "+" << string(12, '-')
         << "+" << string(12, '-')
         << "+" << string(14, '-')
         << "+" << string(16, '-') << "+\n";
}

// In tieu de bang
void InstalledDevice::inTieuDeBang() {
    cout << "\n";
    inDuongKeBang();
    cout << "| " << left << setw(10) << "Ma TB" << " "
         << "| " << setw(16) << "So Serial" << " "
         << "| " << setw(10) << "Ma Loai" << " "
         << "| " << setw(10) << "Ma Tram" << " "
         << "| " << setw(12) << "Ngay Lap" << " "
         << "| " << setw(14) << "Trang Thai" << " |\n";
    inDuongKeBang();
}

// In mot dong trong bang
void InstalledDevice::displayRow() const {
    cout << "| " << left << setw(10) << id << " "
         << "| " << setw(16) << soSerial << " "
         << "| " << setw(10) << maLoai << " "
         << "| " << setw(10) << maTram << " "
         << "| " << setw(12) << ngayLapRap.toString() << " "
         << "| " << setw(14) << trangThai << " |\n";
}

// In thong tin chi tiet
void InstalledDevice::display() const {
    cout << "  - Ma thiet bi lap dat : " << id << "\n";
    cout << "  - So Serial           : " << soSerial << "\n";
    cout << "  - Ma loai thiet bi    : " << maLoai << "\n";
    cout << "  - Ma tram BTS         : " << maTram << "\n";
    cout << "  - Ngay lap rap        : " << ngayLapRap.toString() << "\n";
    cout << "  - Trang thai          : " << trangThai << "\n";
}

// Nhap thong tin tu ban phim
void InstalledDevice::input() {
    string s;

    while (true) {
        s = InputHelper::getString("Nhap so serial: ");
        if (setSoSerial(s)) {
            break;
        }
        cout << "So serial khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap ma loai thiet bi: ");
        if (setMaLoai(s)) {
            break;
        }
        cout << "Ma loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap ma tram BTS: ");
        if (setMaTram(s)) {
            break;
        }
        cout << "Ma tram khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap ngay lap rap (dd/mm/yyyy): ");
        if (setNgayLapRap(s)) {
            break;
        }
        cout << "Ngay lap rap khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Nhap trang thai: ");
        if (setTrangThai(s)) {
            break;
        }
        cout << "Trang thai khong hop le. Hay nhap lai.\n";
    }
}

// Chuyen thong tin thanh chuoi de luu file
string InstalledDevice::toString() const {
    return id + "|" + soSerial + "|" + maLoai + "|" + maTram + "|" +
           ngayLapRap.toString() + "|" + trangThai;
}

// Doc thong tin tu mot dong trong file, cap nhat doi tuong hien tai neu du lieu hop le
void InstalledDevice::fromString(const string& line) {
    stringstream ss(line);
    string ma, serial, loai, tram, ngay, tt;

    if (!getline(ss, ma, '|') ||
        !getline(ss, serial, '|') ||
        !getline(ss, loai, '|') ||
        !getline(ss, tram, '|') ||
        !getline(ss, ngay, '|') ||
        !getline(ss, tt)) {
        throw invalid_argument("Dong du lieu khong dung dinh dang");
    }

    Date ngayTam;
    if (!ngayTam.napTuChuoi(Validator::catKhoangTrang(ngay))) {
        throw invalid_argument("Ngay lap rap khong hop le");
    }

    InstalledDevice duLieuMoi(ma, serial, loai, tram, ngayTam, tt);
    *this = duLieuMoi;
}

// Cap nhat thong tin, Enter de giu gia tri cu
void InstalledDevice::updateInfo() {
    string s;
    cout << "\nNhan Enter neu muon giu nguyen gia tri cu.\n";

    while (true) {
        s = InputHelper::getString("So serial moi (" + soSerial + "): ", true);
        if (s.empty() || setSoSerial(s)) {
            break;
        }
        cout << "So serial khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Ma loai moi (" + maLoai + "): ", true);
        if (s.empty() || setMaLoai(s)) {
            break;
        }
        cout << "Ma loai khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Ma tram moi (" + maTram + "): ", true);
        if (s.empty() || setMaTram(s)) {
            break;
        }
        cout << "Ma tram khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Ngay lap rap moi (" + ngayLapRap.toString() + "): ", true);
        if (s.empty() || setNgayLapRap(s)) {
            break;
        }
        cout << "Ngay lap rap khong hop le. Hay nhap lai.\n";
    }

    while (true) {
        s = InputHelper::getString("Trang thai moi (" + trangThai + "): ", true);
        if (s.empty() || setTrangThai(s)) {
            break;
        }
        cout << "Trang thai khong hop le. Hay nhap lai.\n";
    }
}

//LOP INSTALLEDDEVICEMANAGER
    // khoi tao doi tuong quan ly thiet bi lap dat
    //truyen tham chieu den repository loai thiet bi va repository tram BTS
InstalledDeviceManager::InstalledDeviceManager(Repository<DeviceType>& repoLoai,
                                               Repository<BtsStation>& repoTram)
    : repo("D:/Dev-Cpp/BTL_QuanLyTramBTS_KTLT NHOM 1/data/devices.txt"), repoLoai(repoLoai), repoTram(repoTram) {
}

void InstalledDeviceManager::hienThiMenu() const {
    cout << "\n===== QUAN LY THIET BI LAP DAT =====\n";
    cout << "1. Them thiet bi\n";
    cout << "2. Xem danh sach\n";
    cout << "3. Tim kiem\n";
    cout << "4. Cap nhat\n";
    cout << "5. Xoa\n";
    cout << "0. Quay lai\n";
    cout << "====================================\n";
}

void InstalledDeviceManager::chayChuongTrinh() {
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
        catch (const exception& loi) {
            cout << "Da xay ra loi: " << loi.what() << "\n";
            //neu luong nhap ket thuc thi thoat vong lap
            if (cin.eof()) {
                break;
            }
        }
    }
}

// Them thiet bi moi
void InstalledDeviceManager::themMoi() {
    cout << "\n--- THEM THIET BI LAP DAT ---\n";
    // Kiem tra danh muc loai thiet bi va danh sach tram BTS co du lieu hay khong
    repoLoai.loadFromFile();
    repoTram.loadFromFile();

    if (repoLoai.getAll().empty()) {
        cout << "Danh muc loai thiet bi rong. Hay them loai thiet bi truoc.\n";
        return;
    }
    if (repoTram.getAll().empty()) {
        cout << "Danh sach tram BTS rong. Hay them tram BTS truoc.\n";
        return;
    }

    string maNhap;
    while (true) {
        maNhap = Validator::catKhoangTrang(InputHelper::getString("Nhap ma thiet bi (VD: TB01): "));
        if (!Validator::kiemTraMaHopLe(maNhap)) {
            cout << "Ma thiet bi khong hop le. Hay nhap lai.\n";
            continue;
        }

        if (repo.exists(maNhap)) {
            cout << "Ma thiet bi da ton tai. Hay nhap ma khac.\n";
            continue;
        }
        break;
    }

    InstalledDevice tb;
    tb.setId(maNhap);
    tb.input();

    // Kiem tra trung so serial
    const vector<InstalledDevice>& danhSach = repo.getAll();
    while (true) {
        bool trungSerial = false;
        for (const InstalledDevice& item : danhSach) {
            if (item.getSoSerial() == tb.getSoSerial()) {
                trungSerial = true;
                break;
            }
        }
        if (!trungSerial) {
            break;
        }

        cout << "So serial da duoc thiet bi khac su dung.\n";
        while (true) {
            string serialMoi = InputHelper::getString("Nhap so serial khac: ");
            if (tb.setSoSerial(serialMoi)) {
                break;
            }
            cout << "So serial khong hop le. Hay nhap lai.\n";
        }
    }

    // Kiem tra ma loai trong danh muc
    while (!repoLoai.exists(tb.getMaLoai())) {
        cout << "Ma loai chua ton tai trong danh muc.\n";
        while (true) {
            string loaiMoi = InputHelper::getString("Nhap ma loai da ton tai: ");
            if (tb.setMaLoai(loaiMoi)) {
                break;
            }
            cout << "Ma loai khong hop le. Hay nhap lai.\n";
        }
    }

    // Kiem tra ma tram trong danh sach tram BTS
    while (!repoTram.exists(tb.getMaTram())) {
        cout << "Ma tram chua ton tai trong danh sach tram BTS.\n";
        while (true) {
            string tramMoi = InputHelper::getString("Nhap ma tram da ton tai: ");
            if (tb.setMaTram(tramMoi)) {
                break;
            }
            cout << "Ma tram khong hop le. Hay nhap lai.\n";
        }
    }

    if (repo.add(tb)) {
        cout << "Them thiet bi thanh cong!\n";
    }
    else {
        cout << "Them that bai. Khong the luu file.\n";
    }
}

void InstalledDeviceManager::xemDanhSach() {
    cout << "\n--- DANH SACH THIET BI LAP DAT ---\n";

    const vector<InstalledDevice>& danhSach = repo.getAll();
    if (danhSach.empty()) {
        cout << "Hien chua co du lieu.\n";
        return;
    }

    InstalledDevice::inTieuDeBang();
    for (const InstalledDevice& tb : danhSach) {
        tb.displayRow();
    }
    InstalledDevice::inDuongKeBang();
    cout << "Tong cong: " << danhSach.size() << " ban ghi.\n";
}

void InstalledDeviceManager::timKiem() {
    cout << "\n--- TIM KIEM THIET BI LAP DAT ---\n";
    string maTim = Validator::catKhoangTrang(InputHelper::getString("Nhap ma thiet bi can tim: "));
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        cout << "Khong tim thay thiet bi co ma: " << maTim << "\n";
    }
    else {
        tb->display();
    }
}

void InstalledDeviceManager::capNhat() {
    cout << "\n--- CAP NHAT THIET BI LAP DAT ---\n";

    repoLoai.loadFromFile();
    repoTram.loadFromFile();

    if (repoLoai.getAll().empty()) {
        cout << "Danh muc loai thiet bi rong. Hay them loai thiet bi truoc.\n";
        return;
    }
    if (repoTram.getAll().empty()) {
        cout << "Danh sach tram BTS rong. Hay them tram BTS truoc.\n";
        return;
    }

    string maTim = Validator::catKhoangTrang(InputHelper::getString("Nhap ma thiet bi can sua: "));
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        cout << "Khong tim thay thiet bi.\n";
        return;
    }

    cout << "\nThong tin hien tai:\n";
    tb->display();

    InstalledDevice banSao = *tb;
    banSao.updateInfo();

    // Kiem tra trung so serial
    const vector<InstalledDevice>& danhSach = repo.getAll();
    while (true) {
        bool trungSerial = false;
        for (const InstalledDevice& item : danhSach) {
            if (item.getId() != maTim &&
                item.getSoSerial() == banSao.getSoSerial()) {
                trungSerial = true;
                break;
            }
        }
        if (!trungSerial) {
            break;
        }

        cout << "So serial da duoc thiet bi khac su dung.\n";
        while (true) {
            string serialMoi = InputHelper::getString("Nhap so serial khac: ");
            if (banSao.setSoSerial(serialMoi)) {
                break;
            }
            cout << "So serial khong hop le. Hay nhap lai.\n";
        }
    }

    // Kiem tra ma loai trong danh muc
    while (!repoLoai.exists(banSao.getMaLoai())) {
        cout << "Ma loai chua ton tai trong danh muc.\n";
        while (true) {
            string loaiMoi = InputHelper::getString("Nhap ma loai da ton tai: ");
            if (banSao.setMaLoai(loaiMoi)) {
                break;
            }
            cout << "Ma loai khong hop le. Hay nhap lai.\n";
        }
    }

    // Kiem tra ma tram trong danh sach tram BTS
    while (!repoTram.exists(banSao.getMaTram())) {
        cout << "Ma tram chua ton tai trong danh sach tram BTS.\n";
        while (true) {
            string tramMoi = InputHelper::getString("Nhap ma tram da ton tai: ");
            if (banSao.setMaTram(tramMoi)) {
                break;
            }
            cout << "Ma tram khong hop le. Hay nhap lai.\n";
        }
    }

    if (repo.update(maTim, banSao)) {
        cout << "Cap nhat thanh cong!\n";
    }
    else {
        cout << "Cap nhat that bai. Khong the luu file.\n";
    }
}

void InstalledDeviceManager::xoa() {
    cout << "\n--- XOA THIET BI LAP DAT ---\n";
    string maTim = Validator::catKhoangTrang(InputHelper::getString("Nhap ma thiet bi can xoa: "));
    InstalledDevice* tb = repo.find(maTim);

    if (tb == nullptr) {
        cout << "Khong tim thay thiet bi.\n";
        return;
    }

    cout << "\nThong tin thiet bi muon xoa:\n";
    tb->display();

    string xacNhan = Validator::catKhoangTrang(InputHelper::getString("Ban co chac muon xoa? (y/n): "));
    if (xacNhan == "y" || xacNhan == "Y") {
        if (repo.remove(maTim)) {
            cout << "Da xoa thiet bi lap dat.\n";
        }
        else {
            cout << "Xoa that bai. Khong the luu file.\n";
        }
    }
    else {
        cout << "Da huy thao tac xoa.\n";
    }
}
