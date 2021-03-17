#include "Validator.h"

using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{

}

std::string ValidationException::getMessage() const
{
	return this->message;
}

void FootageValidator::validate(const Footage& f)
{
	string errors;
	FileRepo repo;
	Service service{ repo };

	vector<Footage> footages = repo.get_footages();

	if (f.get_title().size() < 1)
		errors += string("The title name cannot be less than 1 character!\n");
	if (f.get_footagePreview().size() < 1)
		errors += string("The footage preview cannot be less than 1 character!\n");
	if (f.get_dateOfCreation().size() < 1)
		errors += string("The <date of creation> cannot be less than 1 character\n");
	if (f.get_section().size() <= 0)
		errors += string("The <section> cannot be empty\n");
	if (f.get_accessCount() < 0)
		errors += string("The <access Count> cannot be negative\n");
	if (errors.size())
		throw ValidationException(errors);
}

void FootageValidator::validateTitleForDelete(std::string& title)
{
	string errors;
	FileRepo repository;
	Service service{ repository };
	if (service.check_existing(title) == 0)
		errors += string("The <title> is inexistent\n");
	if (errors.size())
		throw ValidationException(errors);
}

std::string RepoException::get_message() const
{
	string FullMessage;
	FullMessage += string(" Repository exception: \n");
	FullMessage += this->message;
	return FullMessage;

}

std::string ServiceException::get_message() const
{
	string FullMessage;
	FullMessage += string(" Service exception: \n");
	FullMessage += this->message;
	return FullMessage;

}

std::string UIException::get_message() const
{
	string FullMessage;
	FullMessage += string(" UI exception: \n");
	FullMessage += this->message;
	return FullMessage;

}
