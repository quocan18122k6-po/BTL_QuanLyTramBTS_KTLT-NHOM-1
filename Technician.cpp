#include "Technician.h"
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

namespace {// viet hoa thanh thuong
	string toLowerStr(string s) {
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(tolower(c)); });
		return s;
	}
}

//  Khoi tao
Technician::Technician() : Entity() {
	hoTen = "";
	soDienThoai = "";
	chungChi = "";
	doiPhuTrach = "";
}

Technician::Technician(const string& id, const string& hoTen, const string& soDienThoai, const string& chungChi, const string& doiPhuTrach) {
	if (!Validator::kiemTraMaHopLe(id)) {
		throw invalid_argument("Ma ky thuat vien khong hop le!");
	}
	setId(Validator::catKhoangTrang(id));
	setHoTen(hoTen);
	setSoDienThoai(soDienThoai);
	setChungChi(chungChi);
	setDoiPhuTrach(doiPhuTrach);
}

// Tra gtri cua thuoc tinh tuong ung Getters
string Technician::getHoTen() const { return hoTen; }
string Technician::getSoDienThoai() const { return soDienThoai; }
string Technician::getChungChi() const { return chungChi; }
string Technician::getDoiPhuTrach() const { return doiPhuTrach; }

// check SETTER
void Technician::setHoTen(const string& hoTenMoi) {
	if (Validator::laChuoiRong(hoTenMoi)) {
		throw invalid_argument("Ho ten khong duoc de trong!");
	}
	if (Validator::chuaKyTuPhanCach(hoTenMoi)) {
		throw invalid_argument("Ho ten khong duoc chua ky tu '|'!");
	}
	hoTen = Validator::catKhoangTrang(hoTenMoi);
}

void Technician::setSoDienThoai(const string& sdtMoi) {
	string sdt = Validator::catKhoangTrang(sdtMoi);
	if (!Validator::kiemTraSoDienThoai(sdt)) {
		throw invalid_argument("So dien thoai phai co 10 chu so va bat dau bang so 0!");
	}
	soDienThoai = sdt;
}

void Technician::setChungChi(const string& chungChiMoi) {
	if (Validator::laChuoiRong(chungChiMoi)) {
		throw invalid_argument("Chung chi khong duoc de trong!");
	}
	if (Validator::chuaKyTuPhanCach(chungChiMoi)) {
		throw invalid_argument("Chung chi khong duoc chua ky tu '|'!");
	}
	chungChi = Validator::catKhoangTrang(chungChiMoi);
}

void Technician::setDoiPhuTrach(const string& doiMoi) {
	if (Validator::laChuoiRong(doiMoi)) {
		throw invalid_argument("Doi phu trach khong duoc de trong!");
	}
	if (Validator::chuaKyTuPhanCach(doiMoi)) {
		throw invalid_argument("Doi phu trach khong duoc chua ky tu '|'!");
	}
	doiPhuTrach = Validator::catKhoangTrang(doiMoi);
}

