#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>

class GUI :
	public QWidget
{
private:
	Service& serv;

	// graphical elements 
	QListWidget* footageListWidget;
	QLineEdit* titleLineEdit;
	QLineEdit* sectionLineEdit;
	QLineEdit* dateOfCreationLineEdit;
	QLineEdit* accessCountLineEdit;
	QLineEdit* footagePreviewLineEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QListWidget* savedFootagesListWidget;

public:
	GUI(Service& s);

private:
	void initGUI();

	void populateFootages();

	void connectSignalsandSlots();

	int getSelectedIndex() const;

	void addFootage();

	void deleteFootage();

	void updateFootage();

};

