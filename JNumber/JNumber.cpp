#include "JNumber.h"
#include "../constants.h"
#include <string.h>
#include <stdexcept>
#include <sstream>
#pragma warning(disable : 4996)

static double convertToDouble(const MyString& str)
{
	double result = 0;
	bool hasDecimalPoint = false;
	size_t strLen = str.length();
	int decimalCount = 0;
	for (size_t i = 0; i < strLen; i++)
	{
		if (!hasDecimalPoint && (str[i] == '.' || str[i] == ','))
		{
			hasDecimalPoint = true;
			continue;
		}

		if (!hasDecimalPoint)
		{
			result *= 10;
			result += str[i] - '0';
		}
		else
		{
			double decimalPartToAdd = str[i] - '0';
			decimalCount++;

			for (size_t i = 0; i < decimalCount; i++)
			{
				decimalPartToAdd /= 10;
			}

			result += decimalPartToAdd;
		}
	}

	return result;
}

void JNumber::moveFrom(JNumber&& other)
{
	this->key = other.key;
	this->value = other.value;
	other.value = nullptr;
}
void JNumber::free()
{
	delete[] this->value;
}
void JNumber::copyFrom(const JNumber& other)
{
	this->key = other.key;
	this->value = new double(*other.value);
}

void JNumber::setValue(const MyString& value)
{
	if (!(value[0] >= '0' && value[0] <= '9'))
		throw std::logic_error(INVALID_TYPE_ERROR.c_str());

	if (this->value != nullptr)
		delete[] this->value;

	this->value = new double(convertToDouble(value));
}

JNumber::JNumber(const MyString& name, const MyString& value, JEntity* parent)
{
	this->parent = parent;
	this->key = name;
	this->setValue(value);
}

JNumber::JNumber(const JNumber& other)
{
	this->copyFrom(other);
}

JNumber::JNumber(JNumber&& other)
{
	this->moveFrom(std::move(other));
}

JNumber& JNumber::operator=(const JNumber& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->copyFrom(other);

	return *this;
}

JNumber& JNumber::operator=(JNumber&& other)
{
	if (this == &other)
		return *this;

	this->free();
	this->moveFrom(std::move(other));

	return *this;
}

JEntity* JNumber::clone() const
{
	return new JNumber(*this);
}

const MyString JNumber::toString(unsigned indentation) const
{
	MyString result("");
	for (size_t i = 0; i < indentation; i++)
	{
		result += "\t";
	}
	result += "\"" + key + "\" " + NAME_SEPARATOR + " " + toValueString(0);

	return result;
}

const MyString JNumber::toValueString(unsigned indentation) const
{
	MyString result("");
	for (size_t i = 0; i < indentation; i++)
	{
		result += "\t";
	}

	//от Stack Overflow
	std::ostringstream strs;
	strs << *value;
	result += strs.str().c_str();

	return result;
}

JNumber::~JNumber()
{
	free();
}