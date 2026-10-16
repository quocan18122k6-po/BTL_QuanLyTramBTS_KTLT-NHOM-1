#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <sstream>
#include <cmath>
#include "Date.h"

class Validator {
public:
    // Cat khoang trang o dau va cuoi chuoi
    static std::string catKhoangTrang(const std::string& s) {
        int dau = 0;
        int cuoi = (int)s.length() - 1;
        while (dau < (int)s.length() &&
               (s[dau] == ' ' || s[dau] == '\t' ||
                s[dau] == '\n' || s[dau] == '\r')) {
            dau++;
        }

        while (cuoi >= dau &&
               (s[cuoi] == ' ' || s[cuoi] == '\t' ||
                s[cuoi] == '\n' || s[cuoi] == '\r')) {
            cuoi--;
        }
        if (dau > cuoi) {
            return "";
        }
        return s.substr(dau, cuoi - dau + 1);
    }

    // Kiem tra chuoi rong
    static bool laChuoiRong(const std::string& s) {
        return catKhoangTrang(s).empty();
    }

    // Kiem tra chuoi co chua ky tu phan cach hay khong
    static bool chuaKyTuPhanCach(const std::string& s, char kyTu = '|') {
        return s.find(kyTu) != std::string::npos;
    }

    // Kiem tra do dai chuoi khong vuot qua gioi han
    static bool kiemTraDoDai(const std::string& s, size_t maxLen) {
        std::string str = catKhoangTrang(s);
        if (str.length() > maxLen) {
            return false;
        }
        return true;
    }

    // Kiem tra chuoi co phai so nguyen duong hay khong
    static bool laSoNguyenDuong(const std::string& s) {
        std::string str = catKhoangTrang(s);
        if (str.empty()) {
            return false;
        }
        // Chi cho phep cac chu so tu 0 den 9
        for (int i = 0; i < (int)str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }

        // Kiem tra gia tri lon hon 0 
        try {
            long long so = std::stoll(str);
            if (so > 0) {
                return true;
            }
            return false;
        }
        catch (...) {
            return false;
        }
    }

    // Kiem tra chuoi co phai so thuc khong am hay khong
    static bool laSoThucKhongAm(const std::string& s) {
        std::string str = catKhoangTrang(s);
        if (str.empty()) {
            return false;
        }
        std::stringstream ss(str);
        double so;
        char kyTu;
        // Kiem tra co doc duoc mot so thuc hay khong
        if (!(ss >> so)) {
            return false;
        }
        // Khong chap nhan ky tu thua sau gia tri so
        if (ss >> kyTu) {
            return false;
        }
        // Khong chap nhan so am
        if ( so < 0) {
            return false;
        }
        return true;
    }

    // Kiem tra ma ID chi gom chu cai, chu so, dau gach ngang va gach duoi
    static bool kiemTraMaHopLe(const std::string& ma) {
        std::string str = catKhoangTrang(ma);
        if (str.empty()) {
            return false;
        }

        bool coChuHoacSo = false;

        for (int i = 0; i < (int)str.length(); i++) {
            char c = str[i];

            // Kiem tra chu cai
            if ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z')) {
                coChuHoacSo = true;
            }
            // Kiem tra chu so
            else if (c >= '0' && c <= '9') {
                coChuHoacSo = true;
            }
            // Cho phep dau gach ngang va gach duoi
            else if (c == '-' || c == '_') {}
            else {
                return false;
            }
        }

        // Ma phai co it nhat mot chu cai hoac chu so
        if (!coChuHoacSo) {
            return false;
        }
        return true;
    }

    // Kiem tra so serial chi gom chu, so, dau gach ngang va gach duoi
    static bool kiemTraSoSerial(const std::string& serial) {
        std::string str = catKhoangTrang(serial);

        if (str.empty()) {
            return false;
        }

        bool coChuHoacSo = false;

        for (int i = 0; i < (int)str.length(); i++) {
            char c = str[i];

            if ((c >= '0' && c <= '9') ||
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z')) {
                coChuHoacSo = true;
            }
            else if (c == '-' || c == '_') {}
            else {
                return false;
            }
        }

        // So serial phai co it nhat mot chu cai hoac chu so
        if (!coChuHoacSo) {
            return false;
        }
        return true;
    }

    // Kiem tra so dien thoai gom 10 chu so va bat dau bang 0
    static bool kiemTraSoDienThoai(const std::string& sdt) {
        std::string str = catKhoangTrang(sdt);

        if (str.length() != 10) {
            return false;
        }
        if (str[0] != '0') {
            return false;
        }
        for (int i = 0; i < (int)str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
        return true;
    }

    // Kiem tra goc nam trong khoang cho phep
    static bool kiemTraGocHopLe(double goc, double gocMin, double gocMax) {
        // Kiem tra cac gia tri co hop le hay khong
        if (!std::isfinite(goc) ||
            !std::isfinite(gocMin) ||
            !std::isfinite(gocMax)) {
            return false;
        }

        // Gioi han nho nhat khong duoc lon hon gioi han lon nhat
        if (gocMin > gocMax) {
            return false;
        }
        if (goc < gocMin || goc > gocMax) {
            return false;
        }
        return true;
    }

    // Kiem tra ngay hop le thong qua lop Date
    static bool kiemTraNgayHopLe(const std::string& strNgay) {
        std::string ngay = catKhoangTrang(strNgay);

        if (ngay.empty()) {
            return false;
        }

        Date dt;

        if (dt.napTuChuoi(ngay)) {
            return true;
        }
        return false;
    }
};

#endif