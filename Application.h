#pragma once
#include <iostream>
#include <string>
class Application {
private:
	void menu();
	void tramVaKhuVuc();
	void thietBi();
	void baoTri();
	void suCoVaAnten();
public:
	Application() {};
	~Application() {};
	void run();
};
