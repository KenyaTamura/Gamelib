#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\Keyboard.h"
#include"Mylib\Input\PS4_impl.h"
#include"Mylib\Window\Window.h"

#include<cassert>

namespace Mylib {
	namespace Input {
		Input_impl* Input_impl::mInstance = 0;

		Input_impl::Input_impl(HWND wh) :
			mX{ 0 },
			mY{ 0 },
			mVelocityX{ 0 },
			mVelocityY{ 0 },
			mWheel{ 0 },
			mPad_number{ 0 },
			mPads{ 0 },
			mEnumerated_pad{ 0 },
			mHwnd{ wh },
			mDouble_buffer_index{ 0 }
		{
			HRESULT hr;
			HINSTANCE hi = GetModuleHandle(0);
			assert(hi);
			hr = DirectInput8Create(hi, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirect_input, 0);
			assert(SUCCEEDED(hr));
			//まず数えて確保
			hr = mDirect_input->EnumDevices(DI8DEVCLASS_ALL, count_callback, this, DIEDFL_ATTACHEDONLY);
			assert(SUCCEEDED(hr));
			if (mPad_number > 0) {
				mPads = new PS4_impl[mPad_number];
			}
			hr = mDirect_input->EnumDevices(DI8DEVCLASS_ALL, create_callback, this, DIEDFL_ATTACHEDONLY);
			assert(SUCCEEDED(hr));
			//マウスボタン初期化
			for (int i = 0; i < BUTTON_MAX; ++i) {
				mButtons[0][i] = false;
				mButtons[1][i] = false;
			}
			//キー初期化
			for (int i = 0; i < KEY_MAX; ++i) {
				mKeys[0][i] = false;
				mKeys[1][i] = false;
			}
		}

		Input_impl::~Input_impl() {
			if (mPads) {
				delete[] mPads;
				mPads = nullptr;
			}
			mDirect_input->Release();
			mDirect_input = nullptr;
		}

		Input_impl* Input_impl::instance() {
			return mInstance;
		}

		void Input_impl::create(void* wh) {
			if (!mInstance) {
				mInstance = new Input_impl(static_cast<HWND>(wh));
			}
		}

		void Input_impl::destroy() {
			if (mInstance) {
				delete mInstance;
				mInstance = nullptr;
			}
		}

		void Input_impl::update() {
			mDouble_buffer_index = 1 - mDouble_buffer_index;	// バッファ入れ替え

			//マウスカーソルを取得して、位置を変換してからマウスにセット
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(mHwnd, &pos);
			int x = pos.x;
			int y = pos.y;
			mVelocityX = x - mX;
			mVelocityY = y - mY;
			mX = x;
			mY = y;
			Window win = Window::instance();
			if (win.is_active()) {
				//キーボード
				unsigned char keys[KEY_MAX];
				GetKeyboardState(keys);
				for (int i = 0; i < KEY_MAX; ++i) {
					mKeys[mDouble_buffer_index][i] = ((keys[i] & 0x80) != 0) ? true : false;
				}
				//マウス
				mButtons[mDouble_buffer_index][0] = (GetAsyncKeyState(VK_LBUTTON) & 0xf000) ? true : false;
				mButtons[mDouble_buffer_index][1] = (GetAsyncKeyState(VK_RBUTTON) & 0xf000) ? true : false;
				mButtons[mDouble_buffer_index][2] = (GetAsyncKeyState(VK_MBUTTON) & 0xf000) ? true : false;
				mWheel = win.get_and_reset_mousewheel();
			}
			else {
				//キーボード
				for (int i = 0; i < KEY_MAX; ++i) {
					mKeys[mDouble_buffer_index][i] = false;
				}
				//マウス
				for (int i = 0; i < BUTTON_MAX; ++i) {
					mButtons[mDouble_buffer_index][i] = false;
				}
				mWheel = 0;
			}
			// ゲームパッド
			for (int i = 0; i < mPad_number; ++i) {
				mPads[i].update();
			}
		}

		bool Input_impl::is_button_on(Mouse::Button i) const {
			assert(i < BUTTON_MAX);
			return mButtons[mDouble_buffer_index][i];
		}

		bool Input_impl::is_button_triggered(Mouse::Button i) const {
			assert(i < BUTTON_MAX);
			int idx = mDouble_buffer_index;
			return mButtons[idx][i] && (!mButtons[1 - idx][i]);
		}

		bool Input_impl::is_key_on(int i) const {
			assert(i < KEY_MAX);
			int idx = mDouble_buffer_index;
			int k = convert_keyID(i);
			return mKeys[idx][k];
		}

		bool Input_impl::is_key_triggered(int i) const {
			assert(i < KEY_MAX);
			int idx = mDouble_buffer_index;
			int k = convert_keyID(i);
			return mKeys[idx][k] & (!mKeys[1 - idx][k]);
		}

