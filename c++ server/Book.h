#pragma once
#include <vector>
#include <string>
#include "RFIDObject.h"
#include <iostream>

typedef std::string string;

class Book : public RFIDObject{
public:

	~Book() = default;

	Book():RFIDObject(){}

	Book(string rfid) :
		RFIDObject(rfid), x(0), y(0), num_of_locations(0){}

	//setters
	/*
	@parameters:there is no restrictions on the values x and y.
	@return: new average location.
	*/
	
	bool insertLocation(double new_x, double new_y) {
		double sum_x = x * num_of_locations;
		double sum_y = y * num_of_locations;
		sum_x += new_x;
		sum_y += new_y;
		num_of_locations++;
		x = sum_x / num_of_locations;
		y = sum_y / num_of_locations;
		return true;
	}
	
	//getters
	double getX(){
		return x;
	}

	double getY() {
		return y;
	}

	string getRfid() {
		return rfid;
	}

	void resetNumOfLocationsToZero(){
	    this->num_of_locations = 0;
	}

	//inner methods
	std::ostream& print(std::ostream& os) const {
		os << "X location: " << x << std::endl;
		os << "Y location: " << y << std::endl;
		return os;
	}

private:
	//average location
	double x;
	double y;
	//number of locations
	int num_of_locations;
};


std::ostream& operator<<(std::ostream& os, Book& book) {
	return book.print(os);
}
