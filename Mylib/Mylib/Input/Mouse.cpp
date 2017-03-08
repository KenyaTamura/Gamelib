#include"Mylib\Input\Input_impl.h"
#include"Mylib\Input\Mouse.h"

namespace Mylib {
	namespace Input {
		Mouse::Mouse() {
		}

		Mouse::~Mouse() {
		}
		// �}�E�X��x���W
		int Mouse::x() const {
			Input_impl* i = Input_impl::instance();
			return i->mX;
		}
		// �}�E�X��y���W
		int Mouse::y() const {
			Input_impl* i = Input_impl::instance();
			return i->mY;
		}
		// x�������̑��x
		int Mouse::velocity_x() const {
			Input_impl* i = Input_impl::instance();
			return i->mVelocityX;
		}
		// y�������̑��x
		int Mouse::velocity_y() const {
			Input_impl* i = Input_impl::instance();
			return i->mVelocityY;
		}
		// �z�C�[��
		int Mouse::wheel() const {
			Input_impl* i = Input_impl::instance();
			return i->mWheel;
		}
		// �{�^����������Ă��邩
		bool Mouse::is_on(Button b) const {
			Input_impl* i = Input_impl::instance();
			return i->is_button_on(b);
		}
		// �{�^���������ꂽ��
		bool Mouse::is_triggered(Button b) const {
			Input_impl* i = Input_impl::instance();
			return i->is_button_triggered(b);
		}

	}
}