#ifndef MYLIB_GRAPHICS_MANAGER_H
#define MYLIB_GRAPHICS_MANAGER_H

#include<string>
#include"Mylib\Graphics\Texture.h"

namespace Mylib {
	namespace Graphics {
		class Manager {
		public:
			Manager();
			~Manager();

			static Manager instance();

			// �ǂݍ��񂾉摜��`��
			void draw_image(const Texture& texture, int posX, int posY, float rotation = 0.0f, float extendX = 1.0f, float extendY = 1.0f) const;
			// �����o��
			void draw_string(const char* str, int posX, int posY) const;
			// �������́Acin����AEnter��true
			bool get_string(std::string* out, int posX, int posY);
			// �F�ւ�
			void set_format(float size, unsigned color = 0xffffffff);
		};
	}
}


#endif