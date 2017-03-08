#ifndef MYLIB_WINDOW_H
#define MYLIB_WINDOW_H

namespace Mylib {
	// ��ɃE�B���h�E�֘A���s��
	// ��{�I�ɒm��Ȃ��Ă����A�O���璼�ڎg��Ȃ�
	class Window {
	public:
		class Configuration {
		public:
			void set_width(int width);
			void set_height(int height);
			void set_title(const char* title);
		};
		Window();
		~Window();
		// ���͂Ŏ�������֐�
		void configure(Configuration*);

		void start(void* windowHandle);
		void update();

		const char* get_title() const;
		int get_title_length() const;
		int get_width() const;
		int get_height() const;
		// �R�}���h���C��������擾
		const char* get_commandline_string() const;
		// timeGetTime�Ŏ�����Ԃ�
		unsigned get_time() const;
		void sleep(int ms) const;
		bool is_active() const;
		bool is_minimized() const;

		static Window instance();
		void request_end(); // �I����v��
		void end();			// �I����ʒm
		bool is_end_requested() const; // �I���v�������邩
		int get_and_reset_mousewheel();	// �}�E�X�z�C�[��
	};
}
#endif