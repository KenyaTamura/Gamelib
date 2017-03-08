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
		// Wave‚ð“n‚µ‚ÄÄ¶
		void Manager::play(Wave& wave) {
			Sound_impl::instance()->play(wave);
		}
		// Wave‚ð“n‚µ‚Ä’âŽ~
		void Manager::stop(Wave& wave) {
			Sound_impl::instance()->stop(wave);
		}
	}
}