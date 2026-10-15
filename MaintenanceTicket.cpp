#include "MaintenanceTicket.h"
#include "InputHelper.h"
#include "Validator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

namespace {
	string toLowerStr(string s) {
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(tolower(c)); });
		return s;
	}
}

// Constructors
MaintenanceTicket::MaintenanceTicket() : Entity() {
	maTram = "";
	maKTV = "";
	ketQua = "";
}

MaintenanceTicket::MaintenanceTicket(const string& id, const string& maTram, const string& maKTV, const Date& ngayBaoTri, const string& ketQua) {
	if (!Validator::kiemTraMaHopLe(id)) {
		throw invalid_argument("Ma phieu bao tri khong hop le!");
	}
	setId(Validator::catKhoangTrang(id));
	setMaTram(maTram);
	setMaKTV(maKTV);
	setNgayBaoTri(ngayBaoTri);
	setKetQua(ketQua);
}

// Getters
string MaintenanceTicket::getMaTram() const { return maTram; }
string MaintenanceTicket::getMaKTV() const { return maKTV; }
Date MaintenanceTicket::getNgayBaoTri() const { return ngayBaoTri; }
string MaintenanceTicket::getKetQua() const { return ketQua; }

// Setters
void MaintenanceTicket::setMaTram(const string& maTramMoi) {
	string tram = Validator::catKhoangTrang(maTramMoi);
	if (!Validator::kiemTraMaHopLe(tram)) {
		throw invalid_argument("Ma tram BTS khong hop le!");
	}
	maTram = tram;
}

void MaintenanceTicket::setMaKTV(const string& maKTVMoi) {
	string ktv = Validator::catKhoangTrang(maKTVMoi);
	if (!Validator::kiemTraMaHopLe(ktv)) {
		throw invalid_argument("Ma KTV khong hop le!");
	}
	maKTV = ktv;
}

void MaintenanceTicket::setNgayBaoTri(const Date& ngayMoi) {
	ngayBaoTri = ngayMoi;
}

void MaintenanceTicket::setKetQua(const string& ketQuaMoi) {
	if (Validator::laChuoiRong(ketQuaMoi)) {
		throw invalid_argument("Ket qua bao tri khong duoc de trong!");
	}
	if (Validator::chuaKyTuPhanCach(ketQuaMoi)) {
		throw invalid_argument("Ket qua bao tri khong duoc chua ky tu '|'!");
	}
	ketQua = Validator::catKhoangTrang(ketQuaMoi);
}

