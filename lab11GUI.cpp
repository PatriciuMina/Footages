#include "lab11GUI.h"
#include "qmessagebox.h"

using namespace std;

lab11GUI::lab11GUI(Service& s, QWidget* parent)
	: QMainWindow(parent), serv{ s }
{
	ui.setupUi(this);
	this->populateList();
	this->populateSaved();
	this->getSelectedIndexS();
	this->connectSignalsAndSlots();
	this->connectSignalsAndSlotsS();
	
}

void lab11GUI::populateList()
{
	

	this->ui.footageListWidget->setStyleSheet("background-color:#ffffff;");
	QFont serifFont("Times", 14);

	this->ui.footageListWidget->setFont(serifFont);

	this->ui.footageListWidget->clear();

	vector<Footage> footages = this->serv.get_all_footages();
	for (Footage& f : footages)
		this->ui.footageListWidget->addItem(QString::fromStdString(f.get_title() + " - " + f.get_section()));

}

int lab11GUI::getSelectedIndexS() const
{

	QModelIndexList selectedIndexes = this->ui.footageListWidget_2->selectionModel()->selectedIndexes();

	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit_2->clear();
		this->ui.sectionLineEdit_2->clear();
		this->ui.dateOfCreationLineEdit_2->clear();
		this->ui.accessCountLineEdit_2->clear();
		this->ui.footagePreviewLineEdit_2->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();

	return selectedIndex;

}

int lab11GUI::getSelectedIndex() const
{

	QModelIndexList selectedIndexes = this->ui.footageListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.sectionLineEdit->clear();
		this->ui.dateOfCreationLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;


}

int lab11GUI::getSelectedIndexF() const
{
	QModelIndexList selectedIndexes = this->ui.footageListWidget_2->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.sectionLineEdit->clear();
		this->ui.dateOfCreationLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;


}

void lab11GUI::nextFootage_gui()
{
	this->ui.footageListWidget_2->clear();
	Footage f = this->serv.next_Footage();
	this->ui.footageListWidget_2->addItem(QString::fromStdString(f.get_title() + " - " + f.get_section() + " - " + f.get_dateOfCreation() + " - " + to_string(f.get_accessCount()) + " - " + f.get_footagePreview()));
	this->ui.titleLineEdit_2->setText(QString::fromStdString(f.get_title()));
	this->ui.sectionLineEdit_2->setText(QString::fromStdString(f.get_section()));
	this->ui.dateOfCreationLineEdit_2->setText(QString::fromStdString(f.get_dateOfCreation()));
	this->ui.accessCountLineEdit_2->setText(QString::fromStdString(to_string(f.get_accessCount())));
	this->ui.footagePreviewLineEdit_2->setText(QString::fromStdString(f.get_footagePreview()));

}


void lab11GUI::deleteFootage()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Not deleted!", "No footage was selected!");
		return;
	}
	Footage f = this->serv.get_all_footages()[selectedIndex];
	this->serv.service_delete_footage(f.get_title());

	QMessageBox::information(this, "Deleted!", "The footage was deleted");

	this->populateList();

	int lastElement = this->serv.get_all_footages().size() - 1;

	this->ui.footageListWidget->setCurrentRow(lastElement);

}

void lab11GUI::connectSignalsAndSlotsS()
{
	QObject::connect(this->ui.footageListWidget_2, &QListWidget::itemSelectionChanged, [this]() {

		int selectedIndex = this->getSelectedIndexS();

		if (selectedIndex < 0)
			return;
		if (this->serv.LowLevelList().size() == 0)
			return;

		Footage f = this->serv.LowLevelList()[selectedIndex];
		this->ui.titleLineEdit_2->setText(QString::fromStdString(f.get_title()));
		this->ui.sectionLineEdit_2->setText(QString::fromStdString(f.get_section()));
		this->ui.dateOfCreationLineEdit_2->setText(QString::fromStdString(f.get_dateOfCreation()));
		this->ui.accessCountLineEdit_2->setText(QString::fromStdString(to_string(f.get_accessCount())));
		this->ui.footagePreviewLineEdit_2->setText(QString::fromStdString(f.get_footagePreview()));
		});
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &lab11GUI::saveByTitle);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &lab11GUI::filterByType);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &lab11GUI::nextFootage_gui);
}

void lab11GUI::connectSignalsAndSlots()
{
	QObject::connect(this->ui.footageListWidget, &QListWidget::itemSelectionChanged, [this]() {

		int selectedIndex = this->getSelectedIndex();

		if (selectedIndex < 0)
			return;
		Footage f = this->serv.get_all_footages()[selectedIndex];
		this->ui.titleLineEdit->setText(QString::fromStdString(f.get_title()));
		this->ui.sectionLineEdit->setText(QString::fromStdString(f.get_section()));
		this->ui.dateOfCreationLineEdit->setText(QString::fromStdString(f.get_dateOfCreation()));
		this->ui.accessCountLineEdit->setText(QString::fromStdString(to_string(f.get_accessCount())));
		this->ui.footagePreviewLineEdit->setText(QString::fromStdString(f.get_footagePreview()));

		});
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &lab11GUI::deleteFootage);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &lab11GUI::addFootage);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &lab11GUI::updateFootage);
	
}


