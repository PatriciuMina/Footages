#include "Footage.h"
#include <string>
#include <Windows.h>
#include <shellapi.h>

Footage::Footage() : title(""), section(""), dateOfCreation(""), accessCount(), footagePreview("") {}

Footage::Footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview)
{
	this->title = title;
	this->section = section;
	this->dateOfCreation = dateOfCreation;
	this->accessCount = accessCount;
	this->footagePreview = footagePreview;
}
std::string Footage::get_title() const
{
	return this->title;
}
std::string Footage::get_section() const
{
	return this->section;
}
std::string Footage::get_dateOfCreation() const
{
	return this->dateOfCreation;
}
int Footage::get_accessCount() const
{
	return this->accessCount;
}
std::string Footage::get_footagePreview() const
{
	return this->footagePreview;
}
string Footage::toString()
{
	return "Title:" + this->get_title() + ", Section: " + this->get_section() + ", Date of creation: " + this->get_dateOfCreation() + ", Access count: " + std::to_string(this->get_accessCount()) + ", Footage Preview: " + this->get_footagePreview();
}

void Footage::reset_footage()
{
	this->title = "";
	this->section = "";
	this->dateOfCreation = "";
	this->accessCount = 0;
	this->footagePreview = "";
}

vector<string> Footage::tokenize(const string& str, char separator)
{
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, separator))
		result.push_back(token);
	return result;
}

void Footage::set_title(string title)
{
	this->title = title;
}

void Footage::set_section(string section)
{
	this->section = section;

}

void Footage::set_dateOfCreation(string dateOfCreation)
{
	this->dateOfCreation = dateOfCreation;
}

void Footage::set_accessCount(int accessCount)
{
	this->accessCount = accessCount;
}

void Footage::set_footagePreview(string footagePreview)
{
	this->footagePreview = footagePreview;
}

std::string Footage::toHTML()
{
	string html_format;
	html_format = "<tr>\n<td>" + this->title + "</td>\n<td>" + this->section + "</td>\n<td>" + this->dateOfCreation + "</td>\n<td>" + std::to_string(this->accessCount) + "</td>\n<td>" + this->footagePreview + "</td>\n</tr";
	return html_format;
}

bool operator==(const Footage& f1, const Footage& f2)
{
	return
	{
		f1.get_title() == f2.get_title() &&
		f1.get_section() == f2.get_section() &&
		f1.get_dateOfCreation() == f2.get_dateOfCreation() &&
		f1.get_accessCount() == f2.get_accessCount() &&
		f1.get_footagePreview() == f2.get_footagePreview()
	};
}

istream& operator>>(istream& is, Footage& f)
{
	
	f.reset_footage();
	string line;
	getline(is, line);
	vector<string> tokens = f.tokenize(line, ',');
	if (tokens.size() != 5)
		return is;
	f.set_title(tokens.at(0));
	f.set_section(tokens.at(1));
	f.set_dateOfCreation(tokens.at(2));
	f.set_accessCount(stoi(tokens.at(3)));
	f.set_footagePreview(tokens.at(4));
	return is;
}

ostream& operator<<(ostream& os, const Footage& f)
{
	os << f.get_title() << "," << f.get_section() << "," << f.get_dateOfCreation() << "," << f.get_accessCount() << "," << f.get_footagePreview() << endl;
	return os;
}
