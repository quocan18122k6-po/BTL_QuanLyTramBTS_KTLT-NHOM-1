#pragma once
#include "Entity.h"
#include "Repository.h"
#include "BtsStation.h"
#include <string>
       //contructor
class AntennaConfig : public Entity {
private:
	std::string maTram;
	std::string loaiAnten;
	double gocNgangTilt;
	double huongPhatAzimuth;
	std::string bangTan;
public:
	AntennaConfig();
	AntennaConfig(
		const std::string &id,
		const std::string& maTram,
		const std::string& loaiAnten,
		double gocNgangTilt,
		double huongPhatAzimuth,
		const std::string& bangTan
		);
		// Getter
		std::string getMaTram() const;
		std::string getLoaiAnten() const;
		double getGocNgangTilt() const;
		double getHuongPhatAzimuth() const;
		std::string getBangTan() const;
		//Setter
		void setMaTram(const std::string & maTramMoi);
		void setLoaiAnten(const std::string & loaiAntenMoi);
		void setGocNgangTilt(double gocMoi);
		void setHuongPhatAzimuth(double huongMoi);
		void setBangTan(const std::string & bangTanMoi);
		//ghi de lop entity
		void input();
		void display() const;
		void displayRow() const;
		std::string toString() const;
		void fromString(const std::string &line) ;
		void updateInfo();
	};
// Ham mo menu va xu ly CRUD Anten.
void quanLyAnten(Repository<AntennaConfig>& repoAnten, Repository<BtsStation>& repoTram);