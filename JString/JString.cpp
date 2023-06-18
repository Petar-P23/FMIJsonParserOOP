#include "JString.h"
#include "../constants.h"
#include <string.h>
#include <stdexcept>
#pragma warning(disable : 4996)

void JString::setValue(const MyString& value)
{
    this->value = value;
}

JString::JString(const MyString& name, const MyString& value, JEntity* parent)
{
    this->parent = parent;
    this->key = name;
    this->setValue(value);
}

JEntity* JString::clone() const
{
    return new JString(*this);
}

const MyString JString::toString(unsigned indentation) const
{
    MyString result("");
    for (size_t i = 0; i < indentation; i++)
    {
        result += "\t";
    }

    result += "\"" + key + "\" " + NAME_SEPARATOR + toValueString(0);

    return result;
}

const MyString JString::toValueString(unsigned indentation) const
{
    MyString result("");
    for (size_t i = 0; i < indentation; i++)
    {
        result += "\t";
    }

    result += "\"" + value + "\"";

    return result;
}