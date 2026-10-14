#include "antenna config.h"
#include "InputHelper.h"
#include "Validator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;
//constructor
AntennaConfig::AntennaConfig() {
	maTram = "";
	loaiAnten = "";
	gocNgangTilt = 0.0;
	huongPhatAzimuth = 0.0;
	bangTan = "";
}
AntennaConfig::AntennaConfig(
	const string& id,
	const string& maTram,
	const string& loaiAnten,
	double gocNgangTilt,
	double huongPhatAzimuth,
	const string& bangTan
) {
	//Kiem tra ma anten hop le
	if (!Validator::kiemTraMaHopLe(id)) {
		throw invalid_argument("Ma anten khong hop le");
	}
//tan dung cac setter de kiem tra
setId(Validator::catKhoangTrang(id));
setMaTram(maTram);
setLoaiAnten(loaiAnten);
setGocNgangTilt(gocNgangTilt);
setHuongPhatAzimuth(huongPhatAzimuth);
setBangTan(bangTan);
}
//getter
string AntennaConfig::getMaTram() const { 
	return maTram; 
}
string AntennaConfig::getLoaiAnten()const {
	return loaiAnten;
}
double AntennaConfig::getGocNgangTilt() const{
	return gocNgangTilt;
}
double AntennaConfig::getHuongPhatAzimuth() const{
	return huongPhatAzimuth;
}
string AntennaConfig::getBangTan() const{
	return bangTan;
}
//setter
void AntennaConfig::setMaTram(const string& maTramMoi) {
	if (!Validator::kiemTraMaHopLe(maTramMoi)) {
		throw invalid_argument("Ma tram khong hop le");
	}
	maTram = Validator::catKhoangTrang(maTramMoi);
}
void AntennaConfig::setLoaiAnten(const string& loaiAntenMoi) {
	if (Validator::laChuoiRong(loaiAntenMoi)) {
		throw invalid_argument("Loai anten khong duoc rong");
	}
	if (Validator::chuaKyTuPhanCach(loaiAntenMoi) || Validator::chuaKyTuPhanCach(loaiAntenMoi, '\n') || Validator::chuaKyTuPhanCach(loaiAntenMoi, '\r')) {
		throw invalid_argument("Loai anten chua ky tu khong hop le");
	}
	loaiAnten = Validator::catKhoangTrang(loaiAntenMoi);
}
void AntennaConfig::setGocNgangTilt(double gocMoi) {
	if (!Validator::kiemTraGocHopLe(gocMoi, -90, 90)) {
		throw invalid_argument(
			"Goc ngang tilt phai tu -90 den 90 do"
		);
	}
	gocNgangTilt = gocMoi;
}
void AntennaConfig::setHuongPhatAzimuth(double huongMoi) {
	if (!Validator::kiemTraGocHopLe(huongMoi, 0, 360)) {
		throw invalid_argument("Huong phat phai tu 0 den 360 do");
	}
	huongPhatAzimuth = huongMoi;
}
void AntennaConfig::setBangTan(const string& bangTanMoi) {
	string giaTri = Validator::catKhoangTrang(bangTanMoi);
	if (giaTri != "900MHz" && giaTri != "1800MHz" && giaTri != "2100MHz") {
		throw invalid_argument("Bang tan chi nhan gia tri 900MHz, 1800MHz hoac 2100MHz");
	}
	bangTan = giaTri;
}
//nhap tu ban phim-CREATE
void AntennaConfig::input() {
	AntennaConfig antenMoi;
	//vong lap nhap ma anten
	while (true) {
		string maAnten = InputHelper::getString("Nhap ma anten: ");
		if (Validator::kiemTraMaHopLe(maAnten)) {
			antenMoi.setId(maAnten);
			break;
		}
		cout << "Loi: Ma anten khong hop le" << endl;
	}
	//Nhap ma tram
	while (true) {
		try {
			string maTramMoi = InputHelper::getString("Nhap ma tram: ");
			antenMoi.setMaTram(maTramMoi);
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	while (true) {
		try {
			string loaiAntenMoi =
				InputHelper::getString("Nhap loai anten: ");

			antenMoi.setLoaiAnten(loaiAntenMoi);
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	//nhap goc tilt
	double gocMoi = InputHelper::getDouble("Nhap goc tilt (-90 den 90): ",-90,90);
	antenMoi.setGocNgangTilt(gocMoi);
	//nhap huong phat azimuth
	double huongMoi = InputHelper::getDouble("Nhap huong phat(0-360): ", 0, 360);
	antenMoi.setHuongPhatAzimuth(huongMoi);
	//nhap bang tan
	while (true) {
		try {
			string bangTanMoi = InputHelper::getString("Nhap bang tan (900MHz/1800MHz/2100MHz): ");
			antenMoi.setBangTan(bangTanMoi);
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	*this = antenMoi;

}
// hien thi du lieu-READ
void AntennaConfig::display() const {
	cout << "Ma anten: " << id << endl;
	cout << "Ma tram: " << maTram << endl;
	cout << "Loai anten: " << loaiAnten << endl;
	cout << "Goc ngang tilt: " << gocNgangTilt << " do\n";
	cout << "Huong phat Azimuth: " << huongPhatAzimuth << " do\n";
	cout << "Bang tan: " << bangTan << endl;
}
//in 1 hang trong bang danh sach
void AntennaConfig::displayRow() const {
	cout << left << setw(12) << id << " | "
		<< setw(12) << maTram << " | "
		<< setw(20) << loaiAnten << " | "
		<< setw(12) << gocNgangTilt << " | "
		<< setw(12) << huongPhatAzimuth << " | "
		<< setw(15) << bangTan << endl;
	cout << right;   //tra cau hinh can le mac dinh

}
//chuyen doi thanh chuoi de luu vao file
string AntennaConfig::toString() const {
	AntennaConfig antenHopLe(id, maTram, loaiAnten, gocNgangTilt, huongPhatAzimuth, bangTan);
	stringstream ss;
	//ghep thong tin thành mot dong ngan cach boi dau |
	ss << setprecision(17);
	ss<<antenHopLe.getId()<<"|"
		<< antenHopLe.getMaTram()<<"|"
		<< antenHopLe.getLoaiAnten() << "|"
		<< antenHopLe.getGocNgangTilt() << "|"
		<< antenHopLe.getHuongPhatAzimuth() << "|"
		<< antenHopLe.getBangTan();
	//Rut chuoi hoan chinh tu luong ss de tra ve (chuan bi ghi vao file)
	return ss.str();
}
// doc file de tao doi tuong
void AntennaConfig::fromString(const string& line) {
	// check du lieu co dung 6 cot hay ko
	int soDau = 0;
	for (int i = 0;i < line.size();i++) {
		if (line[i] == '|') {
			soDau++;
		}
	}
	if (soDau != 5) {
		throw invalid_argument("Loi: Du lieu phai co du 6 cot");
	}
	//lay du lieu tu chuoi 
	stringstream ss(line);
	string idDoc, maTramDoc, loaiAntenDoc, gocDoc, huongDoc, bangTanDoc;
	getline(ss, idDoc, '|');
	getline(ss, maTramDoc, '|');
	getline(ss, loaiAntenDoc, '|');
	getline(ss, gocDoc, '|');
	getline(ss, huongDoc, '|');
	getline(ss, bangTanDoc, '|');
	// chuyen chuoi goc thanh double
	stringstream ssGoc(gocDoc);
	double goc;
	char kyTuDu;
	//tra ve false neu khong o double,true neu la ki tu du
	if (!(ssGoc >> goc) || (ssGoc >> kyTuDu)) {
		throw invalid_argument("Goc ngang tilt trong file khong hop le");
	}
	//chuyen chuoi huong thanh double
	stringstream ssHuong(huongDoc);
	double huong;
	//tra ve false neu khong o double,true neu la ki tu du
	if (!(ssHuong >> huong) || (ssHuong >> kyTuDu)) {
		throw invalid_argument("Huong phat Azimuth trong file khong hop le");
	}
	//contructor de kiem tra cac truong hop con lai
	AntennaConfig antenDoc(idDoc, maTramDoc, loaiAntenDoc, goc, huong, bangTanDoc);
	*this = antenDoc; // chi khi cac du lieu hop le moi gan vao doi tuong
}
//cap nhat thong tin-UPDATE
void AntennaConfig::updateInfo() {
	cout << "\n Thong tin hien tai" << endl;
	display();
	cout << "\n Nhan Enter de giu nguyen" << endl;
	AntennaConfig antenMoi = *this; //tao ban sao de doi tuong goc khong bi anh huong
	while (true) {
		try {
			string maTramMoi = InputHelper::getString("Ma tram moi: ", true);
			if (!maTramMoi.empty()) {
					antenMoi.setMaTram(maTramMoi);
	        } 
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	while (true) {
		try {
			string loaiAntenMoi = InputHelper::getString("Loai anten moi: ", true);
			if (!loaiAntenMoi.empty()) {
				antenMoi.setLoaiAnten(loaiAntenMoi);
			}
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}

	}
	double gocMoi = InputHelper::getDouble("Goc ngang tilt moi (-90-90): ", -90, 90,true, gocNgangTilt);
	antenMoi.setGocNgangTilt(gocMoi);
	double huongMoi = InputHelper::getDouble("Huong phat Azimuth moi (0-360): ", 0, 360, true,huongPhatAzimuth);
	antenMoi.setHuongPhatAzimuth(huongMoi);
	while (true) {
		try {
			string bangTanMoi = InputHelper::getString("Bang tan moi (900MHz/1800MHz/2100MHz): ", true);
			if (!bangTanMoi.empty()) {
				antenMoi.setBangTan(bangTanMoi);
			}
			break;
		}
		catch (const invalid_argument& loi) {
			cout << loi.what() << endl;
		}
	}
	*this = antenMoi;
}