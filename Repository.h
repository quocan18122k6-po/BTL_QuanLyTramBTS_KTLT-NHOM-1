#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T> // Khuon mau lop tong quat: T dai dien cho bat ky Entity nao (AntennaConfig, BtsStation, StationIncident...)
class Repository {
private:
    vector<T> records;
    string fileName;

public:
    // Ham khoi tao.
    explicit Repository(const string& fileName);

    // Them, tim, sua, xoa.
    bool add(const T& record);
    T* find(const string& id); //để biểu diễn trường hợp không tìm thấy bằng giá trị nullptr
    bool update(const string& id, const T& newRecord);
    bool remove(const string& id);

    // Xem, kiem tra.
    const vector<T>& getAll() const;
    bool exists(const string& id) const;

    // Sap xep.
    void sortRecords(function<bool(const T&, const T&)> comparator);//so sanh 2 doi tuong voi nhau theo tieu chi nao do

    // Nap, luu file.
    void loadFromFile();
    bool saveToFile() const;
};

template <typename T> // Trien khai constructor cho Repository theo kieu du lieu T
Repository<T>::Repository(const string& fileName) : fileName(fileName) {
    loadFromFile();
}

template <typename T> // Doc file, yeu cau kieu T phai co ham fromString() va getId()
void Repository<T>::loadFromFile() {
    ifstream file(fileName);// luong doc file

    // Neu khong mo duoc file, thu tao file rong.
    if (!file.is_open()) {
        ofstream newFile(fileName);

        if (!newFile.is_open()) {
            cerr << "Loi: Khong the mo hoac tao file: "
                 << fileName << '\n'; // bao loi khi khong the mo file
            return;
        }

        // Chi xoa du lieu trong bo nho sau khi tao file thanh cong.
        records.clear();
        return;
    }

    // Chi xoa du lieu cu sau khi mo file thanh cong.
    records.clear();

    string line;
    int lineNumber = 0;// dem so thu tu dong

    while (getline(file, line)) { //doc tung dong de xu ly
        ++lineNumber;

        // Bo qua dong rong hoac chi co khoang trang/tab.
        if (line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        try {
            T record;
            record.fromString(line);

            // Bo qua ban ghi co ID trung voi ban ghi da nap.
            if (exists(record.getId())) {
                cerr << "Canh bao: ID trung lap tai dong "
                     << lineNumber << " trong file " << fileName
                     << "; bo qua ban ghi.\n";
                continue;
            }

            records.push_back(record);// them doi tuong hoan chinh vao mang record
        } catch (const exception& e) {
            cerr << "Canh bao: Du lieu khong hop le tai dong "
                 << lineNumber << " trong file " << fileName
                 << ": " << e.what() << "; bo qua ban ghi.\n";
        }
    }

    if (file.bad()) { // Loi thiet bi
        cerr << "Loi: Xay ra loi khi doc file: "
             << fileName << '\n';
    }
}

template <typename T> // Ghi file, yeu cau kieu T phai co ham toString()
bool Repository<T>::saveToFile() const {
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Loi: Khong the mo file de ghi: "
             << fileName << '\n';
        return false;
    }

    for (const T& record : records) { // duyet cac doi tuong cua mang records
        file << record.toString() << '\n';

        if (!file) {
            cerr << "Loi: Ghi du lieu that bai vao file: "
                 << fileName << '\n';
            file.close();
            return false;
        }
    }

    file.close(); // dong luong ghi, day du lieu vao bo nho


    if (file.fail()) {
        cerr << "Loi: Dong file sau khi ghi that bai: "
             << fileName << '\n';
        return false;
    }

    return true;
}

template <typename T> // Kiem tra ton tai: T phai co phuong thuc getId()
bool Repository<T>::exists(const string& id) const {
    for (const T& record : records) {
        if (record.getId() == id) {
            return true;
        }
    }

    return false;
}

template <typename T> // Them ban ghi kieu T va luu file (co rollback neu loi)
bool Repository<T>::add(const T& record) {
    if (exists(record.getId())) {
        return false;
    }

    records.push_back(record);// them tam du lieu

    if (!saveToFile()) {
        records.pop_back(); // hoan tac du lieu
        return false;
    }

    return true;
}

template <typename T> // Lay toan bo danh sach T duoi dang tham chieu hang 
const vector<T>& Repository<T>::getAll() const {
    return records;
}

template <typename T> // Tim kiem ban ghi T theo id, tra ve con tro T* (hoac nullptr)
T* Repository<T>::find(const string& id) {
    for (T& record : records) {
        if (record.getId() == id) { // so sanh voi id can tim
            return &record;
        }
    }

    return nullptr; // tra ve con tro rong khi khong thay
}

template <typename T> // Cap nhat thong tin cho ban ghi T (co hoan tac ve Record cu neu loi
bool Repository<T>::update(const string& id, const T& newRecord) {
    T* record = find(id);

    if (record == nullptr || newRecord.getId() != id) { // khong cho phep doi ma khoa chinh
        return false;
    }

    T oldRecord = *record; // tao ban sao cu de hoan tac
    *record = newRecord;

    if (!saveToFile()) { // neu khong luu duoc thi hoan tac
        *record = oldRecord;
        return false;
    }

    return true;
}

template <typename T> // Xoa ban ghi T khoi vector va cap nhat file
bool Repository<T>::remove(const string& id) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (it->getId() == id) { // tim id can xoa
            T oldRecord = *it;
            auto index = it - records.begin(); // luu vi tri de hoan tac

            records.erase(it);// xoa phan tu khoi mang

            if (!saveToFile()) {
                records.insert(records.begin() + index, oldRecord); // chen doi tuong hoan tac khi gap loi
                return false;
            }

            return true;
        }
    }

    return false;
}

template <typename T>// Sap xep vector<T> thong qua ham so sanh hoac lambda truyen vao
void Repository<T>::sortRecords(
    function<bool(const T&, const T&)> comparator
) {
    sort(records.begin(), records.end(), comparator);
}

#endif
