#include"Mylib\XML\Attribute.h"
#include"Mylib\XML\Element.h"
#include"Mylib\XML\Tag.h"

using namespace std;

namespace Mylib {
	namespace XML {
		Element::Element() {}

		Element::Element(const string& name) : mName(name) {}

		Element::Element(Tag* begin, const string& data, int* p) {
			mName = *(begin->get_name());
			mAttribute = *(begin->get_attribute());
			int size = static_cast<int>(data.size());
			// 次のタグを用意
			for (; *p < size; (*p)++) {
				// 次のタグ
				if (data[*p] == '<') {
					(*p)++;
					// コンストラクタでタグ読み込み
					Tag tag(data, p);
					Tag::Type t = tag.get_type();
					// 開始タグ
					if (t == Tag::BEGIN) {
						// 再帰構造
						mChild_element.push_back(new Element(&tag, data, p));
					}
					// 終了タグ
					else if (t == Tag::END) {
						break;	// タグが終わったらこのエレメントは読み込み完了
					}
				}
			}
		}

		Element::~Element() {
			// 自分でメモリ解放
			for (unsigned i = 0; i < mAttribute.size(); ++i) {
				if (mAttribute[i]) {
					delete mAttribute[i];
					mAttribute[i] = 0;
				}
			}
			for (unsigned i = 0; i < mChild_element.size(); ++i) {
				if (mChild_element[i]) {
					delete mChild_element[i];
					mChild_element[i] = 0;
				}
			}
		}

		// アトリビュート要素数
		int Element::get_attribute_num() const {
			return static_cast<int>(mAttribute.size());
		}
		// i番目のアトリビュート要素を受け取る
		Attribute* Element::get_attribute(int i) const {
			return mAttribute[i];
		}
		// エレメント数
		int Element::get_element_num() const {
			return static_cast<int>(mChild_element.size());
		}
		// i番目のエレメントを受け取る
		Element* Element::get_element(int i) const {
			return mChild_element[i];
		}
		// エレメント名
		const string* Element::get_name() const {
			return &mName;
		}
		// アトリビュートの書き換え、ポインタを渡して書き換える
		Attribute* Element::set_attribute(int i) {
			return mAttribute[i];	// ポインタを渡して書き換える
		}
		// アトリビュート要素数の変更、一度初期化する
		void Element::set_attribute_num(int n) {
			// 一度リセット
			for (unsigned i = 0; i < mAttribute.size(); i++) {
				if (mAttribute[i]) {
					delete mAttribute[i];
					mAttribute[i] = 0;
				}
			}
			mAttribute.resize(n);
			for (int i = 0; i < n; ++i) {
				mAttribute[i] = new Attribute();
			}
		}
		// アトリビュートの追加
		void Element::add_attribute_num() {
			mAttribute.push_back(new Attribute());
		}
		// i番目のアトリビュートの削除
		void Element::del_attribute(int i) {
			mAttribute.erase(mAttribute.begin() + i);
		}
		// エレメントの書き換え、ポインタを渡して書き換える
		Element* Element::set_element(int i) {
			return mChild_element[i];
		}
		// エレメント要素数の変更、一度初期化する
		void Element::set_element_num(int n) {
			for (unsigned i = 0; i < mChild_element.size(); i++) {
				if (mChild_element[i]) {
					delete mChild_element[i];
					mChild_element[i] = 0;
				}
			}
			mChild_element.resize(n);
			for (int i = 0; i < n; i++) {
				mChild_element[i] = new Element();
			}
		}
		// エレメントの追加
		void Element::add_element_num() {
			mChild_element.push_back(new Element());
		}
		// i番目のエレメントの削除
		void Element::del_element(int i) {
			mChild_element.erase(mChild_element.begin() + i);
		}
		// エレメント名の設定
		void Element::set_name(const char* name) {
			mName = name;
		}
		// 書込み用のデータ変換
		void Element::convert_data_string(string* out) const {
			*out += '<';	// タグ開始
			*out += mName;	// エレメント名
							// アトリビュート
			for (unsigned i = 0; i < mAttribute.size(); i++) {
				*out += ' ';	// スペース
				*out += mAttribute[i]->get_name();	// アトリビュート名
				*out += '=';	// イコール
				*out += '"';	// ダブルコーテション
				*out += mAttribute[i]->get_val();	// アトリビュート要素
				*out += '"';	// 終了
			}
			*out += '>';	// タグ終了
			*out += '\n';	// タグごとに改行
							// 子に再帰
			for (unsigned i = 0; i < mChild_element.size(); i++) {
				mChild_element[i]->convert_data_string(out);
			}
			// 終了タグ
			*out += '<';
			*out += '/';
			*out += mName;
			*out += '>';
			*out += '\n';
		}

	}
}