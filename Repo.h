#pragma once
#include "Footage.h"
#include <vector>
#include <iostream>
using namespace std;

class Repository
{
private:

	vector<Footage> footages;
	std::string filename;
	


public:

	//initialize repository
	Repository();

	/*
	Add a new footage to repo
		input: f (footage)
		output: -
	*/
	void add_footage(Footage& f);

	/*
	Update a footage
		input: footage
		output: the updated footage
	*/
	void update_footage(Footage& f);

	/*
	Deletes a footage
		input: title of the footage
		output: the array without the deleted footage
	*/
	void delete_footage(const std::string& title);

	//returns all the footages
	vector<Footage> get_footages();

	bool validate_title(const Footage f, const std::string& title);

	int get_size(vector<Footage> repository);

	Footage get_footage_title(std::string title);
	Footage get_footage_section(std::string section);
	Footage next();

	void initializeIterator();

private:
	void readFromFile();
	void writeToFile();
};

class RepositoryLowLevel
{
private:
	vector<Footage> footagesLowLevel;
public:
	RepositoryLowLevel();
	void add_footages(Footage& f);
	vector<Footage> get_lowlevel();


};