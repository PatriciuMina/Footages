#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include "Footage.h"
#include <vector>
#include <qmessagebox.h>
#include <qicon.h>
#include <qmainwindow.h>
#include <qpalette.h>
#include <qstring>
#include <qlabel.h>
using namespace std;

GUI::GUI(Service& s) :serv{ s }
{
	this->initGUI();
	this->populateFootages();
	this->connectSignalsandSlots();
}

void GUI::initGUI()
{
	this->footageListWidget = new QListWidget{};
	this->titleLineEdit = new QLineEdit{};
	this->sectionLineEdit = new QLineEdit{};
	this->dateOfCreationLineEdit = new QLineEdit{};
	this->accessCountLineEdit = new QLineEdit{};
	this->footagePreviewLineEdit = new QLineEdit{};
	this->addButton = new QPushButton{ "add footage" };
	this->deleteButton = new QPushButton{ "delete footage" };
	this->updateButton = new QPushButton{ "update footage" };



	
	addButton->setStyleSheet("background-color:#ffffff;");
	QFont serifFont("Times", 16, QFont::Bold);
	addButton->setFont(serifFont);

	
	updateButton->setStyleSheet("background-color:#ffffff;");
	updateButton->setFont(serifFont);
	
	deleteButton->setStyleSheet("background-color:#ffffff;");
	deleteButton->setFont(serifFont);
	QLabel* label = new QLabel{ "FOOTAGE LIST" };

	label->setAlignment(Qt::AlignCenter);

	label->setFont(serifFont);

	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	mainLayout->addWidget(label);

	mainLayout->addWidget(this->footageListWidget);

	QFormLayout* footageDetails = new QFormLayout{ this };

	QLabel* label2 = new QLabel{ "FOOTAGE DETAILS" };

	label2->setAlignment(Qt::AlignCenter);
	QFont anotherType("Times", 14, QFont::Bold);

	anotherType.setItalic(true);

	label2->setFont(anotherType);

	mainLayout->addWidget(label2);

	footageDetails->addRow("Title", this->titleLineEdit);
	footageDetails->addRow("Section", this->sectionLineEdit);
	footageDetails->addRow("Date Of Creation", this->dateOfCreationLineEdit);
	footageDetails->addRow("Access Count", this->accessCountLineEdit);
	footageDetails->addRow("Footage Preview", this->footagePreviewLineEdit);

	mainLayout->addLayout(footageDetails);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);

	mainLayout->addLayout(buttonsLayout);

	QGridLayout* buttonsLayout2 = new QGridLayout{};
	buttonsLayout2->addWidget(this->updateButton, 0, 0);

	mainLayout->addLayout(buttonsLayout2);

}

void GUI::populateFootages()
{
	this->footageListWidget->setStyleSheet("background-color:#ffffff;");
	QFont serifFont("Times", 14);

	this->footageListWidget->setFont(serifFont);

	this->footageListWidget->clear();

	vector<Footage> footages = this->serv.get_all_footages();
	for (Footage& f : footages)
		this->footageListWidget->addItem(QString::fromStdString(f.get_title() + " - " + f.get_section() + " - " + f.get_dateOfCreation() + " - " + to_string(f.get_accessCount()) + " - " + f.get_footagePreview()));

}

void GUI::connectSignalsandSlots()
{
	QObject::connect(this->footageListWidget, &QListWidget::itemSelectionChanged, [this]() {

		int selectedIndex = this->getSelectedIndex();

		if (selectedIndex < 0)
			return;
		Footage f = this->serv.get_all_footages()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(f.get_title()));
		this->sectionLineEdit->setText(QString::fromStdString(f.get_section()));
		this->dateOfCreationLineEdit->setText(QString::fromStdString(f.get_dateOfCreation()));
		this->accessCountLineEdit->setText(QString::fromStdString(to_string(f.get_accessCount())));
		this->footagePreviewLineEdit->setText(QString::fromStdString(f.get_footagePreview()));

		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addFootage);

	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteFootage);

	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateFootage);

}

int GUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->footageListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		this->sectionLineEdit->clear();
		this->dateOfCreationLineEdit->clear();
		this->accessCountLineEdit->clear();
		this->footagePreviewLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;


}

void GUI::addFootage()
{
	string title = this->titleLineEdit->text().toStdString();
	string type = this->sectionLineEdit->text().toStdString();
	string lastPerformed = this->dateOfCreationLineEdit->text().toStdString();
	string timesPerformed = this->accessCountLineEdit->text().toStdString();
	string vision = this->footagePreviewLineEdit->text().toStdString();

	if (serv.check_existing(title) == 1)
	{
		QMessageBox::information(this, "Duplicate!", "The footage is already here");
	}
	else if (title.size() == 0)
	{
		QMessageBox::information(this, "No title!", "Please enter a valid title");
	}
	else {
		this->serv.service_add_footage(title, type, lastPerformed, stoi(timesPerformed), vision);

		QMessageBox::information(this, "Added!", "The footage was added");

		this->populateFootages();

		int lastElement = this->serv.get_all_footages().size() - 1;

		this->footageListWidget->setCurrentRow(lastElement);
	}
}

void GUI::deleteFootage()
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

	this->populateFootages();

	int lastElement = this->serv.get_all_footages().size() - 1;

	this->footageListWidget->setCurrentRow(lastElement);
}

void GUI::updateFootage()
{
	string title = this->titleLineEdit->text().toStdString();
	string type = this->sectionLineEdit->text().toStdString();
	string lastPerformed = this->dateOfCreationLineEdit->text().toStdString();
	string timesPerformed = this->accessCountLineEdit->text().toStdString();
	string vision = this->footagePreviewLineEdit->text().toStdString();

	if (this->serv.check_existing(title) == 0)
	{
		QMessageBox::information(this, "Not updated!", "The footage doesn't exist");
	}
	else {
		this->serv.service_update_footage(title, type, lastPerformed, stoi(timesPerformed), vision);

		QMessageBox* updateBox;

		updateBox->information(this, "Updated!", "The footage was updated");

		this->populateFootages();

		int lastElement = this->serv.get_all_footages().size() - 1;

		this->footageListWidget->setCurrentRow(lastElement);
	}
}

