#pragma once

#include "../Contracts/JPrimitive.h"

class JString : public JPrimitive
{
private:
    MyString value;

protected:
    void setValue(const MyString& value) override;

public:
    JString(const MyString& name, const MyString& value, JEntity* parent);

    JEntity *clone() const override;

    const MyString toString(unsigned indentation) const override;
    const MyString toValueString(unsigned indentation) const override;
};