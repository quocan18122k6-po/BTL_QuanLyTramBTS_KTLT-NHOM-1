#ifndef DATE_H
#define DATE_H

#include <bits/stdc++.h>

class Date {
    private:
        int ngay;
        int thang;
        int nam;
    
    public:
        Date(){
            ngay = 1;
            thang = 1;
            nam = 1901;
        }
        static bool laNamNhuan(int nam){
            if((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)){
                return true;
            }
            else{
                return false;
            }
        }
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
        std::string xuatRaChuoi() const {
            return (ngay < 10 ? "0" : "") + std::to_string(ngay) + "/" + (thang < 10 ? "0" : "") + std::to_string(thang) + "/" + std::to_string(nam);
        }
        int getNgay() const { return ngay; }
        int getThang() const { return thang; }
        int getNam() const { return nam; }
        bool setNgay(int ngayMoi) {
        if (kiemTraHopLe(ngayMoi, this->thang, this->nam)) {
            this->ngay = ngayMoi;
            return true;
        }
        return false;
    }

    bool setThang(int thangMoi) {
        if (kiemTraHopLe(this->ngay, thangMoi, this->nam)) {
            this->thang = thangMoi;
            return true;
        }
        return false;
    }

    bool setNam(int namMoi) {
        if (kiemTraHopLe(this->ngay, this->thang, namMoi)) {
            this->nam = namMoi;
            return true;
        }
        return false;
    }

    bool datNgayThangNam(int ngayMoi, int thangMoi, int namMoi) {
        if (!kiemTraHopLe(ngayMoi, thangMoi, namMoi)) {
            return false;
        }
        this->ngay = ngayMoi;
        this->thang = thangMoi;
        this->nam = namMoi;
        return true;
    }
    // so sanh moc thoi gian
    bool operator==(const Date& doiTuongKhac) const{
        return (this->ngay == doiTuongKhac.ngay) && (this->thang == doiTuongKhac.thang) && (this->nam == doiTuongKhac.nam);
    }
    bool operator!=(const Date& doiTuongKhac) const {
        return !(*this == doiTuongKhac);
    }
    bool operator<(const Date& doiTuongKhac) const {
        if (this->nam != doiTuongKhac.nam) return this->nam < doiTuongKhac.nam;
        if (this->thang != doiTuongKhac.thang) return this->thang < doiTuongKhac.thang;
        return this->ngay < doiTuongKhac.ngay;
    }
    bool operator<=(const Date& doiTuongKhac) const {
        return (*this < doiTuongKhac) || (*this == doiTuongKhac);
    }
    bool operator>(const Date& doiTuongKhac) const {
        return !(*this <= doiTuongKhac);
    }
    bool operator>=(const Date& doiTuongKhac) const {
        return !(*this < doiTuongKhac);
    }
    // Nap chong toan tu nhap/xuat luong
    friend std::ostream& operator<<(std::ostream& luongXuat, const Date& dt) {
        luongXuat << dt.toString();
        return luongXuat;
    }

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