#pragma once
#include "./MyString/MyString.h"

const static char BEGIN_ARRAY = '[';
const static char BEGIN_OBJECT = '{';
const static char END_ARRAY = ']';
const static char END_OBJECT = '}';
const static char NAME_SEPARATOR = ':';
const static char VALUE_SEPARATOR = ',';

const static MyString FALSE_LITERAL("false");
const static MyString TRUE_LITERAL("true");
const static MyString NULL_LITERAL("null");

const static MyString PRIMITIVE_CHILDREN_ERROR("Invalid operation. Primitive types do not contain children."); 
const static MyString NO_CHILDREN_ERROR("Invalid operation. Element does not have children."); 
const static MyString NOT_FOUND_ERROR("Invalid operation. Element was not found.");
const static MyString INVALID_TYPE_ERROR("Invalid operation. Element type was invalid.");
const static MyString INVALID_PATH_ERROR("Invalid operation. Path was invalid.");
const static MyString JSON_NOT_LOADED_ERROR("Invalid operation. Please load json first.");
const static MyString INVALID_JSON_ERROR("Invalid JSON file.");

const static MyString NO_ELEMENTS_FOUND_ERROR("No elements were found.");

const static MyString FILE_PATH_PROMPT("Please provide relative path to file.");
const static MyString SEARCH_PROMPT("Please provide key to search for.");
const static MyString PATH_PROMPT("Please provide element path.");
const static MyString VALUE_PROMPT("Please provide a new value.");
const static MyString KEY_PROMPT("Please provide a new key.");
