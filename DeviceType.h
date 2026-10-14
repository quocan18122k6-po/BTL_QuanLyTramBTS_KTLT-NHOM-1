//Chỉ chứa khai báo lớp thực thể và lớp quản lý CRUD

#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H

#include <string>
#include "Entity.h"
#include "Repository.h"

// Lop thuc the loai thiet bi
class DeviceType : public Entity {
private:
    std::string tenLoai;
    std::string chucNang;
    std::string nhaSanXuat;

public:
    DeviceType();
    DeviceType(const std::string& maLoai,
               const std::string& tenLoai,
               const std::string& chucNang,
               const std::string& nhaSanXuat);

    // Getter
    std::string getTenLoai() const;
    std::string getChucNang() const;
    std::string getNhaSanXuat() const;

    // Setter
    bool setTenLoai(const std::string& tenMoi);
    bool setChucNang(const std::string& chucNangMoi);
    bool setNhaSanXuat(const std::string& nsxMoi);

    // In bang
    static void inTieuDeBang();
    static void inDuongKeBang();

    // Cac ham ke thua tu Entity
    void input() override;
    void display() const override;
    void displayRow() const override;
    std::string toString() const override;
    void fromString(const std::string& line) override;
    void updateInfo() override;

    // Ham ho tro tieng Viet
    std::string xuatRaChuoi() const {
        return toString();
    }

    void napTuChuoi(const std::string& line) {
        fromString(line);
    }
};

// Lop quan ly loai thiet bi
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