		int Input_impl::get_pad_num() const {
			return mEnumerated_pad;
		}

		PS4_impl* Input_impl::get_pad(int number) const {
			assert(number < mEnumerated_pad);
			return mPads[number].instance();
		}

		int Input_impl::convert_keyID(int a) {
			typedef Keyboard K;
			int r = 0;
			if (a >= 'a' && a <= 'z') { //大文字に変換
				a = 'A' + (a - 'a');
			}
			bool isAlpha = (a >= 'A' && a <= 'Z');
			bool isNum = (a >= '0' && a <= '9');
			if (isAlpha || isNum) {
				r = a;
			}
			if (r == 0) {
				switch (a) {
				case ' ': r = VK_SPACE; break;
				case '*': r = VK_OEM_1; break;
				case '+': r = VK_OEM_PLUS; break;
				case ',': r = VK_OEM_COMMA; break;
				case '-': r = VK_OEM_MINUS; break;
				case '.': r = VK_OEM_PERIOD; break;
				case '/': r = VK_OEM_2; break;
				case '@': r = VK_OEM_3; break;
				case '[': r = VK_OEM_4; break;
				case '\\': r = VK_OEM_5; break;
				case ']': r = VK_OEM_6; break;
				case '^': r = VK_OEM_7; break;
				case '_': r = VK_OEM_102; break;
				case K::KEY_BACK: r = VK_BACK; break;
				case K::KEY_RETURN: r = VK_RETURN; break;
				case K::KEY_TAB: r = VK_TAB; break;
				case K::KEY_ESC: r = VK_ESCAPE; break;
				case K::KEY_SHIFT: r = VK_SHIFT; break;
				case K::KEY_CONTROL: r = VK_CONTROL; break;
				case K::KEY_ALT: r = VK_MENU; break;
				case K::KEY_F1: r = VK_F1; break;
				case K::KEY_F2: r = VK_F2; break;
				case K::KEY_F3: r = VK_F3; break;
				case K::KEY_F4: r = VK_F4; break;
				case K::KEY_F5: r = VK_F5; break;
				case K::KEY_F6: r = VK_F6; break;
				case K::KEY_F7: r = VK_F7; break;
				case K::KEY_F8: r = VK_F8; break;
				case K::KEY_F9: r = VK_F9; break;
				case K::KEY_F10: r = VK_F10; break;
				case K::KEY_F11: r = VK_F11; break;
				case K::KEY_F12: r = VK_F12; break;
				case K::KEY_UP:	r = VK_UP; break;
				case K::KEY_DOWN: r = VK_DOWN; break;
				case K::KEY_LEFT: r = VK_LEFT; break;
				case K::KEY_RIGHT: r = VK_RIGHT; break;
				case K::KEY_NUM0: r = VK_NUMPAD0; break;
				case K::KEY_NUM1: r = VK_NUMPAD1; break;
				case K::KEY_NUM2: r = VK_NUMPAD2; break;
				case K::KEY_NUM3: r = VK_NUMPAD3; break;
				case K::KEY_NUM4: r = VK_NUMPAD4; break;
				case K::KEY_NUM5: r = VK_NUMPAD5; break;
				case K::KEY_NUM6: r = VK_NUMPAD6; break;
				case K::KEY_NUM7: r = VK_NUMPAD7; break;
				case K::KEY_NUM8: r = VK_NUMPAD8; break;
				case K::KEY_NUM9: r = VK_NUMPAD9; break;
				}
			}
			return r;
		}

		BOOL CALLBACK Input_impl::count_callback(const DIDEVICEINSTANCE* instance, VOID* arg) {
			int type = instance->dwDevType & 0xff; //下位バイトがタイプ
			Input_impl* self = static_cast< Input_impl* >(arg);
			if (type == DI8DEVTYPE_GAMEPAD) {
				++(self->mPad_number);
			}
			return DIENUM_CONTINUE;
		}

		BOOL CALLBACK Input_impl::create_callback(const DIDEVICEINSTANCE* instance, VOID* arg) {
			Input_impl* self = static_cast< Input_impl* >(arg);
			self->create_device(instance);
			return DIENUM_CONTINUE;
		}

		void Input_impl::create_device(const DIDEVICEINSTANCE* instance) {
			int type = instance->dwDevType & 0xff; //下位バイトがタイプ
			IDirectInputDevice8* device;
			HRESULT hr = mDirect_input->CreateDevice(instance->guidInstance, &device, 0);
			assert(SUCCEEDED(hr));

			if (type == DI8DEVTYPE_GAMEPAD) {
				mPads[mEnumerated_pad].create(device, mHwnd);
				++mEnumerated_pad;
			}
		}
	}
}