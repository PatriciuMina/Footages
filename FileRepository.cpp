#include "FileRepository.h"
#include "Validator.h"
#include<string>
#include<iostream>

using namespace std;



vector<Footage> FileRepo::load_footages()
{
	ifstream file{ this->Path };
	vector<Footage> footages;
	Footage f;
	while (file >> f)
		footages.push_back(f);
	file.close();
	return footages;
}
void FileRepo::save_footages(vector<Footage> footages)
{
	ofstream file{ this->Path };
	for (const auto& footage : footages)
		file << footage;
	file.close();
}

FileRepo::FileRepo(){}

void FileRepo::add_footage(Footage& f)
{
	vector<Footage>footages = this->load_footages();
	footages.push_back(f);
	this->save_footages(footages);
}

void FileRepo::update_footage(Footage& f)
{
	int ok = 0;
	vector<Footage>footages = this->load_footages();
	for (int i = 0; i < footages.size(); i++)
		if (footages.at(i).get_title() == f.get_title())
		{
			footages.at(i) = f;
			ok = 1;
		}
	if (ok == 0)
		throw RepoException("There is no such footage\n");
	this->save_footages(footages);
}

void FileRepo::delete_footage(const string& title)
{
	int ok = 0;
	vector<Footage>footages = this->load_footages();
	for (int i = 0; i < footages.size(); i++)
		if (footages.at(i).get_title() == title)
		{
			footages.erase(footages.begin() + i);
			ok = 1;
		}
	if (ok == 0)
		throw RepoException("There is no such footage\n");
	this->save_footages(footages);
}

vector<Footage> FileRepo::get_footages()
{
	vector<Footage>footages = this->load_footages();
	return footages;
}

Footage FileRepo::get_by_title(string title)
{
	vector<Footage>footages = this->load_footages();
	for (const auto& footage : footages)
		if (footage.get_title() == title)
			return footage;
}




void FileRepo::set_file(string& path)
{
	this->Path = path;
}

int FileRepo::getPositionFootage(const Footage& f)
{
	vector<Footage> footages = this->load_footages();
	vector<Footage>::iterator iteratorFootages;
	iteratorFootages = find(footages.begin(), footages.end(), f);

	int index = distance(footages.begin(), iteratorFootages);
	return index;
}

int FileRepo::getRepoSize()
{
	std::vector<Footage> footages = this->load_footages();
	return footages.size();
}


Footage FileRepo::getFootage()
{
	std::vector<Footage> footages = this->load_footages();
	return footages[this->iteratorIndex];
}



void FileRepo::nextFootage()
{
	this->iteratorIndex++;
	if (this->iteratorIndex == this->getRepoSize())
		this->iteratorIndex = 0;
}


bool FileRepo::validate_title(const Footage f, const std::string& title)
{
	if (f.get_title() == title)
		return true;
	return false;
}

