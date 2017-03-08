#ifndef MYLIB_FRAMEWORK_H
#define MYLIB_FRAMEWORK_H

#include<string>

namespace Mylib {
	class Framework {
	public:
		class Configuration {
		public:
			void set_width(int width);
			void set_height(int height);
			void set_title(const char* title);
			void load_file(const char* filename, std::string* out) const;	// 全力で読み込む
		};
		// ユーザ定義関数。これを書く。
		void update();
		void configure(Configuration*);
		// インスタンス取得
		static Framework* instance();
		// 画面幅取得
		int get_width() const;
		// 画面高さ取得
		int get_height() const;
		// タイトル取得
		std::string get_title() const;
		// Frameworkに終了命令を出す
		void request_end();
		// Frameworkに終了命令が出ているか調べる
		bool is_end_requested() const;
		// ミリ秒単位で寝る
		void sleep(int milli_seconds) const;
		// フレームレート
		int get_framerate() const;
		void set_framerate(int framerate);

		// 以下自動で行う部分
		void start(void* hWnd);
		void pre_update();
		void post_update();
		static void create();
		static void destroy();
	private:
		Framework();
		Framework(const Framework&);	// コピーコンストラクタ
		void operator=(const Framework&);	// 代入演算
		~Framework();

		int mWidth;
		int mHeight;
		std::string mTitle;
		unsigned mFramerate;
		unsigned mPrev_frame_interval;
		unsigned mPrev_frametime;
		unsigned mIdeal_frame_interval;
		bool mFirst_loading;
		bool mEnd_requested;
		bool mStarted;

		static Framework* mInstance;
	};
}
#endif
