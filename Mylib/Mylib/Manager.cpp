#include"Mylib\Framework.h"
#include"Mylib\Manager.h"
#include"Mylib\FileIO\Manager.h"
#include"Mylib\Graphics\Manager.h"
#include"Mylib\Input\Manager.h"
#include"Mylib\Input\Mouse.h"
#include"Mylib\Input\Keyboard.h"
#include"Mylib\Input\PS4.h"
#include"Mylib\Sound\Manager.h"

using namespace std;

namespace Mylib {
	Manager::Manager(){}

	Manager::~Manager(){}

	Manager Manager::instance() {
		return Manager();
	}

	// �t���[�����[�N�̋@�\
	// ��ʕ��擾
	int Manager::get_window_width() const {
		return Framework::instance()->get_width();
	}
	// ��ʍ����擾
	int Manager::get_window_height() const {
		return Framework::instance()->get_height();
	}
	// �^�C�g���擾
	std::string Manager::get_title() const {
		return Framework::instance()->get_title();
	}
	// Framework�ɏI�����߂��o��
	void Manager::request_end() {
		Framework::instance()->request_end();
	}
	// Framework�ɏI�����߂��o�Ă��邩���ׂ�
	bool Manager::is_end_requested() const {
		return Framework::instance()->is_end_requested();
	}
	// �~���b�P�ʂŐQ��
	void Manager::sleep(int ms) const {
		Framework::instance()->sleep(ms);
	}
	// �t���[�����[�g�l��
	int Manager::get_framerate() const {
		return Framework::instance()->get_framerate();
	}
	// �t���[�����[�g�Z�b�g
	void Manager::set_framerate(int framerate) {
		Framework::instance()->set_framerate(framerate);
	}
	// �t���[�����[�N�@�\�I��

	// ���̓f�o�C�X
	// �L�[�{�[�h
	// �L�[��������Ă��邩
	bool Manager::is_key_on(int i) const {
		return Input::Keyboard().is_on(i);
	}
	// �L�[�������ꂽ��
	bool Manager::is_key_triggered(int i) const {
		return Input::Keyboard().is_triggered(i);
	}
	// �}�E�X
	// �}�E�X��x���W
	int Manager::get_x() const {
		return Input::Mouse().x();
	}
	// �}�E�X��y���W
	int Manager::get_y() const {
		return Input::Mouse().y();
	}
	// �}�E�X��x�������̑��x
	int Manager::get_velocity_x() const {
		return Input::Mouse().velocity_x();
	}
	// �}�E�X��y�������̑��x
	int Manager::get_velocity_y() const {
		return Input::Mouse().velocity_y();
	}
	// �z�C�[��
	int Manager::get_wheel() const {
		return Input::Mouse().wheel();
	}
	// �Q�[���p�b�h
	// �ڑ���
	int Manager::get_pad_num() const{
		return Input::Manager().get_pad_num();
	}
	// �{�^����
	int Manager::get_button_number(int num) const {
		return Input::PS4(num).get_button_number();
	}
	// �{�^����������Ă��邩
	bool Manager::is_button_on(int i, int num) const {
		return Input::PS4(num).is_on(i);
	}
	// �{�^���������ꂽ��
	bool Manager::is_button_triggered(int i, int num) const {
		return Input::PS4(num).is_triggered(i);
	}
	// �A�i���O�X�e�B�b�N�̐�
	int Manager::get_analog_number(int num) const {
		return Input::PS4(num).get_analog_number();
	}
	// �A�i���O�X�e�B�b�N�l�擾
	int Manager::get_analog(int i, int num) const {
		return Input::PS4(num).get_analog(i);
	}
	//�L����
	bool Manager::is_enabled(int num) const {
		return Input::PS4(num).is_enabled();
	}
	// ���̓f�o�C�X�@�\�I��

	// �t�@�C�����o��
	// �t�@�C���ǂ݂���
	void Manager::read_file(const std::string& filename) {
		FileIO::Manager().read(filename);
	}
	// �t�@�C����������
	void Manager::write_file(const std::string& filename, const char* data, int size) const {
		FileIO::Manager().write(filename, data, size);
	}
	// �t�@�C���폜
	void Manager::remove_file(const std::string& filename) const {
		FileIO::Manager().remove(filename);
	}
	// �f�[�^�l���Achar*�Ŋl��
	void Manager::get_file_data(const std::string& filename, char* out) {
		FileIO::Manager().get_data(filename, out);
	}
	// �f�[�^�l���Achar*�Ŋl��
	char* Manager::get_file_data(const std::string& filename) {
		return FileIO::Manager().get_data(filename);
	}
	// �����J��
	void Manager::release_file(const std::string& filename) {
		FileIO::Manager().release_file(filename);
	}
	// �Ǎ��݊m�F
	bool Manager::is_ready_file(const std::string& filename) {
		return FileIO::Manager().is_ready_file(filename);
	}
	// �t�@�C�����o�͋@�\�I��

	// �O���t�B�b�N�X
	// �ǂݍ��񂾉摜��`��
	void Manager::draw_image(const Graphics::Texture& texture, int posX, int posY, float rotation, float extendX, float extendY) const {
		Graphics::Manager().draw_image(texture, posX, posY, rotation, extendX, extendY);
	}
	// �����o��
	void Manager::draw_string(const char* str, int posX, int posY) const {
		Graphics::Manager().draw_string(str, posX, posY);
	}
	// �������́Acin����AEnter��true
	bool Manager::get_string_in(std::string* out, int posX, int posY) {
		return Graphics::Manager().get_string(out, posX, posY);
	}
	// �����̃t�H�[�}�b�g�ւ�
	void Manager::set_format(float size, unsigned color) {
		Graphics::Manager().set_format(size, color);
	}
	// �O���t�B�b�N�X�@�\�I��

	// �T�E���h�@�\
	// �ǂݍ��񂾉����t�@�C�����Đ�
	void Manager::play_sound(Sound::Wave& wave) {
		Sound::Manager().play(wave);
	}
	// �Đ����̉����t�@�C���̒�~
	void Manager::stop_sound(Sound::Wave& wave) {
		Sound::Manager().stop(wave);
	}
	// �T�E���h�@�\�I��
}