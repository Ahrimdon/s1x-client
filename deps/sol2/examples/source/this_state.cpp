#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>


int main() {
	sol::state lua;

	lua.set_function(
	     "bark", [](sol::this_state s, int a, int b) {
		     lua_State* L = s; // current state
		     return a + b + lua_gettop(L);
	     });

	lua.script(
	     "first = bark(2, 2)"); // only takes 2 arguments, NOT 3

	// Can be at the end, too, or in the middle: doesn't matter
	lua.set_function(
	     "bark", [](int a, int b, sol::this_state s) {
		     lua_State* L = s; // current state
		     return a + b + lua_gettop(L);
	     });

	lua.script("second = bark(2, 2)"); // only takes 2 arguments
	int first = lua["first"];
	SOL_ASSERT(first == 6);
	int second = lua["second"];
	SOL_ASSERT(second == 6);

	return 0;
}
