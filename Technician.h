#pragma once

#include "Entity.h"
#include "Repository.h"
#include <string>
#include <iostream>

// Usecase 1
class Technician : public Entity {
private:
	std::string hoTen;
	std::string soDienThoai;
	std::string chungChi;
	std::string doiPhuTrach;

public:
	// Constructors
	Technician();
	Technician(const std::string& id, const std::string& hoTen, const std::string& soDienThoai, const std::string& chungChi, const std::string& doiPhuTrach);

	// Getters
	std::string getHoTen() const;
	std::string getSoDienThoai() const;
	std::string getChungChi() const;
	std::string getDoiPhuTrach() const;

	// Setters
	void setHoTen(const std::string& hoTenMoi);
	void setSoDienThoai(const std::string& sdtMoi);
	void setChungChi(const std::string& chungChiMoi);
	void setDoiPhuTrach(const std::string& doiMoi);

	// 6 ham ke thua tu Entity.h
	void input() override;
	void display() const override;
	void displayRow() const override;
	std::string toString() const override;
	void fromString(const std::string& line) override;
	void updateInfo() override;

	friend std::ostream& operator<<(std::ostream& out, const Technician& technician);
	friend std::istream& operator>>(std::istream& in, Technician& technician);
};

// Khai bao ham dieu huong Menu CRUD 
class MaintenanceTicket;
void quanLyTechnician(Repository<Technician>& repoKTV, Repository<MaintenanceTicket>* repoPhieu = nullptr);
