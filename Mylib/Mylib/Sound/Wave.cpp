#include"Mylib\Sound\Sound_impl.h"
#include"Mylib\Sound\Wave_impl.h"
#include"Mylib\Sound\Wave.h"

namespace Mylib {
	namespace Sound {
		Wave::Wave(const std::string& filename)
		{
			mWave = new Wave_impl(filename, Sound_impl::instance()->get_direct());
		}

		Wave::~Wave() {
			if (mWave) {
				delete mWave;
				mWave = nullptr;
			}
		}

	}
}