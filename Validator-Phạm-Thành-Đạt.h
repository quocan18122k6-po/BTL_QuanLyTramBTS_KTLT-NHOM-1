#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <sstream>
#include <cmath>
#include "Date.h"

class Validator {
public:
    // Cat khoang trang dau va cuoi chuoi
    static std::string catKhoangTrang(const std::string& s) {
        int dau = 0;
        int cuoi = (int)s.length() - 1;

        while (dau < s.length() &&
              (s[dau] == ' ' || s[dau] == '\t' ||
               s[dau] == '\n' || s[dau] == '\r')) {
            dau++;
        }

        while (cuoi >= dau &&
              (s[cuoi] == ' ' || s[cuoi] == '\t' ||
               s[cuoi] == '\n' || s[cuoi] == '\r')) {
            cuoi--;
        }

        if (dau > cuoi) return "";

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

    // Kiem tra do dai toi da
    static bool kiemTraDoDai(const std::string& s, size_t maxLen) {
        std::string str = catKhoangTrang(s);
        return str.length() <= maxLen;
    }

    // Kiem tra so nguyen duong
    static bool laSoNguyenDuong(const std::string& s) {
        std::string str = catKhoangTrang(s);

        if (str.empty()) return false;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }

        try {
            long long so = std::stoll(str);
            return so > 0;
        }
        catch (...) {
            return false;
        }
    }

    // Kiem tra so thuc khong am
    static bool laSoThucKhongAm(const std::string& s) {
        std::string str = catKhoangTrang(s);

        if (str.empty()) return false;

        std::stringstream ss(str);
        double so;
        char kyTu;

        if (!(ss >> so)) return false;

        if (ss >> kyTu) return false;

        return std::isfinite(so) && so >= 0;
    }

    // Kiem tra ma ID
    static bool kiemTraMaHopLe(const std::string& ma) {
        std::string str = catKhoangTrang(ma);

        if (str.empty()) return false;

        if (chuaKyTuPhanCach(str)) return false;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ' || str[i] == '\t' ||
                str[i] == '\n' || str[i] == '\r') {
                return false;
            }
        }

        return true;
    }

    // Kiem tra serial chi gom chu, so, dau gach ngang va gach duoi
    static bool kiemTraSoSerial(const std::string& serial) {
        std::string str = catKhoangTrang(serial);

        if (str.empty()) return false;

        if (chuaKyTuPhanCach(str)) return false;

        for (int i = 0; i < str.length(); i++) {
            char c = str[i];

            if (!((c >= '0' && c <= '9') ||
                  (c >= 'a' && c <= 'z') ||
                  (c >= 'A' && c <= 'Z') ||
                  c == '-' || c == '_')) {
                return false;
            }
        }

        return true;
    }

    // Kiem tra so dien thoai gom 10 so va bat dau bang 0
    static bool kiemTraSoDienThoai(const std::string& sdt) {
        std::string str = catKhoangTrang(sdt);

        if (str.length() != 10) return false;

        if (str[0] != '0') return false;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }

        return true;
    }

    // Kiem tra goc co nam trong khoang cho phep hay khong
    static bool kiemTraGocHopLe(double goc, double gocMin, double gocMax) {
        return goc >= gocMin && goc <= gocMax;
    }

    // Kiem tra ngay hop le bang lop Date
    static bool kiemTraNgayHopLe(const std::string& strNgay) {
        Date dt;
        return dt.napTuChuoi(catKhoangTrang(strNgay));
    }
};

#endif