#ifndef MYLIB_INPUT_MOUSE_H
#define MYLIB_INPUT_MOUSE_H

namespace Mylib {
	namespace Input {
		// �}�E�X�֘A
		class Mouse {
		public:
			enum Button {
				BUTTON_LEFT,
				BUTTON_RIGHT,
				BUTTON_MIDDLE,
			};
			Mouse();
			~Mouse();

			// �}�E�X�̓�����擾
			int x() const;
			int y() const;
			int velocity_x() const;
			int velocity_y() const;
			int wheel() const;

			// �{�^�����
			bool is_on(Button) const;
			bool is_triggered(Button) const;
		};
	}
}

#endif