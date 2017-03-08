#include"Mylib\Input\Manager.h"
#include"Mylib\Input\Input_impl.h"

namespace Mylib {
	namespace Input {
		Manager::Manager()	{}

		Manager::~Manager() {}
		// �}�E�X�N���X��n��
		Mouse Manager::get_mouse() const{
			return Mouse();
		}
		// �L�[�{�[�h�N���X��n��
		Keyboard Manager::get_keyboard() const {
			return Keyboard();
		}
		// �Q�[���p�b�h�̐ڑ���
		int Manager::get_pad_num() const {
			return Input_impl::instance()->get_pad_num();
		}
		// num�Ԗڂ̃Q�[���p�b�h	
		PS4 Manager::get_pad(int number) const {
			return PS4(number);
		}

		Manager Manager::instance(){
			return Manager();
		}
	}
}