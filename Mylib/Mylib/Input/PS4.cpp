#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\PS4.h"
#include"Mylib\Input\PS4_impl.h"

namespace Mylib {
	namespace Input {
		// PS4基準のボタン配置
		PS4::PS4(int number) : mNumber(number){
			if (mNumber >= Input_impl::instance()->get_pad_num()) {
				mNumber = 0;
			}
		}

		PS4::~PS4() {
		}
		// アナログスティック数
		int PS4::get_analog_number() const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_analog_number();
			}
			else {
				return false;
			}
		}
		// アナログスティックの傾き
		int PS4::get_analog(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_analog(i);
			}
			else {
				return false;
			}
		}
		// ボタンが押されているか
		bool PS4::is_on(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->is_on(i);
			}
			else {
				return false;
			}
		}
		// ボタンが押されたか
		bool PS4::is_triggered(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->is_triggered(i);
			}
			else {
				return false;
			}
		}
		// ボタン数
		int PS4::get_button_number() const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_button_number();
			}
			else {
				return false;
			}
		}
		//有効か
		bool PS4::is_enabled() const {
			if (Input_impl::instance()->get_pad_num() == 0) {
				return false;
			}
			return Input_impl::instance()->get_pad(mNumber)->is_enabled();
		}
	}
}