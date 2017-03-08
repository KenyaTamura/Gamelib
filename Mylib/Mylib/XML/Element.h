#ifndef MYLIB_XML_ELEMENT_H
#define MYLIB_XML_ELEMENT_H

#include<vector>
#include<string>

namespace Mylib {
	namespace XML {
		class Attribute;
		class Tag;
		// �v�f�A�A�g���r���[�g�������Ă���
		// ����q�\���ŗv�f�����Ă�
		class Element {
		public:
			Element();
			// ��̃G�������g�쐬
			explicit Element(const std::string& name);
			// �J�n�^�O����G�������g�쐬
			explicit Element(Tag* begin, const std::string& data, int* reading_point);
			~Element();
			// �A�g���r���[�g
			int get_attribute_num() const;
			Attribute* get_attribute(int i) const;
			void set_attribute_num(int i);
			void add_attribute_num();
			void del_attribute(int i);
			Attribute* set_attribute(int i);
			// �G�������g
			int get_element_num() const;
			Element* get_element(int i) const;
			void set_element_num(int i);
			void add_element_num();
			void del_element(int i);
			Element* set_element(int i);
			// ���O
			const std::string* get_name() const;
			void set_name(const char* name);
			// �f�[�^���܂Ƃ߂�string�ɂ���
			void convert_data_string(std::string* out) const;
		private:
			std::string mName;
			std::vector<Element*> mChild_element;
			std::vector<Attribute*> mAttribute;
		};

	}
}

#endif
