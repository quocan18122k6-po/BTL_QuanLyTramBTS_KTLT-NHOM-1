#pragma once
#include "Entity.h"
#include "Date.h"
#include "Repository.h"
#include "BtsStation.h"
#include <string>

class StationIncident:public Entity {
private:
	std::string maTram;
	std::string loaiSuCo;
	std::string mucDoUuTien;
	Date ngayXayRa;
	Date ngayKhoiPhuc;
	bool daKhoiPhuc;
public:
	//contructor
	StationIncident();
	StationIncident(const std::string& id, const std::string& maTram, const std::string& loaiSuCo,const std::string &mucDoUuTien, const Date& ngayXayRa, const std::string& ngayKhoiPhuc);
	//getter
	std::string getMaTram() const;
	std::string getLoaiSuCo() const;
	std::string getMucDoUuTien() const;
	Date getNgayXayRa() const;
	Date getNgayKhoiPhuc() const;
	bool getDaKhoiPhuc() const;
	//setter
	void setMaTram(const std::string& maTramMoi);
	void setLoaiSuCo(const std::string& loaiSuCoMoi);
	void setMucDoUuTien(const std::string& mucDoMoi);
	void setNgayXayRa(const Date& ngayMoi);
	void setNgayKhoiPhuc(const std::string& ngayMoi);//Neu chuoi rong la chua khoi phuc
	// ham ke thua entity
	void input();
	void display() const;
	void displayRow() const;
	std::string toString() const;
	void fromString(const std::string& line);
	void updateInfo();
};
void quanLySuCo(Repository<StationIncident>& repoSuCo, Repository<BtsStation> &repoTram);