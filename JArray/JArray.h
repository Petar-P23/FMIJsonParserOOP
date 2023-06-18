#pragma once

#include "../Contracts/JComplex.h"

class JArray : public JComplex
{
private:
    void moveFrom(JArray&& other);
    void free();
    void copyFrom(const JArray& other);

protected:
    void setValue(const MyString& value) override;

public:
    JArray(const MyString& name, const MyString& value, JEntity* parent);

    JArray(const JArray& other);
    JArray(JArray&& other);

    JArray& operator=(const JArray& other);
    JArray& operator=(JArray&& other);

    JEntity* clone() const override;

    const MyString toString(unsigned indentation) const override;
    const MyString toValueString(unsigned indentation) const override;

    ~JArray() override;
};