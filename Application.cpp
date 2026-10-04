
#include "Application.h"
#include "InputHelper.h"
#include <iostream>
#include <string>

void Application::menu() {
    std::cout << "\n======================================================\n";
    std::cout << "      HE THONG QUAN LY TRAM PHAT SONG BTS VIEN THONG   \n";
    std::cout << "======================================================\n";
    std::cout << "  1. Quan ly Khu vuc & Tram BTS\n";
    std::cout << "  2. Quan ly Thiet bi phat song\n";
    std::cout << "  3. Quan ly Ky thuat vien & Bao tri\n";
    std::cout << "  4. Quan ly Cau hinh Anten & Su co\n";
    std::cout << "  0. Thoat chuong trinh\n";
    std::cout << "======================================================\n";
}

void Application::tramVaKhuVuc() {
    std::cout << "\n-> Dang mo chuc nang Quan ly Tram & Khu vuc...\n";
}

void Application::thietBi() {
    std::cout << "\n-> Dang mo chuc nang Quan ly Thiet bi...\n";
}

void Application::baoTri() {
    std::cout << "\n-> Dang mo chuc nang Quan ly Bao tri...\n";
}

void Application::suCoVaAnten() {
    std::cout << "\n-> Dang mo chuc nang Quan ly Su co & Anten...\n";
}

void Application::run() {
    int choice = -1;

    do {
        try { //Bao boc toan bo luong dieu khien va nhap lieu cua ung dung.
            menu();
            choice = InputHelper::getInt("Nhap lua chon cua ban (0 - 4): ", 0, 4);

            switch (choice) {
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
                std::cout << "\nTam biet! Chuong trinh dang dong...\n";
                break;
            default:
                std::cout << "\nLua chon khong hop le!\n";
                break;
            }
        }
        catch (const std::exception &e) { //Chot chan cac ngoai le chuan
            std::cout << "\n[LOI HE THONG]: " << e.what() << "\n"; //khong bi vang man hinh
        }
    } while (choice != 0);
}