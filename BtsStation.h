#ifndef BTS_STATION_MODULE_H
#define BTS_STATION_MODULE_H

#include "Entity.h"
#include "Province.h"
#include "Repository.h"

#include <iosfwd>
#include <string>

class InstalledDevice;
class AntennaConfig;
class MaintenanceTicket;
class StationIncident;

// Luu thong tin mot tram BTS. ID trong Entity duoc dung lam ma tram.
class BtsStation : public Entity {
private:
    std::string tenTram;
    std::string maKhuVuc;   // Khoa ngoai tham chieu Province::id
    std::string diaChi;
    double viDo;
    double kinhDo;
    std::string trangThai;

public:
    BtsStation();
    BtsStation(const std::string& maTram,
               const std::string& tenTram,
               const std::string& maKhuVuc,
               const std::string& diaChi,
               double viDo,
               double kinhDo,
               const std::string& trangThai);

    std::string getTenTram() const;
    std::string getMaKhuVuc() const;
    std::string getDiaChi() const;
    double getViDo() const;
    double getKinhDo() const;
    std::string getTrangThai() const;

    void setTenTram(const std::string& value);
    void setMaKhuVuc(const std::string& value);
    void setDiaChi(const std::string& value);
    void setViDo(double value);
    void setKinhDo(double value);
    void setTrangThai(const std::string& value);

    void input() override;
    void display() const override;
    void displayRow() const override;
    std::string toString() const override;
    void fromString(const std::string& line) override;
    void updateInfo() override;

    // Ho tro Repository.h cu doc/ghi bang toan tu >> va <<.
    friend std::ostream& operator<<(std::ostream& out, const BtsStation& station);
    friend std::istream& operator>>(std::istream& in, BtsStation& station);
};

// Menu CRUD cua tram BTS duoc gop cung cap file voi lop BtsStation.
class BtsStationUseCase {
private:
    Repository<BtsStation>& stationRepository;
    Repository<Province>& provinceRepository;
    Repository<InstalledDevice>& deviceRepository;
    Repository<AntennaConfig>& antennaRepository;
    Repository<MaintenanceTicket>& maintenanceRepository;
    Repository<StationIncident>& incidentRepository;

    bool tramDangDuocSuDung(const std::string& maTram);

    void addStation();
    void showStations() const;
    void searchStation() const;
    void sortStations();
    void updateStation();
    void deleteStation();

public:
    BtsStationUseCase(
        Repository<BtsStation>& stationRepository,
        Repository<Province>& provinceRepository,
        Repository<InstalledDevice>& deviceRepository,
        Repository<AntennaConfig>& antennaRepository,
        Repository<MaintenanceTicket>& maintenanceRepository,
        Repository<StationIncident>& incidentRepository
    );

    void run();
};

#endif
