#include"Mylib\FileIO\Manager.h"
#include"Mylib\XML\Document.h"
#include"Mylib\XML\Tag.h"
#include<cassert>

using namespace std;

namespace Mylib {
	namespace XML {
		Document::Document() : mRoot(0) {
		}

		Document::Document(const string& xml_data) : mRoot(0) {
			create(xml_data);
		}

		Document::~Document() {
			if (mRoot) {
				delete mRoot;
				mRoot = 0;
			}
		}

		void Document::create(const string& xml_data) {
			// 気休めのエラー検出
			assert(xml_data.find("<Low_fanction_xml>") != -1);
			// 読み込み開始点
			int reading_point = 1;
			// ルートタグ
			// <Low_fanction_xml>とあるはず
			Tag begin_tag(xml_data, &reading_point);
			// ルートエレメント
			mRoot = new Element(&begin_tag, xml_data, &reading_point);
		}

		// ルートエレメントを受け取る
		const Element* XML::Document::get_root() const {
			return mRoot;
		}

		// ルートエレメントのセット
		void XML::Document::set_root() {
			mRoot = new Element("Low_fanction_xml");
		}
		// ルートエレメントのセット
		void XML::Document::set_root(Element* root) {
			mRoot = root;
		}
		
		// XML形式にして書込み
		void Document::write(const string& filename) const {
			if (mRoot) {
				string s;
				mRoot->convert_data_string(&s);
				FileIO::Manager::instance().write(filename, s.c_str(), s.size());
			}
		}

	}
}