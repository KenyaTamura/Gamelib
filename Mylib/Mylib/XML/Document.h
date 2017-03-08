#ifndef MYLIB_XML_DOCUMENT_H
#define MYLIB_XML_DOCUMENT_H

// これらも使えるようにする
#include"Mylib\XML\Attribute.h"
#include"Mylib\XML\Element.h"

#include<string>

/*
使用例:
<Low_fanction_xml>
<Config width="960" height="720" title="XML test">
</Config>
</Low_fanction_xml>

エラー処理をまともに行ってないので使用注意
フォーマットを守ってください
*/

// 低機能XML関連
namespace Mylib {
	namespace XML {
		class Element;
		// ドキュメント全体
		// XMLはこれで解析したり書き込んだりする
		class Document {
		public:
			Document();
			explicit Document(const std::string& xml_data);
			~Document();

			// XML解析
			// データで渡す
			void create(const std::string& xml_data);
			// ルートエレメントを獲得
			// ここから読み解く
			const Element* get_root() const;
			// ルートエレメントの設定
			void set_root();
			void set_root(Element* root);
			// 書き込み
			void write(const std::string& filename) const;
		private:
			// XML全部を含むエレメント
			Element* mRoot;
		};

	}
}

#endif