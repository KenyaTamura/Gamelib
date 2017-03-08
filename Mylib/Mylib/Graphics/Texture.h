#ifndef MYLIB_GRAPHICS_TEXTURE_H
#define MYLIB_GRAPHICS_TEXTURE_H

#include<string>

namespace Mylib {
	namespace Graphics {
		class Graphics_impl;
		class Texture_impl;
		// 画像を描画するための準備
		// ファイル名かデータとサイズを渡して作る
		class Texture {
		public:
			// 取り敢えずdds限定
			explicit Texture(const std::string& filename);
			// データを受け取ってテクスチャを作る
			// 主に画像の切り分けに使う
			Texture(const unsigned* data, int width, int height);
			~Texture();
			// 利用出来るか確認
			bool is_ready();
			// 画像情報
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
