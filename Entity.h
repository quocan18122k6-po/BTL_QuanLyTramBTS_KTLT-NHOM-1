#pragma once

#include <iostream>
#include <string>
#include <stdexcept>


class Entity {
protected:
    std::string id;
public:
    Entity() {
        id = "";
    }
    explicit Entity(const std::string &id) {   //Ngăn chặn tự động ép kiểu string sang Entity
        this->id = id;
     }
    virtual ~Entity() = default;
    virtual std::string getId() const {
        return id;
    }
    virtual void setId(const std::string &newId) {
        if (newId.empty()) {
            throw std::invalid_argument("Loi: Ma dinh danh khong duoc de trong");
        }
        id = newId;
    }
    virtual void input() = 0;
    virtual void display() const = 0;
    virtual void displayRow() const = 0;
    virtual std::string toString() const = 0;
    virtual void fromString(const std::string &line) = 0;
    virtual void updateInfo() = 0;
};
// Cho phép Repository ghi đối tượng ra file qua p.toString()
inline std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os << entity.toString();
    return os;
}

// Cho phép Repository đọc từng dòng trong file nạp vào p.fromString(line)
inline std::istream& operator>>(std::istream& is, Entity& entity) {
    std::string line;
    if (std::getline(is, line) && !line.empty()) {
        entity.fromString(line);
    }
    return is;
}