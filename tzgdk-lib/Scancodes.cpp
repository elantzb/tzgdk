#include "pch.h"
#include "Scancodes.h"

namespace tzgdk
{
	namespace sc
	{
		bool A()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::A) > 0 && admin::scancode_map.at(sf::Keyboard::Key::A);
		}
		bool B()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::B) > 0 && admin::scancode_map.at(sf::Keyboard::Key::B);
		}
		bool C()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::C) > 0 && admin::scancode_map.at(sf::Keyboard::Key::C);
		}
		bool D()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::D) > 0 && admin::scancode_map.at(sf::Keyboard::Key::D);
		}
		bool E()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::E) > 0 && admin::scancode_map.at(sf::Keyboard::Key::E);
		}
		bool F()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::F) > 0 && admin::scancode_map.at(sf::Keyboard::Key::F);
		}
		bool G()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::G) > 0 && admin::scancode_map.at(sf::Keyboard::Key::G);
		}
		bool H()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::H) > 0 && admin::scancode_map.at(sf::Keyboard::Key::H);
		}
		bool I()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::I) > 0 && admin::scancode_map.at(sf::Keyboard::Key::I);
		}
		bool J()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::J) > 0 && admin::scancode_map.at(sf::Keyboard::Key::J);
		}
		bool K()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::K) > 0 && admin::scancode_map.at(sf::Keyboard::Key::K);
		}
		bool L()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::L) > 0 && admin::scancode_map.at(sf::Keyboard::Key::L);
		}
		bool M()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::M) > 0 && admin::scancode_map.at(sf::Keyboard::Key::M);
		}
		bool N()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::N) > 0 && admin::scancode_map.at(sf::Keyboard::Key::N);
		}
		bool O()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::O) > 0 && admin::scancode_map.at(sf::Keyboard::Key::O);
		}
		bool P()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::P) > 0 && admin::scancode_map.at(sf::Keyboard::Key::P);
		}
		bool Q()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Q) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Q);
		}
		bool R()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::R) > 0 && admin::scancode_map.at(sf::Keyboard::Key::R);
		}
		bool S()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::S) > 0 && admin::scancode_map.at(sf::Keyboard::Key::S);
		}
		bool T()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::T) > 0 && admin::scancode_map.at(sf::Keyboard::Key::T);
		}
		bool U()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::U) > 0 && admin::scancode_map.at(sf::Keyboard::Key::U);
		}
		bool V()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::V) > 0 && admin::scancode_map.at(sf::Keyboard::Key::V);
		}
		bool W()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::W) > 0 && admin::scancode_map.at(sf::Keyboard::Key::W);
		}
		bool X()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::X) > 0 && admin::scancode_map.at(sf::Keyboard::Key::X);
		}
		bool Y()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Y) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Y);
		}
		bool Z()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Z) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Z);
		}
		bool Escape()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Escape) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Escape);
		}
		bool LControl()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::LControl) > 0 && admin::scancode_map.at(sf::Keyboard::Key::LControl);
		}
		bool LShift()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::LShift) > 0 && admin::scancode_map.at(sf::Keyboard::Key::LShift);
		}
		bool Space()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Space) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Space);
		}
		bool Enter()
		{
			return admin::scancode_map.count(sf::Keyboard::Key::Enter) > 0 && admin::scancode_map.at(sf::Keyboard::Key::Enter);
		}
	}

	namespace admin
	{
		std::map<int, bool> scancode_map;

		void trigger_scancode(int scan_code)
		{
			scancode_map.insert_or_assign(scan_code, true);
		}

		void untrigger_scancode(int scan_code)
		{
			scancode_map.insert_or_assign(scan_code, false);
		}
	}
}