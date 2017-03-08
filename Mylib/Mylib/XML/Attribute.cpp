#include"Mylib\XML\Attribute.h"

#include<sstream>

using namespace std;

namespace Mylib {
	namespace XML {

		Attribute::Attribute() {}

		Attribute::Attribute(const string& name, const string& value) :
			mName{ name },
			mVal{ value }
		{
		}

		Attribute::~Attribute() {}

		// �A�g���r���[�g��
		const string& Attribute::get_name() const {
			return mName;
		}
		// �A�g���r���[�g�̒l
		const string& Attribute::get_val() const {
			return mVal;
		}
		// �A�g���r���[�g�̒l(int)
		int Attribute::get_val_int() const {
			istringstream oss(mVal);
			int r = 0;
			oss >> r;
			return r;
		}
		// ��������ꍇ�̃A�g���r���[�g�̒l
		// out�Ɍ��ʁAnum���v�f���A�Ԃ�l�͎��ۂ̗v�f��
		int Attribute::get_val_int(int* out, int num) const {
			istringstream iss(mVal);
			int count = 0;
			int len = static_cast<int>(mVal.size());
			for (int i = 0; i < num; i++) {
				iss >> out[i];
				if (iss.fail()) {
					break;
				}
				count++;	// �v�f��
				iss.ignore(len, ',');	// ','���o��܂Ŕ�΂�
			}
			return count;
		}
		// �A�g���r���[�g�̒l(float)
		float Attribute::get_val_float() const {
			istringstream oss(mVal);
			float r = 0;
			oss >> r;
			return r;
		}
		// ��������ꍇ�̃A�g���r���[�g�̒l
		// out�Ɍ��ʁAnum���v�f���A�Ԃ�l�͎��ۂ̗v�f��
		int Attribute::get_val_float(float* out, int num) const {
			istringstream iss(mVal);
			int count = 0;
			int len = static_cast<int>(mVal.size());
			for (int i = 0; i < num; i++) {
				iss >> out[i];
				if (iss.fail()) {
					break;
				}
				count++;	// �v�f��
				iss.ignore(len, ',');	// ','���o��܂Ŕ�΂�
			}
			return count;
		}
		// ���O�ƒl���Z�b�g
		void Attribute::set(const string& name, const string& val) {
			mName = name;
			mVal = val;
		}
		// ���O�ƒl���Z�b�g(int)
		void Attribute::set(const string& name, const int val) {
			mName = name;
			ostringstream oss;
			oss << val;
			mVal = oss.str();
		}
		// ���O�ƒl���Z�b�g(float)
		void Attribute::set(const string& name, const float val) {
			mName = name;
			ostringstream oss;
			oss << val;
			mVal = oss.str();
		}
		// ���O�ƒl���Z�b�g(�����v�f)
		void Attribute::set(const string& name, const int* val, const int num) {
			mName = name;
			ostringstream oss;
			if (num > 0) {
				for (int i = 0; i < (num - 1); ++i) {
					oss << val[i] << ", ";	// �R���}�ŋ�؂�
				}
				oss << val[num - 1];
			}
			mVal = oss.str();
		}
		// ���O�ƒl���Z�b�g(�����v�f)
		void Attribute::set(const string& name, const float* val, const int num) {
			mName = name;
			ostringstream oss;
			if (num > 0) {
				for (int i = 0; i < (num - 1); i++) {
					oss << val[i] << ",";
				}
				oss << val[num - 1];
			}
			mVal = oss.str();
		}

	}
}