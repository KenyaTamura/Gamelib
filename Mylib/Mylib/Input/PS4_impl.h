#ifndef MYLIB_INPUT_PS4_IMPL_H
#define MYLIB_INPUT_PS4_IMPL_H

#define	DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Mylib {
	namespace Input {
		class Input_impl;
		class PS4_impl {
		public:
			PS4_impl* instance();
			//上下左右の列挙型
			enum Button {
				BUTTON_UP = 128,
				BUTTON_DOWN,
				BUTTON_LEFT,
				BUTTON_RIGHT,
			};

			int get_analog_number() const;
			int get_analog(int i) const; //アナログスティック値取得
								  
			bool is_on(int i) const;
			bool is_triggered(int i) const;
			int get_button_number() const;
			//有効か
			bool is_enabled() const;
		private:
			PS4_impl();
			~PS4_impl();
			void operator=(const PS4_impl&);
			PS4_impl(const PS4_impl&);
			void create(IDirectInputDevice8* device, HWND windowHandle);
			void update();

			friend Input_impl;
			IDirectInputDevice8* mDevice;
			static const int BUTTON_MAX = 128 + 4; //上下左右分
			static const int ANALOG_MAX = 8;
			bool mButtons[2][BUTTON_MAX];
			int mAnalogs[8];
			int mDouble_buffer_index;
			bool mEnabled;
		};
	}
}


#endif
