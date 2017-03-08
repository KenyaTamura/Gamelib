#ifndef MYLIB_XML_TAG_H
#define MYLIB_XML_TAG_H

#include<vector>
#include<string>

namespace Mylib {
	namespace XML {
		class Attribute;
		// �^�O��͂��s��
		class Tag {
		public:
			// �󂯎�����^�O�̎��
			enum Type {
				BEGIN,
				END,
			};
			// ���O�����̋�
			explicit Tag(const std::string& name);
			// �f�[�^���󂯎����߂��s��
			explicit Tag(const std::string& data, int* reading_point);
			~Tag();
			// �G�������g��
			const std::string* get_name() const;
			Type get_type() const;
			// �A�g���r���[�g
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