#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\Keyboard.h"

namespace Mylib {
	namespace Input {
		Keyboard::Keyboard() {
		}

		Keyboard::~Keyboard() {
		}
		// キーが押されているか
		bool Keyboard::is_on(int i) const {
			Input_impl* in = Input_impl::instance();
			return in->is_key_on(i);
		}
		// キーが押されたか
		bool Keyboard::is_triggered(int i) const {
			Input_impl* in = Input_impl::instance();
			return in->is_key_triggered(i);
		}
	}
}
