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

			// 読み込んだ画像を描画
			void draw_image(const Texture& texture, int posX, int posY, float rotation = 0.0f, float extendX = 1.0f, float extendY = 1.0f) const;
			// 文字出力
			void draw_string(const char* str, int posX, int posY) const;
			// 文字入力、cin代わり、Enterでtrue
			bool get_string(std::string* out, int posX, int posY);
			// 色替え
			void set_format(float size, unsigned color = 0xffffffff);
		};
	}
}


#endif