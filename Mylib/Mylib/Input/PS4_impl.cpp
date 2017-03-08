#include"Mylib\Input\PS4_impl.h"

#include<cassert>

namespace Mylib {
	namespace Input {
		PS4_impl::PS4_impl() : 
			mDouble_buffer_index{ 0 },
			mEnabled{ false },
			mDevice{ nullptr }
		{
			for (int i = 0; i < BUTTON_MAX; ++i) {
				mButtons[0][i] = false;
				mButtons[1][i] = false;
			}
			for (int i = 0; i < ANALOG_MAX; ++i) {
				mAnalogs[i] = 0;
			}
		}

		PS4_impl::~PS4_impl() {
			if (mDevice) {
				mDevice->Unacquire();
				mDevice->Release();
				mDevice = nullptr;
			}
		}

		void PS4_impl::create(IDirectInputDevice8* device, HWND windowHandle) {
			mDevice = device;
			HRESULT hr;
			hr = mDevice->SetDataFormat(&c_dfDIJoystick2);
			assert(SUCCEEDED(hr));
			hr = mDevice->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
			assert(SUCCEEDED(hr));
		}

		void PS4_impl::update() {
			mDouble_buffer_index = 1 - mDouble_buffer_index;

			HRESULT hr = mDevice->Acquire();
			assert(hr != DIERR_INVALIDPARAM);
			assert(hr != DIERR_NOTINITIALIZED);
			DIJOYSTATE2 state;
			hr = mDevice->GetDeviceState(sizeof(DIJOYSTATE2), &state);
			if (SUCCEEDED(hr)) {
				for (int i = 0; i < BUTTON_MAX; ++i) {
					mButtons[mDouble_buffer_index][i] = state.rgbButtons[i] ? true : false;
				}
				mAnalogs[0] = state.lX;
				mAnalogs[1] = state.lY;
				mAnalogs[2] = state.lZ;
				mAnalogs[3] = state.lRx;
				mAnalogs[4] = state.lRy;
				mAnalogs[5] = state.lRz;
				mAnalogs[6] = state.rglSlider[0];
				mAnalogs[7] = state.rglSlider[1];
				int pov = state.rgdwPOV[0];

				int dx = 0;
				int dy = 0;
				if ((pov & 0xffff) != 0xffff) {
					//8•ûŒü”»’è
					if (pov > 36000 * 15 / 16) {
						dx = 0;
					}
					else if (pov > 36000 * 9 / 16) {
						dx = -1;
					}
					else if (pov > 36000 * 7 / 16) {
						dx = 0;
					}
					else if (pov > 36000 * 1 / 16) {
						dx = 1;
					}
					else {
						dx = 0;
					}
					if (pov > 36000 * 13 / 16) {
						dy = 1;
					}
					else if (pov > 36000 * 11 / 16) {
						dy = 0;
					}
					else if (pov > 36000 * 5 / 16) {
						dy = -1;
					}
					else if (pov > 36000 * 3 / 16) {
						dy = 0;
					}
					else {
						dy = 1;
					}
				}
				if (dx > 0) {
					mButtons[mDouble_buffer_index][BUTTON_RIGHT] = true;
					mButtons[mDouble_buffer_index][BUTTON_LEFT] = false;
				}
				else if (dx < 0) {
					mButtons[mDouble_buffer_index][BUTTON_RIGHT] = false;
					mButtons[mDouble_buffer_index][BUTTON_LEFT] = true;
				}
				if (dy > 0) {
					mButtons[mDouble_buffer_index][BUTTON_UP] = true;
					mButtons[mDouble_buffer_index][BUTTON_DOWN] = false;
				}
				else if (dy < 0) {
					mButtons[mDouble_buffer_index][BUTTON_UP] = false;
					mButtons[mDouble_buffer_index][BUTTON_DOWN] = true;
				}
				mEnabled = true;
			}
			else {
				for (int i = 0; i < BUTTON_MAX; ++i) {
					mButtons[mDouble_buffer_index][i] = false;
				}
				for (int i = 0; i < ANALOG_MAX; ++i) {
					mAnalogs[i] = 0;
				}
				mEnabled = false;
			}
		}

		PS4_impl* PS4_impl::instance() {
			return this;
		}

		int PS4_impl::get_analog_number() const {
			return ANALOG_MAX;
		}
		
		int PS4_impl::get_analog(int i) const {
			assert(i < ANALOG_MAX);
			return mAnalogs[i];
		}

		bool PS4_impl::is_on(int i) const {
			assert(i < BUTTON_MAX);
			return mButtons[mDouble_buffer_index][i];
		}

		bool PS4_impl::is_triggered(int i) const {
			assert(i < BUTTON_MAX);
			int idx = mDouble_buffer_index;
			return mButtons[idx][i] && (!mButtons[1 - idx][i]);
		}

		int PS4_impl::get_button_number() const {
			return BUTTON_MAX - 4;
		}
		
		bool PS4_impl::is_enabled() const {
			return mEnabled;
		}
	}
}