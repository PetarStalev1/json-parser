// JSONValue.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <cstdint>

class JsonValue {
public:
	using Array = std::vector<JsonValue>;
	using Object = std::map<std::string, JsonValue>;

	enum class Type {
		Null, Bool, Number, String, Array, Object
	};
private:
	std::variant<std::nullptr_t, bool, double, std::string, Array, Object> data;
public:
	JsonValue() : data(nullptr){}
	JsonValue(std::nullptr_t) : data(nullptr) {}
	JsonValue(bool b) : data(b) {}
	JsonValue(double d) : data(d) {}
	JsonValue(int i) : data(static_cast<double>(i)) {}
	JsonValue(const std::string& s) : data(s) {}
	JsonValue(const std::string&& s) : data(std::move(s)) {}
	JsonValue(const char* c) : data(std::string(c)) {}
	JsonValue(const Array& arr) : data(arr) {}
	JsonValue(const Array&& arr) : data(std::move(arr)) {}
	JsonValue(const Object& obj) : data(obj) {}
	JsonValue(const Object&& obj) : data(std::move(obj)) {}


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

	const JsonValue& operator[](size_t index) const;
	const JsonValue& operator[](const std::string& key) const;
};


// TODO: Reference additional headers your program requires here.
