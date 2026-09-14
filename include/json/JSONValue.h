// JSONValue.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <cstdint>

class JSONValue {
public:
	using Array = std::vector<JSONValue>;
	using Object = std::map<std::string, JSONValue>;

	enum class Type {
		Null, Bool, Number, String, Array, Object
	};
private:
	std::variant<std::nullptr_t, bool, double, std::string, Array, Object> data;
public:
	JSONValue() : data(nullptr){}
	JSONValue(std::nullptr_t) : data(nullptr) {}
	JSONValue(bool b) : data(b) {}
	JSONValue(double d) : data(d) {}
	JSONValue(int i) : data(static_cast<double>(i)) {}
	JSONValue(const std::string& s) : data(s) {}
	JSONValue(const std::string&& s) : data(std::move(s)) {}
	JSONValue(const char* c) : data(std::string(c)) {}
	JSONValue(const Array& arr) : data(arr) {}
	JSONValue(const Array&& arr) : data(std::move(arr)) {}
	JSONValue(const Object& obj) : data(obj) {}
	JSONValue(const Object&& obj) : data(std::move(obj)) {}


	Type type() const;
	bool isNull() const;
	bool isBool() const;
	bool isNumber() const;
	bool isString() const;
	bool isArray() const;
	bool isObject() const;

	bool asBool() const;
	double asNumber() const;
	const std::string& asString() const;
	const Array& asArray() const;
	const Object& asObject() const;

	const JSONValue& operator[](size_t index) const;
	const JSONValue& operator[](const std::string& key) const;
};


// TODO: Reference additional headers your program requires here.
