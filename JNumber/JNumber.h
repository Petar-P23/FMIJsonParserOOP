#pragma once

#include "../Contracts/JPrimitive.h"
#include "../MyString/MyString.h"

class JNumber : public JPrimitive
{
private:
    double *value = nullptr;
    void moveFrom(JNumber &&other);
    void free();
    void copyFrom(const JNumber &other);

protected:
    void setValue(const MyString& value) override;

public:
    JNumber(const MyString& name, const MyString& value, JEntity* parent);

    JNumber(const JNumber &other);
    JNumber(JNumber &&other);

    JNumber &operator=(const JNumber &other);
    JNumber &operator=(JNumber &&other);

    JEntity *clone() const override;

    const MyString toString(unsigned indentation) const override;
    const MyString toValueString(unsigned indentation) const override;

    ~JNumber() override;
};