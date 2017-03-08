#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\Mouse.h"

namespace Mylib {
	namespace Input {
		Mouse::Mouse() {
		}

		Mouse::~Mouse() {
		}
		// マウスのx座標
		int Mouse::x() const {
			Input_impl* i = Input_impl::instance();
			return i->mX;
		}
		// マウスのy座標
		int Mouse::y() const {
			Input_impl* i = Input_impl::instance();
			return i->mY;
		}
		// x軸方向の速度
		int Mouse::velocity_x() const {
			Input_impl* i = Input_impl::instance();
			return i->mVelocityX;
		}
		// y軸方向の速度
		int Mouse::velocity_y() const {
			Input_impl* i = Input_impl::instance();
			return i->mVelocityY;
		}
		// ホイール
		int Mouse::wheel() const {
			Input_impl* i = Input_impl::instance();
			return i->mWheel;
		}
		// ボタンが押されているか
		bool Mouse::is_on(Button b) const {
			Input_impl* i = Input_impl::instance();
			return i->is_button_on(b);
		}
		// ボタンが押されたか
		bool Mouse::is_triggered(Button b) const {
			Input_impl* i = Input_impl::instance();
			return i->is_button_triggered(b);
		}

	}
}