#include <json/Parser.h>
#include <cctype>


Parser::Parser(std::string input) : text(std::move(input)) {}



char Parser::peek() const
{
    if (isAtEnd())
    {
        error("Unexpected end of input");
    }
    return text[pos];

}

char Parser::advance()
{
    char c = peek();
    ++pos;
    return c;
}

bool Parser::isAtEnd() const
{
    return pos >= text.size();
}

void Parser::skipWhitespace()
{
    while (!isAtEnd() && std::isspace(static_cast<unsigned char>(peek()))) {
        advance();
    }
}

void Parser::expect(char c)
{
    if (isAtEnd() || peek() != c)
    {
        error(std::string("Expected '") + c + "'");
    }

    advance();
}

[[noreturn]] void Parser::error(const std::string& message) const {
    size_t line = 1;
    size_t column = 1;

    for (size_t i = 0; i < pos && i < text.size(); ++i) {
        if (text[i] == '\n') {
            ++line;
            column = 1;
        }
        else {
            ++column;
        }
    }

    throw JsonParseError(message, line, column);
}

JsonValue Parser::parseValue() {
    skipWhitespace();

    if (isAtEnd())
        error("Unexpected end of input, expected a value");

    char c = peek();

    switch (c) {
    case '{': return parseObject();
    case '[': return parseArray();
    case '"': return parseString();
    case 't': case 'f': case 'n': return parseLiteral();
    default:
        if (c == '-' || std::isdigit(static_cast<unsigned char>(c)))
            return parseNumber();
        error(std::string("Unexpected character '") + c + "'");
    }
}

JsonValue Parser::parseLiteral() {
    char c = peek();

    if (c == 't') {
        expect('t'); expect('r'); expect('u'); expect('e');
        return JsonValue(true);
    }
    if (c == 'f') {
        expect('f'); expect('a'); expect('l'); expect('s'); expect('e');
        return JsonValue(false);
    }
    if (c == 'n') {
        expect('n'); expect('u'); expect('l'); expect('l');
        return JsonValue(nullptr);
    }

    error("Invalid literal");
}

JsonValue Parser::parse() {
    JsonValue result = parseValue();
    skipWhitespace();

    if (!isAtEnd())
        error("Unexpected trailing characters after JSON value");

    return result;
}

JsonValue Parser::parseObject() {
    error("parseObject() not implemented yet");
}

JsonValue Parser::parseArray() {
    error("parseArray() not implemented yet");
}

JsonValue Parser::parseString() {
    error("parseString() not implemented yet");
}

JsonValue Parser::parseNumber() {
    error("parseNumber() not implemented yet");
}

std::string Parser::parseRawString() {
    error("parseRawString() not implemented yet");
}