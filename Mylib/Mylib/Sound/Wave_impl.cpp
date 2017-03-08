#include"Mylib\Manager.h"
#include"Mylib\Sound\Wave_impl.h"

using namespace std;

namespace Mylib {
	namespace Sound {
		Wave_impl::Wave_impl(const string& filename, IDirectSound8* sound) :
			mSound{ sound },
			mBuffer{ nullptr },
			mFilename{ filename }
		{
			Mylib::Manager::instance().read_file(mFilename);
		}

		Wave_impl::~Wave_impl() {
			if (mBuffer) {
				mBuffer->Release();
				mBuffer = nullptr;
			}
			mSound = nullptr;
		}

		void Wave_impl::set_buffer(int frequency, int channels, int bps, int size, const char* data) {
			if (mSound) {
				// 読込んだデータから設定
				WAVEFORMATEX format;
				format.wFormatTag = WAVE_FORMAT_PCM;
				format.nChannels = static_cast< WORD >(channels);
				format.nSamplesPerSec = frequency;
				format.wBitsPerSample = static_cast< WORD >(bps);
				format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
				format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

				DSBUFFERDESC desc;
				desc.dwSize = sizeof(DSBUFFERDESC);
				desc.dwFlags = 0;
				desc.dwBufferBytes = size;
				desc.dwReserved = 0;
				desc.lpwfxFormat = &format;
				desc.guid3DAlgorithm = GUID_NULL;
				// データを書込み
				IDirectSoundBuffer* buffer = 0;
				HRESULT hr = mSound->CreateSoundBuffer(&desc, &buffer, NULL);
				if (SUCCEEDED(hr)) {
					hr = buffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&mBuffer);
				}
				buffer->Release();
				buffer = nullptr;
				mSound = nullptr;
				// メモリロック
				void* p0 = 0;
				DWORD s0;
				hr = mBuffer->Lock(0, 0, &p0, &s0, 0, 0, DSBLOCK_ENTIREBUFFER);
				if (SUCCEEDED(hr)) {
					if (s0 == static_cast< unsigned >(size)) {
						char* dst = static_cast<char*>(p0);
						const char* src = static_cast<const char*>(data);
						for (int i = 0; i < size; ++i) {
							dst[i] = src[i];
						}
					}
					mBuffer->Unlock(p0, s0, 0, 0);
				}
			}
		}

		bool Wave_impl::is_ready() {
			if (Mylib::Manager::instance().is_ready_file(mFilename)) {
				if (mBuffer) {
					// 読込み完了
					return true;
				}
				else {
					char* data;
					data = Mylib::Manager::instance().get_file_data(mFilename);
					int channels = data[22] + (static_cast<unsigned char>(data[23]) << 8);
					int frequency = data[24] +
						(static_cast<unsigned char>(data[25]) << 8) +
						(static_cast<unsigned char>(data[26]) << 16) +
						(static_cast<unsigned char>(data[27]) << 24);
					unsigned bps = data[34] + (static_cast<unsigned char>(data[35]) << 8);
					unsigned size = data[40] + 
						(static_cast<unsigned char>(data[41]) << 8) +
						(static_cast<unsigned char>(data[42]) << 16) +
						(static_cast<unsigned char>(data[43]) << 24);
					int pos = 44;
					set_buffer(frequency, channels, bps, size, data + pos);
					Mylib::Manager::instance().release_file(mFilename);
					return true;
				}
			}
			// まだ読み込めてない
			else {
				return false;
			}
		}

		IDirectSoundBuffer8* Wave_impl::get_buffer() {
			return mBuffer;
		}
	}
}