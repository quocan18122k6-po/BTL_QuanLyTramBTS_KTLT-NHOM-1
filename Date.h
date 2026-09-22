#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>

class Date {
    private:
        int day;
        int month;
        int year;
    
    public:
        Date(){
            day = 1;
            month = 1;
            year = 2000;
        }
        Date(int d, int m, int y){
            this->day = d;
            this->month = m;
            this->year = y;
        }
        static bool isLeapYear(int year){
            if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
                return true;
            }
            else{
                return false;
            }
        }
        static bool isValid(int d, int m, int y){
            if(y < 1900 || y > 2100){
                return false;
            }
            if(m < 1 || m > 12){
                return false;
            }
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(isLeapYear(y) && m == 2){
                daysInMonth[1] = 29;
            }
            if(d < 1 || d > daysInMonth[m - 1]){
                return false;
            }
            return true;
        }
        bool fromString(const std::string& str){
            std::stringstream ss(str);
            int d, m, y;
            char sep1, sep2;
            if(ss >> d >> sep1 >> m >> sep2 >> y){
                if((sep1 == '/' || sep1 =='-') && (sep2 == '/' || sep2 =='-')){
                    if(isValid(d, m, y)){
                        this->day = d;
                        this->month = m;
                        this->year = y;
                        return true;
                    }
                }
            }
            return false;
        }
        std::string toString() const {
            return (day < 10 ? "0" : "") + std::to_string(day) + "/" + (month < 10 ? "0" : "") + std::to_string(month) + "/" + std::to_string(year);
        }
        int getDay() const { return day; }
        int getMonth() const { return month; }
        int getYear() const { return year; }
};
#endif // DATE_H