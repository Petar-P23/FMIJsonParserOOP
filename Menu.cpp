#include <iostream>
#include <fstream>
#include "constants.h"
#include "./JObject/JObject.h"
#include "./JString/JString.h"
#include "Factory/Factory.h"
#include "Menu.h"

MyString readFromFile(MyString& filename) {
	MyString result;

	char buffer[1024];
	std::ifstream ifs;
	ifs.open(filename.c_str());
	while (true)
	{
		if (ifs.eof() || ifs.fail())
			break;

		ifs.getline(buffer, 1024);
		result += buffer;
	}

	ifs.close();

	return result;
}

void saveFile(MyString& fileName, const MyString& jsonText) {
	std::ofstream ofs(fileName.c_str());
	if (ofs.is_open())
	{
		ofs.write(jsonText.c_str(), jsonText.length());
	}

	ofs.close();
}

void minimizeJson(MyString& jsonText) {
	bool shouldRemove = true;
	size_t jsonSize = jsonText.length();
	MyString result("");

	for (size_t i = 0; i < jsonSize; i++)
	{
		if ((jsonText[i] == ' ' || jsonText[i] == '\t') && shouldRemove)
			continue;

		if (jsonText[i] == '"' && shouldRemove)
			shouldRemove = false;
		else if (jsonText[i] == '"' && !shouldRemove)
		{
			shouldRemove = true;
		}

		result = result + jsonText[i];
	}

	jsonText = result;
}

void writeMenuToConsole()
{
	std::cout << " 0 - Load and validate" << std::endl;
	std::cout << " 1 - Print" << std::endl;
	std::cout << " 2 - Search" << std::endl;
	std::cout << " 3 - Set" << std::endl;
	std::cout << " 4 - Create" << std::endl;
	std::cout << " 5 - Delete" << std::endl;
	std::cout << " 6 - Move" << std::endl;
	std::cout << " 7 - Save" << std::endl;
	std::cout << " 8 - Save As" << std::endl;
	std::cout << " Choose: ";
}

JEntity* loadFromFile(MyString& path) {
	Factory fact;
	std::cout << FILE_PATH_PROMPT << std::endl;
	std::cin >> path;
	MyString fromFile = readFromFile(path);
	minimizeJson(fromFile);
	
	try
	{
		return fact.createEntity(path.c_str(), fromFile.c_str(), nullptr);
	}
	catch (const std::exception& ex)
	{
		system("cls");
		std::cout << INVALID_JSON_ERROR << std::endl;
		std::cout << ex.what() << std::endl;
	}
}

void print(const JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	system("cls");
	std::cout << json->toValueString(0) << std::endl;
}

void search(const JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString input;
	std::cout << SEARCH_PROMPT << std::endl;
	std::cin >> input;
	MyString result = json->search(input.c_str());
	system("cls");
	std::cout << (result.length() ? result : NO_ELEMENTS_FOUND_ERROR);
}

void set(JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString path;
	std::cout << PATH_PROMPT << std::endl;
	std::cin >> path;

	MyString value;
	std::cout << VALUE_PROMPT << std::endl;
	std::cin >> value;

	json->setChild(path, value);
	system("cls");
}

void create(JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString path;
	std::cout << PATH_PROMPT << std::endl;
	std::cin >> path;

	MyString key;
	std::cout << KEY_PROMPT << std::endl;
	std::cin >> key;

	MyString value;
	std::cout << VALUE_PROMPT << std::endl;
	std::cin >> value;

	json->createChild(path.c_str(), key, value);
	system("cls");
}

void deleteChild(JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString path;
	std::cout << PATH_PROMPT << std::endl;
	std::cin >> path;

	json->deleteChild(path.c_str());
	system("cls");
}

void move(JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString pathFrom;
	std::cout << PATH_PROMPT << "(From)" << std::endl;
	std::cin >> pathFrom;

	MyString pathTo;
	std::cout << PATH_PROMPT << "(To)" << std::endl;
	std::cin >> pathTo;

	json->moveChild(pathFrom, pathTo);
	system("cls");
}

void saveAs(JEntity* json) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString path;
	std::cout << PATH_PROMPT << std::endl;
	std::cin >> path;

	MyString filePath;
	std::cout << FILE_PATH_PROMPT << std::endl;
	std::cin >> filePath;

	JEntity& jElement = (*json)[path.c_str()];
	saveFile(filePath, jElement.toString(0));
}

void save(JEntity* json, MyString& filePath) {
	if (json == nullptr) {
		std::cout << JSON_NOT_LOADED_ERROR;
		return;
	}

	MyString path;
	std::cout << PATH_PROMPT << std::endl;
	std::cin >> path;

	JEntity& jElement = (*json)[path.c_str()];
	saveFile(filePath, jElement.toString(0));
}

void Menu::run() {
	JEntity* json = nullptr;
	MyString filePath("");
	while (true) {
		try
		{
			writeMenuToConsole();
			char input;
			std::cin >> input;
			switch (input) {
			case '0':
				json = loadFromFile(filePath);
				break;
			case '1':
				print(json);
				break;
			case '2':
				search(json);
				break;
			case '3':
				set(json);
				break;
			case '4':
				create(json);
				break;
			case '5':
				deleteChild(json);
				break;
			case '6':
				move(json);
				break;
			case '7':
				save(json, filePath);
				break;
			case '8':
				saveAs(json);
				break;
			default:
				system("cls");
				std::cout << "Please try again!" << std::endl;
				break;
			}
		}
		catch (const std::exception& ex)
		{
			system("cls");
			std::cout << ex.what() << std::endl;
		}
	}
}