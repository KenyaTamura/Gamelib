#ifndef MYLIB_XML_ATTRIBUTE_H
#define MYLIB_XML_ATTRIBUTE_H

#include<string>

namespace Mylib {
	namespace XML {
		// �����AXML�ŏ��P��
		// mName = "size"�AmVal = "100"�A�݂����Ȋ���
		class Attribute {
		public:
			Attribute();
			Attribute(const std::string& name, const std::string& value);
			~Attribute();
			// �l�̃Z�b�g
			void set(const std::string& name, const std::string& value);
			void set(const std::string& name, int value); //int�l
			void set(const std::string& name, float value); //float�l
			void set(const std::string& name, const int* values, int number); //int�z��
			void set(const std::string& name, const float* values, int number); //float�z��
																		   // �l�擾
			const std::string& get_name() const;
			const std::string& get_val() const;
			// int�Ԃ�
			int get_val_int() const;
			int get_val_int(int* out, int num) const;
			// float�Ԃ�
			float get_val_float() const;
			int get_val_float(float* out, int num) const;
		private:
			std::string mName;
			std::string mVal;
		};

	}
}

#endif

