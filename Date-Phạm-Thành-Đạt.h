#ifndef DATE_H
#define DATE_H

#include <bits/stdc++.h>

class Date {
    private:
        int ngay;
        int thang;
        int nam;
    
    public:
        // Khoi tao ngay mac dinh la 01/01/1901.
        Date(){
            ngay = 1;
            thang = 1;
            nam = 1901;
        }

        // Kiem tra mot nam co phai nam nhuan theo lich Gregory hay khong.
        static bool laNamNhuan(int nam){
            if((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)){
                return true;
            }
            else{
                return false;
            }
        }

        // Kiem tra ngay, thang, nam co hop le trong pham vi nam 1900-2100 hay khong.
        static bool kiemTraHopLe(int ngay, int thang, int nam){
            if(nam < 1900 || nam > 2100){
                return false;
            }
            if(thang < 1 || thang > 12){
                return false;
            }
            int soNgayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(laNamNhuan(nam) && thang == 2){
                soNgayTrongThang[1] = 29;
            }
            if(ngay < 1 || ngay > soNgayTrongThang[thang - 1]){
                return false;
            }
            return true;
        }

        // Khoi tao ngay tu cac gia tri; dung 01/01/1901 neu du lieu khong hop le.
        Date(int ngay, int thang, int nam){
            if(kiemTraHopLe(ngay, thang, nam)){
                this->ngay = ngay;
                this->thang = thang;
                this->nam = nam;
            }
            else{
                this->ngay = 1;
                this->thang = 1;
                this->nam = 1901;
            }
        }

        // Doc ngay tu chuoi dang ngay/thang/nam va chi cap nhat neu chuoi hop le.
        bool napTuChuoi(const std::string& str){
            std::stringstream ss(str);
            int ngay, thang, nam;
            char kiTu1, kiTu2;
            if(ss >> ngay >> kiTu1 >> thang >> kiTu2 >> nam){
                std::string duLieuThua;
                if (ss >> duLieuThua) return false;
                if((kiTu1 == '/' || kiTu1 =='-') && (kiTu2 == '/' || kiTu2 =='-')){
                    if(kiemTraHopLe(ngay, thang, nam)){
                        this->ngay = ngay;
                        this->thang = thang;
                        this->nam = nam;
                        return true;
                    }
                }
            }
            return false;
        }

        // Chuyen ngay hien tai thanh chuoi co dang dd/MM/yyyy.
        std::string xuatRaChuoi() const {
            return (ngay < 10 ? "0" : "") + std::to_string(ngay) + "/" + (thang < 10 ? "0" : "") + std::to_string(thang) + "/" + std::to_string(nam);
        }

        // Tra ve ngay trong thang.
        int getNgay() const { return ngay; }

        // Tra ve thang trong nam.
        int getThang() const { return thang; }

        // Tra ve nam.
        int getNam() const { return nam; }

        // Cap nhat ngay neu ngay moi hop le voi thang va nam hien tai.
        bool setNgay(int ngayMoi) {
        if (kiemTraHopLe(ngayMoi, this->thang, this->nam)) {
            this->ngay = ngayMoi;
            return true;
        }
        return false;
    }

    // Cap nhat thang neu ngay hien tai van hop le trong thang moi.
    bool setThang(int thangMoi) {
        if (kiemTraHopLe(this->ngay, thangMoi, this->nam)) {
            this->thang = thangMoi;
            return true;
        }
        return false;
    }

    // Cap nhat nam neu ngay va thang hien tai van hop le trong nam moi.
    bool setNam(int namMoi) {
        if (kiemTraHopLe(this->ngay, this->thang, namMoi)) {
            this->nam = namMoi;
            return true;
        }
        return false;
    }

    // Cap nhat dong thoi ngay, thang, nam neu bo gia tri moi hop le.
    bool datNgayThangNam(int ngayMoi, int thangMoi, int namMoi) {
        if (!kiemTraHopLe(ngayMoi, thangMoi, namMoi)) {
            return false;
        }
        this->ngay = ngayMoi;
        this->thang = thangMoi;
        this->nam = namMoi;
        return true;
    }

    // Kiem tra hai doi tuong Date co cung ngay, thang va nam hay khong.
    bool operator==(const Date& doiTuongKhac) const{
        return (this->ngay == doiTuongKhac.ngay) && (this->thang == doiTuongKhac.thang) && (this->nam == doiTuongKhac.nam);
    }

    // Kiem tra hai doi tuong Date khong bang nhau.
    bool operator!=(const Date& doiTuongKhac) const {
        return !(*this == doiTuongKhac);
    }

    // Kiem tra ngay hien tai som hon ngay cua doi tuong khac hay khong.
    bool operator<(const Date& doiTuongKhac) const {
        if (this->nam != doiTuongKhac.nam) return this->nam < doiTuongKhac.nam;
        if (this->thang != doiTuongKhac.thang) return this->thang < doiTuongKhac.thang;
        return this->ngay < doiTuongKhac.ngay;
    }

    // Kiem tra ngay hien tai som hon hoac bang ngay cua doi tuong khac.
    bool operator<=(const Date& doiTuongKhac) const {
        return (*this < doiTuongKhac) || (*this == doiTuongKhac);
    }

    // Kiem tra ngay hien tai muon hon ngay cua doi tuong khac.
    bool operator>(const Date& doiTuongKhac) const {
        return !(*this <= doiTuongKhac);
    }

    // Kiem tra ngay hien tai muon hon hoac bang ngay cua doi tuong khac.
    bool operator>=(const Date& doiTuongKhac) const {
        return !(*this < doiTuongKhac);
    }

    // Ghi doi tuong Date ra luong xuat.
    friend std::ostream& operator<<(std::ostream& luongXuat, const Date& dt) {
        luongXuat << dt.toString();
        return luongXuat;
    }

    // Doc chuoi ngay tu luong nhap va bao loi luong neu chuoi khong hop le.
    friend std::istream& operator>>(std::istream& luongNhap, Date& dt) {
        std::string chuoiTam;
        if (luongNhap >> chuoiTam) {
            if (!dt.fromString(chuoiTam)) {
                luongNhap.setstate(std::ios::failbit);
            }
        }
        return luongNhap;
    }
};
#endif // DATE_H