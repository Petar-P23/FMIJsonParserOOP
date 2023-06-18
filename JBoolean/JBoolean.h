#pragma once

#include "../Contracts/JPrimitive.h"

class JBoolean : public JPrimitive
{
private:
    bool *value = nullptr;
    void moveFrom(JBoolean &&other);
    void free();
    void copyFrom(const JBoolean &other);

protected:
    void setValue(const MyString& value) override;

public:
    JBoolean(const MyString& name, const MyString& value, JEntity* parent);

    JBoolean(const JBoolean &other);
    JBoolean(JBoolean &&other);

    JBoolean &operator=(const JBoolean &other);
    JBoolean &operator=(JBoolean &&other);

    JEntity *clone() const override;

    const MyString toString(unsigned indentation) const override;
    const MyString toValueString(unsigned indentation) const override;

    ~JBoolean() override;
};