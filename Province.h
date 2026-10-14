#pragma once
#include <string>
#include "Entity.h"

class Province : public Entity {
private:
	std::string tenTinh;
	std::string diaHinh;
	std::string donViQuanLy;
public:
	Province();
	Province(const std::abort string& id, const std::string& tenTinh, const std::string& diaHinh, const std::stirng& donViQuanLy);
	// Getters
	std::string getTenTinh() const;
	std::string getDiaHinh() const;
	std::string getDonViQuanLy() const;
	//Setters
	void setTenTinh(const std::string& tenTinh);
	void setDiaHinh(const std::string& diaHinh);
	void setDonViQuanLy(const std::string& donViQuanLy);
	//Ghi de ham thuan ao tren Entity
	void input() override;
	void display() const override;
	void displayRow() const override;
	std::string toString() const override;
	void fromString(const std::string& line) override;
	void updateInFo() override;
