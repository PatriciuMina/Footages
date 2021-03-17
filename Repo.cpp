#include"Repo.h"
#include<string>

using namespace std;
Repository::Repository()
{
	this->footages = footages;
}

void Repository::add_footage(Footage& f)
{
	footages.push_back(f);
}

void Repository::update_footage(Footage& f)
{

	for (int i = 0; i < footages.size(); i++)
	{
		if (footages.at(i).get_title() == f.get_title())
			this->footages.at(i) = f;
	}
}

void Repository::delete_footage(const std::string& title)
{

	for (int i = 0; i < footages.size(); i++)
	{
		if (footages.at(i).get_title() == title)
			footages.erase(footages.begin() + i);
	}
}

vector<Footage> Repository::get_footages()
{
	return this->footages;
}

bool Repository::validate_title(const Footage f, const std::string& title)
{
	if (f.get_title() == title)
		return true;
	return false;
}

int Repository::get_size(vector<Footage> repository)
{
	return repository.size();
}
RepositoryLowLevel::RepositoryLowLevel()
{
	this->footagesLowLevel = footagesLowLevel;
}
void RepositoryLowLevel::add_footages(Footage& f)
{
	footagesLowLevel.push_back(f);
}
vector<Footage> RepositoryLowLevel::get_lowlevel()
{
	return this->footagesLowLevel;
}

Footage Repository::get_footage_title(std::string title)
{
	for (const auto& footage : footages)
	{
		if (footage.get_title() == title)
		{
			return footage;
		}
	}
}
Footage Repository::get_footage_section(std::string section)
{
	for (const auto& footage : footages)
	{
		if (footage.get_section() == section)
		{
			return footage;
		}
	}
}

void Repository::readFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		cout << "File couldn't be opened";
	else
	{
		Footage f;
		while (file >> f)
			this->footages.push_back(f);
		file.close();
	}

}
void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		cout << "File couldn't be opened";
	else
	{
		for (auto f : this->footages)
		{
			file << f;
		}
		file.close();
	}
}