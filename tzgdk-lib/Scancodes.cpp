#include "pch.h"
#include "Scancodes.h"

namespace tzgdk
{
	std::map<int, bool> scancode_map;

	bool A()
	{
		return scancode_map.count(sf::Keyboard::Key::A) > 0 && scancode_map.at(sf::Keyboard::Key::A);
	}
	bool B()
	{
		return scancode_map.count(sf::Keyboard::Key::B) > 0 && scancode_map.at(sf::Keyboard::Key::B);
	}
	bool C()
	{
		return scancode_map.count(sf::Keyboard::Key::C) > 0 && scancode_map.at(sf::Keyboard::Key::C);
	}
	bool D()
	{
		return scancode_map.count(sf::Keyboard::Key::D) > 0 && scancode_map.at(sf::Keyboard::Key::D);
	}
	bool E()
	{
		return scancode_map.count(sf::Keyboard::Key::E) > 0 && scancode_map.at(sf::Keyboard::Key::E);
	}
	bool F()
	{
		return scancode_map.count(sf::Keyboard::Key::F) > 0 && scancode_map.at(sf::Keyboard::Key::F);
	}
	bool G()
	{
		return scancode_map.count(sf::Keyboard::Key::G) > 0 && scancode_map.at(sf::Keyboard::Key::G);
	}
	bool H()
	{
		return scancode_map.count(sf::Keyboard::Key::H) > 0 && scancode_map.at(sf::Keyboard::Key::H);
	}
	bool I()
	{
		return scancode_map.count(sf::Keyboard::Key::I) > 0 && scancode_map.at(sf::Keyboard::Key::I);
	}
	bool J()
	{
		return scancode_map.count(sf::Keyboard::Key::J) > 0 && scancode_map.at(sf::Keyboard::Key::J);
	}
	bool K()
	{
		return scancode_map.count(sf::Keyboard::Key::K) > 0 && scancode_map.at(sf::Keyboard::Key::K);
	}
	bool L()
	{
		return scancode_map.count(sf::Keyboard::Key::L) > 0 && scancode_map.at(sf::Keyboard::Key::L);
	}
	bool M()
	{
		return scancode_map.count(sf::Keyboard::Key::M) > 0 && scancode_map.at(sf::Keyboard::Key::M);
	}
	bool N()
	{
		return scancode_map.count(sf::Keyboard::Key::N) > 0 && scancode_map.at(sf::Keyboard::Key::N);
	}
	bool O()
	{
		return scancode_map.count(sf::Keyboard::Key::O) > 0 && scancode_map.at(sf::Keyboard::Key::O);
	}
	bool P()
	{
		return scancode_map.count(sf::Keyboard::Key::P) > 0 && scancode_map.at(sf::Keyboard::Key::P);
	}
	bool Q()
	{
		return scancode_map.count(sf::Keyboard::Key::Q) > 0 && scancode_map.at(sf::Keyboard::Key::Q);
	}
	bool R()
	{
		return scancode_map.count(sf::Keyboard::Key::R) > 0 && scancode_map.at(sf::Keyboard::Key::R);
	}
	bool S()
	{
		return scancode_map.count(sf::Keyboard::Key::S) > 0 && scancode_map.at(sf::Keyboard::Key::S);
	}
	bool T()
	{
		return scancode_map.count(sf::Keyboard::Key::T) > 0 && scancode_map.at(sf::Keyboard::Key::T);
	}
	bool U()
	{
		return scancode_map.count(sf::Keyboard::Key::U) > 0 && scancode_map.at(sf::Keyboard::Key::U);
	}
	bool V()
	{
		return scancode_map.count(sf::Keyboard::Key::V) > 0 && scancode_map.at(sf::Keyboard::Key::V);
	}
	bool W()
	{
		return scancode_map.count(sf::Keyboard::Key::W) > 0 && scancode_map.at(sf::Keyboard::Key::W);
	}
	bool X()
	{
		return scancode_map.count(sf::Keyboard::Key::X) > 0 && scancode_map.at(sf::Keyboard::Key::X);
	}
	bool Y()
	{
		return scancode_map.count(sf::Keyboard::Key::Y) > 0 && scancode_map.at(sf::Keyboard::Key::Y);
	}
	bool Z()
	{
		return scancode_map.count(sf::Keyboard::Key::Z) > 0 && scancode_map.at(sf::Keyboard::Key::Z);
	}
	bool Escape()
	{
		return scancode_map.count(sf::Keyboard::Key::Escape) > 0 && scancode_map.at(sf::Keyboard::Key::Escape);
	}
	bool LControl()
	{
		return scancode_map.count(sf::Keyboard::Key::LControl) > 0 && scancode_map.at(sf::Keyboard::Key::LControl);
	}
	bool LShift()
	{
		return scancode_map.count(sf::Keyboard::Key::LShift) > 0 && scancode_map.at(sf::Keyboard::Key::LShift);
	}
	bool Space()
	{
		return scancode_map.count(sf::Keyboard::Key::Space) > 0 && scancode_map.at(sf::Keyboard::Key::Space);
	}
	bool Enter()
	{
		return scancode_map.count(sf::Keyboard::Key::Enter) > 0 && scancode_map.at(sf::Keyboard::Key::Enter);
	}

	void trigger_scancode(int scan_code)
	{
		scancode_map.insert_or_assign(scan_code, true);
	}

	void untrigger_scancode(int scan_code)
	{
		scancode_map.insert_or_assign(scan_code, false);
	}
}