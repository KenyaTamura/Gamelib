#ifndef MYLIB_FILEIO_FILEIOIMPL_H
#define MYLIB_FILEIO_FILEIOIMPL_H

#include<map>
#include<string>
using namespace std;

namespace Mylib {
	namespace FileIO {
		// �t�@�C�����o�͊֌W�̎�����
		class FileIO_impl {
		public:
			static FileIO_impl* instance();
			static void create();
			static void destroy();

			void update();

			void read(const string& filename);
			void write(const string& filename, const char* data, int size) const;
			void remove(const string& filename) const;
			bool is_ready(const string& filename) const;
			void get_data(const string& filename, char* out);
			char* get_data(const string& filename);
			void release_file(const string& filename);
		private:
			FileIO_impl();
			~FileIO_impl();
			FileIO_impl(const FileIO_impl&);
			void operator=(const FileIO_impl&);

			char* mData;	// �ǂݍ��݂̃o�b�t�@
			string mCurrent_file;
			ifstream* mIfstream;
			int mSize;	// �t�@�C���T�C�Y
			int mReading_point;	// �ǂݍ���ł���ʒu
			map<string, pair<char*, int>> mFile_data;
			static FileIO_impl* mInstance;
			static const int READ_UNIT = 1024 * 1024; //1MB
		};
	}
}
#endif
