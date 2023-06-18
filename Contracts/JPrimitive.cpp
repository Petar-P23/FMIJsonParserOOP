#include <stdexcept>
#include "JPrimitive.h"
#include "../constants.h"

JEntity& JPrimitive::operator[](const char* path) const
{
	throw std::logic_error(PRIMITIVE_CHILDREN_ERROR.c_str());
}

MyString JPrimitive::search(const char* key) const {
	if (this->key == key)
		return this->toValueString(0);

	return MyString("");
}

void JPrimitive::setChild(const MyString& path, const MyString& value)
{
	throw std::logic_error(PRIMITIVE_CHILDREN_ERROR.c_str());
}
void JPrimitive::createChild(const char* path, const MyString& key, const MyString& value)
{
	throw std::logic_error(PRIMITIVE_CHILDREN_ERROR.c_str());
}
void JPrimitive::deleteChild(const const char* path)
{
	throw std::logic_error(PRIMITIVE_CHILDREN_ERROR.c_str());
}

void JPrimitive::moveChild(const MyString& pathFrom, const MyString& pathTo)
{
	throw std::logic_error(PRIMITIVE_CHILDREN_ERROR.c_str());
}