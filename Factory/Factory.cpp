#include "Factory.h"
#include "../Contracts/JEntity.h"
#include "../JBoolean/JBoolean.h"
#include "../JString/JString.h"
#include "../JNumber/JNumber.h"
#include "../JObject/JObject.h"
#include "../JArray/JArray.h"
#include "../constants.h"

JEntity* Factory::createEntity(const char* key, const char* value, JEntity* parent) {
	MyString valueString(value);
	if (valueString == "true" || valueString == "false")
		return new JBoolean(key, value, parent);
	else if (valueString[0] == '"')
		return new JString(key, valueString.substr(1, valueString.length() - 2), parent);
	else if (valueString == "null" || valueString[0] == '{')
		return new JObject(key, value, parent);
	else if (valueString[0] == '[')
		return new JArray(key, value, parent);
	else if (valueString[0] >= '0' && valueString[0] <= '9')
		return new JNumber(key, value, parent);
	else
		throw std::logic_error(INVALID_TYPE_ERROR.c_str());
}