// Input an toan
void MaintenanceTicket::input() {
	while (1) {
		try {
			string ma = InputHelper::getString("Nhap ma phieu (vi du BT001): ");
			if (!Validator::kiemTraMaHopLe(ma)) {
				throw invalid_argument("Ma phieu bao tri khong hop le!");
			}
			setId(Validator::catKhoangTrang(ma));
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string tram = InputHelper::getString("Nhap ma tram BTS: ");
			setMaTram(tram);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string ktv = InputHelper::getString("Nhap ma ky thuat vien: ");
			setMaKTV(ktv);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		string strNgay = InputHelper::getString("Nhap ngay bao tri (dd/MM/yyyy): ");
		Date d;
		if (d.napTuChuoi(strNgay)) {
			ngayBaoTri = d;
			break;
		}
		cout << "Loi: Ngay khong hop le hoac sai dinh dang dd/MM/yyyy!\n";
	}

	while (1) {
		try {
			string kq = InputHelper::getString("Nhap ket qua (Dat / Can thay the): ");
			setKetQua(kq);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}
}

// FIX: Dung getId() thay vi id
void MaintenanceTicket::display() const {
	cout << "------------------------------------------\n";
	cout << "Ma phieu     : " << getId() << "\n";
	cout << "Ma tram      : " << maTram << "\n";
	cout << "Ma KTV       : " << maKTV << "\n";
	cout << "Ngay bao tri : " << ngayBaoTri.xuatRaChuoi() << "\n";
	cout << "Ket qua      : " << ketQua << "\n";
	cout << "------------------------------------------\n";
}

void MaintenanceTicket::displayRow() const {
	cout << left
		<< setw(12) << getId() << " | "
		<< setw(12) << maTram << " | "
		<< setw(12) << maKTV << " | "
		<< setw(15) << ngayBaoTri.xuatRaChuoi() << " | "
		<< setw(18) << ketQua << '\n';
	cout << right;
}

string MaintenanceTicket::toString() const {
	return getId() + "|" + maTram + "|" + maKTV + "|" + ngayBaoTri.xuatRaChuoi() + "|" + ketQua;
}

// Doc file tu chuoi va validate kieu Date 
void MaintenanceTicket::fromString(const string& line) {
	int soDau = 0;
	for (int i = 0; i < (int)line.size(); i++) {
		if (line[i] == '|') soDau++;
	}
	if (soDau != 4) {
		throw invalid_argument("Ban ghi phieu bao tri phai co 5 cot du lieu!");
	}

	size_t p1 = line.find('|');
	size_t p2 = line.find('|', p1 + 1);
	size_t p3 = line.find('|', p2 + 1);
	size_t p4 = line.find('|', p3 + 1);

	string maDoc = line.substr(0, p1);
	string tramDoc = line.substr(p1 + 1, p2 - p1 - 1);
	string ktvDoc = line.substr(p2 + 1, p3 - p2 - 1);
	string strNgayDoc = line.substr(p3 + 1, p4 - p3 - 1);
	string kqDoc = line.substr(p4 + 1);

	Date d;
	if (!d.napTuChuoi(Validator::catKhoangTrang(strNgayDoc))) {
		throw invalid_argument("Ngay bao tri trong file khong hop le!");
	}

	MaintenanceTicket phieuDoc(maDoc, tramDoc, ktvDoc, d, kqDoc);
	*this = phieuDoc;
}

// FIX: Cai dat operator<< va operator>>
ostream& operator<<(ostream& out, const MaintenanceTicket& ticket) {
	out << ticket.toString();
	return out;
}

istream& operator>>(istream& in, MaintenanceTicket& ticket) {
	string line;
	while (getline(in, line)) {
		string trimmed = Validator::catKhoangTrang(line);
		if (!trimmed.empty()) {
			try {
				ticket.fromString(trimmed);
			} catch (const exception&) {
				in.setstate(ios::failbit);
			}
			return in;
		}
	}
	return in;
}

void MaintenanceTicket::updateInfo() {
	cout << "\nThong tin hien tai:" << endl;
	display();
	cout << "\nNhan Enter de giu nguyen gia tri cu" << endl;

	MaintenanceTicket phieuMoi = *this;

	while (1) {
		try {
			string tramMoi = InputHelper::getString("Ma tram moi [" + maTram + "]: ", true);
			if (!tramMoi.empty()) phieuMoi.setMaTram(tramMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	while (1) {
		try {
			string ktvMoi = InputHelper::getString("Ma KTV moi [" + maKTV + "]: ", true);
			if (!ktvMoi.empty()) phieuMoi.setMaKTV(ktvMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	while (1) {
		string ngayStr = InputHelper::getString("Ngay bao tri moi [" + ngayBaoTri.xuatRaChuoi() + "]: ", true);
		if (ngayStr.empty()) break;
		Date d;
		if (d.napTuChuoi(ngayStr)) {
			phieuMoi.setNgayBaoTri(d);
			break;
		}
		cout << "Loi: Dinh dang ngay khong hop le! Nhap lai.\n";
	}

	while (1) {
		try {
			string kqMoi = InputHelper::getString("Ket qua moi [" + ketQua + "]: ", true);
			if (!kqMoi.empty()) phieuMoi.setKetQua(kqMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	*this = phieuMoi;
}

// Menu va dieu huong CRUD 
void quanLyMaintenanceTicket(Repository<MaintenanceTicket>& repoPhieu, Repository<BtsStation>& repoTram, Repository<Technician>& repoKTV) {
	int luaChon;
	do {
		cout << "\n========== QUAN LY PHIEU BAO TRI ==========\n";
		cout << "1. Them phieu bao tri\n";
		cout << "2. Xem danh sach phieu bao tri\n";
		cout << "3. Tim kiem phieu bao tri\n";
		cout << "4. Sua thong tin phieu bao tri\n";
		cout << "5. Xoa phieu bao tri\n";
		cout << "0. Quay lai\n";

		luaChon = InputHelper::getInt("Nhap lua chon: ", 0, 5);

		try {
			switch (luaChon) {
			case 1: { // CREATE
				MaintenanceTicket phieu;
				phieu.input();

				if (repoPhieu.exists(phieu.getId())) {
					cout << "Loi: Ma phieu bao tri da ton tai!" << endl;
					break;
				}

				// Kiểm tra ràng buộc khóa ngoại 
				if (!repoTram.exists(phieu.getMaTram())) {
					cout << "Loi: Ma tram BTS '" << phieu.getMaTram() << "' khong ton tai trong he thong!" << endl;
					break;
				}
				if (!repoKTV.exists(phieu.getMaKTV())) {
					cout << "Loi: Ma KTV '" << phieu.getMaKTV() << "' khong ton tai trong he thong!" << endl;
					break;
				}

				if (repoPhieu.add(phieu)) {
					cout << "Them phieu thanh cong!" << endl;
				} else {
					cout << "Them that bai, kiem tra file du lieu!" << endl;
				}
				break;
			}
			case 2: { // READ ALL
				const vector<MaintenanceTicket>& danhSach = repoPhieu.getAll();
				if (danhSach.empty()) {
					cout << "Danh sach dang rong!" << endl;
					break;
				}

				cout << left
					<< setw(12) << "Ma Phieu" << " | "
					<< setw(12) << "Ma Tram" << " | "
					<< setw(12) << "Ma KTV" << " | "
					<< setw(15) << "Ngay Bao Tri" << " | "
					<< setw(18) << "Ket Qua" << endl;
				cout << string(75, '-') << endl;

				for (int i = 0; i < (int)danhSach.size(); i++) {
					danhSach[i].displayRow();
				}
				cout << right;
				cout << "Tong so phieu bao tri: " << danhSach.size() << endl;
				break;
			}
			case 3: { //  Tim kiem 
				cout << "1. Tim theo Ma phieu\n";
				cout << "2. Tim theo Ma tram\n";
				cout << "3. Tim theo Ma KTV\n";
				cout << "4. Tim theo Ket qua\n";
				int tieuChi = InputHelper::getInt("Chon tieu chi: ", 1, 4);
				string tuKhoa = InputHelper::getString("Nhap tu khoa tim kiem: ");

				const vector<MaintenanceTicket>& ds = repoPhieu.getAll();
				bool timThay = false;

				for (size_t i = 0; i < ds.size(); ++i) {
					bool khop = false;
					switch (tieuChi) {
						case 1: khop = (ds[i].getId() == tuKhoa); break;
						case 2: khop = (ds[i].getMaTram() == tuKhoa); break;
						case 3: khop = (ds[i].getMaKTV() == tuKhoa); break;
						case 4: khop = (toLowerStr(ds[i].getKetQua()).find(toLowerStr(tuKhoa)) != string::npos); break;
					}

					if (khop) {
						if (!timThay) {
							cout << left
								<< setw(12) << "Ma Phieu" << " | "
								<< setw(12) << "Ma Tram" << " | "
								<< setw(12) << "Ma KTV" << " | "
								<< setw(15) << "Ngay Bao Tri" << " | "
								<< setw(18) << "Ket Qua" << endl;
							cout << string(75, '-') << endl;
							timThay = true;
						}
						ds[i].displayRow();
					}
				}

				if (!timThay) {
					cout << "Khong tim thay phieu bao tri nao phu hop!" << endl;
				}
				break;
			}
			case 4: { // UPDATE
				string ma = InputHelper::getString("Nhap ma phieu can sua: ");
				const MaintenanceTicket* phieu = repoPhieu.find(ma);
				if (phieu == nullptr) {
					cout << "Khong tim thay phieu bao tri!" << endl;
					break;
				}

				MaintenanceTicket phieuMoi = *phieu;
				phieuMoi.updateInfo();

				// Kiểm tra ràng buộc khóa ngoại (Foreign Key) cho thông tin mới
				if (!repoTram.exists(phieuMoi.getMaTram())) {
					cout << "Loi: Ma tram BTS '" << phieuMoi.getMaTram() << "' khong ton tai trong he thong!" << endl;
					break;
				}
				if (!repoKTV.exists(phieuMoi.getMaKTV())) {
					cout << "Loi: Ma KTV '" << phieuMoi.getMaKTV() << "' khong ton tai trong he thong!" << endl;
					break;
				}

				if (repoPhieu.update(ma, phieuMoi)) {
					cout << "Cap nhat thanh cong!" << endl;
				} else {
					cout << "Cap nhat that bai, kiem tra file du lieu!" << endl;
				}
				break;
			}
			case 5: { // DELETE
				string ma = InputHelper::getString("Nhap ma phieu can xoa: ");
				const MaintenanceTicket* phieu = repoPhieu.find(ma);
				if (phieu == nullptr) {
					cout << "Khong tim thay phieu bao tri!" << endl;
					break;
				}

				phieu->display();
				string xacNhan;
				while (1) {
					xacNhan = InputHelper::getString("Xac nhan xoa (y/n): ");
					if (xacNhan == "y" || xacNhan == "Y" || xacNhan == "n" || xacNhan == "N") break;
					cout << "Chi nhap y hoac n!" << endl;
				}

				if (xacNhan == "n" || xacNhan == "N") {
					cout << "Da huy xoa!" << endl;
					break;
				}

				if (repoPhieu.remove(ma)) {
					cout << "Xoa thanh cong!" << endl;
				} else {
					cout << "Xoa that bai, kiem tra file du lieu!" << endl;
				}
				break;
			}
			case 0: break;
			}
		} catch (const invalid_argument& loi) {
			cout << "Loi du lieu: " << loi.what() << endl;
		}
	} while (luaChon != 0);
}
