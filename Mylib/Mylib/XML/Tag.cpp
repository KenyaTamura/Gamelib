#include"Mylib\XML\Attribute.h"
#include"Mylib\XML\Tag.h"

using namespace std;

/*
状態の種類
0: 初期状態，'<'の次
1: エレメント名
2: エレメント名の後の空白，アトリビュートの後の空白
3: アトリビュート名
4: アトリビュート名と要素の間，=
5: アトリビュート要素
*/

namespace Mylib {
	namespace XML {

		Tag::Tag(const string& name) :
			mName(name)
		{
		}

		Tag::Tag(const string& data, int* p) :
			mType(Tag::BEGIN)
		{
			// 一時格納
			string buf_name;
			string buf_val;
			// 状態
			int m = 0;
			// ループ脱出
			bool end_flag = false;
			int size = static_cast<int>(data.size());
			for (; *p < size; (*p)++) {
				char c = data[*p];
				switch (m) {
				case 0:	// 初期
					if (c == '/') {
						// 終了タグ
						mType = Tag::END;
					}
					else if (is_normal_char(c)) {
						mName += c;
						m = 1;	// 1へ遷移
					}
					break;
				case 1:	// エレメント名
					if (c == '>') {
						end_flag = true;	// 終了
					}
					else if (is_normal_char(c)) {
						mName += c;
					}
					else {
						m = 2;	// 2へ遷移
					}
					break;
				case 2:	// エレメント名 or アトリビュート終了
					if (c == '>') {
						end_flag = true;	// 終了
					}
					else if (is_normal_char(c)) {
						buf_name += c;	// アトリビュート名
						m = 3;	// 3へ遷移
					}
					break;
				case 3:	// アトリビュート名
					if (c == '=') {
						m = 4;	// 4へ遷移
					}
					else if (is_normal_char(c)) {
						buf_name += c;
					}
					break;
				case 4:	// アトリビュート名終了
					if (c == '"') {
						m = 5;	// 5へ遷移
					}
					break;
				case 5:	// アトリビュート要素
					if (c == '"') {
						m = 2;	// 2へ遷移
						mAttribute.push_back(new Attribute(buf_name.c_str(), buf_val.c_str()));
						//名前と値を初期化
						buf_name.clear();
						buf_val.clear();
					}
					else {
						buf_val += c;
					}
					break;
				default:
					break;
				}
				if (end_flag) { break; }
			}
		}

		Tag::~Tag() {
			// Attributeは渡しているので，ここでは処理しない
		}

		bool Tag::is_normal_char(char c) {
			if (c >= '0' && c <= '9') {
				return true;
			}
			if (c >= 'a' && c <= 'z') {
				return true;
			}
			if (c >= 'A' && c <= 'Z') {
				return true;
			}
			if (c == '_') {
				return true;
			}
			return false;
		}

		const string* Tag::get_name() const {
			return &mName;
		}

		Tag::Type Tag::get_type() const {
			return mType;
		}

		const vector<Attribute*>* Tag::get_attribute() const {
			return &mAttribute;
		}

	}
}