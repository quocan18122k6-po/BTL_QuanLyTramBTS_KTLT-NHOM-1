#include "StationIncident.h"
#include "InputHelper.h"
#include "Validator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;
//constructor
StationIncident::StationIncident() { //constructor mac dinh
	maTram = "";
	loaiSuCo = "";
	mucDoUuTien = "";
	daKhoiPhuc = false; //moi khoi tao nen chua khoi phuc
}
StationIncident::StationIncident(const string &id,const string &maTram,const string &loaiSuCo,const string &mucDoUuTien,const Date &ngayXayRa,const string &ngayKhoiPhuc){
	daKhoiPhuc = false;
	//kiem tra hop le
	if (!Validator::kiemTraMaHopLe(id)) {
		throw invalid_argument("Ma su co khong hop le");
	}
	//tan dung cac setter de kiem tra
	setId(Validator::catKhoangTrang(id));
	setMaTram(maTram);
	setLoaiSuCo(loaiSuCo);
	setMucDoUuTien(mucDoUuTien);
	setNgayXayRa(ngayXayRa);
	setNgayKhoiPhuc(ngayKhoiPhuc);
}
//getter
string StationIncident::getMaTram()const { return maTram; }
string StationIncident::getLoaiSuCo()const { return loaiSuCo; }
string StationIncident::getMucDoUuTien() const { return mucDoUuTien;  }
Date StationIncident::getNgayXayRa() const { return ngayXayRa; }
Date StationIncident::getNgayKhoiPhuc() const { return ngayKhoiPhuc; }
bool StationIncident::getDaKhoiPhuc() const { return daKhoiPhuc; }
//setter
void StationIncident::setMaTram(const string& maTramMoi) {
	if (!Validator::kiemTraMaHopLe(maTramMoi)) {
		throw invalid_argument("Ma tram khong hop le");
	}

	maTram = Validator::catKhoangTrang(maTramMoi);
}
void StationIncident::setLoaiSuCo(const string& loaiSuCoMoi) {
	if (Validator::laChuoiRong(loaiSuCoMoi)) {
		throw invalid_argument("Loai su co khong duoc rong");
	}
// check ki tu phan cach
	if (Validator::chuaKyTuPhanCach(loaiSuCoMoi) || Validator::chuaKyTuPhanCach(loaiSuCoMoi, '\n') || Validator::chuaKyTuPhanCach(loaiSuCoMoi, '\r')) {
		throw invalid_argument("Loai su co chua ky tu khong hop le");

	}
	loaiSuCo = Validator::catKhoangTrang(loaiSuCoMoi);//loai bo dau cach
}
void StationIncident::setMucDoUuTien(const string& mucDoMoi) {
	string giaTri = Validator::catKhoangTrang(mucDoMoi);
	if (giaTri != "Khan cap" && giaTri != "Cao" && giaTri != "Trung binh") {
		throw invalid_argument("Muc do chi nhan Khan cap, Cao hoac Trung binh");
	}
	mucDoUuTien = giaTri;
}
void StationIncident::setNgayXayRa(const Date& ngayMoi) {
	if (daKhoiPhuc && ngayMoi > ngayKhoiPhuc) { //check loi nhap ngay xay ra sau ngay khoi phuc 
		throw invalid_argument("Ngay xay ra khong duoc sau ngay khoi phuc");
	}
	ngayXayRa = ngayMoi;
}
void StationIncident::setNgayKhoiPhuc(const string& ngayMoi) {
	string chuoi = Validator::catKhoangTrang(ngayMoi);
	if (chuoi.empty()) { //Neu khong co ngay khoi phuc thi danh dau su co chua xong, xoa ngay cu va ket thuc ham
		daKhoiPhuc = false;
		ngayKhoiPhuc = Date();
		return;
	}
	Date ngay;
	if (!ngay.napTuChuoi(chuoi)) {
		throw invalid_argument("Ngay khoi phuc khong hop le");
	}
	if (ngay < ngayXayRa) {
		throw invalid_argument("Ngay khoi phuc khong duoc truoc ngay xay ra");

	}
	ngayKhoiPhuc = ngay;
	daKhoiPhuc = true;
}
//ham nhap 
void StationIncident::input() {
	while (true) {
		try { //check loi nhap den khi nhap dung moi thoi
			string ma = InputHelper::getString("Ma su co: ");
			string maTramMoi = InputHelper::getString("Ma tram: ");
			string loaiSuCoMoi = InputHelper::getString("Loai su co: ");
			string mucDoMoi = InputHelper::getString("Muc do (Khan cap/Cao/Trung binh): ");
			string ngayXayRaMoi = InputHelper::getString("Ngay xay ra (dd/MM/yyyy): ");
			Date ngay;
			if (!ngay.napTuChuoi(ngayXayRaMoi)) {
				throw invalid_argument("Ngay xay ra khong hop le");
			}
			string ngayKhoiPhucMoi = InputHelper::getString("Ngay khoi phuc (Enter neu chua khoi phuc): ", true);//Nhan enter la chua khoi phuc

		StationIncident suCoMoi(ma, maTramMoi, loaiSuCoMoi, mucDoMoi,ngay, ngayKhoiPhucMoi);
		*this = suCoMoi;
		return;// thoat khoi vong lap
	    }
	catch (const invalid_argument& loi) {
		cout << "Loi: " << loi.what() << endl;
		cout << "Vui long nhap lai thong tin su co" << endl;
	}
	}
}
//hien thi ra man hinh
void StationIncident::display() const {
	cout << "Ma su co: " << id << endl;
	cout << "Ma tram: " << maTram << endl;
	cout << "Loai su co: " << loaiSuCo << endl;
	cout << "Muc do uu tien: " << mucDoUuTien << endl;
	cout << "Ngay xay ra: " << ngayXayRa<<endl;
	if (daKhoiPhuc) {
		cout << "Ngay khoi phuc: " << ngayKhoiPhuc << endl;
	}
	else {
		cout << "Trang thai: Chua khoi phuc " << endl;
	}
}
void StationIncident::displayRow() const{
	string ngayKetThuc = "Chua khoi phuc";
	if (daKhoiPhuc) {
		ngayKetThuc = ngayKhoiPhuc.toString();
	}
	cout << left
		<< setw(12) << id << " | "
		<< setw(12) << maTram << " | "
		<< setw(25) << loaiSuCo << " | "
		<< setw(15) << mucDoUuTien << " | "
		<< setw(12) << ngayXayRa.toString() << " | "
		<< setw(15) << ngayKetThuc << '\n';

	cout << right;
}
// chuyen thanh dang chuoi 
string StationIncident::toString()const {
	string ngayKetThuc = ""; //Neu chua khoi phuc thi la rong
	if (daKhoiPhuc) {
		ngayKetThuc = ngayKhoiPhuc.toString();
	}
	//dung constructor kiem tra du lieu
	StationIncident suCoHopLe(id, maTram, loaiSuCo, mucDoUuTien, ngayXayRa, ngayKetThuc);
	stringstream ss; //dung stringstream de gan du lieu vao cac cot
	ss << suCoHopLe.getId() << "|"
		<< suCoHopLe.getMaTram() << "|"
		<< suCoHopLe.getLoaiSuCo() << "|"
		<< suCoHopLe.getMucDoUuTien() << "|"
		<< suCoHopLe.getNgayXayRa().toString() << "|"
		<< ngayKetThuc;
	return ss.str();
}
//doc tu chuoi
void StationIncident::fromString(const string&line){
	int soDau = 0;
	for (int i = 0;i < (int)line.size();i++) {
		if (line[i] == '|') soDau++;
	}
		if (soDau != 5) {
			throw invalid_argument("Ban ghi su co phai co 6 cot du lieu");
		}
		stringstream ss(line); //nap chuoi van ban vao stringstream

		string idDoc, maTramDoc, loaiSuCoDoc, mucDoDoc, ngayXayRaDoc, ngayKhoiPhucDoc;
		getline(ss, idDoc, '|');
		getline(ss, maTramDoc, '|');
		getline(ss, loaiSuCoDoc, '|');
		getline(ss, mucDoDoc, '|');
		getline(ss, ngayXayRaDoc, '|');
		getline(ss, ngayKhoiPhucDoc);
		Date ngay;
		if (!ngay.napTuChuoi(Validator::catKhoangTrang(ngayXayRaDoc))) {
			throw invalid_argument("Ngay xay ra trong file khong hop le");
		}
		StationIncident suCoDoc(idDoc, maTramDoc, loaiSuCoDoc, mucDoDoc, ngay, ngayKhoiPhucDoc);// tao ban sao luu doi tuong de dung constructor check
		*this = suCoDoc;
}
//cap nhat
void StationIncident::updateInfo() {
	cout << "\nThong tin hien tai:" << endl;
	display();
	cout << "\n Nhan Enter de giu nguyen" << endl;
	cout << "Ngay khoi phuc:nhap dau - de chuyen ve chua khoi phuc" << endl;
	StationIncident suCoMoi = *this;// tao ban sao de khong anh huong den doi tuong goc
	// khong doi id
	while (true) {
		try {
			string maTramMoi = InputHelper::getString("Ma tram moi: ", true);// duoc phep de rong
			if (!maTramMoi.empty()) {
				suCoMoi.setMaTram(maTramMoi); // chi gan gia tri khi nhap dung ki tu
			}
			break;// ki tu hop le hoac enter thi thoat vong lap
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	while (true) {
		try {
			string loaiSuCoMoi = InputHelper::getString("Loai su co moi: ", true); // duoc phep de rong
			if (!loaiSuCoMoi.empty()) {
				suCoMoi.setLoaiSuCo(loaiSuCoMoi);
			}
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	while (true) {
		try {
			string mucDoMoi = InputHelper::getString("Muc do moi (Khan cap/Cao/Trung binh): ", true);
			if (!mucDoMoi.empty()) {
				suCoMoi.setMucDoUuTien(mucDoMoi);
			}
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	Date ngayXayRaMoi = ngayXayRa;//lay ngay cu neu nhap enter
	while (true) {
		string chuoi = InputHelper::getString("Ngay xay ra moi (dd/MM/yyyy): ", true);
		if (chuoi.empty()) break;
		if (ngayXayRaMoi.napTuChuoi(chuoi)) break;
		cout << "Ngay xay ra khong hop le" << endl;
	}
	// bo ngay khoi phuc tren ban sao de tranh xung dot ngay xya ra moi
	suCoMoi.setNgayKhoiPhuc("");
	suCoMoi.setNgayXayRa(ngayXayRaMoi);
	while (true) {
		try {
			string chuoi = InputHelper::getString("Ngay khoi phuc moi (Enter de giu,- de xoa): ", true);
			if (chuoi.empty()) { //bam enter
				if (daKhoiPhuc) { // neu da khoi phuc check xem co khop voi ngay xay ra moi khong
					chuoi = ngayKhoiPhuc.toString();
				}
			}
			else if (chuoi == "-") { //neu bam - thi chuyen ve trang thai chua khoi phuc
				chuoi = "";
			}
			suCoMoi.setNgayKhoiPhuc(chuoi); // kiem tra ngay xay ra moi co hop le khong
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	*this = suCoMoi;//tra ve doi tuong hien tai
}
//MENU va CRUD
void quanLySuCo(Repository<StationIncident> &repoSuCo,Repository<BtsStation> &repoTram){
	int luaChon;
	do {
		cout << "\n========== QUAN LY SU CO ==========\n";
		cout << "1. Them su co\n";
		cout << "2. Xem danh sach su co\n";
		cout << "3. Tim su co theo ma\n";
		cout << "4. Sua thong tin su co\n";
		cout << "5. Xoa su co\n";
		cout << "0. Quay lai\n";
		luaChon = InputHelper::getInt("Nhap lua chon: ", 0, 5);
		try {
			switch (luaChon) {
			case 1: { // tao moi (CREATE)
				StationIncident suCo;
				suCo.input();
				if (repoSuCo.exists(suCo.getId())) {//su co da ton tai thi bao loi,ve menu
					cout << "Ma su co da ton tai" << endl;
					break;
				}
				if (!repoTram.exists(suCo.getMaTram())) { //ma tram khong ton tai
					cout << "Ma tram khong ton tai. Huy them." << endl;
					break;
				}
				if (repoSuCo.add(suCo)) {
					cout << "Them thanh cong" << endl;
				}
				else {
					cout << "Them that bai, kiem tra file du lieu" << endl;
				}
				break;
			}
			case 2: { //xem danh sach (READ)
				const vector<StationIncident>& danhSach = repoSuCo.getAll();//lay toan bo danh sach dang quan ly 
				if (danhSach.empty()) {
					cout << "Danh sach dang rong" << endl;
					break;
				}
				cout << left
					<< setw(12) << "Ma su co" << " | "
					<< setw(12) << "Ma tram" << " | "
					<< setw(25) << "Loai su co" << " | "
					<< setw(15) << "Uu tien" << " | "
					<< setw(12) << "Ngay xay ra" << " | "
					<< setw(15) << "Ngay khoi phuc" << endl;
				for (int i = 0;i < (int)danhSach.size();i++) {
					danhSach[i].displayRow();
				}
				cout << right;
				cout << "Tong so su co: " << danhSach.size() << endl;
				break;
			}
			case 3: {// tim kiem su co (READ)
				string ma = InputHelper::getString("Nhap ma su co can tim: ");
				const StationIncident* suCo = repoSuCo.find(ma); //tim su co theo ma, neu khong thay tra ve nullptr
				if (suCo == nullptr) {
					cout << "Khong tim thay su co" << endl;
				}
				else {
					suCo->display();// goi phuong thuc hien thi cua con tro su co
				}
				break;
			}
			case 4: { // sua thong tin (UPDATE)
				string ma = InputHelper::getString("Nhap ma su co can sua: ");
				const StationIncident* suCo = repoSuCo.find(ma);
				if (suCo == nullptr) {
					cout << "Khong tim thay su co" << endl;
					break;
				}
				StationIncident suCoMoi = *suCo;
				suCoMoi.updateInfo();
				if (!repoTram.exists(suCoMoi.getMaTram())) {
					cout << "Ma tram khong ton tai. Huy cap nhat." << endl;
					break;
				}
				if (repoSuCo.update(ma, suCoMoi)) {
					cout << "Cap nhat thanh cong" << endl;
				}
				else {
					cout << "Cap nhat that bai, kiem tra file du lieu" << endl;
				}
				break;
			}
			case 5: { // xoa thong tin (DELETE)
				string ma = InputHelper::getString("Nhap ma su co can xoa: ");
				const StationIncident* suCo = repoSuCo.find(ma);
				if (suCo == nullptr) {
					cout << "Khong tim thay su co" << endl;
					break;
				}
				suCo->display();
				string xacNhan;
				while (true) {
					xacNhan = InputHelper::getString("Xac nhan xoa (y/n): ");
					if (xacNhan == "y" || xacNhan == "Y" || xacNhan == "n" || xacNhan == "N") {
						break;
					}
					cout << "Chi nhap y hoac n" << endl;
				}
				if (xacNhan == "n" || xacNhan == "N") {
					cout << "Da huy xoa" << endl;
					break;
				}
				if (repoSuCo.remove(ma)) {
					cout << "Xoa thanh cong" << endl;
				}
				else {
					cout << "Xoa that bai, kiem tra file du lieu" << endl;
				}
				break;
			}
			case 0: break;
		    } 
	    }
			catch (const invalid_argument& loi) {
				cout << "Loi du lieu: " << loi.what() << endl;
			}
	}
		while (luaChon != 0);
}

				



				 



