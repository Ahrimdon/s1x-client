#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>


int main(int, char*[]) {

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script(R"(
		abc = { [0] = 24 }
		def = { 
			ghi = { 
				bark = 50, 
				woof = abc 
			} 
		}
	)");

	sol::table abc = lua["abc"];
	sol::table def = lua["def"];
	sol::table ghi = lua["def"]["ghi"];

	int bark1 = def["ghi"]["bark"];
	int bark2 = lua["def"]["ghi"]["bark"];
	SOL_ASSERT(bark1 == 50);
	SOL_ASSERT(bark2 == 50);

	int abcval1 = abc[0];
	int abcval2 = ghi["woof"][0];
	SOL_ASSERT(abcval1 == 24);
	SOL_ASSERT(abcval2 == 24);

	sol::optional<int> will_not_error
	     = lua["abc"]["DOESNOTEXIST"]["ghi"];
	SOL_ASSERT(will_not_error == sol::nullopt);

	int also_will_not_error
	     = lua["abc"]["def"]["ghi"]["jklm"].get_or(25);
	SOL_ASSERT(also_will_not_error == 25);

	// if you don't go safe,
	// will throw (or do at_panic if no exceptions)
	// int aaaahhh = lua["boom"]["the_dynamite"];

	return 0;
}
