#pragma once

#include <string>

#include "Repository.h"
#include "Province.h"
#include "BtsStation.h"
#include "DeviceType.h"
#include "InstalledDevice.h"
#include "Technician.h"
#include "MaintenanceTicket.h"
#include "antenna config.h"
#include "StationIncident.h"

class Application {
private:
    // Kho du lieu dung chung trong ung dung.
    Repository<Province> repoTinh;
    Repository<BtsStation> repoTram;
    Repository<DeviceType> repoLoai;
    Repository<InstalledDevice> repoThietBi;
    Repository<Technician> repoKTV;
    Repository<MaintenanceTicket> repoBaoTri;
    Repository<AntennaConfig> repoAnten;
    Repository<StationIncident> repoSuCo;

    void menu();

    // Menu cua tung nhom chuc nang.
    void tramVaKhuVuc();
    void thietBi();
    void baoTri();
    void suCoVaAnten();

    // Chua co menu Province rieng nen xu ly tai day.
    void quanLyKhuVuc();

    // Kiem tra truoc khi xoa.
    bool tinhDangDuocSuDung(const std::string& maTinh) const;
    bool tramDangDuocSuDung(const std::string& maTram);

public:
    // Tao thu muc data va nap cac kho du lieu.
    Application();

    // Chay menu chinh.
    void run();
};