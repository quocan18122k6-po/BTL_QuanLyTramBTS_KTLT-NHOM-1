#ifndef PROVINCE_MODULE_H
#define PROVINCE_MODULE_H

#include "Entity.h"
#include "Repository.h"

#include <functional>
#include <iosfwd>
#include <string>

// Luu thong tin mot khu vuc/tinh.
class Province : public Entity {
private:
    std::string tenTinh;
    std::string diaHinh;
    std::string donViQuanLy;

public:
    Province();
    Province(const std::string& maKhuVuc,
             const std::string& tenTinh,
             const std::string& diaHinh,
             const std::string& donViQuanLy);

    std::string getTenTinh() const;
    std::string getDiaHinh() const;
    std::string getDonViQuanLy() const;

    void setTenTinh(const std::string& value);
    void setDiaHinh(const std::string& value);
    void setDonViQuanLy(const std::string& value);

    void input() override;
    void display() const override;
    void displayRow() const override;
    std::string toString() const override;
    void fromString(const std::string& line) override;
    void updateInfo() override;

    // Tuong thich voi Repository.h dang doc/ghi bang toan tu >> va <<.
    friend std::ostream& operator<<(std::ostream& out, const Province& province);
    friend std::istream& operator>>(std::istream& in, Province& province);
};

// Chuc nang quan ly khu vuc/tinh (CRUD, tim kiem va sap xep).
// Lop nay duoc khai bao cung file voi Province de giam so luong file module.
class ProvinceUseCase {
private:
    Repository<Province>& repository;
    std::function<bool(const std::string&)> isReferenced;

    void addProvince();
    void showProvinces() const;
    void searchProvince() const;
    void sortProvinces();
    void updateProvince();
    void deleteProvince();

public:
    explicit ProvinceUseCase(
        Repository<Province>& repository,
        std::function<bool(const std::string&)> isReferenced =
            std::function<bool(const std::string&)>()
    );

    void run();
};

#endif
