#ifndef MYLIB_XML_TAG_H
#define MYLIB_XML_TAG_H

#include<vector>
#include<string>

namespace Mylib {
	namespace XML {
		class Attribute;
		// タグ解析を行う
		class Tag {
		public:
			// 受け取ったタグの種類
			enum Type {
				BEGIN,
				END,
			};
			// 名前だけの空
			explicit Tag(const std::string& name);
			// データを受け取り解釈を行う
			explicit Tag(const std::string& data, int* reading_point);
			~Tag();
			// エレメント名
			const std::string* get_name() const;
			Type get_type() const;
			// アトリビュート
			const std::vector<Attribute*>* get_attribute() const;
		private:
			std::vector<Attribute*> mAttribute;
			std::string mName;
			Type mType;
			bool is_normal_char(char c);
		};
	}
}
#endif