#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\PS4.h"
#include"Mylib\Input\PS4_impl.h"

namespace Mylib {
	namespace Input {
		// PS4��̃{�^���z�u
		PS4::PS4(int number) : mNumber(number){
			if (mNumber >= Input_impl::instance()->get_pad_num()) {
				mNumber = 0;
			}
		}

		PS4::~PS4() {
		}
		// �A�i���O�X�e�B�b�N��
		int PS4::get_analog_number() const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_analog_number();
			}
			else {
				return false;
			}
		}
		// �A�i���O�X�e�B�b�N�̌X��
		int PS4::get_analog(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_analog(i);
			}
			else {
				return false;
			}
		}
		// �{�^����������Ă��邩
		bool PS4::is_on(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->is_on(i);
			}
			else {
				return false;
			}
		}
		// �{�^���������ꂽ��
		bool PS4::is_triggered(int i) const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->is_triggered(i);
			}
			else {
				return false;
			}
		}
		// �{�^����
		int PS4::get_button_number() const {
			if (is_enabled()) {
				return Input_impl::instance()->get_pad(mNumber)->get_button_number();
			}
			else {
				return false;
			}
		}
		//�L����
		bool PS4::is_enabled() const {
			if (Input_impl::instance()->get_pad_num() == 0) {
				return false;
			}
			return Input_impl::instance()->get_pad(mNumber)->is_enabled();
		}
	}
}