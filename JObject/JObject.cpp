#include "JObject.h"
#include "../constants.h"
#include <stdexcept>
#include "../MyString/MyString.h"
#include "../Factory/Factory.h"
#pragma warning(disable : 4996)

void JObject::moveFrom(JObject&& other)
{
	this->key = other.key;
	this->children = other.children;
	other.children = nullptr;
}
void JObject::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] children[i];
	}

	delete[] this->children;
}
void JObject::copyFrom(const JObject& other)
{
	this->key = other.key;
	this->children = new JEntity * [other.size];
	for (size_t i = 0; i < other.size; i++)
	{
		this->children[i] = other.children[i]->clone();
	}
}

void JObject::setValue(const MyString& value)
{
	if (value[0] != '{')
		throw std::logic_error(INVALID_TYPE_ERROR.c_str());

	if (this->children != nullptr)
		free();

	this->children = new JEntity * [4] {nullptr };
	this->size = 0;
	this->capacity = 4;

	static Factory factory;
	MyString key("");
	MyString val("");
	MyString* writeTo = &key;
	bool shouldWrite = false;

	size_t valueSize = value.length();
	for (size_t i = 0; i < valueSize; i++)
	{
		if (value[i] == ' ' && value[i + 1] == ':')
			continue;

		if (value[i] == '"' && writeTo == &key && !shouldWrite)
		{
			shouldWrite = !shouldWrite;
			continue;
		}

		if (value[i] == '"' && writeTo == &key && shouldWrite)
		{
			shouldWrite = !shouldWrite;
			continue;
		}

		if (value[i] == NAME_SEPARATOR)
		{
			writeTo = &val;
			if (value[i + 1] == BEGIN_OBJECT || value[i + 1] == BEGIN_ARRAY) {
				*writeTo = value.substr(i + 1, valueSize - 2 - i);
				i += writeTo->length();
			}
			continue;
		}

		if (writeTo == &val && !shouldWrite && value[i] != ' ')
		{
			shouldWrite = true;
		}

		if (value[i] == VALUE_SEPARATOR || value[i] == END_OBJECT || value == "{}")
		{
			if (size == capacity)
				expand();

			if (value == "{}")
				val = "{}";

			if (key.length() == 0 || val.length() == 0)
				break;

			children[size++] = factory.createEntity(key.c_str(), val.c_str(), this);
			key = "";
			val = "";
			writeTo = &key;
			shouldWrite = false;

			if (val[0] == BEGIN_OBJECT)
				break;

			continue;
		}

		if (!shouldWrite)
			continue;

		*writeTo = *writeTo + value[i];
	}
}

JObject::JObject(const MyString& name, const MyString& value, JEntity* parent)
{
	this->parent = parent;
	this->key = name;
	this->capacity = 4;

	if (value == "null")
		this->children = nullptr;
	else {
		this->setValue(value);
	}
}

JObject::JObject(const JObject& other)
{
	this->copyFrom(other);
}

JObject::JObject(JObject&& other)
{
	this->moveFrom(std::move(other));
}

JObject& JObject::operator=(const JObject& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->copyFrom(other);

	return *this;
}

JObject& JObject::operator=(JObject&& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->moveFrom(std::move(other));

	return *this;
}

JEntity* JObject::clone() const
{
	return new JObject(*this);
}

const MyString JObject::toString(unsigned indentation) const
{
	MyString result("");
	for (size_t i = 0; i < indentation; i++)
	{
		result += "\t";
	}
	result += "\"" + key + "\" " + NAME_SEPARATOR + " " + this->toValueString(indentation);

	return result;
}

const MyString JObject::toValueString(unsigned indentation) const
{
	if (this->children == nullptr)
		return "null";

	MyString result("");
	result = result + BEGIN_OBJECT + "\r\n";
	for (size_t i = 0; i < size; i++)
	{
		result += children[i]->toString(indentation + 1);
		if (i == size - 1)
			result += "\r\n";
		else
			result += ",\r\n";
	}

	for (size_t j = 0; j < indentation + 1; j++)
	{
		result += "\t";
	}
	result = result + END_OBJECT;

	return result;
}

JObject::~JObject()
{
	free();
}