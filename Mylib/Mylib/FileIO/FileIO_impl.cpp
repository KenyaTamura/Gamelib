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
			// 自動でdeleteしてくれるはず
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
			// 読み込み中のファイル
			if (!mCurrent_file.empty()) {
				// 本当にあるか調べる
				bool found = false;
				It i = mFile_data.find(mCurrent_file);
				// ある場合
				if (i != mFile_data.end()) {
					int rest = mSize - mReading_point;	// 残量
					int size = rest;
					if (rest > READ_UNIT) {	// 残量が多ければ読み込む量を制限
						size = READ_UNIT;
					}
					mIfstream->read(mData + mReading_point, size);
					mReading_point += size;	// 読み込んだ部分を記録
					if (size == rest) {	// 読み込み完了
										// データを渡す
						mFile_data[mCurrent_file] = pair<char*, int>(mData, mSize);
						// 意図的に解放してない
						mData = 0;
						delete mIfstream;
						mIfstream = 0;
						mSize = mReading_point = 0;
						mCurrent_file.clear();
					}
				}
				// ない場合中止する
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
			// 読み込んでいるファイルがない
			else {
				for (It i = mFile_data.begin(); i != mFile_data.end(); ++i) {
					if (i->second.second == 0) {	// ロードが未終了，サイズ=0のこと
						mCurrent_file = i->first;
						mIfstream = new ifstream(mCurrent_file.c_str(), ifstream::binary);
						if (mIfstream) {
							// 読み込みデータ
							mIfstream->seekg(0, ifstream::end);
							mSize = static_cast<int>(mIfstream->tellg());
							mIfstream->seekg(0, ifstream::beg);
							mData = new char[mSize];
							break;
						}
						else {
							assert(0); //読み込みエラー
						}
					}
				}
			}
		}

		void FileIO_impl::read(const string& filename) {
			// デフォルト値で挿入
			// 既にあれば何も起こらない
			mFile_data[filename];
		}

		void FileIO_impl::write(const string& filename, const char* data, int size) const {
			ofstream out(filename.c_str(), ofstream::binary);
			if (out) {
				// 書き込みは一気にやる
				out.write(data, size);
			}
			else {
				assert(0); // 書き込みエラー
			}
		}

		void FileIO_impl::remove(const string& filename) const {
			std::remove(filename.c_str());
		}

		bool FileIO_impl::is_ready(const string& filename) const {
			// 未設定
			if (mFile_data.find(filename) == mFile_data.end()) {
				return false;
			}
			// 未終了
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
				// 見つけたらデータを渡す
				return mFile_data[filename].first;
			}
			else {
				// 見つからない
				return 0;
			}
		}

		void FileIO_impl::release_file(const string& filename) {
			mFile_data.erase(filename);
		}

	}
}