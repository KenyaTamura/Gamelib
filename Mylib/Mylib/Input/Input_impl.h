#ifndef MYLIB_INPUT_INPUTIMPL_H
#define MYLIB_INPUT_INPUTIMPL_H

#include"Mylib\Input\Mouse.h"

#include<windows.h>
#define	DIRECTINPUT_VERSION 0x0800
#include<dinput.h>

// 入力関連クラスの本体
namespace Mylib {
	namespace Input {
		class PS4_impl;
		class Input_impl {
		public:
			static Input_impl* instance();
			static void create(void* wh);
			static void destroy();
			void update();
			// マウス
			bool is_button_on(Mouse::Button i) const;
			bool is_button_triggered(Mouse::Button i) const;
			// キーボード
			bool is_key_on(int i) const;
			bool is_key_triggered(int i) const;
			// ゲームパッド(PS4)
			int get_pad_num() const;
			PS4_impl* get_pad(int number) const;
			//マウス
			int mX;
			int mY;
			int mVelocityX;
			int mVelocityY;
			int mWheel;
		private:
			explicit Input_impl(HWND);
			~Input_impl();
			void operator=(const Input_impl&);
			Input_impl(const Input_impl&);

			static int convert_keyID(int a);
			static BOOL CALLBACK count_callback(const DIDEVICEINSTANCE* instance, VOID* arg);
			static BOOL CALLBACK create_callback(const DIDEVICEINSTANCE* instance, VOID* arg);
			void create_device(const DIDEVICEINSTANCE* instance);

			static Input_impl* mInstance;

			const HWND mHwnd;
			int mDouble_buffer_index;

			// ゲームパッド
			int mPad_number;
			PS4_impl* mPads;
			int mEnumerated_pad;
			IDirectInput8* mDirect_input;
			// マウス
			static const int BUTTON_MAX = 3;
			bool mButtons[2][BUTTON_MAX];
			//キーボード
			static const int KEY_MAX = 256;
			bool mKeys[2][KEY_MAX];
		};
	}
}


#endif