#ifndef INSTALLED_DEVICE_H
#define INSTALLED_DEVICE_H

#include <string>
#include "Entity.h"
#include "Repository.h"
#include "Date.h"

// Lop thuc the thiet bi lap dat
class InstalledDevice : public Entity {
private:
    std::string soSerial;
    std::string maLoai;
    std::string maTram;
    Date ngayLapRap;
    std::string trangThai;

public:
    InstalledDevice();
    InstalledDevice(const std::string& maThietBi,
                    const std::string& soSerial,
                    const std::string& maLoai,
                    const std::string& maTram,
                    const Date& ngayLapRap,
                    const std::string& trangThai);

    // Getter
    std::string getSoSerial() const;
    std::string getMaLoai() const;
    std::string getMaTram() const;
    Date getNgayLapRap() const;
    std::string getTrangThai() const;

    // Setter
    bool setSoSerial(const std::string& serialMoi);
    bool setMaLoai(const std::string& maLoaiMoi);
    bool setMaTram(const std::string& maTramMoi);
    bool setNgayLapRap(const Date& ngayMoi);
    bool setNgayLapRap(const std::string& chuoiNgay);
    bool setTrangThai(const std::string& trangThaiMoi);

    // In bang danh sach
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

// Lop quan ly CRUD thiet bi lap dat
class InstalledDeviceManager {
private:
    Repository<InstalledDevice> repo;

    void hienThiMenu() const;
    void themMoi();
    void xemDanhSach();
    void timKiem();
    void capNhat();
    void xoa();

public:
    InstalledDeviceManager();
    void chayChuongTrinh();
};

#endif