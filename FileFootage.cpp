#include "FileFootage.h"

FileFootage::FileFootage() : Footage{}, filename{ "" }
{

}

void FileFootage::setFileName(const std::string& filename)
{
	this->filename = filename;
}