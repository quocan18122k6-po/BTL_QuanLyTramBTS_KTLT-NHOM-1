#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class InputHelper {
private:
    // Cat khoang trang o dau va cuoi chuoi
    static string catKhoangTrang(const string& str) {
        size_t dau = str.find_first_not_of(" \t\n\r\f\v");
        if (dau == string::npos) {
            return "";
        }
        size_t cuoi = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(dau, cuoi - dau + 1);
    }

public:
    // Nhap chuoi, co the cho phep rong khi can
    static string getString(string thongBao, bool choPhepRong = false) {
        string ketQua;

        while (true) {
            cout << thongBao;
            if (!getline(cin, ketQua)) {
                throw ios_base::failure("Ket thuc luong nhap.");
            }

            ketQua = catKhoangTrang(ketQua);

            if (!ketQua.empty() || choPhepRong) {
                return ketQua;
            }

            cout << "Loi: Khong duoc de trong, vui long nhap lai!\n";
        }
    }

    // Nhap so nguyen trong khoang cho phep
    static int getInt(string thongBao, int minVal = -999999, int maxVal = 999999) {
        string dong;

        while (true) {
            cout << thongBao;
            if (!getline(cin, dong)) {
                throw ios_base::failure("Ket thuc luong nhap.");
            }

            dong = catKhoangTrang(dong);

            if (dong.empty()) {
                cout << "Loi: Phai nhap so nguyen!\n";
                continue;
            }

            stringstream ss(dong);
            int so;
            char kyTuDu;

            if (!(ss >> so) || (ss >> kyTuDu)) {
                cout << "Loi: Du lieu nhap phai la so nguyen!\n";
                continue;
            }

            if (so < minVal || so > maxVal) {
                cout << "Loi: Gia tri phai nam trong [" << minVal << " - " << maxVal << "]!\n";
                continue;
            }
            return so;
        }
    }
};
