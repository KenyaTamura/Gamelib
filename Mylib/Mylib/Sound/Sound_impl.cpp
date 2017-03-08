#include"Mylib\Sound\Sound_impl.h"
#include"Mylib\Sound\Wave.h"
#include"Mylib\Sound\Wave_impl.h"

namespace Mylib {
	namespace Sound {
		Sound_impl* Sound_impl::mInstance = 0;

		Sound_impl::Sound_impl(HWND hwnd){
			HRESULT hr = DirectSoundCreate8(NULL, &mDirect_sound, NULL);
			if (SUCCEEDED(hr)) {
				hr = mDirect_sound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
			}
		};

		Sound_impl::~Sound_impl() {
			mDirect_sound->Release();
			mDirect_sound = nullptr;
		}

		IDirectSound8* Sound_impl::get_direct() {
			return mDirect_sound;
		}

		Sound_impl* Sound_impl::instance() {
			return mInstance;
		}

		void Sound_impl::create(void* wh) {
			if (!mInstance) {
				mInstance = new Sound_impl(static_cast<HWND>(wh));
			}
		}

		void Sound_impl::destroy() {
			if (mInstance) {
				delete mInstance;
				mInstance = nullptr;
			}
		}

		void Sound_impl::play(Wave& wave) {
			if (wave.mWave->is_ready()) {
				wave.mWave->get_buffer()->Play(0, 0, true);
			}
		}

		void Sound_impl::stop(Wave& wave) {
			if (wave.mWave->is_ready()) {
				wave.mWave->get_buffer()->Stop();
			}
		}

	}
}