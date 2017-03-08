#include"Mylib\FileIO\FileIO_impl.h"
#include"Mylib\FileIO\Manager.h"

namespace Mylib {
	namespace FileIO {
		
		Manager::Manager() {}
		
		Manager::~Manager() {}

		Manager Manager::instance() {
			return Manager();
		}
		// �t�@�C���ǂݍ���
		void Manager::read(const std::string& filename) {
			FileIO_impl::instance()->read(filename);
		}
		// �t�@�C����������
		void Manager::write(const std::string& filename, const char* data, int size) const {
			FileIO_impl::instance()->write(filename, data, size);
		}
		// �t�@�C���폜
		void Manager::remove(const std::string& filename) const {
			FileIO_impl::instance()->remove(filename);
		}
		// �t�@�C�����̃f�[�^�A���łɓǂݍ���ł���K�v������
		void Manager::get_data(const string& filename, char* out) {
			FileIO_impl::instance()->get_data(filename, out);
		}
		// �t�@�C�����̃f�[�^�A���łɓǂݍ���ł���K�v������
		char* Manager::get_data(const string& filename) {
			return FileIO_impl::instance()->get_data(filename);
		}
		// ���
		void Manager::release_file(const std::string& filename) {
			FileIO_impl::instance()->release_file(filename);
		}
		// ����������
		bool Manager::is_ready_file(const std::string& filename) {
			return FileIO_impl::instance()->is_ready(filename);
		}
	}
}