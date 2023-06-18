#include "JBoolean.h"
#include "../constants.h"
#include <stdexcept>
#include "../MyString/MyString.h"
#pragma warning(disable : 4996)

void JBoolean::moveFrom(JBoolean &&other)
{
    this->key = other.key;
    this->value = other.value;
    other.value = nullptr;
}
void JBoolean::free()
{
    delete[] this->value;
}
void JBoolean::copyFrom(const JBoolean &other)
{
    this->key = other.key;
    this->value = new bool(other.value);
}

void JBoolean::setValue(const MyString& value)
{
    if (this->value != nullptr)
        delete[] this->value;
    
    if (value == FALSE_LITERAL)
        this->value = new bool(false);
    else if (value == TRUE_LITERAL)
        this->value = new bool(true);
    else
        throw std::invalid_argument(INVALID_TYPE_ERROR.c_str());
}

JBoolean::JBoolean(const MyString& name, const MyString& value, JEntity* parent)
{
    this->parent = parent;
    this->key = name;
    this->setValue(value);
}

JBoolean::JBoolean(const JBoolean &other)
{
    this->copyFrom(other);
}

JBoolean::JBoolean(JBoolean &&other)
{
    this->moveFrom(std::move(other));
}

JBoolean &JBoolean::operator=(const JBoolean &other)
{
    if (this == &other)
        return *this;

    this->free();
    this->copyFrom(other);

    return *this;
}

JBoolean &JBoolean::operator=(JBoolean &&other)
{
    if (this == &other)
        return *this;

    this->free();
    this->moveFrom(std::move(other));

    return *this;
}

JEntity *JBoolean::clone() const
{
    return new JBoolean(*this);
}

const MyString JBoolean::toString(unsigned indentation) const
{
    const MyString valueString = value ? TRUE_LITERAL : FALSE_LITERAL;
    MyString result("");
    for (size_t i = 0; i < indentation; i++)
    {
        result += "\t";
    }

    result += "\"" + key + "\" " + NAME_SEPARATOR + " " + valueString;

    return result;
}

const MyString JBoolean::toValueString(unsigned indentation) const
{
    MyString result("");
    for (size_t i = 0; i < indentation; i++)
    {
        result += "\t";
    }

    result += value ? TRUE_LITERAL : FALSE_LITERAL;
    return result;
}

JBoolean::~JBoolean()
{
    free();
}