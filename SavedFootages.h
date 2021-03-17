#pragma once
#include "Footage.h"
#include <vector> 

class SavedFootages
{
protected:
	std::string path;
public:
	void add(const Footage& f);

	std::vector<Footage> get_all();

	void set_path(std::string path);

	virtual void save_file(std::vector<Footage> footages) {};
	virtual std::vector<Footage> load_file() { return std::vector<Footage>(); };

	virtual void open_file() {  };

};

class CSVmylist : public SavedFootages
{
public:
	void save_file(std::vector<Footage> footages)override;
	std::vector<Footage> load_file() override;

};

class HTMLmylist : public SavedFootages
{
public:
	void save_file(std::vector<Footage> footages)override;
	std::vector<Footage> load_file() override;
	
};