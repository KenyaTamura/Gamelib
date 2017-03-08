#ifndef MYLIB_INPUT_MANAGER_H
#define MYLIB_INPUT_MANAGER_H

#include"Mylib\Input\Keyboard.h"
#include"Mylib\Input\Mouse.h"
#include"Mylib\Input\PS4.h"

// 入力デバイス関連
namespace Mylib {
	namespace Input {
		class Manager {
		public:
			Manager();
			~Manager();
			static Manager instance();

			Mouse get_mouse() const;
			Keyboard get_keyboard() const;
			int get_pad_num() const;
			PS4 get_pad(int number) const;
		};

	}
}

#endif