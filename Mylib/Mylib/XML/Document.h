#ifndef MYLIB_XML_DOCUMENT_H
#define MYLIB_XML_DOCUMENT_H

// �������g����悤�ɂ���
#include"Mylib\XML\Attribute.h"
#include"Mylib\XML\Element.h"

#include<string>

/*
�g�p��:
<Low_fanction_xml>
<Config width="960" height="720" title="XML test">
</Config>
</Low_fanction_xml>

�G���[�������܂Ƃ��ɍs���ĂȂ��̂Ŏg�p����
�t�H�[�}�b�g������Ă�������
*/

// ��@�\XML�֘A
namespace Mylib {
	namespace XML {
		class Element;
		// �h�L�������g�S��
		// XML�͂���ŉ�͂����菑�����񂾂肷��
		class Document {
		public:
			Document();
			explicit Document(const std::string& xml_data);
			~Document();

			// XML���
			// �f�[�^�œn��
			void create(const std::string& xml_data);
			// ���[�g�G�������g���l��
			// ��������ǂ݉���
			const Element* get_root() const;
			// ���[�g�G�������g�̐ݒ�
			void set_root();
			void set_root(Element* root);
			// ��������
			void write(const std::string& filename) const;
		private:
			// XML�S�����܂ރG�������g
			Element* mRoot;
		};

	}
}

#endif