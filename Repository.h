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

template <typename T>
class Repository {
private:
    vector<T> records;
    string fileName;

public:
    // Ham khoi tao.
    explicit Repository(const string& fileName);

    // Them, tim, sua, xoa.
    bool add(const T& record);
    T* find(const string& id);
    bool update(const string& id, const T& newRecord);
    bool remove(const string& id);

    // Xem, kiem tra.
    const vector<T>& getAll() const;
    bool exists(const string& id) const;

    // Sap xep.
    void sortRecords(function<bool(const T&, const T&)> comparator);

    // Nap, luu file.
    void loadFromFile();
    bool saveToFile() const;
};

template <typename T>
Repository<T>::Repository(const string& fileName) : fileName(fileName) {
    loadFromFile();
}

template <typename T>
void Repository<T>::loadFromFile() {
    ifstream file(fileName);

    // Neu khong mo duoc file, thu tao file rong.
    if (!file.is_open()) {
        ofstream newFile(fileName);

        if (!newFile.is_open()) {
            cerr << "Loi: Khong the mo hoac tao file: "
                 << fileName << '\n';
            return;
        }

        // Chi xoa du lieu trong bo nho sau khi tao file thanh cong.
        records.clear();
        return;
    }

    // Chi xoa du lieu cu sau khi mo file thanh cong.
    records.clear();

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
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

            records.push_back(record);
        } catch (const exception& e) {
            cerr << "Canh bao: Du lieu khong hop le tai dong "
                 << lineNumber << " trong file " << fileName
                 << ": " << e.what() << "; bo qua ban ghi.\n";
        }
    }

    if (file.bad()) {
        cerr << "Loi: Xay ra loi khi doc file: "
             << fileName << '\n';
    }
}

template <typename T>
bool Repository<T>::saveToFile() const {
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Loi: Khong the mo file de ghi: "
             << fileName << '\n';
        return false;
    }

    for (const T& record : records) {
        file << record.toString() << '\n';

        if (!file) {
            cerr << "Loi: Ghi du lieu that bai vao file: "
                 << fileName << '\n';
            file.close();
            return false;
        }
    }

    file.close();

    if (file.fail()) {
        cerr << "Loi: Dong file sau khi ghi that bai: "
             << fileName << '\n';
        return false;
    }

    return true;
}

template <typename T>
bool Repository<T>::exists(const string& id) const {
    for (const T& record : records) {
        if (record.getId() == id) {
            return true;
        }
    }

    return false;
}

template <typename T>
bool Repository<T>::add(const T& record) {
    if (exists(record.getId())) {
        return false;
    }

    records.push_back(record);

    if (!saveToFile()) {
        records.pop_back();
        return false;
    }

    return true;
}

template <typename T>
const vector<T>& Repository<T>::getAll() const {
    return records;
}

template <typename T>
T* Repository<T>::find(const string& id) {
    for (T& record : records) {
        if (record.getId() == id) {
            return &record;
        }
    }

    return nullptr;
}

template <typename T>
bool Repository<T>::update(const string& id, const T& newRecord) {
    T* record = find(id);

    if (record == nullptr || newRecord.getId() != id) {
        return false;
    }

    T oldRecord = *record;
    *record = newRecord;

    if (!saveToFile()) {
        *record = oldRecord;
        return false;
    }

    return true;
}

template <typename T>
bool Repository<T>::remove(const string& id) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (it->getId() == id) {
            T oldRecord = *it;
            auto index = it - records.begin();

            records.erase(it);

            if (!saveToFile()) {
                records.insert(records.begin() + index, oldRecord);
                return false;
            }

            return true;
        }
    }

    return false;
}

template <typename T>
void Repository<T>::sortRecords(
    function<bool(const T&, const T&)> comparator
) {
    sort(records.begin(), records.end(), comparator);
}

#endif
