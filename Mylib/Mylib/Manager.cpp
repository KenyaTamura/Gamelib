#include"Mylib\Framework.h"
#include"Mylib\Manager.h"
#include"Mylib\FileIO\Manager.h"
#include"Mylib\Graphics\Manager.h"
#include"Mylib\Input\Manager.h"
#include"Mylib\Input\Mouse.h"
#include"Mylib\Input\Keyboard.h"
#include"Mylib\Input\PS4.h"
#include"Mylib\Sound\Manager.h"

using namespace std;

namespace Mylib {
	Manager::Manager(){}

	Manager::~Manager(){}

	Manager Manager::instance() {
		return Manager();
	}

	// フレームワークの機能
	// 画面幅取得
	int Manager::get_window_width() const {
		return Framework::instance()->get_width();
	}
	// 画面高さ取得
	int Manager::get_window_height() const {
		return Framework::instance()->get_height();
	}
	// タイトル取得
	std::string Manager::get_title() const {
		return Framework::instance()->get_title();
	}
	// Frameworkに終了命令を出す
	void Manager::request_end() {
		Framework::instance()->request_end();
	}
	// Frameworkに終了命令が出ているか調べる
	bool Manager::is_end_requested() const {
		return Framework::instance()->is_end_requested();
	}
	// ミリ秒単位で寝る
	void Manager::sleep(int ms) const {
		Framework::instance()->sleep(ms);
	}
	// フレームレート獲得
	int Manager::get_framerate() const {
		return Framework::instance()->get_framerate();
	}
	// フレームレートセット
	void Manager::set_framerate(int framerate) {
		Framework::instance()->set_framerate(framerate);
	}
	// フレームワーク機能終了

	// 入力デバイス
	// キーボード
	// キーが押されているか
	bool Manager::is_key_on(int i) const {
		return Input::Keyboard().is_on(i);
	}
	// キーが押されたか
	bool Manager::is_key_triggered(int i) const {
		return Input::Keyboard().is_triggered(i);
	}
	// マウス
	// マウスのx座標
	int Manager::get_x() const {
		return Input::Mouse().x();
	}
	// マウスのy座標
	int Manager::get_y() const {
		return Input::Mouse().y();
	}
	// マウスのx軸方向の速度
	int Manager::get_velocity_x() const {
		return Input::Mouse().velocity_x();
	}
	// マウスのy軸方向の速度
	int Manager::get_velocity_y() const {
		return Input::Mouse().velocity_y();
	}
	// ホイール
	int Manager::get_wheel() const {
		return Input::Mouse().wheel();
	}
	// ゲームパッド
	// 接続数
	int Manager::get_pad_num() const{
		return Input::Manager().get_pad_num();
	}
	// ボタン数
	int Manager::get_button_number(int num) const {
		return Input::PS4(num).get_button_number();
	}
	// ボタンが押されているか
	bool Manager::is_button_on(int i, int num) const {
		return Input::PS4(num).is_on(i);
	}
	// ボタンが押されたか
	bool Manager::is_button_triggered(int i, int num) const {
		return Input::PS4(num).is_triggered(i);
	}
	// アナログスティックの数
	int Manager::get_analog_number(int num) const {
		return Input::PS4(num).get_analog_number();
	}
	// アナログスティック値取得
	int Manager::get_analog(int i, int num) const {
		return Input::PS4(num).get_analog(i);
	}
	//有効か
	bool Manager::is_enabled(int num) const {
		return Input::PS4(num).is_enabled();
	}
	// 入力デバイス機能終了

	// ファイル入出力
	// ファイル読みこみ
	void Manager::read_file(const std::string& filename) {
		FileIO::Manager().read(filename);
	}
	// ファイル書き込み
	void Manager::write_file(const std::string& filename, const char* data, int size) const {
		FileIO::Manager().write(filename, data, size);
	}
	// ファイル削除
	void Manager::remove_file(const std::string& filename) const {
		FileIO::Manager().remove(filename);
	}
	// データ獲得、char*で獲得
	void Manager::get_file_data(const std::string& filename, char* out) {
		FileIO::Manager().get_data(filename, out);
	}
	// データ獲得、char*で獲得
	char* Manager::get_file_data(const std::string& filename) {
		return FileIO::Manager().get_data(filename);
	}
	// 資源開放
	void Manager::release_file(const std::string& filename) {
		FileIO::Manager().release_file(filename);
	}
	// 読込み確認
	bool Manager::is_ready_file(const std::string& filename) {
		return FileIO::Manager().is_ready_file(filename);
	}
	// ファイル入出力機能終了

	// グラフィックス
	// 読み込んだ画像を描画
	void Manager::draw_image(const Graphics::Texture& texture, int posX, int posY, float rotation, float extendX, float extendY) const {
		Graphics::Manager().draw_image(texture, posX, posY, rotation, extendX, extendY);
	}
	// 文字出力
	void Manager::draw_string(const char* str, int posX, int posY) const {
		Graphics::Manager().draw_string(str, posX, posY);
	}
	// 文字入力、cin代わり、Enterでtrue
	bool Manager::get_string_in(std::string* out, int posX, int posY) {
		return Graphics::Manager().get_string(out, posX, posY);
	}
	// 文字のフォーマット替え
	void Manager::set_format(float size, unsigned color) {
		Graphics::Manager().set_format(size, color);
	}
	// グラフィックス機能終了

	// サウンド機能
	// 読み込んだ音声ファイルを再生
	void Manager::play_sound(Sound::Wave& wave) {
		Sound::Manager().play(wave);
	}
	// 再生中の音声ファイルの停止
	void Manager::stop_sound(Sound::Wave& wave) {
		Sound::Manager().stop(wave);
	}
	// サウンド機能終了
}