#ifndef MYLIB_GRAPHICS_GRAPHICSIMPL_H
#define MYLIB_GRAPHICS_GRAPHICSIMPL_H

#include<windows.h>
#include<string>
#include<vector>
#include<d2d1.h>
#include<dwrite.h>

namespace Mylib {
	namespace Graphics {
		class Texture;
		// 出力関連の実装部
		class Graphics_impl {
		public:
			static Graphics_impl* instance();
			static void create(void* wh);
			static void destroy();
			// 読み込んだ画像を描画
			void draw_image(const Texture& texture, int posX, int posY, float rotation = 0.0f, float extendX = 1.0f, float extendY = 1.0f) const;
			// 文字出力
			void draw_string(const char* str, int posX, int posY) const;
			// 文字入力、cin代わり、Enterでtrue
			bool get_string(std::string* out, int posX, int posY);
			// 色替え
			void set_format(float size, unsigned color = 0xffffffff);
			// 描画準備
			void begin_draw();
			void end_draw();
		private:
			explicit Graphics_impl(HWND);
			~Graphics_impl();
			void operator=(const Graphics_impl&);
			Graphics_impl(const Graphics_impl&);

			D2D1::ColorF convert_color_unsigned(unsigned in) const;

			PAINTSTRUCT mPs;
			ID2D1Factory* mFactory;
			ID2D1HwndRenderTarget* mRender;
			// 文字関連
			ID2D1SolidColorBrush* mText_color;
			IDWriteFactory* mWrite_factory;
			IDWriteTextFormat* mText_format;
			const WCHAR* FONT_NAME = L"consolas";
			FLOAT mFont_size;
			std::string mBuffer;
			bool mInput_end;
			static const int STRING_MAX = 1024;
			const float PER_255 = 1.0f / 255.0f;

			static Graphics_impl* mInstance;
			const HWND mHwnd;
		};

	}
}

#endif