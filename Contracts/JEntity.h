#pragma once
#include <string>
#include "../MyString/MyString.h"

class JEntity
{
protected:
	MyString key;
	JEntity* parent = nullptr;

public:
	const char* getKey() {
		return key.c_str();
	}

	virtual void setValue(const MyString& value) = 0;
	virtual JEntity* clone() const = 0;
	virtual JEntity& operator[](const char* path) const = 0;
	virtual MyString search(const char* key) const = 0;

	virtual void setChild(const MyString& path, const MyString& value) = 0;
	virtual void createChild(const char* path, const MyString& key, const MyString& value) = 0;
	virtual void deleteChild(const const char* path) = 0;

	virtual void moveChild(const MyString& pathFrom, const MyString& pathTo) = 0;

	virtual const MyString toString(unsigned indentation) const = 0;
	virtual const MyString toValueString(unsigned indentation) const = 0;


	virtual ~JEntity() = default;
};