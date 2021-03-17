#pragma once
#include "Footage.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class FileRepo
{
private:
	string Path;
	vector<Footage> next_footages;
	vector<Footage>::iterator it;
	int iteratorIndex = 0;

	void save_footages(vector<Footage>footages);
public:
	FileRepo();
	void add_footage(Footage& f);
	void update_footage(Footage& f);
	void delete_footage(const string& title);
	vector<Footage>get_footages();
	void initializeIterator();
	Footage get_by_title(string title);
	Footage getFootage();
	int getPositionFootage(const Footage& f);
	void nextFootage();
	int getRepoSize();
	
	void set_file(string& path);
	vector<Footage> load_footages();
	bool validate_title(const Footage f, const std::string& title);
};