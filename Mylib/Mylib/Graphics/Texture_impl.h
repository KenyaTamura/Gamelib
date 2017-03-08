#ifndef MYLIB_GRAPHICS_TEXTUREIMPL_H
#define MYLIB_GRAPHICS_TEXTUREIMPL_H

#include<string>
#include<d2d1.h>

namespace Mylib {
	namespace Graphics {
		// �摜�`�揀���̎�����
		class Texture_impl {
		public:
			// ��芸����dds����
			explicit Texture_impl(const std::string& filename);
			// �f�[�^���󂯎���ăe�N�X�`�������
			// ��ɉ摜�̐؂蕪���Ɏg��
			Texture_impl(const unsigned* data, int width, int height);
			~Texture_impl();
			// ���p�o���邩�m�F
			bool is_ready();
			// �摜���
			int get_width() const;
			int get_height() const;
			const unsigned* get_data();
			// ���p�҂͋C�ɂ��Ȃ�
			ID2D1Bitmap* get_bitmap() const;
			bool is_bitmap(ID2D1RenderTarget*);
		private:
			void analyze_dds(const char* data);
			unsigned convert_unsigned(const char* data) const;
			enum EXTENTION {
				FORMAT_DDS,
				NOT_DEFINE
			};
			int mWidth;
			int mHeight;
			unsigned* mData;
			std::string mFilename;
			EXTENTION mFormat;
			ID2D1Bitmap *mBitmap;	// �`��Ɏg���r�b�g�}�b�v
		};

	}
}

#endif
