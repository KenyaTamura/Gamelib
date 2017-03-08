#ifndef MYLIB_FILEIO_MANAGER_H
#define MYLIB_FILEIO_MANAGER_H

#include<string>

namespace Mylib {
	namespace FileIO {
		// ファイル入出力関連
		class Manager {
		public:
			Manager();
			~Manager();

			static Manager instance();

			// ファイル読み書き
			void read(const std::string& filename);
			void write(const std::string& filename, const char* data, int size) const;
			// ファイル削除
			void remove(const std::string& filename) const;
			// データ獲得
			void get_data(const std::string& filename, char* out);
			char* get_data(const std::string& filename);
			// 資源開放
			void release_file(const std::string& filename);
			// 読込み確認
			bool is_ready_file(const std::string& filename);
		};

	}
}

#endif