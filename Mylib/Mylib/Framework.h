#ifndef MYLIB_FRAMEWORK_H
#define MYLIB_FRAMEWORK_H

#include<string>

namespace Mylib {
	class Framework {
	public:
		class Configuration {
		public:
			void set_width(int width);
			void set_height(int height);
			void set_title(const char* title);
			void load_file(const char* filename, std::string* out) const;	// �S�͂œǂݍ���
		};
		// ���[�U��`�֐��B����������B
		void update();
		void configure(Configuration*);
		// �C���X�^���X�擾
		static Framework* instance();
		// ��ʕ��擾
		int get_width() const;
		// ��ʍ����擾
		int get_height() const;
		// �^�C�g���擾
		std::string get_title() const;
		// Framework�ɏI�����߂��o��
		void request_end();
		// Framework�ɏI�����߂��o�Ă��邩���ׂ�
		bool is_end_requested() const;
		// �~���b�P�ʂŐQ��
		void sleep(int milli_seconds) const;
		// �t���[�����[�g
		int get_framerate() const;
		void set_framerate(int framerate);

		// �ȉ������ōs������
		void start(void* hWnd);
		void pre_update();
		void post_update();
		static void create();
		static void destroy();
	private:
		Framework();
		Framework(const Framework&);	// �R�s�[�R���X�g���N�^
		void operator=(const Framework&);	// ������Z
		~Framework();

		int mWidth;
		int mHeight;
		std::string mTitle;
		unsigned mFramerate;
		unsigned mPrev_frame_interval;
		unsigned mPrev_frametime;
		unsigned mIdeal_frame_interval;
		bool mFirst_loading;
		bool mEnd_requested;
		bool mStarted;

		static Framework* mInstance;
	};
}
#endif
