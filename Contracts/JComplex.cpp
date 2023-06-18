#include <stdexcept>
#include "JComplex.h"
#include "../constants.h"
#include "../Factory/Factory.h"

JEntity& JComplex::operator[](const char* path) const
{
	if (children == nullptr)
		throw std::logic_error(NO_CHILDREN_ERROR.c_str());

	MyString next("");
	while (*path != '/' && *path != '\0')
	{
		next = next + *path;
		path++;
	}

	bool isLastNode = *path == '\0';
	JEntity* result = nullptr;
	for (size_t i = 0; i < size; i++)
	{
		MyString key(children[i]->getKey());
		if (key == next) {
			result = children[i];
			break;
		}
	}

	if (result == nullptr)
		throw std::logic_error(NOT_FOUND_ERROR.c_str());

	if (isLastNode)
	{
		return *result;
	}

	const char* restOfPath = path + 1;

	return (*result)[restOfPath];

	throw std::logic_error(NOT_FOUND_ERROR.c_str());
}

MyString JComplex::search(const char* key) const {
	if (this->key == key)
		return this->toValueString(0);

	MyString result("");
	for (size_t i = 0; i < size; i++)
	{
		MyString found = this->children[i]->search(key);
		result += found + (found.length() ? "\r\n" : "");
	}

	return result;
}

void JComplex::expand() {
	JEntity** temp = new JEntity * [2 * capacity];
	capacity = 2 * capacity;
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = children[i];
	}

	delete[] children;
	children = temp;
}


void JComplex::setChild(const MyString& path, const MyString& value)
{
	JEntity& child = (*this)[path.c_str()];
	child.setValue(value);
}
void JComplex::createChild(const char* path, const MyString& key, const MyString& value)
{
	static Factory fact;
	if (std::strlen(path) != 0) {
		MyString next("");
		while (*path != '/' && *path != '\0')
		{
			next = next + *path;
			path++;
		}

		try
		{
			(*this)[next.c_str()].createChild(*path == '\0' ? path : path + 1, key, value);
		}
		catch (const std::exception&)
		{
			if (this->size == this->capacity)
				this->expand();

			this->children[size++] = fact.createEntity(next.c_str(), "{}", this);
			(*this)[next.c_str()].createChild(*path == '\0' ? path : path + 1, key, value);
		}

		return;
	}

	if (this->size == this->capacity)
		this->expand();

	this->children[size++] = fact.createEntity(key.c_str(), value.c_str(), this);
}
void JComplex::deleteChild(const char* path)
{
	MyString next("");
	if (path == nullptr || path == next)
	{
		throw std::logic_error(INVALID_PATH_ERROR.c_str());
	}

	while (*path != '/' && *path != '\0')
	{
		next = next + *path;
		path++;
	}

	JEntity& child = (*this)[next.c_str()];

	if (*path == '\0')
	{
		delete[] & child;
		for (size_t i = 1; i < size; i++)
		{
			this->children[i - 1] = this->children[i];
		}

		size--;
		return;
	}

	child.deleteChild(path + 1);
}

void JComplex::moveChild(const MyString& pathFrom, const MyString& pathTo)
{
	JEntity& child = (*this)[pathFrom.c_str()];
	this->createChild(pathTo.c_str(), child.getKey(), child.toValueString(0));
	this->deleteChild(pathFrom.c_str());
}