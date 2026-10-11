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
    // 1. Nhap chuoi: ho tro bat buoc hoac cho phep bo trong khi update
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

    // 2. Nhap so nguyen co kiem tra hop le
    // - choPhepRong = true: nguoi dung an Enter -> tra ve giaTriMacDinh (dung khi Update)
    static int getInt(string thongBao, int minVal = -999999, int maxVal = 999999, 
                      bool choPhepRong = false, int giaTriMacDinh = 0) {
        string dong;

        while (true) {
            cout << thongBao;
            if (!getline(cin, dong)) {
                throw ios_base::failure("Ket thuc luong nhap.");
            }

            dong = catKhoangTrang(dong);

            // Xu ly khi bo trong (Enter)
            if (dong.empty()) {
                if (choPhepRong) {
                    return giaTriMacDinh;
                }
                cout << "Loi: Khong duoc de trong, phai nhap so nguyen!\n";
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
                cout << "Loi: Gia tri phai nam trong [" 
                     << minVal << " - " << maxVal << "]!\n";
                continue;
            }

            return so;
        }
    }

    // 3. Nhap so thuc (double) - phuc vu SV4 nhap goc tilt, azimuth
    // - choPhepRong = true: nguoi dung an Enter -> tra ve giaTriMacDinh (dung khi Update)
    static double getDouble(string thongBao, double minVal = -999999.0, double maxVal = 999999.0, 
                            bool choPhepRong = false, double giaTriMacDinh = 0.0) {
        string dong;

        while (true) {
            cout << thongBao;
            if (!getline(cin, dong)) {
                throw ios_base::failure("Ket thuc luong nhap.");
            }

            dong = catKhoangTrang(dong);

            // Xu ly khi bo trong (Enter)
            if (dong.empty()) {
                if (choPhepRong) {
                    return giaTriMacDinh;
                }
                cout << "Loi: Khong duoc de trong, phai nhap so thuc!\n";
                continue;
            }

            stringstream ss(dong);
            double so;
            char kyTuDu;

            if (!(ss >> so) || (ss >> kyTuDu)) {
                cout << "Loi: Du lieu nhap phai la so thuc hop le!\n";
                continue;
            }

            if (so < minVal || so > maxVal) {
                cout << "Loi: Gia tri phai nam trong [" 
                     << minVal << " - " << maxVal << "]!\n";
                continue;
            }

            return so;
        }
    }
};
