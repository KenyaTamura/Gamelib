#ifndef MYLIB_MANAGER_H
#define MYLIB_MANAGER_H

#include<string>

#include"Input\Manager.h"

namespace Mylib {
	namespace Graphics {
		class Texture;
	}
	namespace Sound {
		class Wave;
	}
	// �قڑS�@�\���g����}�l�[�W���[�N���X
	// �e�N�X�`����XML�͕ʂɍs��
	class Manager {
	public:
		Manager();
		~Manager();
		static Manager instance();

		// �t���[�����[�N�̋@�\
		// ��ʕ��擾
		int get_window_width() const;
		// ��ʍ����擾
		int get_window_height() const;
		// �^�C�g���擾
		std::string get_title() const;
		// Framework�ɏI�����߂��o��
		void request_end();
		// Framework�ɏI�����߂��o�Ă��邩���ׂ�
		bool is_end_requested() const;
		// �~���b�P�ʂŐQ��
		void sleep(int milli_seconds) const;
		// �t���[�����[�g
		// �t���[�����[�g�l��
		int get_framerate() const;
		// �t���[�����[�g�Z�b�g
		void set_framerate(int framerate);

		// ���̓f�o�C�X
		// �L�[�{�[�h
		// �L�[��������Ă��邩
		bool is_key_on(int i) const;
		// �L�[�������ꂽ��
		bool is_key_triggered(int i) const;
		// �}�E�X
		// �}�E�X��x���W
		int get_x() const;
		// �}�E�X��y���W
		int get_y() const;
		// �}�E�X��x�������̑��x
		int get_velocity_x() const;
		// �}�E�X��y�������̑��x
		int get_velocity_y() const;
		// �z�C�[��
		int get_wheel() const;
		// �Q�[���p�b�h(PS4)
		// �ڑ���
		int get_pad_num() const;
		// �{�^����
		int get_button_number(int num = 0) const;
		// �{�^����������Ă��邩
		bool is_button_on(int i, int num = 0) const;
		// �{�^���������ꂽ��
		bool is_button_triggered(int i, int num = 0) const;
		// �A�i���O�X�e�B�b�N�̐�
		int get_analog_number(int num = 0) const;
		// �A�i���O�X�e�B�b�N�l�擾
		int get_analog(int i, int num = 0) const;
		//�L����
		bool is_enabled(int num = 0) const;

		// �t�@�C�����o��
		// �t�@�C�����ƃf�[�^�ƃf�[�^�T�C�Y�̑g���킹
		typedef std::tuple<std::string, const char*, int> File;
		// �t�@�C���ǂ݂���
		void read_file(const std::string& filename);
		// �t�@�C����������
		void write_file(const std::string& filename, const char* data, int size) const;
		// �t�@�C���폜
		void remove_file(const std::string& filename) const;
		// �f�[�^�l��
		// string�Ŋl��
		void get_file_data(const std::string& filename, char* out);
		char* get_file_data(const std::string& filename);
		// �����J��
		void release_file(const std::string& filename);
		// �Ǎ��݊m�F
		bool is_ready_file(const std::string& filename);

		// �O���t�B�b�N�X
		// �ǂݍ��񂾉摜��`��
		void draw_image(const Graphics::Texture& texture, int posX, int posY, float rotation = 0.0f, float extendX = 1.0f, float extendY = 1.0f) const;
		// �����o��
		void draw_string(const char* str, int posX, int posY) const;
		// �������́Acin����AEnter��true
		bool get_string_in(std::string* out, int posX = 0, int posY = 0);
		// �����̃t�H�[�}�b�g�ւ�
		void set_format(float size, unsigned color = 0xffffffff);

		// �T�E���h
		// �����t�@�C���ǂݍ��݂�Wave�𗘗p
		// �Đ�
		void play_sound(Sound::Wave& wave);
		// ��~
		void stop_sound(Sound::Wave& wave);
	};
}

#endif
