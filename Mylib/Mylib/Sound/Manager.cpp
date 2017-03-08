#include"Mylib\Sound\Manager.h"
#include"Mylib\Sound\Sound_impl.h"

namespace Mylib {
	namespace Sound {
		Manager::Manager() {
		}

		Manager::~Manager() {
		}

		Manager Manager::instance() {
			return Manager();
		}
		// Wave��n���čĐ�
		void Manager::play(Wave& wave) {
			Sound_impl::instance()->play(wave);
		}
		// Wave��n���Ē�~
		void Manager::stop(Wave& wave) {
			Sound_impl::instance()->stop(wave);
		}
	}
}