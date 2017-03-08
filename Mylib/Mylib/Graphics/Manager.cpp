#include"Mylib\Graphics\Graphics_impl.h"
#include"Mylib\Graphics\Manager.h"

namespace Mylib {
	namespace Graphics {
		
		Manager::Manager(){}

		Manager::~Manager(){}

		Manager Manager::instance() {
			return Manager();
		}
		// Textureを描画
		void Manager::draw_image(const Texture& texture, int posX, int posY, float rotation, float extendX, float extendY) const{
			Graphics_impl::instance()->draw_image(texture, posX, posY, rotation, extendX, extendY);
		}
		// 文字列出力
		void Manager::draw_string(const char* str, int posX, int posY) const{
			Graphics_impl::instance()->draw_string(str, posX, posY);
		}
		// 文字入力
		bool Manager::get_string(std::string* out, int posX, int posY) {
			return Graphics_impl::instance()->get_string(out, posX, posY);
		}
		// 文字のフォーマット
		void Manager::set_format(float size, unsigned color) {
			Graphics_impl::instance()->set_format(size, color);
		}

	}
}