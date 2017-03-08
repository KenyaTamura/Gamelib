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

		// アトリビュート名
		const string& Attribute::get_name() const {
			return mName;
		}
		// アトリビュートの値
		const string& Attribute::get_val() const {
			return mVal;
		}
		// アトリビュートの値(int)
		int Attribute::get_val_int() const {
			istringstream oss(mVal);
			int r = 0;
			oss >> r;
			return r;
		}
		// 複数ある場合のアトリビュートの値
		// outに結果、numが要素数、返り値は実際の要素数
		int Attribute::get_val_int(int* out, int num) const {
			istringstream iss(mVal);
			int count = 0;
			int len = static_cast<int>(mVal.size());
			for (int i = 0; i < num; i++) {
				iss >> out[i];
				if (iss.fail()) {
					break;
				}
				count++;	// 要素数
				iss.ignore(len, ',');	// ','が出るまで飛ばす
			}
			return count;
		}
		// アトリビュートの値(float)
		float Attribute::get_val_float() const {
			istringstream oss(mVal);
			float r = 0;
			oss >> r;
			return r;
		}
		// 複数ある場合のアトリビュートの値
		// outに結果、numが要素数、返り値は実際の要素数
		int Attribute::get_val_float(float* out, int num) const {
			istringstream iss(mVal);
			int count = 0;
			int len = static_cast<int>(mVal.size());
			for (int i = 0; i < num; i++) {
				iss >> out[i];
				if (iss.fail()) {
					break;
				}
				count++;	// 要素数
				iss.ignore(len, ',');	// ','が出るまで飛ばす
			}
			return count;
		}
		// 名前と値をセット
		void Attribute::set(const string& name, const string& val) {
			mName = name;
			mVal = val;
		}
		// 名前と値をセット(int)
		void Attribute::set(const string& name, const int val) {
			mName = name;
			ostringstream oss;
			oss << val;
			mVal = oss.str();
		}
		// 名前と値をセット(float)
		void Attribute::set(const string& name, const float val) {
			mName = name;
			ostringstream oss;
			oss << val;
			mVal = oss.str();
		}
		// 名前と値をセット(複数要素)
		void Attribute::set(const string& name, const int* val, const int num) {
			mName = name;
			ostringstream oss;
			if (num > 0) {
				for (int i = 0; i < (num - 1); ++i) {
					oss << val[i] << ", ";	// コンマで区切る
				}
				oss << val[num - 1];
			}
			mVal = oss.str();
		}
		// 名前と値をセット(複数要素)
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