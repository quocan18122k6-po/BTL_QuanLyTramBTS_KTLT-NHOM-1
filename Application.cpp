#include "Application.h"
#include "InputHelper.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

namespace {
    // Thu muc data nam trong thu muc chay chuong trinh.
    std::string duongDanData(const std::string& tenFile) {
        return "data/" + tenFile;
    }
    void thongBaoKetQua(bool thanhCong) {
        if (thanhCong) {
            std::cout << "Thanh cong! Du lieu da duoc luu.\n";
        }
        else {
            std::cout
                << "Thao tac that bai. Kiem tra ma va kha nang ghi file.\n";
        }
    }

    bool xacNhanXoa() {
        while (true) {
            std::string traLoi =
                InputHelper::getString("Xac nhan xoa (y/n): ");

            if (traLoi == "y" || traLoi == "Y") {
                return true;
            }

            if (traLoi == "n" || traLoi == "N") {
                return false;
            }

            std::cout << "Chi nhap y hoac n.\n";
        }
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

// ==================== MENU CHINH ====================

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

            int luaChon =
                InputHelper::getInt("Nhap lua chon: ", 0, 4);

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

// ==================== KHU VUC & TRAM ====================

void Application::tramVaKhuVuc() {
    while (std::cin) {
        std::cout
            << "\n========== KHU VUC & TRAM BTS ==========\n"
            << "  1. Quan ly khu vuc/tinh\n"
            << "  2. Quan ly tram BTS\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =
            InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1:
            quanLyKhuVuc();
            break;

        case 2: {
            BtsStationUseCase quanLyTram(
                repoTram,
                repoTinh,
                [this](const std::string& maTram) {
                    return tramDangDuocSuDung(maTram);
                }
            );

            quanLyTram.run();
            break;
        }

        case 0:
            return;
        }
    }
}

bool Application::tinhDangDuocSuDung(
    const std::string& maTinh
) const {
    for (const auto& tram : repoTram.getAll()) {
        if (tram.getMaKhuVuc() == maTinh) {
            return true;
        }
    }

    return false;
}

bool Application::tramDangDuocSuDung(
    const std::string& maTram
) {
    // InstalledDeviceManager hien giu Repository rieng.
    // Nap lai de kiem tra danh sach thiet bi moi nhat.
    repoThietBi.loadFromFile();

    for (const auto& thietBi : repoThietBi.getAll()) {
        if (thietBi.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& anten : repoAnten.getAll()) {
        if (anten.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& phieu : repoBaoTri.getAll()) {
        if (phieu.getMaTram() == maTram) {
            return true;
        }
    }

    for (const auto& suCo : repoSuCo.getAll()) {
        if (suCo.getMaTram() == maTram) {
            return true;
        }
    }

    return false;
}

void Application::quanLyKhuVuc() {
    while (std::cin) {
        try {
            std::cout
                << "\n========== QUAN LY KHU VUC/TINH ==========\n"
                << "  1. Them moi\n"
                << "  2. Xem danh sach\n"
                << "  3. Tim theo ma / xem chi tiet\n"
                << "  4. Cap nhat\n"
                << "  5. Xoa\n"
                << "  0. Quay lai\n";

            int luaChon =
                InputHelper::getInt("Nhap lua chon: ", 0, 5);

            if (luaChon == 0) {
                return;
            }

            if (luaChon == 1) {
                Province tinhMoi;
                tinhMoi.input();

                if (repoTinh.exists(tinhMoi.getId())) {
                    std::cout << "Ma khu vuc/tinh da ton tai.\n";
                }
                else {
                    thongBaoKetQua(repoTinh.add(tinhMoi));
                }

                continue;
            }

            if (luaChon == 2) {
                const auto& danhSach = repoTinh.getAll();

                if (danhSach.empty()) {
                    std::cout << "Chua co du lieu khu vuc/tinh.\n";
                    continue;
                }

                // Do rong cot tu tang theo noi dung.
                std::size_t rongMa = 10;
                std::size_t rongTen = 20;
                std::size_t rongDiaHinh = 20;
                std::size_t rongDonVi = 20;

                for (const auto& tinh : danhSach) {
                    if (tinh.getId().size() > rongMa)
                        rongMa = tinh.getId().size();

                    if (tinh.getTenTinh().size() > rongTen)
                        rongTen = tinh.getTenTinh().size();

                    if (tinh.getDiaHinh().size() > rongDiaHinh)
                        rongDiaHinh = tinh.getDiaHinh().size();

                    if (tinh.getDonViQuanLy().size() > rongDonVi)
                        rongDonVi = tinh.getDonViQuanLy().size();
                }

                std::cout << std::left
                    << std::setw(static_cast<int>(rongMa))
                    << "Ma tinh" << " | "
                    << std::setw(static_cast<int>(rongTen))
                    << "Ten tinh" << " | "
                    << std::setw(static_cast<int>(rongDiaHinh))
                    << "Dia hinh" << " | "
                    << std::setw(static_cast<int>(rongDonVi))
                    << "Don vi quan ly" << '\n';

                for (const auto& tinh : danhSach) {
                    std::cout
                        << std::setw(static_cast<int>(rongMa))
                        << tinh.getId() << " | "
                        << std::setw(static_cast<int>(rongTen))
                        << tinh.getTenTinh() << " | "
                        << std::setw(static_cast<int>(rongDiaHinh))
                        << tinh.getDiaHinh() << " | "
                        << std::setw(static_cast<int>(rongDonVi))
                        << tinh.getDonViQuanLy() << '\n';
                }

                std::cout << "Tong so: " << danhSach.size() << '\n';
                continue;
            }

            std::string ma =
                InputHelper::getString("Nhap ma khu vuc/tinh: ");

            Province* tinh = repoTinh.find(ma);

            if (tinh == nullptr) {
                std::cout << "Khong tim thay khu vuc/tinh.\n";
                continue;
            }

            tinh->display();

            switch (luaChon) {
            case 3:
                // Da hien thi chi tiet o tren.
                break;

            case 4: {
                // Sua ban sao, chi cap nhat kho khi hop le.
                Province banSao = *tinh;
                banSao.updateInfo();

                if (banSao.getId() != ma) {
                    std::cout << "Khong duoc thay doi ma.\n";
                    break;
                }

                thongBaoKetQua(repoTinh.update(ma, banSao));
                break;
            }

            case 5:
                if (tinhDangDuocSuDung(ma)) {
                    std::cout
                        << "Khong the xoa: khu vuc/tinh dang co tram BTS.\n";
                    break;
                }

                if (xacNhanXoa()) {
                    thongBaoKetQua(repoTinh.remove(ma));
                }
                else {
                    std::cout << "Da huy thao tac xoa.\n";
                }
                break;
            }
        }
        catch (const std::exception& e) {
            if (!std::cin) {
                throw;
            }

            std::cout << "[LOI]: " << e.what() << '\n';
        }
    }
}

// ==================== THIET BI ====================

void Application::thietBi() {
    while (std::cin) {
        std::cout
            << "\n========== QUAN LY THIET BI ==========\n"
            << "  1. Quan ly loai thiet bi\n"
            << "  2. Quan ly thiet bi lap dat\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =
            InputHelper::getInt("Nhap lua chon: ", 0, 2);

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

            InstalledDeviceManager quanLyThietBi(
                repoLoai,
                repoTram
            );

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

// ==================== KY THUAT VIEN & BAO TRI ====================

void Application::baoTri() {
    while (std::cin) {
        std::cout
            << "\n========== KY THUAT VIEN & BAO TRI ==========\n"
            << "  1. Quan ly ky thuat vien\n"
            << "  2. Quan ly phieu bao tri\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =
            InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1:
            // Truyen phieu bao tri de kiem tra khi xoa KTV.
            quanLyTechnician(repoKTV, &repoBaoTri);
            break;

        case 2:
            quanLyMaintenanceTicket(
                repoBaoTri,
                repoTram,
                repoKTV
            );
            break;

        case 0:
            return;
        }
    }
}

// ==================== ANTEN & SU CO ====================

void Application::suCoVaAnten() {
    while (std::cin) {
        std::cout
            << "\n========== ANTEN & SU CO ==========\n"
            << "  1. Quan ly cau hinh anten\n"
            << "  2. Quan ly nhat ky su co\n"
            << "  0. Quay lai menu chinh\n";

        int luaChon =
            InputHelper::getInt("Nhap lua chon: ", 0, 2);

        switch (luaChon) {
        case 1:
            quanLyAnten(repoAnten, repoTram);
            break;

        case 2:
            quanLySuCo(repoSuCo, repoTram);
            break;

        case 0:
            return;
        }
    }
}
