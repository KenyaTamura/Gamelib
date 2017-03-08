#ifndef MYLIB_XML_ATTRIBUTE_H
#define MYLIB_XML_ATTRIBUTE_H

#include<string>

namespace Mylib {
	namespace XML {
		// 属性、XML最小単位
		// mName = "size"、mVal = "100"、みたいな感じ
		class Attribute {
		public:
			Attribute();
			Attribute(const std::string& name, const std::string& value);
			~Attribute();
			// 値のセット
			void set(const std::string& name, const std::string& value);
			void set(const std::string& name, int value); //int値
			void set(const std::string& name, float value); //float値
			void set(const std::string& name, const int* values, int number); //int配列
			void set(const std::string& name, const float* values, int number); //float配列
																		   // 値取得
			const std::string& get_name() const;
			const std::string& get_val() const;
			// int返し
			int get_val_int() const;
			int get_val_int(int* out, int num) const;
			// float返し
			float get_val_float() const;
			int get_val_float(float* out, int num) const;
		private:
			std::string mName;
			std::string mVal;
		};

	}
}

#endif

