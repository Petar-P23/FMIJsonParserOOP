#pragma once

#include "JEntity.h"
class JPrimitive : public JEntity
{
public:
    JEntity &operator[](const char* path) const override;
    MyString search(const char* key) const override;

    void setChild(const MyString &path, const MyString &value) override;
    void createChild(const char* path, const MyString& key, const MyString& value) override;
    void deleteChild(const const char* path) override;

    void moveChild(const MyString &pathFrom, const MyString &pathTo) override;
};