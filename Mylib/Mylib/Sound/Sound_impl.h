#ifndef MYLIB_SOUND_SOUND_IMPL_H
#define MYLIB_SOUND_SOUND_IMPL_H 

#include<dsound.h>
#include<map>
#include<string>

namespace Mylib {
	namespace Sound {
		class Wave;
		class Sound_impl {
		public:
			static Sound_impl* instance();
			static void create(void* wh);
			static void destroy();

			IDirectSound8* get_direct();
			void play(Wave&);
			void stop(Wave&);
		private:
			explicit Sound_impl(HWND);
			Sound_impl();
			~Sound_impl();
			void operator=(const Sound_impl&);
			Sound_impl(const Sound_impl&);

			static Sound_impl* mInstance;
			IDirectSound8* mDirect_sound;
		};

	}
}



#endif