// Input
void Technician::input() {
	while (1) {
		try {
			string ma = InputHelper::getString("Nhap ma KTV (vi du KTV01): ");
			if (!Validator::kiemTraMaHopLe(ma)) {
				throw invalid_argument("Ma KTV khong hop le!");
			}
			setId(Validator::catKhoangTrang(ma));
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string ten = InputHelper::getString("Nhap ho ten: ");
			setHoTen(ten);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string sdt = InputHelper::getString("Nhap so dien thoai (10 chu so): ");
			setSoDienThoai(sdt);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string cc = InputHelper::getString("Nhap chung chi: ");
			setChungChi(cc);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}

	while (1) {
		try {
			string doi = InputHelper::getString("Nhap doi phu trach: ");
			setDoiPhuTrach(doi);
			break;
		} catch (const exception& e) {
			cout << "Loi: " << e.what() << "\n";
		}
	}
}

// Hien thi chi tiet
void Technician::display() const {
	cout << "------------------------------------------\n";
	cout << "Ma KTV        : " << getId() << "\n";
	cout << "Ho va ten     : " << hoTen << "\n";
	cout << "So dien thoai : " << soDienThoai << "\n";
	cout << "Chung chi     : " << chungChi << "\n";
	cout << "Doi phu trach : " << doiPhuTrach << "\n";
	cout << "------------------------------------------\n";
}

void Technician::displayRow() const {
	cout << left
		<< setw(12) << getId() << " | "
		<< setw(22) << hoTen << " | "
		<< setw(14) << soDienThoai << " | "
		<< setw(18) << chungChi << " | "
		<< setw(16) << doiPhuTrach << '\n';
	cout << right;
}

string Technician::toString() const {
	return getId() + "|" + hoTen + "|" + soDienThoai + "|" + chungChi + "|" + doiPhuTrach;
}
// Doc file tu chuoi 
void Technician::fromString(const string& line) {
	int soDau = 0;
	for (int i = 0; i < (int)line.size(); i++) {
		if (line[i] == '|') soDau++;
	}
	if (soDau != 4) {
		throw invalid_argument("Ban ghi ky thuat vien phai co 5 cot du lieu!");
	}

	size_t p1 = line.find('|');
	size_t p2 = line.find('|', p1 + 1);
	size_t p3 = line.find('|', p2 + 1);
	size_t p4 = line.find('|', p3 + 1);

	string maDoc = line.substr(0, p1);
	string tenDoc = line.substr(p1 + 1, p2 - p1 - 1);
	string sdtDoc = line.substr(p2 + 1, p3 - p2 - 1);
	string ccDoc = line.substr(p3 + 1, p4 - p3 - 1);
	string doiDoc = line.substr(p4 + 1);

	Technician ktvDoc(maDoc, tenDoc, sdtDoc, ccDoc, doiDoc);
	*this = ktvDoc;
}
// Xuat nhap du lieu
ostream& operator<<(ostream& out, const Technician& technician) {
	out << technician.toString();
	return out;
}

istream& operator>>(istream& in, Technician& technician) {
	string line;
	while (getline(in, line)) {
		string trimmed = Validator::catKhoangTrang(line);
		if (!trimmed.empty()) {
			try {
				technician.fromString(trimmed);
			} catch (const exception&) {
				in.setstate(ios::failbit);
			}
			return in;
		}
	}
	return in;
}
// sua thong tin
void Technician::updateInfo() {
	cout << "\nThong tin hien tai:" << endl;
	display();
	cout << "\nNhan Enter de giu nguyen gia tri cu" << endl;

	Technician ktvMoi = *this;

	while (1) {
		try {
			string tenMoi = InputHelper::getString("Ho ten moi [" + hoTen + "]: ", true);
			if (!tenMoi.empty()) ktvMoi.setHoTen(tenMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	while (1) {
		try {
			string sdtMoi = InputHelper::getString("So dien thoai moi [" + soDienThoai + "]: ", true);
			if (!sdtMoi.empty()) ktvMoi.setSoDienThoai(sdtMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	while (1) {
		try {
			string ccMoi = InputHelper::getString("Chung chi moi [" + chungChi + "]: ", true);
			if (!ccMoi.empty()) ktvMoi.setChungChi(ccMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	while (1) {
		try {
			string doiMoi = InputHelper::getString("Doi phu trach moi [" + doiPhuTrach + "]: ", true);
			if (!doiMoi.empty()) ktvMoi.setDoiPhuTrach(doiMoi);
			break;
		} catch (const invalid_argument& loi) {
			cout << "Loi: " << loi.what() << endl;
		}
	}

	*this = ktvMoi;
}

// Menu va CRUD
void quanLyTechnician(Repository<Technician>& repoKTV, Repository<MaintenanceTicket>* repoPhieu) {
	int luaChon;
	do {
		cout << "\n========== QUAN LY KY THUAT VIEN ==========\n";
		cout << "1. Them ky thuat vien\n";
		cout << "2. Xem danh sach ky thuat vien\n";
		cout << "3. Tim kiem ky thuat vien\n";
		cout << "4. Sua thong tin ky thuat vien\n";
		cout << "5. Xoa ky thuat vien\n";
		cout << "0. Quay lai\n";

		luaChon = InputHelper::getInt("Nhap lua chon: ", 0, 5);

		try {
			switch (luaChon) {
			case 1: { // Them ky thuat vien
				Technician ktv;
				ktv.input();

				if (repoKTV.exists(ktv.getId())) {
					cout << "Loi: Ma ky thuat vien da ton tai!" << endl;
					break;
				}

				if (repoKTV.add(ktv)) {
					cout << "Them thanh cong!" << endl;
				} else {
					cout << "Them that bai, kiem tra file du lieu!" << endl;
				}
				break;
			}
			case 2: { // Xem danh sach ky thuat vien
				const vector<Technician>& danhSach = repoKTV.getAll();
				if (danhSach.empty()) {
					cout << "Danh sach dang rong!" << endl;
					break;
				}

				cout << left
					<< setw(12) << "Ma KTV" << " | "
					<< setw(22) << "Ho va Ten" << " | "
					<< setw(14) << "So dien thoai" << " | "
					<< setw(18) << "Chung chi" << " | "
					<< setw(16) << "Doi phu trach" << endl;
				cout << string(85, '-') << endl;

				for (int i = 0; i < (int)danhSach.size(); i++) {
					danhSach[i].displayRow();
				}
				cout << right;
				cout << "Tong so ky thuat vien: " << danhSach.size() << endl;
				break;
			}
			case 3: { // Tim kiem ky thuat vien
				cout << "1. Tim theo Ma KTV\n";
				cout << "2. Tim theo Ho ten\n";
				cout << "3. Tim theo So dien thoai\n";
				cout << "4. Tim theo Chung chi\n";
				cout << "5. Tim theo Doi phu trach\n";
				int tieuChi = InputHelper::getInt("Chon tieu chi: ", 1, 5);
				string tuKhoa = InputHelper::getString("Nhap tu khoa tim kiem: ");

				const vector<Technician>& ds = repoKTV.getAll();
				bool timThay = false;

				for (size_t i = 0; i < ds.size(); ++i) {
					bool khop = false;
					switch (tieuChi) {
						case 1: khop = (ds[i].getId() == tuKhoa); break;
						case 2: khop = (toLowerStr(ds[i].getHoTen()).find(toLowerStr(tuKhoa)) != string::npos); break;
						case 3: khop = (ds[i].getSoDienThoai().find(tuKhoa) != string::npos); break;
						case 4: khop = (toLowerStr(ds[i].getChungChi()).find(toLowerStr(tuKhoa)) != string::npos); break;
						case 5: khop = (toLowerStr(ds[i].getDoiPhuTrach()).find(toLowerStr(tuKhoa)) != string::npos); break;
					}

					if (khop) {
						if (!timThay) {
							cout << left
								<< setw(12) << "Ma KTV" << " | "
								<< setw(22) << "Ho va Ten" << " | "
								<< setw(14) << "So dien thoai" << " | "
								<< setw(18) << "Chung chi" << " | "
								<< setw(16) << "Doi phu trach" << endl;
							cout << string(85, '-') << endl;
							timThay = true;
						}
						ds[i].displayRow();
					}
				}

				if (!timThay) {
					cout << "Khong tim thay ky thuat vien nao phu hop!" << endl;
				}
				break;
			}
			case 4: { // Sua thong tin ky thuat vien
				string ma = InputHelper::getString("Nhap ma KTV can sua: ");
				const Technician* ktv = repoKTV.find(ma);
				if (ktv == nullptr) {
					cout << "Khong tim thay ky thuat vien!" << endl;
					break;
				}

				Technician ktvMoi = *ktv;
				ktvMoi.updateInfo();

				if (repoKTV.update(ma, ktvMoi)) {
					cout << "Cap nhat thanh cong!" << endl;
				} else {
					cout << "Cap nhat that bai, kiem tra file du lieu!" << endl;
				}
				break;
			}
			case 5: { // Xoa ky thuat vien
				string ma = InputHelper::getString("Nhap ma KTV can xoa: ");
				const Technician* ktv = repoKTV.find(ma);
				if (ktv == nullptr) {
					cout << "Khong tim thay ky thuat vien!" << endl;
					break;
				}

				// Kiểm tra ràng buộc khóa ngoại 
				if (repoPhieu != nullptr) {
					bool dangCoPhieu = false;
					const vector<MaintenanceTicket>& dsPhieu = repoPhieu->getAll();
					for (size_t i = 0; i < dsPhieu.size(); ++i) {
						if (dsPhieu[i].getMaKTV() == ma) {
							dangCoPhieu = true;
							break;
						}
					}
					if (dangCoPhieu) {
						cout << "Loi: Khong the xoa KTV " << ma << " vi dang co phieu bao tri tham chieu den!" << endl;
						break;
					}
				}

				ktv->display();
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

				if (repoKTV.remove(ma)) {
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
