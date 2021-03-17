#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Footage
{
private:
	string title;
	string section;
	string dateOfCreation;
	int accessCount;
	string footagePreview;

public:
	//default constructor of the footage
	Footage();


	//"more complex" constructor where parameters are added
	Footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview);



	string get_title() const;
	string get_section() const;
	string get_dateOfCreation() const;
	int get_accessCount() const;
	string get_footagePreview() const;

	//returns all Footage data
	string toString();
	void reset_footage();
	vector<string>tokenize(const string& str, char separator);
	void set_title(string title);
	void set_section(string section);
	void set_dateOfCreation(string dateOfCreation);
	void set_accessCount(int accessCount);
	void set_footagePreview(string footagePreview);

	friend bool operator==(const Footage&, const Footage&);

	friend istream& operator>>(istream& is, Footage& f);
	friend ostream& operator<<(ostream& os, const Footage& f);

	std::string toHTML();




};