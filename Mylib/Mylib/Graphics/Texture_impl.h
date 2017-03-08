#ifndef MYLIB_GRAPHICS_TEXTUREIMPL_H
#define MYLIB_GRAPHICS_TEXTUREIMPL_H

#include<string>
#include<d2d1.h>

namespace Mylib {
	namespace Graphics {
		// 画像描画準備の実装部
		class Texture_impl {
		public:
			// 取り敢えずdds限定
			explicit Texture_impl(const std::string& filename);
			// データを受け取ってテクスチャを作る
			// 主に画像の切り分けに使う
			Texture_impl(const unsigned* data, int width, int height);
			~Texture_impl();
			// 利用出来るか確認
			bool is_ready();
			// 画像情報
			int get_width() const;
			int get_height() const;
			const unsigned* get_data();
			// 利用者は気にしない
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
			ID2D1Bitmap *mBitmap;	// 描画に使うビットマップ
		};

	}
}

#endif
