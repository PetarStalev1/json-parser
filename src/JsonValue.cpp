#include <stdexcept>
#include <json/JSONValue.h>



JSONValue::Type JSONValue::type() const {
	return static_cast<Type>(data.index());
}

bool JSONValue::isNull() const
{
	return std::holds_alternative<std::nullptr_t>(data);
}

bool JSONValue::isBool() const {
	return std::holds_alternative<bool>(data);
}

bool JSONValue::isNumber() const
{
	return std::holds_alternative<double>(data);
}

bool JSONValue::isString() const{
	return std::holds_alternative<std::string>(data);
}

bool JSONValue::isArray() const
{
	return std::holds_alternative<Array>(data);
}

bool JSONValue::isObject() const
{
	return std::holds_alternative<Object>(data);
}

bool JSONValue::asBool() const
{
	if (!isBool())
	{
		throw std::runtime_error("JSONValue: not a bool.");
	}
	return std::get<bool>(data);
}

double JSONValue::asNumber() const
{
	if (!isNumber())
	{
		throw std::runtime_error("JSONValue: not a number.");
	}
	return std::get<double>(data);
}

const std::string& JSONValue::asString() const
{
	if (!isString())
	{
		throw std::runtime_error("JSONValue: not a string.");
	}
	return std::get<std::string>(data);
}

const JSONValue::Array& JSONValue::asArray() const
{
	if (!isArray())
	{
		throw std::runtime_error("JSONValue: not an array.");
	}
	return std::get<Array>(data);
}

const JSONValue::Object& JSONValue::asObject() const
{
	if (!isObject())
	{
		throw std::runtime_error("JSONValue: not a object.");
	}
	return std::get<Object>(data);
}

const JSONValue& JSONValue::operator[](size_t index) const
{
	const Array& arr = asArray();
	if (index >= arr.size())
	{
		throw std::out_of_range("JSONValue: array index out of range.");
	}
	return arr[index];
}

const JSONValue& JSONValue::operator[](const std::string& key) const
{
	const Object& obj = asObject();
	auto it = obj.find(key);
	if (it == obj.end())
	{
		throw std::out_of_range("JsonValue: key not found: " + key);
	}
	return it->second;
}
