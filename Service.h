#pragma once
#include "Repo.h"
#include "FileRepository.h"
#include "SavedFootages.h"
#include "FileFootage.h"
class Service
{
private:
	FileRepo repository;
	FileFootage* footage;
	RepositoryLowLevel repositoryLowLevel;
	vector<Footage> footages;
	SavedFootages* saved_footages;
public:
	//initializes the service by the repository 
	Service(const FileRepo& r) :repository{ r } { this->saved_footages = nullptr; }

	/*
	returns all the footages
	*/
	vector<Footage> get_all_footages();

	/*
	Adds a footage if it doesn't already exist.
		input: title, section, dateOfCreation, footagePreview string
				 accessCount -int
		output: 1- if the footage has been added successfully
				0-  if the footage hasn't been added successfully
	*/
	int service_add_footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview);

	/*
	Updates a valid footage
		input: title, section, dateOfCreation, footagePreview string
				 accessCount -int
		output: 1- if the footage has been updated successfully
				0-  if the footage hasn't been updated successfully
	*/
	int service_update_footage(const std::string& title, const std::string& section, const std::string& dateOfCreation, const int accessCount, const std::string& footagePreview);

	/*
	Delete a valid footage
		input: title- string
		output: 1- if the footage is deleted
				0- if the footage is not deleted
	*/
	int service_delete_footage(const std::string& title);


	/*
	Checks the existence of the title of the footage in the dynamic vector
			input: title- string
			output: 1- if the title exists
					0- otherwise
	*/
	int check_existing(const std::string& title);

	// return all the section filtered by section and number of accesses
	vector<Footage> service_filter_section(const std::string& section, int accessCount);


	// Save a footage
	void save(std::string title);
	//Return the list for the low level clearance
	vector<Footage> LowLevelList();

	Footage next_Footage();

	void file_location(string Path);

	void set_mylist_location(std::string path);

	/*Footage service_next();*/



};