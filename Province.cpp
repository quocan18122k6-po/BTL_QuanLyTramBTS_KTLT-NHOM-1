#include "Province.h"
#include "InputHelper.h"
#include "Validator.h"
#include "Date.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace {
    // Xoa khoang trang o dau va cuoi chuoi.
    string trim(const string& value) {
        return Validator::catKhoangTrang(value);
    }

    // Dung Validator de kiem tra du lieu truoc khi luu vao file text.
    void validateField(const string& value, const string& fieldName) {
        if (Validator::laChuoiRong(value)) {
            throw invalid_argument(fieldName + " khong duoc de trong.");
        }
        if (Validator::chuaKyTuPhanCach(value)) {
            throw invalid_argument(fieldName + " khong duoc chua ky tu '|'.");
        }
    }

    // Dung InputHelper de nhap chuoi va cat khoang trang dau/cuoi.
    string readLine(const string& prompt, bool choPhepRong = false) {
        return InputHelper::getString(prompt, choPhepRong);
    }
}

// Ham khoi tao mac dinh.
Province::Province()
    : Entity(), tenTinh(""), diaHinh(""), donViQuanLy("") {
}

// Ham khoi tao day du thong tin.
Province::Province(const string& maKhuVuc,
                   const string& tenTinh,
                   const string& diaHinh,
                   const string& donViQuanLy)
    : Entity(), tenTinh(""), diaHinh(""), donViQuanLy("") {
    string ma = trim(maKhuVuc);

    if (!Validator::kiemTraMaHopLe(ma) || Validator::chuaKyTuPhanCach(ma)) {
        throw invalid_argument("Ma khu vuc khong hop le.");
    }

    setId(ma);
    setTenTinh(tenTinh);
    setDiaHinh(diaHinh);
    setDonViQuanLy(donViQuanLy);
}

// Getter.
string Province::getTenTinh() const {
    return tenTinh;
}

string Province::getDiaHinh() const {
    return diaHinh;
}

string Province::getDonViQuanLy() const {
    return donViQuanLy;
}

// Setter co kiem tra du lieu.
void Province::setTenTinh(const string& value) {
    string cleanedValue = trim(value);
    validateField(cleanedValue, "Ten tinh");
    tenTinh = cleanedValue;
}

void Province::setDiaHinh(const string& value) {
    string cleanedValue = trim(value);
    validateField(cleanedValue, "Dia hinh");
    diaHinh = cleanedValue;
}

void Province::setDonViQuanLy(const string& value) {
    string cleanedValue = trim(value);
    validateField(cleanedValue, "Don vi quan ly");
    donViQuanLy = cleanedValue;
}

