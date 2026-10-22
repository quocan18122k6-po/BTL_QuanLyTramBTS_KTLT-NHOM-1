#include "InstalledDevice.h"
#include "AntennaConfig.h"
#include "MaintenanceTicket.h"
#include "StationIncident.h"
#include "BtsStation.h"
#include "InputHelper.h"
#include "Validator.h"
#include "Date.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

namespace {
string trim(const string& value) {
    return Validator::catKhoangTrang(value);
}

void validateText(const string& value, const string& fieldName) {
    if (Validator::laChuoiRong(value)) {
        throw invalid_argument(fieldName + " khong duoc de trong.");
    }
    if (Validator::chuaKyTuPhanCach(value)) {
        throw invalid_argument(fieldName + " khong duoc chua ky tu '|'.");
    }
}

string readLine(const string& prompt, bool choPhepRong = false) {
    return InputHelper::getString(prompt, choPhepRong);
}

double parseCoordinate(const string& text, const string& fieldName) {
    size_t used = 0;
    double value;
    try {
        value = stod(text, &used);
    } catch (...) {
        throw invalid_argument(fieldName + " phai la mot so thuc hop le.");
    }
    if (used != text.size() || !isfinite(value)) {
        throw invalid_argument(fieldName + " phai la mot so thuc hop le.");
    }
    return value;
}

string formatDouble(double value) {
    ostringstream out;
    out << setprecision(15) << value;
    return out.str();
}

void readCoordinate(const string& prompt, double& output,
                    const string& fieldName, double minimum, double maximum) {
    while (true) {
        try {
            double value = InputHelper::getDouble(prompt, minimum, maximum);
            if (!Validator::kiemTraGocHopLe(value, minimum, maximum)) {
                throw out_of_range(fieldName + " nam ngoai khoang cho phep.");
            }
            output = value;
            return;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }
}
}

BtsStation::BtsStation()
    : Entity(), tenTram(""), maKhuVuc(""), diaChi(""),
      viDo(0.0), kinhDo(0.0), trangThai("") {}

BtsStation::BtsStation(const string& maTram,
                 const string& tenTram,
                 const string& maKhuVuc,
                 const string& diaChi,
                 double viDo,
                 double kinhDo,
                 const string& trangThai)
    : Entity(), tenTram(""), maKhuVuc(""), diaChi(""),
      viDo(0.0), kinhDo(0.0), trangThai("") {
    string cleanedId = trim(maTram);
    if (!Validator::kiemTraMaHopLe(cleanedId) ||
        Validator::chuaKyTuPhanCach(cleanedId)) {
        throw invalid_argument("Ma tram khong hop le.");
    }
    setId(cleanedId);
    setTenTram(tenTram);
    setMaKhuVuc(maKhuVuc);
    setDiaChi(diaChi);
    setViDo(viDo);
    setKinhDo(kinhDo);
    setTrangThai(trangThai);
}

string BtsStation::getTenTram() const { return tenTram; }
string BtsStation::getMaKhuVuc() const { return maKhuVuc; }
string BtsStation::getDiaChi() const { return diaChi; }
double BtsStation::getViDo() const { return viDo; }
double BtsStation::getKinhDo() const { return kinhDo; }
string BtsStation::getTrangThai() const { return trangThai; }

void BtsStation::setTenTram(const string& value) {
    string cleaned = trim(value);
    validateText(cleaned, "Ten tram");
    tenTram = cleaned;
}

void BtsStation::setMaKhuVuc(const string& value) {
    string cleaned = trim(value);
    if (!Validator::kiemTraMaHopLe(cleaned) ||
        Validator::chuaKyTuPhanCach(cleaned)) {
        throw invalid_argument("Ma khu vuc khong hop le.");
    }
    maKhuVuc = cleaned;
}

void BtsStation::setDiaChi(const string& value) {
    string cleaned = trim(value);
    validateText(cleaned, "Dia chi");
    diaChi = cleaned;
}

void BtsStation::setViDo(double value) {
    if (!isfinite(value) || value < -90.0 || value > 90.0) {
        throw out_of_range("Vi do phai nam trong khoang -90 den 90.");
    }
    viDo = value;
}

void BtsStation::setKinhDo(double value) {
    if (!isfinite(value) || value < -180.0 || value > 180.0) {
        throw out_of_range("Kinh do phai nam trong khoang -180 den 180.");
    }
    kinhDo = value;
}

void BtsStation::setTrangThai(const string& value) {
    string cleaned = trim(value);
    validateText(cleaned, "Trang thai");
    trangThai = cleaned;
}

void BtsStation::input() {
    while (true) {
        try {
            string maTram = readLine("Nhap ma tram BTS: ");
            if (!Validator::kiemTraMaHopLe(maTram) ||
                Validator::chuaKyTuPhanCach(maTram)) {
                throw invalid_argument("Ma tram khong hop le.");
            }
            setId(maTram);
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setTenTram(readLine("Nhap ten tram: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setMaKhuVuc(readLine("Nhap ma khu vuc: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    while (true) {
        try {
            setDiaChi(readLine("Nhap dia chi/vi tri dat tram: "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }

    readCoordinate("Nhap vi do (-90 den 90): ", viDo, "Vi do", -90.0, 90.0);
    readCoordinate("Nhap kinh do (-180 den 180): ", kinhDo, "Kinh do", -180.0, 180.0);

    while (true) {
        try {
            setTrangThai(readLine("Nhap trang thai (Hoat dong/Bao tri/Ngung hoat dong): "));
            break;
        } catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }
    }
}

void BtsStation::display() const {
    cout << "Ma tram: " << getId() << '\n'
         << "Ten tram: " << tenTram << '\n'
         << "Ma khu vuc: " << maKhuVuc << '\n'
         << "Dia chi/vi tri: " << diaChi << '\n'
         << "Vi do: " << viDo << '\n'
         << "Kinh do: " << kinhDo << '\n'
         << "Trang thai: " << trangThai << '\n';
}

void BtsStation::displayRow() const {
    cout << left << setw(14) << getId()
         << setw(24) << tenTram
         << setw(14) << maKhuVuc
         << setw(28) << diaChi
         << setw(13) << fixed << setprecision(5) << viDo
         << setw(13) << fixed << setprecision(5) << kinhDo
         << trangThai << '\n';
}

// Dinh dang luu: maTram|tenTram|maKhuVuc|diaChi|viDo|kinhDo|trangThai
string BtsStation::toString() const {
    return getId() + "|" + tenTram + "|" + maKhuVuc + "|" + diaChi + "|" +
           formatDouble(viDo) + "|" + formatDouble(kinhDo) + "|" + trangThai;
}

void BtsStation::fromString(const string& line) {
    string fields[7];
    size_t start = 0;
    for (int i = 0; i < 6; ++i) {
        size_t pos = line.find('|', start);
        if (pos == string::npos) {
            throw invalid_argument("Ban ghi BtsStation phai co dung 7 truong.");
        }
        fields[i] = line.substr(start, pos - start);
        start = pos + 1;
    }
    if (line.find('|', start) != string::npos) {
        throw invalid_argument("Ban ghi BtsStation phai co dung 7 truong.");
    }
    fields[6] = line.substr(start);

    string maTram = trim(fields[0]);
    if (!Validator::kiemTraMaHopLe(maTram) ||
        Validator::chuaKyTuPhanCach(maTram)) {
        throw invalid_argument("Ma tram khong hop le.");
    }
    setId(maTram);
    setTenTram(fields[1]);
    setMaKhuVuc(fields[2]);
    setDiaChi(fields[3]);
    setViDo(parseCoordinate(trim(fields[4]), "Vi do"));
    setKinhDo(parseCoordinate(trim(fields[5]), "Kinh do"));
    setTrangThai(fields[6]);
}

void BtsStation::updateInfo() {
    cout << "Bo trong neu muon giu nguyen gia tri hien tai.\n";
    string value;

    value = readLine("Ten tram [" + tenTram + "]: ", true);
    if (!trim(value).empty()) {
        try { setTenTram(value); }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }

    value = readLine("Ma khu vuc [" + maKhuVuc + "]: ", true);
    if (!trim(value).empty()) {
        try { setMaKhuVuc(value); }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }

    value = readLine("Dia chi/vi tri [" + diaChi + "]: ", true);
    if (!trim(value).empty()) {
        try { setDiaChi(value); }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }

    value = readLine("Vi do [" + formatDouble(viDo) + "]: ", true);
    if (!trim(value).empty()) {
        try {
            double newValue = parseCoordinate(trim(value), "Vi do");
            if (!Validator::kiemTraGocHopLe(newValue, -90.0, 90.0))
                throw out_of_range("Vi do phai nam trong khoang -90 den 90.");
            setViDo(newValue);
        }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }

    value = readLine("Kinh do [" + formatDouble(kinhDo) + "]: ", true);
    if (!trim(value).empty()) {
        try {
            double newValue = parseCoordinate(trim(value), "Kinh do");
            if (!Validator::kiemTraGocHopLe(newValue, -180.0, 180.0))
                throw out_of_range("Kinh do phai nam trong khoang -180 den 180.");
            setKinhDo(newValue);
        }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }

    value = readLine("Trang thai [" + trangThai + "]: ", true);
    if (!trim(value).empty()) {
        try { setTrangThai(value); }
        catch (const exception& e) { cout << "Loi: " << e.what() << ". Giu nguyen gia tri cu.\n"; }
    }
}


// Toan tu ghi mot ban ghi BtsStation ra file.
ostream& operator<<(ostream& out, const BtsStation& station) {
    out << station.toString();
    return out;
}

// Toan tu doc tung dong du lieu tu file.
istream& operator>>(istream& in, BtsStation& station) {
    string line;
    while (getline(in, line)) {
        if (line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }
        try {
            station.fromString(line);
        } catch (const exception&) {
            in.setstate(ios::failbit);
        }
        return in;
    }
    return in;
}


// ============================================================
// BtsStationUseCase: menu va thao tac quan ly tram BTS
// ============================================================

namespace {
string stationLowerCase(string value) {
    transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return value;
}

string readUseCaseLine(const string& prompt, bool choPhepRong = false) {
    return InputHelper::getString(prompt, choPhepRong);
}

int readStationChoice(const string& prompt) {
    return InputHelper::getInt(prompt);
}

void printStationHeader() {
    cout << left << setw(14) << "Ma tram" << setw(24) << "Ten tram"
         << setw(14) << "Ma khu vuc" << setw(28) << "Dia chi/vi tri"
         << setw(13) << "Vi do" << setw(13) << "Kinh do"
         << "Trang thai\n" << string(119, '-') << '\n';
}
}

BtsStationUseCase::BtsStationUseCase(
    Repository<BtsStation>& stationRepository,
    Repository<Province>& provinceRepository,
    Repository<InstalledDevice>& deviceRepository,
    Repository<AntennaConfig>& antennaRepository,
    Repository<MaintenanceTicket>& maintenanceRepository,
    Repository<StationIncident>& incidentRepository
) : stationRepository(stationRepository),
    provinceRepository(provinceRepository),
    deviceRepository(deviceRepository),
    antennaRepository(antennaRepository),
    maintenanceRepository(maintenanceRepository),
    incidentRepository(incidentRepository) {}

void BtsStationUseCase::run() {
    while (true) {
        cout << "\n=============== QUAN LY TRAM BTS ===============\n"
             << "1. Them tram BTS\n"
             << "2. Xem danh sach tram BTS\n"
             << "3. Tim kiem tram BTS\n"
             << "4. Sap xep danh sach\n"
             << "5. Cap nhat thong tin tram\n"
             << "6. Xoa tram BTS\n"
             << "0. Quay lai\n";

        switch (readStationChoice("Nhap lua chon: ")) {
            case 1: addStation(); break;
            case 2: showStations(); break;
            case 3: searchStation(); break;
            case 4: sortStations(); break;
            case 5: updateStation(); break;
            case 6: deleteStation(); break;
            case 0: return;
            default: cout << "Lua chon khong hop le.\n";
        }
    }
}

void BtsStationUseCase::addStation() {
    try {
        BtsStation tram;
        tram.input();

        if (stationRepository.exists(tram.getId())) {
            cout << "Ma tram da ton tai.\n";
            return;
        }
        if (!provinceRepository.exists(tram.getMaKhuVuc())) {
            cout << "Ma khu vuc khong ton tai. Hay tao khu vuc truoc.\n";
            return;
        }

        cout << (stationRepository.add(tram)
            ? "Them tram BTS thanh cong.\n"
            : "Them that bai; kiem tra file du lieu.\n");
    } catch (const exception& e) {
        cout << "Khong the them tram BTS: " << e.what() << '\n';
    }
}

void BtsStationUseCase::showStations() const {
    const vector<BtsStation>& all = stationRepository.getAll();
    if (all.empty()) {
        cout << "Danh sach tram BTS rong.\n";
        return;
    }
    printStationHeader();
    for (const BtsStation& tram : all) tram.displayRow();
}

void BtsStationUseCase::searchStation() const {
    cout << "1. Ma tram\n2. Ten tram\n3. Ma khu vuc\n"
         << "4. Dia chi/vi tri\n5. Trang thai\n";
    int criterion = readStationChoice("Tieu chi tim kiem: ");
    string keyword = readUseCaseLine("Nhap tu khoa: ");
    string keyLower = stationLowerCase(keyword);
    bool found = false;

    for (const BtsStation& tram : stationRepository.getAll()) {
        bool match = false;
        switch (criterion) {
            case 1: match = tram.getId() == keyword; break;
            case 2: match = stationLowerCase(tram.getTenTram()).find(keyLower) != string::npos; break;
            case 3: match = tram.getMaKhuVuc() == keyword; break;
            case 4: match = stationLowerCase(tram.getDiaChi()).find(keyLower) != string::npos; break;
            case 5: match = stationLowerCase(tram.getTrangThai()).find(keyLower) != string::npos; break;
            default: cout << "Tieu chi tim kiem khong hop le.\n"; return;
        }
        if (match) {
            if (!found) printStationHeader();
            tram.displayRow();
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay tram BTS phu hop.\n";
}

void BtsStationUseCase::sortStations() {
    cout << "1. Ma tram\n2. Ten tram\n3. Ma khu vuc\n4. Trang thai\n";
    int criterion = readStationChoice("Sap xep theo: ");
    switch (criterion) {
        case 1:
            stationRepository.sortRecords([](const BtsStation& a, const BtsStation& b) {
                return a.getId() < b.getId();
            });
            break;
        case 2:
            stationRepository.sortRecords([](const BtsStation& a, const BtsStation& b) {
                return stationLowerCase(a.getTenTram()) < stationLowerCase(b.getTenTram());
            });
            break;
        case 3:
            stationRepository.sortRecords([](const BtsStation& a, const BtsStation& b) {
                return a.getMaKhuVuc() < b.getMaKhuVuc();
            });
            break;
        case 4:
            stationRepository.sortRecords([](const BtsStation& a, const BtsStation& b) {
                return stationLowerCase(a.getTrangThai()) < stationLowerCase(b.getTrangThai());
            });
            break;
        default:
            cout << "Tieu chi sap xep khong hop le.\n";
            return;
    }

    cout << "Da sap xep danh sach trong bo nho (chua ghi lai thu tu vao file).\n";
    showStations();
}

void BtsStationUseCase::updateStation() {
    string id = readUseCaseLine("Nhap ma tram can cap nhat: ");
    BtsStation* current = stationRepository.find(id);
    if (!current) {
        cout << "Khong tim thay ma tram.\n";
        return;
    }

    current->display();
    BtsStation updated = *current;
    updated.updateInfo();

    if (!provinceRepository.exists(updated.getMaKhuVuc())) {
        cout << "Ma khu vuc moi khong ton tai; huy cap nhat.\n";
        return;
    }

    cout << (stationRepository.update(id, updated)
        ? "Cap nhat tram BTS thanh cong.\n"
        : "Cap nhat that bai; du lieu chua duoc luu.\n");
}

bool BtsStationUseCase::tramDangDuocSuDung(const std::string& maTram) {
    // InstalledDeviceManager hien giu Repository rieng.
    // Nap lai de kiem tra danh sach thiet bi moi nhat.
    deviceRepository.loadFromFile();

    for (const auto& thietBi : deviceRepository.getAll()) {
        if (thietBi.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& anten : antennaRepository.getAll()) {
        if (anten.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& phieu : maintenanceRepository.getAll()) {
        if (phieu.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& suCo : incidentRepository.getAll()) {
        if (suCo.getMaTram() == maTram) {
            return true;
        }
    }

    return false;
}

void BtsStationUseCase::deleteStation() {
    string id = readUseCaseLine("Nhap ma tram can xoa: ");
    BtsStation* tram = stationRepository.find(id);
    if (!tram) {
        cout << "Khong tim thay ma tram.\n";
        return;
    }
    tram->display();

    if (tramDangDuocSuDung(id)) {
        cout << "Khong the xoa: tram dang duoc doi tuong khac tham chieu.\n";
        return;
    }

    string confirm = readUseCaseLine("Xac nhan xoa (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "Da huy thao tac.\n";
        return;
    }
    cout << (stationRepository.remove(id)
        ? "Xoa tram BTS thanh cong.\n"
        : "Xoa that bai; kiem tra file du lieu.\n");
}
