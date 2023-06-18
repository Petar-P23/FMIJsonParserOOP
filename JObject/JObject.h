#pragma once

#include "../Contracts/JComplex.h"

class JObject : public JComplex
{
private:
    void moveFrom(JObject&& other);
    void free();
    void copyFrom(const JObject& other);

protected:
    void setValue(const MyString& value) override;

public:
    JObject(const MyString& name, const MyString& value, JEntity* parent);

    JObject(const JObject& other);
    JObject(JObject&& other);

    JObject& operator=(const JObject& other);
    JObject& operator=(JObject&& other);

    JEntity* clone() const override;

    const MyString toString(unsigned indentation) const override;
    const MyString toValueString(unsigned indentation) const override;

    ~JObject() override;
};