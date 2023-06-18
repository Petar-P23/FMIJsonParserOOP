#pragma once

#include "JEntity.h"
class JComplex : public JEntity
{
protected:
	JEntity** children = nullptr;
	size_t size = 0;
	size_t capacity = 0;
	void expand();

public:
	JEntity& operator[](const char* path) const override;
	MyString search(const char* key) const override;


	void setChild(const MyString& path, const MyString& value) override;
	void createChild(const char* path, const MyString& key, const MyString& value) override;
	void deleteChild(const const char* path) override;

	void moveChild(const MyString& pathFrom, const MyString& pathTo) override;
};