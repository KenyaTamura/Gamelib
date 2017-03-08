#ifndef MYLIB_INPUT_MOUSE_H
#define MYLIB_INPUT_MOUSE_H

namespace Mylib {
	namespace Input {
		// マウス関連
		class Mouse {
		public:
			enum Button {
				BUTTON_LEFT,
				BUTTON_RIGHT,
				BUTTON_MIDDLE,
			};
			Mouse();
			~Mouse();

			// マウスの動作情報取得
			int x() const;
			int y() const;
			int velocity_x() const;
			int velocity_y() const;
			int wheel() const;

			// ボタン情報
			bool is_on(Button) const;
			bool is_triggered(Button) const;
		};
	}
}

#endif