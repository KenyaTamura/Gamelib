#include"Mylib\FileIO\FileIO_impl.h"

#include<fstream>
#include<cassert>
#include<cstdio>

namespace Mylib {
	namespace FileIO {
		FileIO_impl* FileIO_impl::mInstance = 0;

		FileIO_impl::FileIO_impl() :
			mData{ nullptr },
			mSize{ 0 },
			mReading_point{ 0 }
		{
		}

		FileIO_impl::~FileIO_impl() {
			// ������delete���Ă����͂�
			mFile_data.clear();
		}

		FileIO_impl* FileIO_impl::instance() {
			return mInstance;
		}

		void FileIO_impl::create() {
			if (!mInstance) {
				mInstance = new FileIO_impl;
			}
		}

		void FileIO_impl::destroy() {
			if (mInstance) {
				delete mInstance;
				mInstance = nullptr;
			}
		}

		void FileIO_impl::update() {
			typedef map<string, pair<char*, int>>::iterator It;
			// �ǂݍ��ݒ��̃t�@�C��
			if (!mCurrent_file.empty()) {
				// �{���ɂ��邩���ׂ�
				bool found = false;
				It i = mFile_data.find(mCurrent_file);
				// ����ꍇ
				if (i != mFile_data.end()) {
					int rest = mSize - mReading_point;	// �c��
					int size = rest;
					if (rest > READ_UNIT) {	// �c�ʂ�������Γǂݍ��ޗʂ𐧌�
						size = READ_UNIT;
					}
					mIfstream->read(mData + mReading_point, size);
					mReading_point += size;	// �ǂݍ��񂾕������L�^
					if (size == rest) {	// �ǂݍ��݊���
										// �f�[�^��n��
						mFile_data[mCurrent_file] = pair<char*, int>(mData, mSize);
						// �Ӑ}�I�ɉ�����ĂȂ�
						mData = 0;
						delete mIfstream;
						mIfstream = 0;
						mSize = mReading_point = 0;
						mCurrent_file.clear();
					}
				}
				// �Ȃ��ꍇ���~����
				else {
					if (mData) {
						delete mData;
						mData = 0;
					}
					if (mIfstream) {
						delete mIfstream;
						mIfstream = 0;
					}
					mSize = mReading_point = 0;
					mCurrent_file.clear();
				}
			}
			// �ǂݍ���ł���t�@�C�����Ȃ�
			else {
				for (It i = mFile_data.begin(); i != mFile_data.end(); ++i) {
					if (i->second.second == 0) {	// ���[�h�����I���C�T�C�Y=0�̂���
						mCurrent_file = i->first;
						mIfstream = new ifstream(mCurrent_file.c_str(), ifstream::binary);
						if (mIfstream) {
							// �ǂݍ��݃f�[�^
							mIfstream->seekg(0, ifstream::end);
							mSize = static_cast<int>(mIfstream->tellg());
							mIfstream->seekg(0, ifstream::beg);
							mData = new char[mSize];
							break;
						}
						else {
							assert(0); //�ǂݍ��݃G���[
						}
					}
				}
			}
		}

		void FileIO_impl::read(const string& filename) {
			// �f�t�H���g�l�ő}��
			// ���ɂ���Ή����N����Ȃ�
			mFile_data[filename];
		}

		void FileIO_impl::write(const string& filename, const char* data, int size) const {
			ofstream out(filename.c_str(), ofstream::binary);
			if (out) {
				// �������݂͈�C�ɂ��
				out.write(data, size);
			}
			else {
				assert(0); // �������݃G���[
			}
		}

		void FileIO_impl::remove(const string& filename) const {
			std::remove(filename.c_str());
		}

		bool FileIO_impl::is_ready(const string& filename) const {
			// ���ݒ�
			if (mFile_data.find(filename) == mFile_data.end()) {
				return false;
			}
			// ���I��
			else if (mFile_data.find(filename)->second.second == 0) {
				return false;
			}
			return true;
		}

		void FileIO_impl::get_data(const string& filename, char* out) {
			out = FileIO_impl::get_data(filename);
		}

		char* FileIO_impl::get_data(const string& filename){
			if (is_ready(filename)) {
				// ��������f�[�^��n��
				return mFile_data[filename].first;
			}
			else {
				// ������Ȃ�
				return 0;
			}
		}

		void FileIO_impl::release_file(const string& filename) {
			mFile_data.erase(filename);
		}

	}
}