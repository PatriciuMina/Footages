#include "SavedFootages.h"
#include <string>
#include <fstream>
#include <Windows.h>


void SavedFootages::add(const Footage& f)
{
	cout << endl << "FOOTAGES SUCCESSFULLY SAVED" << endl << endl << endl;
	vector<Footage> savedFootages = this->load_file();;
	savedFootages.push_back(f);
	this->save_file(savedFootages);
}

std::vector<Footage> SavedFootages::get_all()
{
	vector<Footage> savedFootages = this->load_file();
	return savedFootages;
}

void SavedFootages::set_path(std::string path)
{
	this->path = path;
}

std::vector<Footage> CSVmylist::load_file()
{
	std::vector<Footage> footages;
	Footage f;
	ifstream file{ this->path };
	while (file >> f)
		footages.push_back(f);
	file.close();
	return footages;
}

void CSVmylist::save_file(std::vector<Footage> footages)
{
	ofstream file{ this->path };
	for (const auto& footage : footages)
		file << footage << endl;
	file.close();
}



void HTMLmylist::save_file(std::vector<Footage> footages)
{
	ofstream file{ this->path };
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>SAVED Footages</title>\n";
	file << "</head>\n<body style=\"background-color:#0099ff;\">\n<table border=\"1\"\n";

	file << "<tr>\n<td><b>Title</td></b>\n<td><b>Section</td></b>\n<td><b>DateOfCreation</td></b>\n<td><b>AccessCount</td></b>\n<td><b>FootagePreview</td></b>\n</tr>\n";

	for (auto footage : footages)
		file << footage.toHTML() << endl;

	file << "</table>\n</body>\n</html>";
	file.close();
}

std::vector<Footage> HTMLmylist::load_file()
{
	std::vector<Footage> savedFootages;
	string line;
	ifstream file{ this->path };
	string title, section, dateOfCreation, accessCount, footagePreview;

	for (int i = 0; i <= 13; i++)
		getline(file, line);

	getline(file, line); //<tr>
	while (line == "<tr>")
	{
		getline(file, line);
		title = line.substr(4, line.size() - 9);
		getline(file, line);
		section = line.substr(4, line.size() - 9);
		getline(file, line);
		dateOfCreation = line.substr(4, line.size() - 9);
		getline(file, line);
		accessCount = line.substr(4, line.size() - 9);
		getline(file, line);
		footagePreview = line.substr(4, line.size() - 9);

		Footage f{ title,section,dateOfCreation,stoi(accessCount),footagePreview };
		savedFootages.push_back(f);

		getline(file, line); //</tr>
		getline(file, line); //<tr>
	}
	file.close();
	return savedFootages;
}
