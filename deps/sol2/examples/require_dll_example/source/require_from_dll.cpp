#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <my_object/my_object.hpp>

#include <iostream>

int main(int, char*[]) {
	std::cout << "=== require from DLL ===" << std::endl;

	sol::state lua;
	lua.open_libraries(sol::lib::package, sol::lib::base);

	const auto& code = R"(
mo = require("my_object")

obj = mo.test.new(24)
print(obj.value))";
	auto script_result
	     = lua.safe_script(code, &sol::script_pass_on_error);
	if (script_result.valid()) {
		std::cout << "The DLL was require'd from successfully!"
		          << std::endl;
	}
	else {
		sol::error err = script_result;
		std::cout << "Something bad happened: " << err.what()
		          << std::endl;
	}
	SOL_ASSERT(script_result.valid());
	my_object::test& obj = lua["obj"];
	SOL_ASSERT(obj.value == 24);

	return 0;
}
