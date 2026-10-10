//Chỉ chứa khai báo lớp thực thể và lớp quản lý CRUD

#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H

#include <bits/stdc++.h>
// LOP THUC THE
class DeviceType : public Entity {
private:
    std::string tenLoai;
    std::string chucNang;
    std::string nhaSanXuat;

public:
    DeviceType();
    DeviceType(const std::string& maLoai, const std::string& tenLoai, 
               const std::string& chucNang, const std::string& nhaSanXuat);

    // Getters & Setters (Kiem tra du lieu hop le)
    std::string getTenLoai() const;
    std::string getChucNang() const;
    std::string getNhaSanXuat() const;

    bool setTenLoai(const std::string& tenMoi);
    bool setChucNang(const std::string& chucNangMoi);
    bool setNhaSanXuat(const std::string& nsxMoi);

    // Dinh dang bang Console
    static void inTieuDeBang();
    static void inDuongKeBang();

    // Ghi de du 6 phuong thuc thuan ao tu lop cha Entity
    void input() override;
    void display() const override;
    void displayRow() const override;
    std::string toString() const override;
    void fromString(const std::string& line) override;
    void updateInfo() override;

    // Phuong thuc alias phu tro tieng Viet neu can goi
    std::string xuatRaChuoi() const { return toString(); }
    void napTuChuoi(const std::string& line) { fromString(line); }
};

// LOP DIEU KHIEN USE CASE (CRUD)
class DeviceTypeManager {
private:
    Repository<DeviceType> repo;

    void hienThiMenu() const;
    void themMoi();
    void xemDanhSach();
    void timKiem();
    void capNhat();
    void xoa();

public:
    DeviceTypeManager();
    void chayChuongTrinh();
};

#endif