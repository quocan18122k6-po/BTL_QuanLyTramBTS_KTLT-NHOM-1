#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Repository {
private:
    vector<T> records;
    string fileName;

public:
    Repository(const string& fileName);

    // Thêm, tìm, s?a, xóa. 
    bool add(const T& record);
    T* find(const string& id);
    bool update(const string& id, const T& newRecord);
    bool remove(const string& id);

    // Xem, ki?m tra.
    const vector<T>& getAll() const;
    bool exists(const string& id) const;

    // S?p x?p. 
    void sortRecords(function<bool(const T&, const T&)> comparator);

    // N?p, luu file. 
    void loadFromFile();
    bool saveToFile() const;
};

template <typename T>
Repository<T>::Repository(const string& fileName) {
	this->fileName = fileName;
	loadFromFile();
}
 
template <typename T>
void Repository<T>::loadFromFile() {
	ifstream file(fileName);
	
	if (!file.is_open()) {
        ofstream newFile(fileName);
        return;
    }
	
	T record;
	
	while (file >> record) {
		records.push_back(record);
	}
	
	file.close();
}

template <typename T>
bool Repository<T>::saveToFile() const {
	ofstream file(fileName);
	
	if (!file.is_open()) {
    	return false;
	}
	
	for (const T& record : records) {
		file << record << "\n";
	}
	
	file.close();
	
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
	
	if (record == nullptr) {
		return false;
	}
	
	if (newRecord.getId() != id) {
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
			auto idx = it - records.begin();
			
			records.erase(it);
			
			if (!saveToFile()) {
				records.insert(records.begin() + idx, oldRecord);
				return false;
			}
			
			return true;
		}
	}
	
	return false;
}

template <typename T>
void Repository<T>::sortRecords(function<bool(const T&, const T&)> comparator) {
    sort(records.begin(), records.end(), comparator);
}

#endif
