#include <stdexcept>
#include <json/JSONValue.h>



JsonValue::Type JsonValue::type() const {
	return static_cast<Type>(data.index());
}

bool JsonValue::isNull() const
{
	return std::holds_alternative<std::nullptr_t>(data);
}

bool JsonValue::isBool() const {
	return std::holds_alternative<bool>(data);
}

bool JsonValue::isNumber() const
{
	return std::holds_alternative<double>(data);
}

bool JsonValue::isString() const{
	return std::holds_alternative<std::string>(data);
}

bool JsonValue::isArray() const
{
	return std::holds_alternative<Array>(data);
}

bool JsonValue::isObject() const
{
	return std::holds_alternative<Object>(data);
}

bool JsonValue::asBool() const
{
	if (!isBool())
	{
		throw std::runtime_error("JSONValue: not a bool.");
	}
	return std::get<bool>(data);
}

double JsonValue::asNumber() const
{
	if (!isNumber())
	{
		throw std::runtime_error("JSONValue: not a number.");
	}
	return std::get<double>(data);
}

const std::string& JsonValue::asString() const
{
	if (!isString())
	{
		throw std::runtime_error("JSONValue: not a string.");
	}
	return std::get<std::string>(data);
}

const JsonValue::Array& JsonValue::asArray() const
{
	if (!isArray())
	{
		throw std::runtime_error("JSONValue: not an array.");
	}
	return std::get<Array>(data);
}

const JsonValue::Object& JsonValue::asObject() const
{
	if (!isObject())
	{
		throw std::runtime_error("JSONValue: not a object.");
	}
	return std::get<Object>(data);
}

const JsonValue& JsonValue::operator[](size_t index) const
{
	const Array& arr = asArray();
	if (index >= arr.size())
	{
		throw std::out_of_range("JSONValue: array index out of range.");
	}
	return arr[index];
}

const JsonValue& JsonValue::operator[](const std::string& key) const
{
	const Object& obj = asObject();
	auto it = obj.find(key);
	if (it == obj.end())
	{
		throw std::out_of_range("JsonValue: key not found: " + key);
	}
	return it->second;
}
