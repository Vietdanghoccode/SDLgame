#pragma once

#include <iostream>
#include <string>

class LogStatus {
private:
	std::string area = "";
public:
	LogStatus() {};
	LogStatus(std::string p_area) {
		area = p_area;
	};
	void Status(const std::string msg) {
		std::cout << area << ":" << msg << std::endl;
	};
};