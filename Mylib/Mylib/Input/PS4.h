#ifndef MYLIB_INPUT_PS4_H
#define MYLIB_INPUT_PS4_H

namespace Mylib {
	namespace Input {
		class PS4 {
		public:
			// �ڑ��ԍ�
			explicit PS4(int number);
			~PS4();
			// �{�^���̗񋓌^
			enum Button {
				BUTTON_SQUARE,	// ��
				BUTTON_CROSS,	// �~
				BUTTON_CIRCLE,	// ��
				BUTTON_TRIANGLE,// ��
				BUTTON_L1,
				BUTTON_R1,
				BUTTON_L2,
				BUTTON_R2,
				BUTTON_SHARE,
				BUTTON_OPTION,
				BUTTON_L3,
				BUTTON_R3,
				BUTTON_HOME,
				BUTTON_UP = 128,
				BUTTON_DOWN,
				BUTTON_LEFT,
				BUTTON_RIGHT,
			};
			// �A�i���O�p�b�h�̎�
			enum ANALOG {
				ANALOG_LX,
				ANALOG_LY,
				ANALOG_RX,
				ANALOG_RY = 5
			};

			int get_analog_number() const;
			int get_analog(int i) const; //�A�i���O�X�e�B�b�N�l�擾

			bool is_on(int i) const;
			bool is_triggered(int i) const;
			int get_button_number() const;
			//�L����
			bool is_enabled() const;
		private:
			int mNumber;
		};
	}
}


#endif