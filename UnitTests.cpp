using namespace std;
#include<assert.h>
#include "UnitTests.h"
#include "Footage.h"
// #include "DynamicVector.h"
#include "Repo.h"
#include "Service.h"
#include "FileRepository.h"
#include<iostream>
#include<crtdbg.h>

void testChores()
{
	Footage newFootage{ "Title", "section", "12-12-1212", 1, "prev" };
	assert(newFootage.get_title() == "Title");
	assert(newFootage.get_section() == "section");
	assert(newFootage.get_dateOfCreation() == "12-12-1212");
	assert(newFootage.get_accessCount() == 1);
	assert(newFootage.get_footagePreview() == "prev");
}

void testAdd()
{
	string textFile = "history.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	//assert(service.addChore_service(title, type, lastPerformed, timesPerformed, vision) == 1);
	string title2 = "a", type2 = "b", lastPerformed2 = "c", vision2 = "d";
	int timesPerformed2 = 1;
	//assert(service.addChore_service(title2, type2, lastPerformed2, timesPerformed2, vision2) == 0);
	remove("history.txt");
}

void testUpdate()
{
	string textFile = "history.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	assert(service.service_add_footage(title, type, lastPerformed, timesPerformed, vision) == 1);
	int timesPerformed2 = 2;
	string typeUpdate = "c", lastPerformedUpd = "d", visionUpd = "e";
	string invalidTitle = "p";
	assert(service.service_update_footage(title, typeUpdate, lastPerformedUpd, timesPerformed2, visionUpd) == 1);
	assert(service.service_update_footage(invalidTitle, type, lastPerformed, timesPerformed, vision) == 0);
	remove("history.txt");
}

void testDelete()
{
	string textFile = "history.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	assert(service.service_add_footage(title, type, lastPerformed, timesPerformed, vision) == 1);
	string titleDelete = "a";
	assert(service.service_delete_footage(titleDelete) == 1);
	string title2 = "c";
	assert(service.service_add_footage(title2, type, lastPerformed, timesPerformed, vision) == 1);
	assert(service.service_delete_footage(titleDelete) == 0);
	remove("history.txt");
}

//void testSave()
//{
//
//	string textFile = "history.txt";
//	FileRepo repo{};
//	Service service{ repo };
//	service.file_location(textFile);
//	string title = "a", section = "b", dateOfCreation = "c", Preview = "d";
//	int accesCount = 1;
//	assert(service.service_add_footage(title, section, dateOfCreation, accesCount, Preview) == 1);
//	service.save(title);
//	assert(service.LowLevelList().size() == 1);
//	remove("history.txt");
//
//}
void testToString()
{
	Footage f{ "a","b","c",1,"d" };
	string toString = "Title:a, Section: b, Date of creation: c, Access count: 1, Footage Preview: d";
	assert(f.toString() == toString);
}

void tests()
{
	testChores();
	testAdd();
	testDelete();
	testUpdate();
	/*testSave();*/
	testToString();
}