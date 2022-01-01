#pragma once
#include <string>

typedef std::string string;

class RFIDObject
{
public:
	RFIDObject(string rfid) : rfid(rfid) {}
	RFIDObject() = default;
	virtual ~RFIDObject() = default;

	string getRfid() {
		return rfid;
	}

protected:
	string rfid;
};
