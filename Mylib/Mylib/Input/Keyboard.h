#ifndef MYLIB_INPUT_KEYBOARD_H
#define MYLIB_INPUT_KEYBOARD_H

namespace Mylib {
	namespace Input {
		// キーボード関連
		class Keyboard {
		public:
			Keyboard();
			~Keyboard();
			enum Key { // isKeyOn,isKeyPressedの引数。a-z,0-9はそのまま
				KEY_BACK = 0x80,	// 128番以降を使う
				KEY_RETURN,
				KEY_TAB,
				KEY_ESC,
				KEY_SHIFT,
				KEY_CONTROL,
				KEY_ALT,
				KEY_F1,
				KEY_F2,
				KEY_F3,
				KEY_F4,
				KEY_F5,
				KEY_F6,
				KEY_F7,
				KEY_F8,
				KEY_F9,
				KEY_F10,
				KEY_F11,
				KEY_F12,
				KEY_UP,
				KEY_DOWN,
				KEY_LEFT,
				KEY_RIGHT,
				KEY_NUM0,
				KEY_NUM1,
				KEY_NUM2,
				KEY_NUM3,
				KEY_NUM4,
				KEY_NUM5,
				KEY_NUM6,
				KEY_NUM7,
				KEY_NUM8,
				KEY_NUM9,
			};
			bool is_on(int i) const;
			bool is_triggered(int i) const;
		};
	}
}

#endif
