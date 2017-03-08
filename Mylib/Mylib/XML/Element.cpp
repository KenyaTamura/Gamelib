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
			// ���̃^�O��p��
			for (; *p < size; (*p)++) {
				// ���̃^�O
				if (data[*p] == '<') {
					(*p)++;
					// �R���X�g���N�^�Ń^�O�ǂݍ���
					Tag tag(data, p);
					Tag::Type t = tag.get_type();
					// �J�n�^�O
					if (t == Tag::BEGIN) {
						// �ċA�\��
						mChild_element.push_back(new Element(&tag, data, p));
					}
					// �I���^�O
					else if (t == Tag::END) {
						break;	// �^�O���I������炱�̃G�������g�͓ǂݍ��݊���
					}
				}
			}
		}

		Element::~Element() {
			// �����Ń��������
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

		// �A�g���r���[�g�v�f��
		int Element::get_attribute_num() const {
			return static_cast<int>(mAttribute.size());
		}
		// i�Ԗڂ̃A�g���r���[�g�v�f���󂯎��
		Attribute* Element::get_attribute(int i) const {
			return mAttribute[i];
		}
		// �G�������g��
		int Element::get_element_num() const {
			return static_cast<int>(mChild_element.size());
		}
		// i�Ԗڂ̃G�������g���󂯎��
		Element* Element::get_element(int i) const {
			return mChild_element[i];
		}
		// �G�������g��
		const string* Element::get_name() const {
			return &mName;
		}
		// �A�g���r���[�g�̏��������A�|�C���^��n���ď���������
		Attribute* Element::set_attribute(int i) {
			return mAttribute[i];	// �|�C���^��n���ď���������
		}
		// �A�g���r���[�g�v�f���̕ύX�A��x����������
		void Element::set_attribute_num(int n) {
			// ��x���Z�b�g
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
		// �A�g���r���[�g�̒ǉ�
		void Element::add_attribute_num() {
			mAttribute.push_back(new Attribute());
		}
		// i�Ԗڂ̃A�g���r���[�g�̍폜
		void Element::del_attribute(int i) {
			mAttribute.erase(mAttribute.begin() + i);
		}
		// �G�������g�̏��������A�|�C���^��n���ď���������
		Element* Element::set_element(int i) {
			return mChild_element[i];
		}
		// �G�������g�v�f���̕ύX�A��x����������
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
		// �G�������g�̒ǉ�
		void Element::add_element_num() {
			mChild_element.push_back(new Element());
		}
		// i�Ԗڂ̃G�������g�̍폜
		void Element::del_element(int i) {
			mChild_element.erase(mChild_element.begin() + i);
		}
		// �G�������g���̐ݒ�
		void Element::set_name(const char* name) {
			mName = name;
		}
		// �����ݗp�̃f�[�^�ϊ�
		void Element::convert_data_string(string* out) const {
			*out += '<';	// �^�O�J�n
			*out += mName;	// �G�������g��
							// �A�g���r���[�g
			for (unsigned i = 0; i < mAttribute.size(); i++) {
				*out += ' ';	// �X�y�[�X
				*out += mAttribute[i]->get_name();	// �A�g���r���[�g��
				*out += '=';	// �C�R�[��
				*out += '"';	// �_�u���R�[�e�V����
				*out += mAttribute[i]->get_val();	// �A�g���r���[�g�v�f
				*out += '"';	// �I��
			}
			*out += '>';	// �^�O�I��
			*out += '\n';	// �^�O���Ƃɉ��s
							// �q�ɍċA
			for (unsigned i = 0; i < mChild_element.size(); i++) {
				mChild_element[i]->convert_data_string(out);
			}
			// �I���^�O
			*out += '<';
			*out += '/';
			*out += mName;
			*out += '>';
			*out += '\n';
		}

	}
}