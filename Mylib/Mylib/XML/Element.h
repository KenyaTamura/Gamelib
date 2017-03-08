#ifndef MYLIB_XML_ELEMENT_H
#define MYLIB_XML_ELEMENT_H

#include<vector>
#include<string>

namespace Mylib {
	namespace XML {
		class Attribute;
		class Tag;
		// 要素、アトリビュートを持っている
		// 入れ子構造で要素も持てる
		class Element {
		public:
			Element();
			// 空のエレメント作成
			explicit Element(const std::string& name);
			// 開始タグからエレメント作成
			explicit Element(Tag* begin, const std::string& data, int* reading_point);
			~Element();
			// アトリビュート
			int get_attribute_num() const;
			Attribute* get_attribute(int i) const;
			void set_attribute_num(int i);
			void add_attribute_num();
			void del_attribute(int i);
			Attribute* set_attribute(int i);
			// エレメント
			int get_element_num() const;
			Element* get_element(int i) const;
			void set_element_num(int i);
			void add_element_num();
			void del_element(int i);
			Element* set_element(int i);
			// 名前
			const std::string* get_name() const;
			void set_name(const char* name);
			// データをまとめてstringにする
			void convert_data_string(std::string* out) const;
		private:
			std::string mName;
			std::vector<Element*> mChild_element;
			std::vector<Attribute*> mAttribute;
		};

	}
}

#endif
