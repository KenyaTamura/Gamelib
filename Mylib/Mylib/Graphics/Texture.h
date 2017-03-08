#ifndef MYLIB_GRAPHICS_TEXTURE_H
#define MYLIB_GRAPHICS_TEXTURE_H

#include<string>

namespace Mylib {
	namespace Graphics {
		class Graphics_impl;
		class Texture_impl;
		// �摜��`�悷�邽�߂̏���
		// �t�@�C�������f�[�^�ƃT�C�Y��n���č��
		class Texture {
		public:
			// ��芸����dds����
			explicit Texture(const std::string& filename);
			// �f�[�^���󂯎���ăe�N�X�`�������
			// ��ɉ摜�̐؂蕪���Ɏg��
			Texture(const unsigned* data, int width, int height);
			~Texture();
			// ���p�o���邩�m�F
			bool is_ready();
			// �摜���
			int get_width() const;
			int get_height() const;
			const unsigned* get_data();
		private:
			Texture_impl* mInstance;
			friend Graphics_impl;
		};

	}
}

#endif
