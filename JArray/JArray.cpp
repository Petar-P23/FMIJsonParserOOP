#include "JArray.h"
#include "../constants.h"
#include <stdexcept>
#include "../MyString/MyString.h"
#include "../Factory/Factory.h"
#pragma warning(disable : 4996)

void JArray::moveFrom(JArray&& other)
{
	this->key = other.key;
	this->children = other.children;
	other.children = nullptr;
}
void JArray::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] children[i];
	}

	delete[] this->children;
}
void JArray::copyFrom(const JArray& other)
{
	this->key = other.key;
	this->children = new JEntity * [other.size];
	for (size_t i = 0; i < other.size; i++)
	{
		this->children[i] = other.children[i]->clone();
	}
}

void JArray::setValue(const MyString& value)
{
	if (value[0] != '[')
		throw std::logic_error(INVALID_TYPE_ERROR.c_str());

	static Factory factory;
	MyString val("");
	bool shouldWrite = false;

	size_t valueSize = value.length();
	for (size_t i = 1; i < valueSize; i++)
	{
		if (value[i] == ' ' && !shouldWrite)
			continue;

		if (value[i] == '"' && !shouldWrite)
		{
			shouldWrite = !shouldWrite;
		}
		else if (value[i] != VALUE_SEPARATOR && value[i] != BEGIN_ARRAY && !shouldWrite)
		{
			shouldWrite = !shouldWrite;
		}

		if (value[i] == ' ' && value[i + 1] == VALUE_SEPARATOR && shouldWrite)
		{
			shouldWrite = !shouldWrite;
			continue;
		}

		if (value[i] == BEGIN_ARRAY) {
			size_t sbstrSize = 0;
			for (size_t j = i; j < valueSize; j++)
			{
				if (value[j] == END_ARRAY)
					break;

				sbstrSize++;
			}
			val = value.substr(i, sbstrSize);
			i += sbstrSize;
		}
		else if (value[i] == BEGIN_OBJECT) {
			size_t sbstrSize = 0;
			for (size_t j = i; j < valueSize; j++)
			{
				if (value[j] == END_OBJECT)
					break;

				sbstrSize++;
			}
			val = value.substr(i, sbstrSize);
			i += sbstrSize;
		}

		if (value[i] == VALUE_SEPARATOR || value[i] == END_ARRAY)
		{
			if (size == capacity)
				expand();

			if (val.length() == 0)
				break;

			children[size++] = factory.createEntity("", val.c_str(), this);
			val = "";
			shouldWrite = false;

			if (val[0] == BEGIN_ARRAY)
				break;

			continue;
		}

		if (!shouldWrite)
			continue;

		val = val + value[i];
	}
}

JArray::JArray(const MyString& name, const MyString& value, JEntity* parent)
{
	this->parent = parent;
	this->key = name;
	this->capacity = 4;

	this->children = new JEntity * [4] {nullptr };
	this->setValue(value);
}

JArray::JArray(const JArray& other)
{
	this->copyFrom(other);
}

JArray::JArray(JArray&& other)
{
	this->moveFrom(std::move(other));
}

JArray& JArray::operator=(const JArray& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->copyFrom(other);

	return *this;
}

JArray& JArray::operator=(JArray&& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->moveFrom(std::move(other));

	return *this;
}

JEntity* JArray::clone() const
{
	return new JArray(*this);
}

const MyString JArray::toString(unsigned indentation) const
{
	MyString result("");
	for (size_t i = 0; i < indentation; i++)
	{
		result += "\t";
	}

	result += "\"" + key + "\" " + NAME_SEPARATOR + " " + this->toValueString(indentation);

	return result;
}

const MyString JArray::toValueString(unsigned indentation) const
{
	MyString result("");
	result = result + BEGIN_ARRAY + "\r\n";
	for (size_t i = 0; i < size; i++)
	{
		result += children[i]->toValueString(indentation + 1);
		if (i == size - 1)
			result += "\r\n";
		else
			result += ",\r\n";
	}

	for (size_t j = 0; j < indentation + 1; j++)
	{
		result += "\t";
	}

	result = result + END_ARRAY;

	return result;
}

JArray::~JArray()
{
	free();
}