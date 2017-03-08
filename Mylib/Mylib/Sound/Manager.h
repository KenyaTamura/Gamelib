#ifndef MYLIB_SOUND_MANAGER_H
#define MYLIB_SOUND_MANAGER_H

#include<string>
#include"Mylib\Sound\Wave.h"

namespace Mylib {
	namespace Sound {
		class Manager {
		public:
			Manager();
			~Manager();
			static Manager instance();
			// �炷
			void play(Wave& wave);
			// �~�߂�
			void stop(Wave& wave);
		};
	}
}


#endif