#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <bits/stdc++.h>
class Validator {
public:
    // 1. Cat bo khoang trang thua (dau cach, tab, xuong dong) o hai dau chuoi
    static std::string catKhoangTrang(const std::string& chuoiGoc) {
        size_t viTriDau = chuoiGoc.find_first_not_of(" \t\n\r");
        if (viTriDau == std::string::npos) {
            return "";
        }
        size_t viTriCuoi = chuoiGoc.find_last_not_of(" \t\n\r");
        return chuoiGoc.substr(viTriDau, viTriCuoi - viTriDau + 1);
    }

    // 2. Kiem tra chuoi co bi bo trong hoac chi chua toan khoang trang
    static bool laChuoiRong(const std::string& chuoiKiemTra) {
        return catKhoangTrang(chuoiKiemTra).empty();
    }

    // 3. Kiem tra chuoi co chua ky tu phan tach file khong (chong loi hong file .txt)
    static bool chuaKyTuPhanCach(const std::string& chuoiKiemTra, char kyTuPhanCach = '|') {
        return chuoiKiemTra.find(kyTuPhanCach) != std::string::npos;
    }

    // 4. Kiem tra do dai toi da cua chuoi ky tu
    static bool kiemTraDoDai(const std::string& chuoiKiemTra, size_t doDaiToiDa) {
        return catKhoangTrang(chuoiKiemTra).length() <= doDaiToiDa;
    }

    // 5. Kiem tra so nguyen duong (> 0)
    static bool laSoNguyenDuong(const std::string& chuoiKiemTra) {
        std::string chuoiXuLy = catKhoangTrang(chuoiKiemTra);
        if (chuoiXuLy.empty()) {
            return false;
        }
        for (char kiTu : chuoiXuLy) {
            if (!std::isdigit(static_cast<unsigned char>(kiTu))) {
                return false;
            }
        }
        try {
            long long giaTri = std::stoll(chuoiXuLy);
            return giaTri > 0;
        } catch (...) {
            return false;
        }
    }

    // 6. Kiem tra so thuc khong am (double >= 0.0)
    static bool laSoThucKhongAm(const std::string& chuoiKiemTra) {
        std::string chuoiXuLy = catKhoangTrang(chuoiKiemTra);
        if (chuoiXuLy.empty()) {
            return false;
        }
        std::stringstream ss(chuoiXuLy);
        double giaTri;
        char kiTuDu;
        if ((ss >> giaTri) && !(ss >> kiTuDu)) {
            return giaTri >= 0.0;
        }
        return false;
    }

    // 7. Kiem tra ma dinh danh / khoa ngoai hop le (khong rong, khong co dau cach, khong chua '|')
    static bool kiemTraMaHopLe(const std::string& maDinhDanh) {
        std::string chuoiXuLy = catKhoangTrang(maDinhDanh);
        if (chuoiXuLy.empty() || chuaKyTuPhanCach(chuoiXuLy)) {
            return false;
        }
        for (char kiTu : chuoiXuLy) {
            if (std::isspace(static_cast<unsigned char>(kiTu))) {
                return false;
            }
        }
        return true;
    }

    // 8. Kiem tra so Serial cua thiet bi (chi chua chu cai, chu so, dau '-' hoac '_')
    static bool kiemTraSoSerial(const std::string& soSerial) {
        std::string chuoiXuLy = catKhoangTrang(soSerial);
        if (chuoiXuLy.empty() || chuaKyTuPhanCach(chuoiXuLy)) {
            return false;
        }
        for (char kiTu : chuoiXuLy) {
            if (!std::isalnum(static_cast<unsigned char>(kiTu)) && kiTu != '-' && kiTu != '_') {
                return false;
            }
        }
        return true;
    }

    // 9. Kiem tra so dien thoai di dong (dung cho Technician: 10 chu so, bat dau bang so '0')
    static bool kiemTraSoDienThoai(const std::string& soDienThoai) {
        std::string chuoiXuLy = catKhoangTrang(soDienThoai);
        if (chuoiXuLy.length() != 10 || chuoiXuLy[0] != '0') {
            return false;
        }
        for (char kiTu : chuoiXuLy) {
            if (!std::isdigit(static_cast<unsigned char>(kiTu))) {
                return false;
            }
        }
        return true;
    }

    // 10. Kiem tra goc phat hop le (dung cho gocNgangTilt: 0-90, huongPhatAzimuth: 0-360)
    static bool kiemTraGocHopLe(double giaTriGoc, double gocNhoNhat, double gocLonNhat) {
        return (giaTriGoc >= gocNhoNhat && giaTriGoc <= gocLonNhat);
    }

    // 11. Kiem tra chuoi ngay thang dd/MM/yyyy (tich hop truc tiep qua ham napTuChuoi cua Date)
    static bool kiemTraNgayHopLe(const std::string& chuoiNgay) {
        Date doiTuongNgay;
        return doiTuongNgay.napTuChuoi(catKhoangTrang(chuoiNgay));
    }
};

#endif // VALIDATOR_H