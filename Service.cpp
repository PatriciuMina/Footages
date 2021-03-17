#include"Service.h"
#include <iostream>
#include "FileRepository.h"
#include "Validator.h"
using namespace std;

vector<Footage> Service::get_all_footages()
{
	return repository.get_footages();
}

int Service::check_existing(const std::string& title)
{
	vector<Footage> footages = this->get_all_footages();
	for (const auto& footage : footages)
	{
		if (footage.get_title() == title)
			return 1;
	}
	return 0;
}

int Service::service_add_footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview)
{
	int ok = 0;
	Footage f{ title, section, dateOfCreation, accessCount, footagePreview };
	try {
		FootageValidator::validate(f);
	}
	catch (ValidationException& ex)
	{
		ok = 1;
		cout << ex.getMessage() << endl;

	}
	if (this->check_existing(title) == 0 && ok == 0)
	{
		this->repository.add_footage(f);
		return 1;
	}
	return 0;
}

int Service::service_update_footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview)
{
	int ok = 0;
	Footage f{ title, section, dateOfCreation, accessCount, footagePreview };
	try {
		FootageValidator::validate(f);
	}
	catch (ValidationException& ex)
	{
		ok = 1;
		cout << ex.getMessage() << endl;

	}
	if (this->check_existing(title) == 1 && ok == 0)
	{
		this->repository.update_footage(f);
		return 1;
	}
	return 0;
}

int Service::service_delete_footage(const std::string& title)
{
	if (this->check_existing(title))
	{
		this->repository.delete_footage(title);
		return 1;
	}
	return 0;
}

vector<Footage> Service::service_filter_section(const std::string& section, int accessCount)
{
	vector<Footage> filterFootages;
	vector<Footage> footages = this->get_all_footages();
	for (const auto& f : footages)
	{
		if (f.get_section() == section && f.get_accessCount() < accessCount)
			filterFootages.push_back(f);
	}

	return filterFootages;

}

void Service::save(std::string title)
{
	int aux;
	aux = check_existing(title);
	if (aux == 1)
	{
		Footage f = repository.get_by_title(title);
		repositoryLowLevel.add_footages(f);
	}
	else if (aux == 0)
	{
		cout << "the title is inexistent" << '\n';
	}

}

vector<Footage> Service::LowLevelList()
{
	vector<Footage> footages = this->repositoryLowLevel.get_lowlevel();
	return footages;
}

Footage Service::next_Footage()
{
	Footage f = this->repository.getFootage();
	this->repository.nextFootage();
	return f;
}

void Service::file_location(string Path)
{
	this->repository.set_file(Path);
}

void Service::set_mylist_location(std::string path)
{
	string extension = path.substr(path.size() - 4);


	if (extension == ".csv")
	{
		this->saved_footages = new CSVmylist{};
	}
	else if (extension == "html")
	{
		this->saved_footages = new HTMLmylist{};
	}
	
	this->saved_footages->set_path(path);
}

