#include"Mylib\Input\Manager.h"
#include"Mylib\Input\Input_impl.h"

namespace Mylib {
	namespace Input {
		Manager::Manager()	{}

		Manager::~Manager() {}
		// マウスクラスを渡す
		Mouse Manager::get_mouse() const{
			return Mouse();
		}
		// キーボードクラスを渡す
		Keyboard Manager::get_keyboard() const {
			return Keyboard();
		}
		// ゲームパッドの接続数
		int Manager::get_pad_num() const {
			return Input_impl::instance()->get_pad_num();
		}
		// num番目のゲームパッド	
		PS4 Manager::get_pad(int number) const {
			return PS4(number);
		}

		Manager Manager::instance(){
			return Manager();
		}
	}
}