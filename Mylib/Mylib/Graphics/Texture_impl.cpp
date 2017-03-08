#include"Mylib\FileIO\Manager.h"
#include"Mylib\Graphics\Graphics_impl.h"
#include"Mylib\Graphics\Texture_impl.h"
#include<cassert>

namespace Mylib {
	namespace Graphics{
		Texture_impl::Texture_impl(const std::string& filename) :
			mData{ nullptr },
			mWidth{ 0 },
			mHeight{ 0 },
			mFormat{ EXTENTION::NOT_DEFINE },
			mBitmap{ nullptr },
			mFilename{ filename }
		{
			std::string format;
			format.assign(mFilename, mFilename.size() - 4, mFilename.size() - 1);	// �{���͒��g�Ŕ��f����ׂ�
			if (format == ".dds") {
				mFormat = FORMAT_DDS;
			}
			else {
				// �w��O�̌`��
				assert(0);
			}
			FileIO::Manager::instance().read(mFilename);
		}

		Texture_impl::Texture_impl(const unsigned* data, int width, int height) :
			mData{ nullptr },
			mWidth{ 0 },
			mHeight{ 0 },
			mFormat{ EXTENTION::NOT_DEFINE },
			mBitmap{ nullptr },
			mFilename{ 0 }
		{
			mHeight = height;
			mWidth = width;
			mData = new unsigned int[mHeight * mWidth];
			for (int i = 0; i < mHeight*mWidth; ++i) {
				mData[i] = data[i];
			}
		}
		
		Texture_impl::~Texture_impl() {
			if (mData) {
				delete[] mData;
				mData = nullptr;
			}
			if (mBitmap) {
				mBitmap->Release();
				mBitmap = nullptr;
			}
		}

		bool Texture_impl::is_ready(){
			if (mData) {
				return true;
			}
			FileIO::Manager fileio = FileIO::Manager::instance();
			if (fileio.is_ready_file(mFilename)) {
				char* s;
				s = fileio.get_data(mFilename);
				// �g���q�ŕ���
				switch (mFormat) {
				case FORMAT_DDS:
					analyze_dds(s);
					break;
				}
				fileio.release_file(mFilename);
				delete[] s;
				return true;
			}
			// �t�@�C�����Ǎ��߂ĂȂ�
			else {
				return false;
			}
		}

		ID2D1Bitmap* Texture_impl::get_bitmap() const {
			if (mBitmap) {
				return mBitmap;
			}
			// �܂��o���ĂȂ�
			else {
				return 0;
			}
		}

		int Texture_impl::get_width() const {
			return mWidth;
		}

		int Texture_impl::get_height() const {
			return mHeight;
		}

		const unsigned* Texture_impl::get_data() {
			if (mData) {
				return mData;
			}
			else if (is_ready()) {
				return mData;
			}
			// �܂��ǂݍ��߂ĂȂ�
			else {
				return 0;
			}
		}

		bool Texture_impl::is_bitmap(ID2D1RenderTarget* render) {
			if (mBitmap) {
				return true;
			}
			else if (is_ready()) {
				// �r�b�g�}�b�v�쐬
				D2D1_PIXEL_FORMAT pf = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
				D2D1_BITMAP_PROPERTIES bitpor = D2D1::BitmapProperties(pf);
				UINT32 pitch = mWidth * 4;
				render->CreateBitmap(D2D1::SizeU(mWidth, mHeight), mData, pitch, bitpor, &mBitmap);
				return true;
			}
			// �܂��o���ĂȂ�
			else {
				return false;
			}
		}

		void Texture_impl::analyze_dds(const char* data) {
			mHeight = convert_unsigned(data + 12);
			mWidth = convert_unsigned(data + 16);
			mData = new unsigned int[mHeight * mWidth];
			for (int i = 0; i < mHeight*mWidth; ++i) {
				mData[i] = convert_unsigned(data + (128 + i * 4));
			}
		}

		unsigned Texture_impl::convert_unsigned(const char* data) const {
			unsigned int r = 0;
			r = static_cast<unsigned char>(data[0]);
			r |= static_cast<unsigned char>(data[1]) << 8;
			r |= static_cast<unsigned char>(data[2]) << 16;
			r |= static_cast<unsigned char>(data[3]) << 24;
			return r;
		}

	}
}