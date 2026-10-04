#pragma once

#include <iostream>
#include <string>

using namespace std;

class InputHelper {
public:
    static string getString(string thongBao) {
        string ketQua;

        cout << thongBao;
        getline(cin, ketQua);

        while (ketQua.empty()) {
            cout << "Khong duoc de trong, nhap lai: ";
            getline(cin, ketQua);
        }

        return ketQua;
    }

    static int getInt(string thongBao, int minVal = -999999, int maxVal = 999999) {
        int so;

        while (1) {
            cout << thongBao;
            cin >> so;

            if (cin.fail()) {
                cout << "Loi: Phai nhap so nguyen!\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (so < minVal || so > maxVal) {
                cout << "Loi: Gia tri phai nam trong [" 
                     << minVal << " - " << maxVal << "]!\n";
                cin.ignore(1000, '\n');
            }
            else {
                cin.ignore(1000, '\n');
                return so;
            }
        }
    }
};
có lỗi về phần chống trôi lệnh tôi fix như này được không
