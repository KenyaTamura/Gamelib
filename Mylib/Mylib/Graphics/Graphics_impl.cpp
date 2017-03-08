#include"Mylib\Framework.h"
#include"Mylib\Input\Keyboard.h"
#include"Mylib\Graphics\Graphics_impl.h"
#include"Mylib\Graphics\Texture.h"
#include"Mylib\Graphics\Texture_impl.h"
#include<cassert>

using namespace std;

namespace Mylib {
	namespace Graphics {
		Graphics_impl* Graphics_impl::mInstance = 0;

		Graphics_impl::Graphics_impl(HWND hwnd) :
			mHwnd{ hwnd },
			mFactory{ nullptr },
			mRender{ nullptr },
			mWrite_factory{ nullptr },
			mText_format{ nullptr },
			mText_color{ nullptr },
			mFont_size{ 16 },
			mInput_end{ false }
		{
			HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory);
			if (SUCCEEDED(hr)) {
				// 文字出力関係
				hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(mWrite_factory), reinterpret_cast<IUnknown **>(&mWrite_factory));
				if (SUCCEEDED(hr)) {
					hr = mWrite_factory->CreateTextFormat(FONT_NAME, NULL,
						DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
						mFont_size, L"", &mText_format);
				}
				Framework* f = Framework::instance();
				D2D1_SIZE_U size = D2D1::SizeU(f->get_width(), f->get_height());
				hr = mFactory->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),
					D2D1::HwndRenderTargetProperties(mHwnd, size),
					&mRender);
				if (SUCCEEDED(hr)) {
					D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::White);
					mRender->CreateSolidColorBrush(color, &mText_color);
				}
				else {
					assert(0);
				}
			}
			else {
				assert(0);	// 失敗
			}
		}

		Graphics_impl::~Graphics_impl() {
			mFactory->Release();
			mFactory = nullptr;
			mRender->Release();
			mRender = nullptr;
			mWrite_factory->Release();
			mWrite_factory = nullptr;
			mText_format->Release();
			mText_format = nullptr;
		}

		Graphics_impl* Graphics_impl::instance() {
			return mInstance;
		}

		void Graphics_impl::create(void* wh) {
			if (!mInstance) {
				mInstance = new Graphics_impl(static_cast<HWND>(wh));
			}
		}

		void Graphics_impl::destroy() {
			if (mInstance) {
				delete mInstance;
				mInstance = 0;
			}
		}

		void Graphics_impl::draw_image(const Texture& texture, int posX, int posY, float rotation, float extendX, float extendY) const {
			if (!texture.mInstance->is_bitmap(mRender)) {
				return;
			}
			D2D1::Matrix3x2F matrix1 =   // 中心で回してから
				D2D1::Matrix3x2F::Rotation(
					rotation, 
					D2D1::Point2F(static_cast<FLOAT>(posX + texture.get_width() / 2),
					static_cast<FLOAT>(posY + texture.get_height() / 2))
					);
			D2D1::Matrix3x2F matrix2 =   // 拡大
				D2D1::Matrix3x2F::Scale(
					extendX, 
					extendY, 
					D2D1::Point2F(static_cast<FLOAT>(posX), static_cast<FLOAT>(posY))
					);
			//回転と拡大を合わせる 
			D2D1::Matrix3x2F matrix3 = matrix1 * matrix2;
			// 行列セット
			mRender->SetTransform(matrix3);		
			// 描画
			mRender->DrawBitmap(
				texture.mInstance->get_bitmap(),
				D2D1::RectF(static_cast<FLOAT>(posX), static_cast<FLOAT>(posY),
					static_cast<FLOAT>(posX + texture.get_width()), static_cast<FLOAT>(posY + texture.get_height()))
				);
			mRender->SetTransform(D2D1::Matrix3x2F::Rotation(0));	// 元に戻す
		}

		void Graphics_impl::draw_string(const char* str, int posX, int posY) const {
			RECT rc;
			GetClientRect(mHwnd, &rc);
			WCHAR wc[STRING_MAX];
			size_t len;
			setlocale(LC_CTYPE, "jpn");
			mbstowcs_s(&len, wc, STRING_MAX, str, _TRUNCATE);
			mRender->DrawText(
				wc,
				len - 1,
				mText_format,
				D2D1::RectF(static_cast<FLOAT>(posX), static_cast<FLOAT>(posY), static_cast<FLOAT>(rc.right), static_cast<FLOAT>(rc.bottom)),
				mText_color
				);
		}

		bool Graphics_impl::get_string(string* out, int posX, int posY) {
			// cin代わり
			Input::Keyboard k;
			Graphics_impl* g = instance();
			bool entered = false;
			// EnterとBack spaceは個別
			if (k.is_triggered(Input::Keyboard::KEY_RETURN)) {
				// 文字入力がまだならスルー
				if (g->mInput_end) {
					g->mBuffer += '\n';
					entered = true;
				}
			}
			else if (k.is_triggered(Input::Keyboard::KEY_BACK)) {
				// 一度スペースを表示して文字を消す
				if (g->mBuffer.size() > 0) {
					g->mBuffer.pop_back();
				}
				if (g->mBuffer.size() == 0) {
					g->mInput_end = false;
				}
			}
			for (int i = 0; i < 0x80; ++i) { //キー全部見る
				if (k.is_triggered(i)) {
					// 大文字はShiftを押してるときだけ
					if (i >= 'A' && i <= 'Z' && k.is_on(Input::Keyboard::KEY_SHIFT)) {
						g->mBuffer += static_cast<char>(i);
						g->mInput_end = true;
					}
					else if (i >= 'a' && i <= 'z' && !k.is_on(Input::Keyboard::KEY_SHIFT)) {
						g->mBuffer += static_cast<char>(i);
						g->mInput_end = true;
					}
					else if (i < 'A' || i > 'z' || (i > 'Z' && i < 'a')) {
						g->mBuffer += static_cast<char>(i);
						g->mInput_end = true;
					}
				}
			}
			// 文字列出力
			g->draw_string(mBuffer.c_str(), posX, posY);
			// Enterで終了を知らせる
			if (entered) {
				// 結果をコピー
				*out = g->mBuffer;
				g->mBuffer.clear();
				return true;
			}
			return false;
		}

		// フォーマット設定
		void Graphics_impl::set_format(float size, unsigned color) {
			mFont_size = size;
			color |= 0xff000000;
			HRESULT hr = mWrite_factory->CreateTextFormat(FONT_NAME, NULL,
				DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
				mFont_size, L"", &mText_format);
			if (SUCCEEDED(hr)) {
				D2D1_COLOR_F cf = convert_color_unsigned(color);
				mRender->CreateSolidColorBrush(cf, &mText_color);
			}
			else {
				assert(0);
			}
		}

		D2D1::ColorF Graphics_impl::convert_color_unsigned(unsigned in) const {
			D2D1::ColorF out = { 0 };
			out.r = PER_255 * (in & 0xff);
			out.g = PER_255 * ((in & 0xff00) >> 8);
			out.b = PER_255 * ((in & 0xff0000) >> 16);
			out.a = PER_255 * ((in & 0xff000000) >> 24);
			return out;
		}

		void Graphics_impl::begin_draw() {
			// 描画準備
			BeginPaint(mHwnd, &mPs);
			mRender->BeginDraw();
			//mRender->Clear();
		}

		void Graphics_impl::end_draw() {
			// 描画終了
			mRender->EndDraw();
			//InvalidateRect(mHwnd, NULL, FALSE);
			EndPaint(mHwnd, &mPs);
		}

	}
}