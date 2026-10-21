#pragma once

#include "Entity.h"
#include "Date.h"
#include "Repository.h"
#include "BtsStation.h"
#include "Technician.h"
#include <string>
#include <iostream>

// Usecase 2
class MaintenanceTicket : public Entity {
private:
	std::string maTram;
	std::string maKTV;
	Date ngayBaoTri;
	std::string ketQua;

public:
	// Constructors
	MaintenanceTicket();
	MaintenanceTicket(const std::string& id, const std::string& maTram, const std::string& maKTV, const Date& ngayBaoTri, const std::string& ketQua);

	// Getters
	std::string getMaTram() const;
	std::string getMaKTV() const;
	Date getNgayBaoTri() const;
	std::string getKetQua() const;

	// Setters
	void setMaTram(const std::string& maTramMoi);
	void setMaKTV(const std::string& maKTVMoi);
	void setNgayBaoTri(const Date& ngayMoi);
	void setKetQua(const std::string& ketQuaMoi);

	// 6 ham ke thua tu Entity.h
	void input() override;
	void display() const override;
	void displayRow() const override;
	std::string toString() const override;
	void fromString(const std::string& line) override;
	void updateInfo() override;

	friend std::ostream& operator<<(std::ostream& out, const MaintenanceTicket& ticket);
	friend std::istream& operator>>(std::istream& in, MaintenanceTicket& ticket);
};

// Khai bao ham dieu huong Menu CRUD 
void quanLyMaintenanceTicket(Repository<MaintenanceTicket>& repoPhieu, Repository<BtsStation>& repoTram, Repository<Technician>& repoKTV);
