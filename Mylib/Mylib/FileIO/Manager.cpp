#include"Mylib\FileIO\FileIO_impl.h"
#include"Mylib\FileIO\Manager.h"

namespace Mylib {
	namespace FileIO {
		
		Manager::Manager() {}
		
		Manager::~Manager() {}

		Manager Manager::instance() {
			return Manager();
		}
		// ファイル読み込み
		void Manager::read(const std::string& filename) {
			FileIO_impl::instance()->read(filename);
		}
		// ファイル書き込み
		void Manager::write(const std::string& filename, const char* data, int size) const {
			FileIO_impl::instance()->write(filename, data, size);
		}
		// ファイル削除
		void Manager::remove(const std::string& filename) const {
			FileIO_impl::instance()->remove(filename);
		}
		// ファイル名のデータ、すでに読み込んでいる必要がある
		void Manager::get_data(const string& filename, char* out) {
			FileIO_impl::instance()->get_data(filename, out);
		}
		// ファイル名のデータ、すでに読み込んでいる必要がある
		char* Manager::get_data(const string& filename) {
			return FileIO_impl::instance()->get_data(filename);
		}
		// 解放
		void Manager::release_file(const std::string& filename) {
			FileIO_impl::instance()->release_file(filename);
		}
		// 準備完了か
		bool Manager::is_ready_file(const std::string& filename) {
			return FileIO_impl::instance()->is_ready(filename);
		}
	}
}