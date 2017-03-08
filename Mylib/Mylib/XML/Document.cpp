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
			// �C�x�߂̃G���[���o
			assert(xml_data.find("<Low_fanction_xml>") != -1);
			// �ǂݍ��݊J�n�_
			int reading_point = 1;
			// ���[�g�^�O
			// <Low_fanction_xml>�Ƃ���͂�
			Tag begin_tag(xml_data, &reading_point);
			// ���[�g�G�������g
			mRoot = new Element(&begin_tag, xml_data, &reading_point);
		}

		// ���[�g�G�������g���󂯎��
		const Element* XML::Document::get_root() const {
			return mRoot;
		}

		// ���[�g�G�������g�̃Z�b�g
		void XML::Document::set_root() {
			mRoot = new Element("Low_fanction_xml");
		}
		// ���[�g�G�������g�̃Z�b�g
		void XML::Document::set_root(Element* root) {
			mRoot = root;
		}
		
		// XML�`���ɂ��ď�����
		void Document::write(const string& filename) const {
			if (mRoot) {
				string s;
				mRoot->convert_data_string(&s);
				FileIO::Manager::instance().write(filename, s.c_str(), s.size());
			}
		}

	}
}