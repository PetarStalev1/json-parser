#pragma once

#include <json/JsonValue.h>
#include <string>
#include <stdexcept>

class JsonParseError : public std::runtime_error {
public:
	size_t line;
	size_t column;
	
	
	JsonParseError(const std::string& message, size_t line, size_t column ) : std::runtime_error(message +
		" (line " + std::to_string(line) + ", column " + std::to_string(column) + ")"),line(line),column(column){ }

};

class Parser {

public:
	explicit Parser(std::string input);
	JsonValue parse();
private:
	std::string text;
	size_t pos = 0;

	char peek() const;
	char advance();
	bool isAtEnd() const;
	void skipWhitespace();
	void expect(char c);

	JsonValue parseValue();
	JsonValue parseObject();
	JsonValue parseArray();
	JsonValue parseString();
	JsonValue parseNumber();
	JsonValue parseLiteral();

	std::string parseRawString();

	[[noreturn]] void error(const std::string& message) const;

};