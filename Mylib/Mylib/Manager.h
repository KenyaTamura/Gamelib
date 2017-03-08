#ifndef MYLIB_MANAGER_H
#define MYLIB_MANAGER_H

#include<string>

#include"Input\Manager.h"

namespace Mylib {
	namespace Graphics {
		class Texture;
	}
	namespace Sound {
		class Wave;
	}
	// ほぼ全機能を使えるマネージャークラス
	// テクスチャとXMLは別に行う
	class Manager {
	public:
		Manager();
		~Manager();
		static Manager instance();

		// フレームワークの機能
		// 画面幅取得
		int get_window_width() const;
		// 画面高さ取得
		int get_window_height() const;
		// タイトル取得
		std::string get_title() const;
		// Frameworkに終了命令を出す
		void request_end();
		// Frameworkに終了命令が出ているか調べる
		bool is_end_requested() const;
		// ミリ秒単位で寝る
		void sleep(int milli_seconds) const;
		// フレームレート
		// フレームレート獲得
		int get_framerate() const;
		// フレームレートセット
		void set_framerate(int framerate);

		// 入力デバイス
		// キーボード
		// キーが押されているか
		bool is_key_on(int i) const;
		// キーが押されたか
		bool is_key_triggered(int i) const;
		// マウス
		// マウスのx座標
		int get_x() const;
		// マウスのy座標
		int get_y() const;
		// マウスのx軸方向の速度
		int get_velocity_x() const;
		// マウスのy軸方向の速度
		int get_velocity_y() const;
		// ホイール
		int get_wheel() const;
		// ゲームパッド(PS4)
		// 接続数
		int get_pad_num() const;
		// ボタン数
		int get_button_number(int num = 0) const;
		// ボタンが押されているか
		bool is_button_on(int i, int num = 0) const;
		// ボタンが押されたか
		bool is_button_triggered(int i, int num = 0) const;
		// アナログスティックの数
		int get_analog_number(int num = 0) const;
		// アナログスティック値取得
		int get_analog(int i, int num = 0) const;
		//有効か
		bool is_enabled(int num = 0) const;

		// ファイル入出力
		// ファイル名とデータとデータサイズの組合わせ
		typedef std::tuple<std::string, const char*, int> File;
		// ファイル読みこみ
		void read_file(const std::string& filename);
		// ファイル書き込み
		void write_file(const std::string& filename, const char* data, int size) const;
		// ファイル削除
		void remove_file(const std::string& filename) const;
		// データ獲得
		// stringで獲得
		void get_file_data(const std::string& filename, char* out);
		char* get_file_data(const std::string& filename);
		// 資源開放
		void release_file(const std::string& filename);
		// 読込み確認
		bool is_ready_file(const std::string& filename);

		// グラフィックス
		// 読み込んだ画像を描画
		void draw_image(const Graphics::Texture& texture, int posX, int posY, float rotation = 0.0f, float extendX = 1.0f, float extendY = 1.0f) const;
		// 文字出力
		void draw_string(const char* str, int posX, int posY) const;
		// 文字入力、cin代わり、Enterでtrue
		bool get_string_in(std::string* out, int posX = 0, int posY = 0);
		// 文字のフォーマット替え
		void set_format(float size, unsigned color = 0xffffffff);

		// サウンド
		// 音声ファイル読み込みはWaveを利用
		// 再生
		void play_sound(Sound::Wave& wave);
		// 停止
		void stop_sound(Sound::Wave& wave);
	};
}

#endif
