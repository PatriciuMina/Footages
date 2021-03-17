#pragma once
#include "Footage.h"

class FileFootage : public Footage
{
protected:
	std::string filename;
public:
	FileFootage();
	virtual ~FileFootage() {}
	void setFileName(const std::string& filename);
	virtual void writeToFile() = 0;
	virtual void displayPlaylist() const = 0;

};