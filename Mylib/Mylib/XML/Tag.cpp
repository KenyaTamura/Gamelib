#include"Mylib\XML\Attribute.h"
#include"Mylib\XML\Tag.h"

using namespace std;

/*
��Ԃ̎��
0: ������ԁC'<'�̎�
1: �G�������g��
2: �G�������g���̌�̋󔒁C�A�g���r���[�g�̌�̋�
3: �A�g���r���[�g��
4: �A�g���r���[�g���Ɨv�f�̊ԁC=
5: �A�g���r���[�g�v�f
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
			// �ꎞ�i�[
			string buf_name;
			string buf_val;
			// ���
			int m = 0;
			// ���[�v�E�o
			bool end_flag = false;
			int size = static_cast<int>(data.size());
			for (; *p < size; (*p)++) {
				char c = data[*p];
				switch (m) {
				case 0:	// ����
					if (c == '/') {
						// �I���^�O
						mType = Tag::END;
					}
					else if (is_normal_char(c)) {
						mName += c;
						m = 1;	// 1�֑J��
					}
					break;
				case 1:	// �G�������g��
					if (c == '>') {
						end_flag = true;	// �I��
					}
					else if (is_normal_char(c)) {
						mName += c;
					}
					else {
						m = 2;	// 2�֑J��
					}
					break;
				case 2:	// �G�������g�� or �A�g���r���[�g�I��
					if (c == '>') {
						end_flag = true;	// �I��
					}
					else if (is_normal_char(c)) {
						buf_name += c;	// �A�g���r���[�g��
						m = 3;	// 3�֑J��
					}
					break;
				case 3:	// �A�g���r���[�g��
					if (c == '=') {
						m = 4;	// 4�֑J��
					}
					else if (is_normal_char(c)) {
						buf_name += c;
					}
					break;
				case 4:	// �A�g���r���[�g���I��
					if (c == '"') {
						m = 5;	// 5�֑J��
					}
					break;
				case 5:	// �A�g���r���[�g�v�f
					if (c == '"') {
						m = 2;	// 2�֑J��
						mAttribute.push_back(new Attribute(buf_name.c_str(), buf_val.c_str()));
						//���O�ƒl��������
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
			// Attribute�͓n���Ă���̂ŁC�����ł͏������Ȃ�
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