void lab11GUI::addFootage()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string section = this->ui.sectionLineEdit->text().toStdString();
	string dateOfCreation = this->ui.dateOfCreationLineEdit->text().toStdString();
	string accessCount = this->ui.accessCountLineEdit->text().toStdString();
	string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();
	


	if (serv.check_existing(title) == 1)
	{
		QMessageBox::information(this, "Duplciate!", "The footage already exists");
	}
	else if (title.size() == 0)
	{
		QMessageBox::information(this, "No title!", "Please enter a valid title");
	}
	else {
		this->serv.service_add_footage(title, section, dateOfCreation, stoi(accessCount), footagePreview);

		QMessageBox::information(this, "Added!", "The footage was added");

		this->populateList();

		int lastElement = this->serv.get_all_footages().size() - 1;

		this->ui.footageListWidget->setCurrentRow(lastElement);
	}
}


void lab11GUI::updateFootage()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string section = this->ui.sectionLineEdit->text().toStdString();
	string dateOfCreation = this->ui.dateOfCreationLineEdit->text().toStdString();
	string accessCount = this->ui.accessCountLineEdit->text().toStdString();
	string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();

	if (this->serv.check_existing(title) == 0)
	{
		QMessageBox::information(this, "Not updated!", "The footage doesn't exist");
	}
	else {
		this->serv.service_update_footage(title, section, dateOfCreation, stoi(accessCount), footagePreview);

		QMessageBox* updateBox;

		updateBox->information(this, "Updated!", "The footage was updated");

		this->populateList();

		int lastElement = this->serv.get_all_footages().size() - 1;

		this->ui.footageListWidget->setCurrentRow(lastElement);
	}
}


void lab11GUI::populateSaved()
{

	

	this->ui.footageListWidget_2->setStyleSheet("background-color:#ffffff;");
	QFont serifFont("Times", 14);

	this->ui.footageListWidget_2->setFont(serifFont);

	this->ui.footageListWidget_2->clear();

	
	
	vector<Footage> footages = this->serv.LowLevelList();
	for (Footage& f : footages)
		this->ui.footageListWidget_2->addItem(QString::fromStdString(f.get_title() + " - " + f.get_section()));

}

void lab11GUI::saveByTitle()
{
	int ok = 1;
	if (this->ui.titleLineEdit_2->text().size() == 0)
	{
		ok = 0;
		QMessageBox::information(this, "Not saved", "Not enough information");
	}
	if (ok == 1) {
		string title = this->ui.titleLineEdit_2->text().toStdString();
		if (this->serv.check_existing(title) == 0)
		{
			QMessageBox::information(this, "Not saved", "Title doesn't exist");
		}
		else
		{
			this->serv.save(title);

			QMessageBox::information(this, "Saved!", "The footage was saved");

			this->populateSaved();

			int lastElement = this->serv.LowLevelList().size() - 1;

			this->ui.footageListWidget_2->setCurrentRow(lastElement);
		}
	}
}

void lab11GUI::filterByType()
{
	int ok = 1;
	int index = 0;
	string section = this->ui.sectionLineEdit_2->text().toStdString();
	string filterrr;
	if (this->ui.accessCountLineEdit_2->text().size() == 0 || this->ui.sectionLineEdit_2->text().size() == 0)
	{
		ok = 0;
		QMessageBox::information(this, "Not filtered!", "There wasn't enough information added");
	}
	string accessCount = this->ui.accessCountLineEdit_2->text().toStdString();
	
	if (ok == 1) {
		vector<Footage> filtered = this->serv.service_filter_section(section, stoi(accessCount));



		if (filtered.size() == 0)
		{
			QMessageBox::information(this, "Not filtered!", "There were not any chores matching");
		}
		else
		{
			//QMessageBox::information(this, "Filtered!", "There were some chores matching");
			this->ui.footageListWidget_2->setStyleSheet("background-color:#ffffff;");
			QFont serifFont("Times", 14);

			this->ui.footageListWidget_2->setFont(serifFont);

			this->ui.footageListWidget_2->clear();

			for (Footage& f : filtered)
			{
				index++;
				filterrr += to_string(index) + ". " + "Title: " + f.get_title() + "\n Section: " + f.get_section() + "\nDate Of Creation: " + f.get_dateOfCreation() + "\n Access Count: " + to_string(f.get_accessCount()) + "\n Footage Preview: " + f.get_footagePreview() + '\n';

			}

			QMessageBox::information(this, "Filtered!", QString::fromStdString(filterrr));

			//this->ui.savedCList->setCurrentRow(index-1);

		}

	}
}


