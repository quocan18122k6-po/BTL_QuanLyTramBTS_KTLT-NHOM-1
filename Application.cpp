#include "Application.h"
#include "InputHelper.h"

#include <exception>
#include <iostream>
#include <string>

namespace {
    // Thu muc data nam trong thu muc chay chuong trinh.
    std::string duongDanData(const std::string& tenFile) {
        return "data/" + tenFile;
    }
}

Application::Application()
    : repoTinh(duongDanData("provinces.txt")),
    repoTram(duongDanData("stations.txt")),
    repoLoai(duongDanData("device_types.txt")),
    repoThietBi(duongDanData("devices.txt")),
    repoKTV(duongDanData("technicians.txt")),
    repoBaoTri(duongDanData("maintenances.txt")),
    repoAnten(duongDanData("antennas.txt")),
    repoSuCo(duongDanData("incidents.txt")) {
}

//MENU CHINH

void Application::menu() {
    std::cout
        << "\n=================================================\n"
        << "        HE THONG QUAN LY HA TANG TRAM BTS\n"
        << "=================================================\n"
        << "  1. Quan ly Khu vuc & Tram BTS\n"
        << "  2. Quan ly Thiet bi\n"
        << "  3. Quan ly Ky thuat vien & Bao tri\n"
        << "  4. Quan ly Anten & Su co\n"
        << "  0. Thoat chuong trinh\n"
        << "=================================================\n";
}

void Application::run() {
    while (std::cin) {
        try {
            menu();

            int luaChon = InputHelper::getInt("Nhap lua chon: ", 0, 4);

            switch (luaChon) {
            case 1:
                tramVaKhuVuc();
                break;

            case 2:
                thietBi();
                break;

            case 3:
                baoTri();
                break;

            case 4:
                suCoVaAnten();
                break;

            case 0:
                std::cout << "Tam biet!\n";
                return;
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[LOI]: " << e.what() << '\n';

            // Tranh lap lai menu khi luong nhap da dong.
            if (!std::cin) {
                return;
            }
        }
    }
}

// KHU VUC & TRAM

void Application::tramVaKhuVuc() {
    while (std::cin) {
        std::cout
            << "\n========== KHU VUC & TRAM BTS ==========\n"
            << "  1. Quan ly khu vuc/tinh\n"
            << "  2. Quan ly tram BTS\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1: {
            ProvinceUseCase quanLyTinh(repoTinh, repoTram);//tham chieu voi ma tram

            quanLyTinh.run();
            break;
        }

        case 2: {
            BtsStationUseCase quanLyTram(repoTram, repoTinh, repoThietBi,repoAnten, repoBaoTri, repoSuCo); //lam tham chieu cho cac usecase
            quanLyTram.run();
            break;
        }

        case 0:
            return;
        }
    }
}

// THIET BI

void Application::thietBi() {
    while (std::cin) {
        std::cout
            << "\n========== QUAN LY THIET BI ==========\n"
            << "  1. Quan ly loai thiet bi\n"
            << "  2. Quan ly thiet bi lap dat\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1: {
            DeviceTypeManager quanLyLoai;
            quanLyLoai.chayChuongTrinh();

            // Dong bo voi Repository rieng cua manager.
            repoLoai.loadFromFile();
            break;
        }

        case 2: {
            repoLoai.loadFromFile();

            InstalledDeviceManager quanLyThietBi( repoLoai,repoTram); // tham chieu voi ma tram
            quanLyThietBi.chayChuongTrinh();
            // Cap nhat du lieu dung de kiem tra xoa tram.
            repoThietBi.loadFromFile();
            break;
        }

        case 0:
            return;
        }
    }
}

// KY THUAT VIEN & BAO TRI

void Application::baoTri() {
    while (std::cin) {
        std::cout
            << "\n========== KY THUAT VIEN & BAO TRI ==========\n"
            << "  1. Quan ly ky thuat vien\n"
            << "  2. Quan ly phieu bao tri\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1:
            // Truyen phieu bao tri de kiem tra khi xoa KTV.
            quanLyTechnician(repoKTV, &repoBaoTri);
            break;

        case 2:
            quanLyMaintenanceTicket(repoBaoTri,repoTram,repoKTV); // truyen tham chieu voi ma tram và KTV
            break;

        case 0:
            return;
        }
    }
}

// ANTEN & SU CO

void Application::suCoVaAnten() {
    while (std::cin) {
        std::cout
            << "\n========== ANTEN & SU CO ==========\n"
            << "  1. Quan ly cau hinh anten\n"
            << "  2. Quan ly nhat ky su co\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1:
            quanLyAnten(repoAnten, repoTram); // tham chieu voi ma tram
            break;
        case 2:
            quanLySuCo(repoSuCo, repoTram); // tham chieu voi ma tram
            break;

        case 0:
            return;
        }
    }
}
