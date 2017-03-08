#ifndef MYLIB_WINDOW_H
#define MYLIB_WINDOW_H

namespace Mylib {
	// 主にウィンドウ関連を行う
	// 基本的に知らなくていい、外から直接使わない
	class Window {
	public:
		class Configuration {
		public:
			void set_width(int width);
			void set_height(int height);
			void set_title(const char* title);
		};
		Window();
		~Window();
		// 自力で実装する関数
		void configure(Configuration*);

		void start(void* windowHandle);
		void update();

		const char* get_title() const;
		int get_title_length() const;
		int get_width() const;
		int get_height() const;
		// コマンドライン文字列取得
		const char* get_commandline_string() const;
		// timeGetTimeで時刻を返す
		unsigned get_time() const;
		void sleep(int ms) const;
		bool is_active() const;
		bool is_minimized() const;

		static Window instance();
		void request_end(); // 終わりを要求
		void end();			// 終わりを通知
		bool is_end_requested() const; // 終わり要求があるか
		int get_and_reset_mousewheel();	// マウスホイール
	};
}
#endif