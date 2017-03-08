#ifndef MYLIB_SOUND_WAVE_IMPL_H
#define MYLIB_SOUND_WAVE_IMPL_H

#include<string>
#include<dsound.h>

namespace Mylib {
	namespace Sound {
		class Wave_impl {
		public:
			explicit Wave_impl(const std::string& filename, IDirectSound8* sound);
			~Wave_impl();
			// ファイル読込みが完了しているか
			bool is_ready();
			IDirectSoundBuffer8* get_buffer();
		private:
			// バッファにセット
			void set_buffer(int channels, int frequency, int bps, int size, const char* data);
			IDirectSound8* mSound;
			IDirectSoundBuffer8* mBuffer;
			std::string mFilename;
		};
	}
}


#endif
