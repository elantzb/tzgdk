#pragma once
#include <map>
#include <SFML/Window.hpp>

namespace tzgdk
{
	namespace sc
	{
		bool A();
		bool B();
		bool C();
		bool D();
		bool E();
		bool F();
		bool G();
		bool H();
		bool I();
		bool J();
		bool K();
		bool L();
		bool M();
		bool N();
		bool O();
		bool P();
		bool Q();
		bool R();
		bool S();
		bool T();
		bool U();
		bool V();
		bool W();
		bool X();
		bool Y();
		bool Z();
		bool Escape();
		bool LControl();
		bool LShift();
		bool Space();
		bool Enter();
	}

	namespace admin
	{
		extern std::map<int, bool> scancode_map;
		void trigger_scancode(int scan_code);
		void untrigger_scancode(int scan_code);
	}
}
