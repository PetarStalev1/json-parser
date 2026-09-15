#include <iostream>
#include <json/Parser.h>

using namespace std;

int main()
{
	try
	{
		Parser p1("true");
		JsonValue v1 = p1.parse();
		std::cout << "true -> " << v1.asBool() << std::endl;

		Parser p2("null");
		JsonValue v2 = p2.parse();
		std::cout << "null -> isNull: " << v2.isNull() << std::endl;

		Parser p3("false");
		JsonValue v3 = p3.parse();
		std::cout << "false -> " << v3.asBool() << std::endl;

		// Тест за грешка - трябва да хвърли изключение
		Parser p4("trux");
		JsonValue v4 = p4.parse();


	}
	catch (const JsonParseError& e) {
		std::cout << "Caught expected error: " << e.what() << std::endl;
	}

	return 0;
}