// Nhap du lieu cho mot khu vuc/tinh.
void Province::input() {
    while (true) {
        try {
            string maKhuVuc = readLine("Nhap ma khu vuc: ");

            if (!Validator::kiemTraMaHopLe(maKhuVuc) ||
                Validator::chuaKyTuPhanCach(maKhuVuc)) {
                throw invalid_argument("Ma khu vuc khong hop le.");
            }

            setId(maKhuVuc);
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setTenTinh(readLine("Nhap ten tinh/thanh pho: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setDiaHinh(readLine("Nhap dia hinh trien khai: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setDonViQuanLy(readLine("Nhap don vi quan ly: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }
}

// Hien thi day du thong tin.
void Province::display() const {
    cout << "Ma khu vuc: " << getId() << '\n'
         << "Ten tinh/thanh pho: " << tenTinh << '\n'
         << "Dia hinh: " << diaHinh << '\n'
         << "Don vi quan ly: " << donViQuanLy << '\n';
}

// Hien thi mot ban ghi theo dang bang.
void Province::displayRow() const {
    cout << left
         << setw(14) << getId()
         << setw(26) << tenTinh
         << setw(22) << diaHinh
         << donViQuanLy << '\n';
}

// Chuyen doi doi tuong thanh mot dong de luu vao file.
// Dinh dang: id|tenTinh|diaHinh|donViQuanLy
string Province::toString() const {
    return getId() + "|" + tenTinh + "|" + diaHinh + "|" + donViQuanLy;
}

// Doc mot dong trong file va chuyen thanh doi tuong Province.
void Province::fromString(const string& line) {
    size_t p1 = line.find('|');
    size_t p2 = (p1 == string::npos)
                    ? string::npos
                    : line.find('|', p1 + 1);
    size_t p3 = (p2 == string::npos)
                    ? string::npos
                    : line.find('|', p2 + 1);

    // Phai co dung 4 truong, tuong ung 3 dau '|'.
    if (p1 == string::npos || p2 == string::npos || p3 == string::npos ||
        line.find('|', p3 + 1) != string::npos) {
        throw invalid_argument("Ban ghi Province phai co dung 4 truong.");
    }

    string maKhuVuc = trim(line.substr(0, p1));
    string ten = line.substr(p1 + 1, p2 - p1 - 1);
    string hinh = line.substr(p2 + 1, p3 - p2 - 1);
    string donVi = line.substr(p3 + 1);

    if (!Validator::kiemTraMaHopLe(maKhuVuc) ||
        Validator::chuaKyTuPhanCach(maKhuVuc)) {
        throw invalid_argument("Ma khu vuc khong hop le.");
    }

    setId(maKhuVuc);
    setTenTinh(ten);
    setDiaHinh(hinh);
    setDonViQuanLy(donVi);
}

// Toan tu ghi: moi Province duoc luu tren mot dong theo dinh dang toString().
ostream& operator<<(ostream& out, const Province& province) {
    out << province.toString();
    return out;
}

// Toan tu doc: doc mot dong va chuyen no thanh doi tuong Province.
// Ham nay giup tuong thich voi Repository.h cu dung file >> record.
istream& operator>>(istream& in, Province& province) {
    string line;
    while (getline(in, line)) {
        if (!trim(line).empty()) {
            try {
                province.fromString(line);
            } catch (const exception&) {
                in.setstate(ios::failbit);
            }
            return in;
        }
    }
    return in;
}

// Cap nhat cac truong; bo trong de giu gia tri cu.
// Ma khu vuc (id) khong duoc thay doi.
void Province::updateInfo() {
    cout << "Bo trong neu muon giu nguyen gia tri hien tai.\n";
    string value;

    while (true) {
        value = readLine("Ten tinh/thanh pho [" + tenTinh + "]: ", true);
        if (trim(value).empty()) {
            break;
        }
        try {
            setTenTinh(value);
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        value = readLine("Dia hinh [" + diaHinh + "]: ", true);
        if (trim(value).empty()) {
            break;
        }
        try {
            setDiaHinh(value);
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        value = readLine("Don vi quan ly [" + donViQuanLy + "]: ", true);
        if (trim(value).empty()) {
            break;
        }
        try {
            setDonViQuanLy(value);
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }
}

// ============================================================
// ProvinceUseCase: chuc nang quan ly khu vuc/tinh
// ============================================================

namespace {
string lowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}
string readUseCaseLine(const string& prompt, bool choPhepRong = false) {
    return InputHelper::getString(prompt, choPhepRong);
}
int readChoice(const string& prompt) {
    return InputHelper::getInt(prompt);
}
void header() {
    cout << left << setw(14) << "Ma khu vuc" << setw(26) << "Ten tinh/thanh pho"
         << setw(22) << "Dia hinh" << "Don vi quan ly\n"
         << string(85, '-') << '\n';
}
}

ProvinceUseCase::ProvinceUseCase(
    Repository<Province>& repository,
    function<bool(const string&)> isReferenced
) : repository(repository), isReferenced(isReferenced) {}

void ProvinceUseCase::run() {
    while (true) {
        cout << "\n========== QUAN LY KHU VUC / TINH ==========\n"
             << "1. Them khu vuc\n2. Xem danh sach\n3. Tim kiem\n"
             << "4. Sap xep\n5. Cap nhat\n6. Xoa\n0. Quay lai\n";
        switch (readChoice("Nhap lua chon: ")) {
            case 1: addProvince(); break;
            case 2: showProvinces(); break;
            case 3: searchProvince(); break;
            case 4: sortProvinces(); break;
            case 5: updateProvince(); break;
            case 6: deleteProvince(); break;
            case 0: return;
            default: cout << "Lua chon khong hop le.\n";
        }
    }
}

void ProvinceUseCase::addProvince() {
    try {
        Province p;
        p.input();
        if (repository.exists(p.getId())) {
            cout << "Ma khu vuc da ton tai.\n";
            return;
        }
        cout << (repository.add(p) ? "Them thanh cong.\n" :
                "Them that bai; kiem tra file du lieu.\n");
    } catch (const exception& e) {
        cout << "Khong the them: " << e.what() << '\n';
    }
}

void ProvinceUseCase::showProvinces() const {
    const vector<Province>& all = repository.getAll();
    if (all.empty()) { cout << "Danh sach rong.\n"; return; }
    header();
    for (const Province& p : all) p.displayRow();
}

void ProvinceUseCase::searchProvince() const {
    cout << "1. Ma khu vuc\n2. Ten tinh/thanh pho\n3. Dia hinh\n4. Don vi quan ly\n";
    int choice = readChoice("Tieu chi: ");
    string key = readUseCaseLine("Tu khoa: ");
    bool found = false;
    for (const Province& p : repository.getAll()) {
        bool match = false;
        switch (choice) {
            case 1: match = p.getId() == key; break;
            case 2: match = lowerCase(p.getTenTinh()).find(lowerCase(key)) != string::npos; break;
            case 3: match = lowerCase(p.getDiaHinh()).find(lowerCase(key)) != string::npos; break;
            case 4: match = lowerCase(p.getDonViQuanLy()).find(lowerCase(key)) != string::npos; break;
            default: cout << "Tieu chi khong hop le.\n"; return;
        }
        if (match) {
            if (!found) header();
            p.displayRow();
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua.\n";
}

void ProvinceUseCase::sortProvinces() {
    cout << "1. Ma khu vuc\n2. Ten tinh/thanh pho\n3. Dia hinh\n4. Don vi quan ly\n";
    int choice = readChoice("Sap xep theo: ");
    switch (choice) {
        case 1: repository.sortRecords([](const Province& a, const Province& b) { return a.getId() < b.getId(); }); break;
        case 2: repository.sortRecords([](const Province& a, const Province& b) { return lowerCase(a.getTenTinh()) < lowerCase(b.getTenTinh()); }); break;
        case 3: repository.sortRecords([](const Province& a, const Province& b) { return lowerCase(a.getDiaHinh()) < lowerCase(b.getDiaHinh()); }); break;
        case 4: repository.sortRecords([](const Province& a, const Province& b) { return lowerCase(a.getDonViQuanLy()) < lowerCase(b.getDonViQuanLy()); }); break;
        default: cout << "Tieu chi khong hop le.\n"; return;
    }
    cout << "Da sap xep danh sach trong bo nho.\n";
    showProvinces();
}

void ProvinceUseCase::updateProvince() {
    string id = readUseCaseLine("Nhap ma khu vuc can cap nhat: ");
    Province* p = repository.find(id);
    if (!p) { cout << "Khong tim thay ma khu vuc.\n"; return; }
    p->display();
    Province updated = *p;
    updated.updateInfo();
    cout << (repository.update(id, updated) ? "Cap nhat thanh cong.\n" :
             "Cap nhat that bai; du lieu chua duoc luu.\n");
}

void ProvinceUseCase::deleteProvince() {
    string id = readUseCaseLine("Nhap ma khu vuc can xoa: ");
    Province* p = repository.find(id);
    if (!p) { cout << "Khong tim thay ma khu vuc.\n"; return; }
    p->display();

    if (!isReferenced) {
        cout << "Chua ket noi kiem tra tham chieu TramBTS; tam thoi khong cho xoa.\n";
        return;
    }
    if (isReferenced(id)) {
        cout << "Khong the xoa: khu vuc dang duoc tram BTS tham chieu.\n";
        return;
    }

    string confirm = readUseCaseLine("Xac nhan xoa (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "Da huy thao tac.\n";
        return;
    }
    cout << (repository.remove(id) ? "Xoa thanh cong.\n" :
             "Xoa that bai; kiem tra file du lieu.\n");
}
