#ifndef MYLIB_SOUND_WAVE_H
#define MYLIB_SOUND_WAVE_H

#include<string>

namespace Mylib {
	namespace Sound {
		class Wave_impl;
		class Wave {
		public:
			explicit Wave(const std::string& filename);
		private:
			Wave();
			~Wave();
			void operator=(const Wave&);
			Wave(const Wave&);
			Wave_impl* mWave;
			friend class Sound_impl;
		};
	}
}


#endif