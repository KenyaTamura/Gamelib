#ifndef MYLIB_FILEIO_MANAGER_H
#define MYLIB_FILEIO_MANAGER_H

#include<string>

namespace Mylib {
	namespace FileIO {
		// �t�@�C�����o�͊֘A
		class Manager {
		public:
			Manager();
			~Manager();

			static Manager instance();

			// �t�@�C���ǂݏ���
			void read(const std::string& filename);
			void write(const std::string& filename, const char* data, int size) const;
			// �t�@�C���폜
			void remove(const std::string& filename) const;
			// �f�[�^�l��
			void get_data(const std::string& filename, char* out);
			char* get_data(const std::string& filename);
			// �����J��
			void release_file(const std::string& filename);
			// �Ǎ��݊m�F
			bool is_ready_file(const std::string& filename);
		};

	}
}

#endif